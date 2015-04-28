/*
 * GraphicObjectFactory.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "GraphicObjectFactory.h"
#include "GeometryObjectsTypes.h"
#include "GeometryDummy.h"
#include "GeometryPoint.h"
#include "GeometryLink.h"
#include "GeometrySpring.h"
#include "GraphicPoint.h"
#include "GraphicLink.h"
#include "GraphicSpring.h"

#include "GeometryDummy.h"
#include "GeometryPointDynamic.h"
#include "GeometryLinkDynamic.h"
#include "GeometrySpringDynamic.h"
#include "GraphicPointDynamic.h"
#include "GraphicLinkDynamic.h"
#include "GraphicSpringDynamic.h"

GraphicObjectFactory::GraphicObjectFactory()
{

}

GraphicObjectFactory::~GraphicObjectFactory()
{
}

IGraphicObject * GraphicObjectFactory::createGraphicObject( IGeometryObject * geometryObject, Evas_Object * canvas )
{
	IGraphicObject * object = 0;
	switch( geometryObject->getType() )
	{
		case GEOMETRYOBJECT_POINT:
				object = new GraphicPoint( geometryObject, canvas );
			break;
		case GEOMETRYOBJECT_LINK:
				object = new GraphicLink( geometryObject, canvas );
			break;
		case GEOMETRYOBJECT_SPRING:
				object = new GraphicSpring( geometryObject, canvas );
			break;
		default:
			break;
	}
	return object;
}

IGraphicObject * GraphicObjectFactory::createGraphicObject( IDynamicObject * dynamicObject, Evas_Object * canvas )
{
	IGraphicObject * object = 0;
	switch( dynamicObject->getGeometryObject().getType() )
	{
		case GEOMETRYOBJECT_POINT:
				object = new GraphicPointDynamic( (GeometryPointDynamic *)dynamicObject, canvas );
			break;
		case GEOMETRYOBJECT_LINK:
				object = new GraphicLinkDynamic( (GeometryLinkDynamic *)dynamicObject, canvas );
			break;
		case GEOMETRYOBJECT_SPRING:
				object = new GraphicSpringDynamic( (GeometrySpringDynamic *)dynamicObject, canvas );
			break;
		default:
			break;
	}
	return object;
}

GraphicObjectFactory & GraphicObjectFactory::getInstance()
{
	static GraphicObjectFactory instance;
	return instance;
}














