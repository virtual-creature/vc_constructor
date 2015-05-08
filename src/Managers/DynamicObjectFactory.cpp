/*
 * DynamicObjectFactory.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#include "DynamicObjectFactory.h"
#include "GeometryPointDynamic.h"
#include "GeometryLinkDynamic.h"
#include "GeometrySpringDynamic.h"
#include "GraphicPointDynamic.h"
#include "GraphicLinkDynamic.h"
#include "GraphicSpringDynamic.h"
#include "DynamicSpaceHolder.h"

DynamicObjectFactory::DynamicObjectFactory()
{
}

DynamicObjectFactory::~DynamicObjectFactory()
{
}

IDynamicObject * DynamicObjectFactory::createDynamicObject( IGeometryObject * geometryObject )
{
	cpSpace * space = DynamicSpaceHolder::getInstance().getSpace();
	IDynamicObject * object = 0;
	switch( geometryObject->getType() )
	{
		case GEOMETRYOBJECT_POINT:
				object = new GeometryPointDynamic( space, (GeometryPoint *)geometryObject );
			break;
		case GEOMETRYOBJECT_LINK:
				object = new GeometryLinkDynamic( space, (GeometryLink *)geometryObject );
			break;
		case GEOMETRYOBJECT_SPRING:
				object = new GeometrySpringDynamic( space, (GeometrySpring *)geometryObject );
			break;
		default:
			break;
	}
	return object;
}

DynamicObjectFactory & DynamicObjectFactory::getInstance()
{
	static DynamicObjectFactory instance;
	return instance;
}
















