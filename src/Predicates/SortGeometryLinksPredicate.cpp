/*
 * SortGeometryLinksPredicate.cpp
 *
 *  Created on: 4 мая 2015
 *      Author: vadim
 */

#include "SortGeometryLinksPredicate.h"
#include "GeometryLinksGetCrossPoint.h"
#include "GeometryLinkGetAbsoluteAnglePredicate.h"
#include "GeometrySpringGetAngles.h"
#include <cassert>
using namespace std;

SortGeometryLinksPredicate::SortGeometryLinksPredicate()
{
}

SortGeometryLinksPredicate::~SortGeometryLinksPredicate()
{
}

bool SortGeometryLinksPredicate::operator ()( const GeometryLink * geometryLink1, const GeometryLink * geometryLink2 ) const
{
	GeometrySpringGetAngles getAngles( geometryLink1, geometryLink2 );

	if( false == getAngles.getHasCrospoint() )
	{
		assert( false );
	}
	int angle1 = getAngles.getLinkFromAngle();
	int angle2 = getAngles.getLinkToAngle();

	if( angle1 < angle2 )
	{
		return true;
	}
	return false;
}










