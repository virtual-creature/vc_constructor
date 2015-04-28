/*
 * GeometryObjectFactory.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "GeometryObjectFactory.h"

#include "GeometryDummy.h"
#include "GeometryPoint.h"
#include "GeometryLink.h"
#include "GeometrySpring.h"
#include "GraphicPoint.h"
#include "GraphicLink.h"
#include "GraphicSpring.h"

GeometryObjectFactory::GeometryObjectFactory()
{

}

GeometryObjectFactory::~GeometryObjectFactory()
{
}

void GeometryObjectFactory::deleteGeometryObject( IGeometryObject * bufferObject )
{
	m_bufferObjectAllocator.deallocObjectBuffer( bufferObject );
}

IGeometryObject * GeometryObjectFactory::createGeometryObject( GeometryObjectsTypes type )
{
	IGeometryObject * object = 0;
	void * objectBuffer = m_bufferObjectAllocator.allocObjectBuffer();
	switch( type )
	{
		case GEOMETRYOBJECT_POINT:
				object = new(objectBuffer) GeometryPoint();
			break;
		case GEOMETRYOBJECT_LINK:
				object = new(objectBuffer) GeometryLink();
			break;
		case GEOMETRYOBJECT_SPRING:
				object = new(objectBuffer) GeometrySpring();
			break;
		default:
			break;
	}
	return object;
}

GeometryObjectFactory & GeometryObjectFactory::getInstance()
{
	static GeometryObjectFactory instance;
	return instance;
}














