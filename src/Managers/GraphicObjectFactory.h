/*
 * GeometryObjectFactory.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef GRAPHICOBJECTFACTORY_H_
#define GRAPHICOBJECTFACTORY_H_

#include "IGeometryObject.h"
#include "IGraphicObject.h"
#include "IDynamicObject.h"

class GraphicObjectFactory
{
public:
	GraphicObjectFactory();
	virtual ~GraphicObjectFactory();

	IGraphicObject * createGraphicObject( IGeometryObject * geometryObject, Evas_Object * canvas );
	IGraphicObject * createGraphicObject( IDynamicObject * dynamicObject, Evas_Object * canvas );

	static GraphicObjectFactory & getInstance();
};

#endif /* GRAPHICOBJECTFACTORY_H_ */
