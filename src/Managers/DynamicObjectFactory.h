/*
 * DynamicObjectFactory.h
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#ifndef DYNAMICOBJECTFACTORY_H_
#define DYNAMICOBJECTFACTORY_H_

#include "IGeometryObject.h"
#include "IDynamicObject.h"
#include "IGraphicObject.h"
#include "GeometryObjectsTypes.h"
#include "GeometryPointDynamic.h"

class DynamicObjectFactory
{
public:
	DynamicObjectFactory();
	virtual ~DynamicObjectFactory();

	IDynamicObject * createDynamicObject( IGeometryObject * geometryObject );
	IGraphicObject * createGraphicObject( IDynamicObject * geometryObject, Evas_Object * canvas );

	static DynamicObjectFactory & getInstance();

};

#endif /* DYNAMICOBJECTFACTORY_H_ */
