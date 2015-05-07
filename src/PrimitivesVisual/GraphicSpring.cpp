/*
 * GraphicSpring.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#include "GraphicSpring.h"
#include "GeometrySpringGetCrosslinkPredicate.h"
#include "GeometrySpringGetShortestLinkPredicate.h"
#include "GeometryLinkGetAbsoluteAnglePredicate.h"
#include "GetAnglesRangeBy3PointsPredicate.h"
#include "GetAnglesRangeBy2PointsPredicate.h"
#include "GeometrySpringGetAngles.h"
#include "MouseCoordinatesHolder.h"
#include "GetCoordsOnPhypotenuzeByWidth.h"
#include <iostream>
using namespace std;

GraphicSpring::GraphicSpring( IGeometryObject * geometryObject, Evas_Object * canvas ) : GraphicObjectBase( canvas ), m_springRotateAngle( 0 )
{
	m_geometrySpring = (GeometrySpring *)geometryObject;

	initShaders();

	m_Color[0] = ( (float)( rand() % 255 ) ) / 255.0f;
	m_Color[1] = ( (float)( rand() % 255 ) ) / 255.0f;
	m_Color[2] = ( (float)( rand() % 255 ) ) / 255.0f;

	m_ColorUniformIdx = m_glApi->glGetUniformLocation( m_Program, "color" );

}

GraphicSpring::GraphicSpring( const GraphicSpring & src )
{
	m_geometrySpring = src.m_geometrySpring;
	m_springRotateAngle = src.m_springRotateAngle;

	initShaders();

	m_ColorUniformIdx = m_glApi->glGetUniformLocation( m_Program, "color" );
}

GraphicSpring::~GraphicSpring()
{
}

void GraphicSpring::draw()
{
//	if( true == m_geometrySpring->getIsRigid() )
//	{
//        return;
//  }
	initCircleVertexes();
	draw_line_2d();
}

IGeometryObject & GraphicSpring::getGeometryObject()
{
	return *m_geometrySpring;
}

void GraphicSpring::initLineVertexes()
{
	vector<GLfloat> objectVertexes;

	int from_x = ( m_geometrySpring->getLinkFrom()->getPointFrom()->getX() + m_geometrySpring->getLinkFrom()->getPointTo()->getX() ) / 2;
	int from_y = ( m_geometrySpring->getLinkFrom()->getPointFrom()->getY() + m_geometrySpring->getLinkFrom()->getPointTo()->getY() ) / 2;

	int to_x = ( m_geometrySpring->getLinkTo()->getPointFrom()->getX() + m_geometrySpring->getLinkTo()->getPointTo()->getX() ) / 2;
	int to_y = ( m_geometrySpring->getLinkTo()->getPointFrom()->getY() + m_geometrySpring->getLinkTo()->getPointTo()->getY() ) / 2;

	objectVertexes.push_back( pixels_to_coords_x( from_x ) );
	objectVertexes.push_back( pixels_to_coords_y( from_y ) );

	objectVertexes.push_back( pixels_to_coords_x( to_x ) );
	objectVertexes.push_back( pixels_to_coords_y( to_y ) );

	m_vertexBuffer.push_back( objectVertexes );
}

void GraphicSpring::initCircleAtLinks( int x0, int y0, int radius )
{
	vector<GLfloat> objectVertexes;
	const int vertexNumber = 49;

	float ang = 0;
	float da = (float) (M_PI / 180 * (360.0f / vertexNumber));

	{//Circle Points
		float first_coord_x = 0 + 1.0 * cos( ang );
		float first_coord_y = 0 + 1.0 * sin( ang );
		float last_coord_x = first_coord_x;
		float last_coord_y = first_coord_y;
		objectVertexes.push_back( pixels_to_coords_x( x0 ) );
		objectVertexes.push_back( pixels_to_coords_y( y0 ) );
		objectVertexes.push_back( 0.0 );
		objectVertexes.push_back( 0.0 );
		for(double v_i = 0; v_i < vertexNumber; v_i ++ )
		{
			float fsin = sin( ang );
			float fcos = cos( ang );
			float coordX = 0 + 1.0 * fcos;
			float coordY = 0 + 1.0 * fsin;



//			objectVertexes.push_back( last_coord_x );
//			objectVertexes.push_back( last_coord_y );
			objectVertexes.push_back( coordX );
			objectVertexes.push_back( coordY );

			last_coord_x = coordX;
			last_coord_y = coordY;

			ang += da;
		}
//		objectVertexes.push_back( 0.0 );
//		objectVertexes.push_back( 0.0 );
//		objectVertexes.push_back( last_coord_x );
//		objectVertexes.push_back( last_coord_y );
		objectVertexes.push_back( first_coord_x );
		objectVertexes.push_back( first_coord_y );
	}
	m_vertexBuffer.push_back( objectVertexes );
}

void GraphicSpring::initPartialCircleVertex()
{
	const GeometrySpring * geometrySpring = (GeometrySpring *)&( getGeometryObject() );

	GeometrySpringGetAngles getAngles( geometrySpring );
	int linkFromAngle = getAngles.getLinkFromAngle();
	int linkToAngle = getAngles.getLinkToAngle();

	if( linkFromAngle == linkToAngle )
	{
		return;
	}

	GeometrySpringGetCrosslinkPredicate getCrosslinkPoint( geometrySpring );
	const GeometryPoint * crosslinkPoint = getCrosslinkPoint();
	int X0 = crosslinkPoint->getX();
	int Y0 = crosslinkPoint->getY();

	GeometrySpringGetShortestLinkPredicate getShortesLink( geometrySpring );
	const GeometryLink * shorteslink = getShortesLink();
	int outerRadius = shorteslink->getWidth() / 2;

	int mouseX = MouseCoordinatesHolder::getInstance().getX();
	int mouseY = MouseCoordinatesHolder::getInstance().getY();

	GeometryLinkGetAbsoluteAnglePredicate getCurrentPointAbsoluteAngle( X0, Y0, mouseX, mouseY );
	int currentMouseAngle = getCurrentPointAbsoluteAngle();

	GetAnglesRangeBy3PointsPredicate isMouseAngleBetween( linkFromAngle, linkToAngle, geometrySpring->getIsClosedPath(), currentMouseAngle );

	int minAngle = isMouseAngleBetween.getMinAngle();//min( currentMouseAngle, linkFromAngle );
	int maxAngle = isMouseAngleBetween.getMaxAngle();//max( currentMouseAngle, linkFromAngle );

//	cout << "minAngle=" << minAngle << "; maxAngle=" << maxAngle << endl << flush;
	float radian = ( (float)minAngle / 180.0 ) * M_PI;
	const int segmentMinAngle = 20;
	float segmentsCount = (float)( abs( maxAngle - minAngle ) ) / (float)segmentMinAngle;
	float deltaAngle = (float)( maxAngle - minAngle ) / (float)segmentsCount;
	for( int angle_i = minAngle ; angle_i < maxAngle ; angle_i += deltaAngle )
	{
		radian = ( (float)angle_i / 180.0 ) * M_PI;
		int coordX = X0 + outerRadius * cos( radian );
		int coordY = Y0 - outerRadius * sin( radian );

		initCircleAtLinks( coordX, coordY, 8 );
	}
}

void GraphicSpring::initCompleteCircleVertex()
{
	const GeometrySpring * geometrySpring = (GeometrySpring *)&( getGeometryObject() );
	GeometrySpringGetAngles getAngles( geometrySpring );
	int linkFromAngle = getAngles.getLinkFromAngle();
	int linkToAngle = getAngles.getLinkToAngle();

	if( linkFromAngle == linkToAngle )
	{
		return;
	}

	GeometrySpringGetCrosslinkPredicate getCrosslinkPoint( geometrySpring );
	const GeometryPoint * crosslinkPoint = getCrosslinkPoint();
	int X0 = crosslinkPoint->getX();
	int Y0 = crosslinkPoint->getY();

	GeometrySpringGetShortestLinkPredicate getShortesLink( geometrySpring );
	const GeometryLink * shorteslink = getShortesLink();
	int outerRadius = shorteslink->getWidth() / 2;

	GetAnglesRangeBy2PointsPredicate getRange( linkFromAngle, linkToAngle, geometrySpring->getIsClosedPath() );

	int minAngle = getRange.getMinAngle();
	int maxAngle = getRange.getMaxAngle();

//	cout << "minAngle=" << minAngle << "; maxAngle=" << maxAngle << endl << flush;
	cout << "diffAngles=" << abs( maxAngle - minAngle ) << endl << flush;
	float radian = ( (float)minAngle / 180.0 ) * M_PI;
	const int segmentMinAngle = 20;
	float segmentsCount = (float)( abs( maxAngle - minAngle ) ) / (float)segmentMinAngle;
	float deltaAngle = (float)( maxAngle - minAngle ) / (float)segmentsCount;

	for( int angle_i = minAngle ; angle_i < maxAngle ; angle_i += deltaAngle )
	{
		radian = ( (float)angle_i / 180.0 ) * M_PI;
		int coordX = X0 + outerRadius * cos( radian );
		int coordY = Y0 - outerRadius * sin( radian );

		initCircleAtLinks( coordX, coordY, 8 );
	}
}

void GraphicSpring::initCircleVertexes()
{
	const GeometrySpring * geometrySpring = (GeometrySpring *)&( getGeometryObject() );
	GeometryLinkGetAbsoluteAnglePredicate getLinkFromAbsoluteAngle( geometrySpring->getLinkFrom() );
	GeometryLinkGetAbsoluteAnglePredicate getLinkToAbsoluteAngle( geometrySpring->getLinkTo() );
	int linkFromAngle     = getLinkFromAbsoluteAngle();
	int linkToAngle     = getLinkToAbsoluteAngle();

	if( linkFromAngle == linkToAngle )
	{
		return;
	}

	GeometrySpringGetCrosslinkPredicate getCrosslinkPoint( geometrySpring );

	const int innerRadius = 13;
	if( geometrySpring->getConstructingState() == GEOMETRYOBJECTCONSTRUCTING_INPROGRESS )
	{
		GeometrySpringGetAngles getAngles( geometrySpring );
		const GeometryPoint * crossPoint = getAngles.getCrospoint();
		const GeometryPoint * linkFromAdjustmentPoint = getAngles.getLinkFromAdjacentPoint();
		const GeometryPoint * linkToAdjustmentPoint = getAngles.getLinkToAdjacentPoint();

		GeometrySpringGetShortestLinkPredicate getShortestLink( geometrySpring );
		int shortHalfWidth = getShortestLink()->getWidth() / 2;

		{
			GetCoordsOnPhypotenuzeByWidth getWidthCoords( crossPoint, linkFromAdjustmentPoint, shortHalfWidth );

			int widthX = getWidthCoords.getX();
			int widthY = getWidthCoords.getY();

			initCircleAtLinks( widthX, widthY, innerRadius );
		}

		initPartialCircleVertex();

		{
			GetCoordsOnPhypotenuzeByWidth getWidthCoords( crossPoint, linkToAdjustmentPoint, shortHalfWidth );
			int widthX = getWidthCoords.getX();
			int widthY = getWidthCoords.getY();

			initCircleAtLinks( widthX, widthY, innerRadius );
		}
	}
	else
	{
		GeometrySpringGetAngles getAngles( geometrySpring );
		const GeometryPoint * crossPoint = getAngles.getCrospoint();
		const GeometryPoint * linkFromAdjustmentPoint = getAngles.getLinkFromAdjacentPoint();
		const GeometryPoint * linkToAdjustmentPoint = getAngles.getLinkToAdjacentPoint();

		GeometrySpringGetShortestLinkPredicate getShortestLink( geometrySpring );
		int shortHalfWidth = getShortestLink()->getWidth() / 2;

		{
			GetCoordsOnPhypotenuzeByWidth getWidthCoords( crossPoint, linkFromAdjustmentPoint, shortHalfWidth );

			int widthX = getWidthCoords.getX();
			int widthY = getWidthCoords.getY();

			initCircleAtLinks( widthX, widthY, innerRadius );
		}

		initCompleteCircleVertex();

		GetCoordsOnPhypotenuzeByWidth getWidthCoords( crossPoint, linkToAdjustmentPoint, shortHalfWidth );
		int widthX = getWidthCoords.getX();
		int widthY = getWidthCoords.getY();

		initCircleAtLinks( widthX, widthY, innerRadius );
	}
}
#include <fstream>
#include <cassert>
void dump( vector<float> & arr )
{
	ofstream file( "./dump.txt" );
	if( false == file.is_open() )
	{
		assert( false );
	}

	file << arr.size() << endl << endl << flush;

	vector<float>::iterator begin = arr.begin();
	vector<float>::iterator end = arr.end();
	vector<float>::iterator iter = begin;
	for(  ; iter != end ; iter++ )
	{
		file << (* iter) << endl << flush;
	}
}

void GraphicSpring::draw_line_2d()
{
	Evas_GL_API * __evas_gl_glapi = m_glApi;

	float dimension = m_DrawCanvasWidth / (float)m_DrawCanvasHeight;

	GLfloat translateMatrix[16];
	GLfloat scaleMatrix[16];
	GLfloat rotateMatrix[16];

	GLfloat perspective[16];
	init_matrix( perspective );
	init_matrix( translateMatrix );
	init_matrix( scaleMatrix );
	init_matrix( rotateMatrix );

	scale_xyz( scaleMatrix, 0.025 / dimension, 0.025, 1.0 );

	int from_x = ( m_geometrySpring->getLinkFrom()->getPointFrom()->getX() + m_geometrySpring->getLinkFrom()->getPointTo()->getX() ) / 2;
	int from_y = ( m_geometrySpring->getLinkFrom()->getPointFrom()->getY() + m_geometrySpring->getLinkFrom()->getPointTo()->getY() ) / 2;

	translate_xyz( translateMatrix, pixels_to_coords_x( from_x ), pixels_to_coords_y( from_y ), 0.0f );

	const int coordinates_in_point = 2;

	__evas_gl_glapi->glUseProgram( m_Program );

	__evas_gl_glapi->glEnableVertexAttribArray( m_positionIdx );

	const int matrixCount = 1;

	__evas_gl_glapi->glUniformMatrix4fv( m_perspective_idx, matrixCount, GL_FALSE, perspective );
	__evas_gl_glapi->glUniformMatrix4fv( m_scale_idx, matrixCount, GL_FALSE, scaleMatrix );
	__evas_gl_glapi->glUniformMatrix4fv( m_rotate_idx, matrixCount, GL_FALSE, rotateMatrix );
	__evas_gl_glapi->glUniform3f( m_ColorUniformIdx, m_Color[0], m_Color[1], m_Color[2] );

	__evas_gl_glapi->glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	__evas_gl_glapi->glEnable( GL_BLEND );

	size_t objectCount = m_vertexBuffer.size();
	for( size_t object_i = 0 ; object_i < objectCount ; object_i++ )
	{
		vector<GLfloat> & objectVertexes = m_vertexBuffer[object_i];
		size_t vertixesCount = objectVertexes.size() / coordinates_in_point;

		init_matrix( translateMatrix );
		GLfloat x0 = objectVertexes[0];
		GLfloat y0 = objectVertexes[1];
		translate_xyz( translateMatrix, x0, y0, 0.0f );
		__evas_gl_glapi->glUniformMatrix4fv( m_translate_idx, matrixCount, GL_FALSE, translateMatrix );

		__evas_gl_glapi->glVertexAttribPointer( m_positionIdx, coordinates_in_point, GL_FLOAT, GL_FALSE, coordinates_in_point * sizeof(GLfloat), &objectVertexes[2] );

		__evas_gl_glapi->glDrawArrays( GL_TRIANGLE_FAN, 0, vertixesCount );
	}
	__evas_gl_glapi->glDisable( GL_BLEND );

	__evas_gl_glapi->glDisableVertexAttribArray( m_positionIdx );

	m_vertexBuffer.clear();

	__evas_gl_glapi->glUseProgram( 0 );
}

string GraphicSpring::getVertexShader()
{
	string shader = SHADER(
\n
\n		attribute vec2 vPosition;
\n		uniform mat4 perspective;
\n		uniform mat4 translate;
\n		uniform mat4 scale;
\n		varying vec2 fragPos;
\n		varying vec2 centerPos;
\n		void main()
\n		{
\n			gl_Position = perspective * translate * scale * vec4( vPosition.xy, 0.0, 1.0 );
\n			fragPos = vPosition.xy;
\n			centerPos = vec2( translate[0][3], translate[1][3] );
\n		}
\n
						);

	return shader;
}

string GraphicSpring::getFragmentShader()
{
	string shader =	SHADER(
\n
\n		uniform vec3 color;
\n		varying vec2 fragPos;
\n		varying vec2 centerPos;
\n		void main()
\n		{
\n			float length = length( fragPos );
\n			gl_FragColor = vec4( color.xyz, 1.0 - length );
\n		}
\n
						);

	return shader;
}












