/*
 * GeometryDummy.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#include "GeometryDummy.h"
#include <cstdlib>
#include <sstream>
#include <iostream>
using namespace std;

GeometryDummy::GeometryDummy() : m_Id( rand() )
{
}

GeometryDummy::GeometryDummy( const GeometryDummy & src )
{
	m_Id = src.m_Id;
}

GeometryDummy::~GeometryDummy()
{
}

int GeometryDummy::getId() const
{
	return m_Id;
}

void GeometryDummy::setId( int id)
{
	m_Id = id;
}

IGeometryObject * GeometryDummy::clone()
{
	GeometryDummy * newObject = new GeometryDummy;

	newObject->m_Id = m_Id;

	return newObject;
}

string GeometryDummy::toString()
{
	stringstream stream;

	stream << getType() << " " << getId() << " " << flush;

	return stream.str();
}

bool GeometryDummy::fromString( string str )
{
	GeometryObjectsTypes geometryObjectType = GEOMETRYOBJECT_DUMMY;
	sscanf( str.c_str(), "%d", (int*)&geometryObjectType );
	if( geometryObjectType != GEOMETRYOBJECT_POINT )
	{
//		assert( false );
		return false;
	}

	return true;
}

IGeometryObject & GeometryDummy::operator = ( IGeometryObject & src )
{
	return *this;
}

GeometryObjectsTypes GeometryDummy::getType() const
{
	return GEOMETRYOBJECT_DUMMY;
}

GeometryObjectsConstructiongStates GeometryDummy::getConstructingState() const
{
	return GEOMETRYOBJECTCONSTRUCTING_COMPLETE;
}

bool GeometryDummy::isValid()
{
	return true;
}
