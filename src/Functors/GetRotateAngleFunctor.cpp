/*
 * GetRotateAngleFunctor.cpp
 *
 *  Created on: 24 апр. 2015
 *      Author: vadim
 */

#include "GetRotateAngleFunctor.h"
#include "GeometrySpringGetAngles.h"
#include "GetAnglesRangeBy2PointsPredicate.h"

GetRotateAngleFunctor::GetRotateAngleFunctor( const GeometrySpring * geometrySpring ) :
	m_GeometrySpring( geometrySpring ), m_RotateAngle( 0 )
{
	GeometrySpringGetAngles getAngles( m_GeometrySpring );
	m_AngleFrom = getAngles.getLinkFromAngle();
	m_AngleTo   = getAngles.getLinkToAngle();

	GetAnglesRangeBy2PointsPredicate getRange( m_AngleFrom, m_AngleTo, geometrySpring->getIsClosedPath() );

	int minAngle = getRange.getMinAngle();
	int maxAngle = getRange.getMaxAngle();

	m_RotateAngle = maxAngle - minAngle;
}

GetRotateAngleFunctor::~GetRotateAngleFunctor()
{
}

void GetRotateAngleFunctor::calcAngle()
{

}

int GetRotateAngleFunctor::getAngle() const
{
	return m_RotateAngle;
}















