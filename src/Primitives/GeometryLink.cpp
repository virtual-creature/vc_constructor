/*
 * GeometryLink.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "GeometryLink.h"
#include "GeometryLinkGetAbsoluteAnglePredicate.h"
#include "GeometryObjectsManager.h"
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <cassert>
using namespace std;

GeometryLink::GeometryLink() : m_Id( rand() )
{
}

GeometryLink::GeometryLink( GeometryPoint * point_1, GeometryPoint * point_2 ) : m_Id( rand() )
{
	m_Points[0] = point_1;
	m_Points[1] = point_2;
}

GeometryLink::~GeometryLink()
{
}

GeometryObjectsTypes GeometryLink::getType() const
{
	return GEOMETRYOBJECT_LINK;
}

GeometryObjectsConstructiongStates GeometryLink::getConstructingState() const
{
	return GEOMETRYOBJECTCONSTRUCTING_COMPLETE;
}

int GeometryLink::getId() const
{
	return m_Id;
}

void GeometryLink::setId( int id )
{
	m_Id = id;
}

IGeometryObject * GeometryLink::clone()
{
	GeometryLink * newLink = new GeometryLink;

	newLink->setId( getId() );
	newLink->setPointFrom( getPointFrom() );
	newLink->setPointTo( getPointTo() );

	return newLink;
}

string GeometryLink::toString()
{
	stringstream stream;

	stream << getType() << " " << getId() << " " << getPointFrom()->getId() << " " << getPointTo()->getId() << flush;

	return stream.str();
}

bool GeometryLink::fromString( string str )
{
	GeometryObjectsTypes geometryObjectType = GEOMETRYOBJECT_DUMMY;
	int Id = 0;
	int pointFromId = 0;
	int pointToId = 0;
	sscanf( str.c_str(), "%d %d %d %d", (int*)&geometryObjectType, &Id, &pointFromId, &pointToId );
	if( geometryObjectType != GEOMETRYOBJECT_LINK )
	{
//		assert( false );
		return false;
	}
	setId( Id );
	const GeometryPoint *pointFrom = dynamic_cast<const GeometryPoint *>( GeometryObjectsManager::getInstance().getObject( pointFromId ) );
	const GeometryPoint *pointTo = dynamic_cast<const GeometryPoint *>( GeometryObjectsManager::getInstance().getObject( pointToId ) );
	setPointFrom( pointFrom );
	setPointTo( pointTo );

	return true;
}

GeometryLink & GeometryLink::operator = ( const GeometryLink & src )
{
	if( *this == src )
	{
		return *this;
	}
	const GeometryPoint * point = src.getPointFrom();
	setPointFrom( point );
	setPointTo( src.getPointTo() );
	return *this;
}

bool GeometryLink::operator != ( const GeometryLink & src ) const
{
	return ( *this == src ) == false;
}

bool GeometryLink::operator == ( const GeometryLink & src ) const
{
	if( getPointFrom() != src.getPointFrom() )
	{
		return false;
	}
	if( getPointTo() !=  src.getPointTo() )
	{
		return false;
	}
	return true;
}

IGeometryObject & GeometryLink::operator = ( IGeometryObject & src )
{
	if( src.getType() != GEOMETRYOBJECT_LINK )
	{
		return *this;
	}
	setPointFrom( ((GeometryLink &)src).getPointFrom() );
	setPointTo(   ((GeometryLink &)src).getPointTo()   );

	m_Id = ((GeometryLink &)src).m_Id;

	return *this;
}

bool GeometryLink::isValid()
{
    if ( ((IGeometryObject *)getPointFrom())->getType() == GEOMETRYOBJECT_DUMMY )
    {
        return false;
    }
    if ( ((IGeometryObject *)getPointTo())->getType() == GEOMETRYOBJECT_DUMMY )
    {
        return false;
    }
	return true;
}

void GeometryLink::setPointFrom( const GeometryPoint * point )
{
	m_Points[0] = point;
}

void GeometryLink::setPointTo( const GeometryPoint * point )
{
	m_Points[1] = point;
}

const GeometryPoint * GeometryLink::getPointFrom() const
{
	const GeometryPoint * p = m_Points[0];
	return p;
}

const GeometryPoint * GeometryLink::getPointTo() const
{
	const GeometryPoint * p = m_Points[1];
	return p;
}

int GeometryLink::getWidth() const
{
	int linkfrom_katet_width = abs( getPointFrom()->getX() - getPointTo()->getX() );
	int linkfrom_katet_height = abs( getPointFrom()->getY() - getPointTo()->getY() );

	int linkfrom_width = sqrt( linkfrom_katet_width * linkfrom_katet_width + linkfrom_katet_height * linkfrom_katet_height );

	return linkfrom_width;
}

int GeometryLink::getMiddleX() const
{
	return ( getPointFrom()->getX() + getPointTo()->getX() ) / 2;
}

int GeometryLink::getMiddleY() const
{
	return ( getPointFrom()->getY() + getPointTo()->getY() ) / 2;
}






