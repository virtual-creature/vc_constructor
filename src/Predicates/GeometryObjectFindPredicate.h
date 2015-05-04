/*
 * GeometryObjectFindPredicate.h
 *
 *  Created on: Mar 25, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYOBJECTFINDPREDICATE_H_
#define GEOMETRYOBJECTFINDPREDICATE_H_

#include "IGeometryObject.h"

class GeometryObjectFindPredicate
{
public:
	GeometryObjectFindPredicate( const IGeometryObject * origin );
	GeometryObjectFindPredicate( int Id );
	~GeometryObjectFindPredicate();
	bool operator()( const IGeometryObject * object );
private:
	int m_Id;
};

#endif /* GEOMETRYOBJECTFINDPREDICATE_H_ */
