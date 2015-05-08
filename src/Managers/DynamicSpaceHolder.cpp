/*
 * DynamicSpaceHolder.cpp
 *
 *  Created on: 8 мая 2015
 *      Author: vadim
 */

#include "DynamicSpaceHolder.h"
#include "DynamicTimeLineManager.h"

#define GRABBABLE_MASK_BIT (1<<31)
static cpShapeFilter GRAB_FILTER = {CP_NO_GROUP, GRABBABLE_MASK_BIT, GRABBABLE_MASK_BIT};
static cpShapeFilter NOT_GRABBABLE_FILTER = {CP_NO_GROUP, ~GRABBABLE_MASK_BIT, ~GRABBABLE_MASK_BIT};

DynamicSpaceHolder::DynamicSpaceHolder() : m_Space( 0 ), m_LeftBorder( 0 ), m_RightBorder( 0 ),
m_TopBorder( 0 ), m_BottomBorder( 0 ), m_CanvasWidth( 0 ), m_CanvasHeight( 0 ), m_Inited( false )
{
}

DynamicSpaceHolder::~DynamicSpaceHolder()
{
	cpShapeFree( m_LeftBorder );
	cpShapeFree( m_RightBorder );
	cpShapeFree( m_TopBorder );
	cpShapeFree( m_BottomBorder );
	cpSpaceFree( m_Space );
}

cpSpace * DynamicSpaceHolder::getSpace() const
{
	return m_Space;
}

void DynamicSpaceHolder::init()
{
	if( true == m_Inited )
	{
		return;
	}
	initSpace();
	initCanvasBorders();

	m_Inited = true;
}

void DynamicSpaceHolder::initCanvasBorders()
{
	cpBody * staticBody = cpSpaceGetStaticBody( m_Space );
	m_LeftBorder = cpSpaceAddShape( m_Space, cpSegmentShapeNew( staticBody, cpv( 0, 60 ), 			cpv( 0, m_CanvasHeight + 60 ), 0.0f ) );
	cpShapeSetElasticity( m_LeftBorder, 1.0f );
	cpShapeSetFriction( m_LeftBorder, 1.0f );
	cpShapeSetFilter( m_LeftBorder, NOT_GRABBABLE_FILTER );

	m_RightBorder = cpSpaceAddShape( m_Space, cpSegmentShapeNew( staticBody, cpv( m_CanvasWidth, 60 ), cpv( m_CanvasWidth, m_CanvasHeight + 60 ), 0.0f ) );
	cpShapeSetElasticity( m_RightBorder, 1.0f );
	cpShapeSetFriction( m_RightBorder, 1.0f );
	cpShapeSetFilter( m_RightBorder, NOT_GRABBABLE_FILTER );

	m_TopBorder = cpSpaceAddShape( m_Space, cpSegmentShapeNew( staticBody, cpv( 0, 60 ), 			cpv( m_CanvasWidth, 60 ), 0.0f ) );
	cpShapeSetElasticity( m_TopBorder, 1.0f );
	cpShapeSetFriction( m_TopBorder, 1.0f );
	cpShapeSetFilter( m_TopBorder, NOT_GRABBABLE_FILTER );

	m_BottomBorder = cpSpaceAddShape( m_Space, cpSegmentShapeNew( staticBody, cpv( 0, m_CanvasHeight + 60 ), cpv( m_CanvasWidth, m_CanvasHeight + 60 ), 0.0f ) );
	cpShapeSetElasticity( m_BottomBorder, 1.0f );
	cpShapeSetFriction( m_BottomBorder, 100.0f );
	cpShapeSetFilter( m_BottomBorder, NOT_GRABBABLE_FILTER );
}

void DynamicSpaceHolder::initSpace()
{
	// cpVect is a 2D vector and cpv() is a shortcut for initializing them.
	m_Gravity = cpv( 0, 0 );
	// Create an empty space.
	m_Space = cpSpaceNew();
	cpSpaceSetGravity( m_Space, m_Gravity );

	DynamicTimeLineManager::getInstance().setSpace( m_Space );
}

void DynamicSpaceHolder::setCanvasWidth( unsigned int width )
{
	m_CanvasWidth = width;
}

void DynamicSpaceHolder::setCanvasHeight( unsigned int height )
{
	m_CanvasHeight = height;
}

unsigned int DynamicSpaceHolder::getCanvasWidth() const
{
	return m_CanvasWidth;
}

unsigned int DynamicSpaceHolder::getCanvasHeight() const
{
	return m_CanvasHeight;
}

DynamicSpaceHolder & DynamicSpaceHolder::getInstance()
{
	static DynamicSpaceHolder instance;
	return instance;
}











