/*
 * GeometrySpringGetAngles.h
 *
 *  Created on: 22 апр. 2015
 *      Author: vadim
 */

#ifndef FUNCTORS_GEOMETRYSPRINGGETANGLES_H_
#define FUNCTORS_GEOMETRYSPRINGGETANGLES_H_

#include "GeometrySpring.h"
#include "GeometryLink.h"

class GeometrySpringGetAngles
{
public:
	GeometrySpringGetAngles( const GeometrySpring * geometrySpring );
	GeometrySpringGetAngles( const GeometryLink * geometryLink1, const GeometryLink * geometryLink2 );
	virtual ~GeometrySpringGetAngles();

	bool getHasCrospoint() const;

	int getLinkFromAngle() const;
	int getLinkToAngle() const;

	const GeometryPoint * getLinkFromAdjacentPoint() const;
	const GeometryPoint * getLinkToAdjacentPoint() const;

	const GeometryPoint * getCrospoint() const;

private:

	const GeometryLink * m_GeometryLinkFrom;
	const GeometryLink * m_GeometryLinkTo;

	const GeometryPoint * m_CrossPoint;

};

#endif /* FUNCTORS_GEOMETRYSPRINGGETANGLES_H_ */
