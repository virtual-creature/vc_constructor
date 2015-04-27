/*
 * GeometryLinksGetCrossPoint.cpp
 *
 *  Created on: 27 апр. 2015
 *      Author: vadim
 */

#include "GeometryLinksGetCrossPoint.h"

GeometryLinksGetCrossPoint::GeometryLinksGetCrossPoint( const GeometryLink * link1, const GeometryLink * link2 )
{
	const GeometryLink * linkFrom = link1;
	const GeometryLink * linkTo = link2;

	const GeometryPoint * result = NULL;

	if( linkFrom->getPointFrom() == linkTo->getPointFrom() )
	{
		result = linkFrom->getPointFrom();
	}
	else if( linkFrom->getPointTo() == linkTo->getPointTo() )
	{
		result = linkFrom->getPointTo();
	}
	else if( linkFrom->getPointFrom() == linkTo->getPointTo() )
	{
		result = linkFrom->getPointTo();
	}
	else if( linkFrom->getPointTo() == linkTo->getPointFrom() )
	{
		result = linkFrom->getPointTo();
	}

	m_Crosslink = result;
}

GeometryLinksGetCrossPoint::~GeometryLinksGetCrossPoint()
{
}

bool GeometryLinksGetCrossPoint::getHasCrosslink() const
{
	return m_Crosslink != NULL;
}

const GeometryPoint * GeometryLinksGetCrossPoint::getCrosslink() const
{
	return m_Crosslink;
}




















