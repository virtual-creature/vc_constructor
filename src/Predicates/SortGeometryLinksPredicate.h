/*
 * SortGeometryLinksPredicate.h
 *
 *  Created on: 4 мая 2015
 *      Author: vadim
 */

#ifndef PREDICATES_SORTGEOMETRYLINKSPREDICATE_H_
#define PREDICATES_SORTGEOMETRYLINKSPREDICATE_H_

#include "GeometryLink.h"

class SortGeometryLinksPredicate
{
public:
	SortGeometryLinksPredicate();
	virtual ~SortGeometryLinksPredicate();

	bool operator ()( const GeometryLink * geometryLink1, const GeometryLink * geometryLink2 ) const;
};

#endif /* PREDICATES_SORTGEOMETRYLINKSPREDICATE_H_ */
