/*
 * GeometrySpringGetAngles.cpp
 *
 *  Created on: 22 апр. 2015
 *      Author: vadim
 */

#include "GeometrySpringGetAngles.h"
#include "GeometryLinksGetCrossPoint.h"
#include "GeometrySpringGetCrosslinkPredicate.h"
#include "GeometryLinkGetAbsoluteAnglePredicate.h"
#include <cassert>
using namespace std;

GeometrySpringGetAngles::GeometrySpringGetAngles( const GeometrySpring * geometrySpring ) : m_CrossPoint( 0 )
{
	GeometrySpringGetCrosslinkPredicate getCrosspoint( geometrySpring );
	m_GeometryLinkFrom = ( geometrySpring->getLinkFrom() );
	m_GeometryLinkTo = ( geometrySpring->getLinkTo() );
	m_CrossPoint = getCrosspoint();
}

GeometrySpringGetAngles::GeometrySpringGetAngles( const GeometryLink * geometryLink1, const GeometryLink * geometryLink2 )
{
	GeometryLinksGetCrossPoint getCrosslink( geometryLink1, geometryLink2 );

	if( false == getCrosslink.getHasCrosslink() )
	{
		assert( false );
	}

	m_CrossPoint = getCrosslink.getCrosslink();

	m_GeometryLinkFrom = geometryLink1;
	m_GeometryLinkTo = geometryLink2;

}

GeometrySpringGetAngles::~GeometrySpringGetAngles()
{
}

bool GeometrySpringGetAngles::getHasCrospoint() const
{
	return m_CrossPoint != NULL;
}

const GeometryPoint * GeometrySpringGetAngles::getCrospoint() const
{
	return m_CrossPoint;
}

const GeometryPoint * GeometrySpringGetAngles::getLinkFromAdjacentPoint() const
{
	const GeometryPoint * result = NULL;

	if( m_GeometryLinkFrom->getPointFrom() == getCrospoint() )
	{
		result = m_GeometryLinkFrom->getPointTo();
	}
	else
	{
		result = m_GeometryLinkFrom->getPointFrom();
	}

	return result;
}

const GeometryPoint * GeometrySpringGetAngles::getLinkToAdjacentPoint() const
{
	const GeometryPoint * result = NULL;

	if( m_GeometryLinkTo->getPointFrom() == getCrospoint() )
	{
		result = m_GeometryLinkTo->getPointTo();
	}
	else
	{
		result = m_GeometryLinkTo->getPointFrom();
	}

	return result;
}

int GeometrySpringGetAngles::getLinkFromAngle() const
{
	int linkX1 = getCrospoint()->getX();
	int linkY1 = getCrospoint()->getY();
	int linkX2 = getLinkFromAdjacentPoint()->getX();
	int linkY2 = getLinkFromAdjacentPoint()->getY();

	GeometryLinkGetAbsoluteAnglePredicate getLinkAbsoluteAngle( linkX1, linkY1, linkX2, linkY2 );
	return getLinkAbsoluteAngle();
}

int GeometrySpringGetAngles::getLinkToAngle() const
{
	int linkX1 = getCrospoint()->getX();
	int linkY1 = getCrospoint()->getY();
	int linkX2 = getLinkToAdjacentPoint()->getX();
	int linkY2 = getLinkToAdjacentPoint()->getY();

	GeometryLinkGetAbsoluteAnglePredicate getLinkAbsoluteAngle( linkX1, linkY1, linkX2, linkY2 );
	return getLinkAbsoluteAngle();
}








