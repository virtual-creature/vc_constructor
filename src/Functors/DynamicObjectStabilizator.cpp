/*
 * DynamicObjectStabilizator.cpp
 *
 *  Created on: 7 мая 2015
 *      Author: vadim
 */

#include "DynamicObjectStabilizator.h"
#include "GeometryPoint.h"
#include "DynamicTimeLineManager.h"
#include <cassert>

#define GRABBABLE_MASK_BIT (1<<31)
static cpShapeFilter GRAB_FILTER = {CP_NO_GROUP, GRABBABLE_MASK_BIT, GRABBABLE_MASK_BIT};

DynamicObjectStabilizator::DynamicObjectStabilizator( cpSpace * space, vector<IDynamicObject *> & geometryObjects ) :
	m_Space( space ), m_DynamicObjects( geometryObjects )
{
}

DynamicObjectStabilizator::~DynamicObjectStabilizator()
{
}

void DynamicObjectStabilizator::stabilize()
{
	if( m_DynamicObjects.size() < 2 )
	{
		return;
	}
	fixatePoints();
	runTimeLine();
	clearResources();
}

void DynamicObjectStabilizator::fixatePoints()
{
//	vector<IDynamicObject *>::iterator begin = m_DynamicObjects.begin();
//	vector<IDynamicObject *>::iterator end = m_DynamicObjects.end();
//	vector<IDynamicObject *>::iterator iter = begin + 1;
//	for(  ; iter != end ; iter++ )
	size_t count = m_DynamicObjects.size();
	for( size_t object_i = 0 ; object_i < 2 ; object_i++ )
	{
		const IGeometryObject & geometryObjext = m_DynamicObjects[object_i]->getGeometryObject();
		if( geometryObjext.getType() != GEOMETRYOBJECT_POINT )
		{
//			assert( false );
			continue;
		}
		cpBody * kineticBody = cpBodyNewKinematic();
		cpSpaceAddBody( m_Space, kineticBody );
		m_KineticBodies.push_back( kineticBody );

		const GeometryPoint & geometryPoint = dynamic_cast<const GeometryPoint &>( geometryObjext );

		int x = geometryPoint.getX();
		int y = geometryPoint.getY();
		cpVect mousePoint = cpv( x, y );
		cpShape * shape = cpSpacePointQueryNearest( m_Space, mousePoint, 100.0, GRAB_FILTER, 0 );

		if( 0 == shape )
		{
			return;
		}

		cpVect new_mouse_position = cpv( x, y );
		cpBodySetPosition( kineticBody, new_mouse_position );

		cpBody * trackingBody = cpShapeGetBody( shape );


		cpConstraint * joint = cpPivotJointNew2( kineticBody, trackingBody, cpvzero, cpvzero );
		cpSpaceAddConstraint( m_Space, joint );

		m_Joints.push_back( joint );

		break; //one pointb
	}
}

void DynamicObjectStabilizator::runTimeLine()
{
	const unsigned int count = 100;
	for( unsigned int time_i = 0 ; time_i < count ; time_i++ )
	{
		DynamicTimeLineManager::getInstance().stepSpace();
	}
}

void DynamicObjectStabilizator::clearResources()
{
	{
		vector<cpBody *>::iterator begin = m_KineticBodies.begin();
		vector<cpBody *>::iterator end = m_KineticBodies.end();
		vector<cpBody *>::iterator iter = begin;
		for(  ; iter != end ; iter++ )
		{
			cpBody * kineticBody = (* iter );
			cpSpaceRemoveBody( m_Space, kineticBody );
		}
	}
	{
		vector<cpConstraint *>::iterator begin = m_Joints.begin();
		vector<cpConstraint *>::iterator end = m_Joints.end();
		vector<cpConstraint *>::iterator iter = begin;
		for(  ; iter != end ; iter++ )
		{
			cpConstraint * joint = (* iter );
			cpSpaceRemoveConstraint( m_Space, joint );
		}
	}
}











