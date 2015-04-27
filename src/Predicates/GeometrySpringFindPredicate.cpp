/*
 * GeometrySpringFindPredicate.cpp
 *
 *  Created on: 27 апр. 2015
 *      Author: vadim
 */

#include "GeometrySpringFindPredicate.h"
#include "GeometrySpringGetAngles.h"

GeometrySpringFindPredicate::GeometrySpringFindPredicate( const GeometryLink * geometryLink1,  const GeometryLink * geometryLink2 ) :
	m_GeometryLink1( geometryLink1 ), m_GeometryLink2( geometryLink2)
{
}

GeometrySpringFindPredicate::~GeometrySpringFindPredicate()
{
}

bool GeometrySpringFindPredicate::operator()( IGeometryObject * currGeometryObject )
{
	const GeometrySpring * currGeometrySpring = dynamic_cast<const GeometrySpring *>( currGeometryObject );

	if( ( currGeometrySpring->getLinkFrom() != m_GeometryLink1 &&
		  currGeometrySpring->getLinkFrom() != m_GeometryLink2 )
		||
		( currGeometrySpring->getLinkTo() != m_GeometryLink1 &&
		  currGeometrySpring->getLinkTo() != m_GeometryLink2 )
	  )
	{
		return false;
	}

	return true;
}


















