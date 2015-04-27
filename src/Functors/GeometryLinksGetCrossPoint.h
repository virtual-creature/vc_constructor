/*
 * GeometryLinksGetCrossPoint.h
 *
 *  Created on: 27 апр. 2015
 *      Author: vadim
 */

#ifndef FUNCTORS_GEOMETRYLINKSGETCROSSPOINT_H_
#define FUNCTORS_GEOMETRYLINKSGETCROSSPOINT_H_

#include "GeometryLink.h"
#include "GeometryPoint.h"

class GeometryLinksGetCrossPoint {
public:
	GeometryLinksGetCrossPoint( const GeometryLink * link1, const GeometryLink * link2 );
	virtual ~GeometryLinksGetCrossPoint();

	bool getHasCrosslink() const;
	const GeometryPoint * getCrosslink() const;

private:

	const GeometryPoint * m_Crosslink;

};

#endif /* FUNCTORS_GEOMETRYLINKSGETCROSSPOINT_H_ */
