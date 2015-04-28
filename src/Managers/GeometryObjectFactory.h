/*
 * GeometryObjectFactory.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYOBJECTFACTORY_H_
#define GEOMETRYOBJECTFACTORY_H_

#include "IGeometryObject.h"
#include "IGraphicObject.h"
#include "GeometryObjectsTypes.h"
#include "GeometryObjectBufferAllocator.h"

class GeometryObjectFactory
{
public:
	GeometryObjectFactory();
	virtual ~GeometryObjectFactory();

	IGeometryObject * createGeometryObject( GeometryObjectsTypes type );

	void deleteGeometryObject( IGeometryObject * geometryObject );

	static GeometryObjectFactory & getInstance();

private:

	GeometryObjectBufferAllocator m_bufferObjectAllocator;
};

#endif /* GEOMETRYOBJECTFACTORY_H_ */
