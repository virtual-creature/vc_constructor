/*
 * GeometrySpringFindPredicate.h
 *
 *  Created on: 27 апр. 2015
 *      Author: vadim
 */

#ifndef PREDICATES_GEOMETRYSPRINGFINDPREDICATE_H_
#define PREDICATES_GEOMETRYSPRINGFINDPREDICATE_H_

#include "GeometrySpring.h"
#include "GeometryLink.h"

class GeometrySpringFindPredicate
{
public:
	GeometrySpringFindPredicate( const GeometryLink * geometryLink1,  const GeometryLink * geometryLink2 );
	virtual ~GeometrySpringFindPredicate();

	bool operator()( IGeometryObject * geometrySpring );

private:

	const GeometryLink * m_GeometryLink1;
	const GeometryLink * m_GeometryLink2;

};

#endif /* PREDICATES_GEOMETRYSPRINGFINDPREDICATE_H_ */
