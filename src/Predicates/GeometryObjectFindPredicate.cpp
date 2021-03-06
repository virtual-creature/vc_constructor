/*
 * GeometryObjectFindPredicate.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: vostanin
 */

#include "GeometryObjectFindPredicate.h"

GeometryObjectFindPredicate::GeometryObjectFindPredicate( const IGeometryObject * origin )
{
	m_Id = origin->getId();
}

GeometryObjectFindPredicate::GeometryObjectFindPredicate( int Id ) : m_Id( Id )
{
}

GeometryObjectFindPredicate::~GeometryObjectFindPredicate()
{
	;
}

bool GeometryObjectFindPredicate::operator()( const IGeometryObject * object )
{
	if( object->getId() == m_Id )
	{
		return true;
	}
	return false;
}

