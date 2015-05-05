/*
 * SetRigidSpringBetweenUnusedLinksFunctor.cpp
 *
 *  Created on: 27 апр. 2015
 *      Author: vadim
 */

#include "SetRigidSpringBetweenUnusedLinksFunctor.h"
#include "GeometryObjectsManager.h"
#include "GeometrySpringFindPredicate.h"
#include "GeometryObjectFindPredicate.h"
#include "GeometryLinksGetCrossPoint.h"
#include "GeometryObjectFactory.h"
#include "SortGeometryLinksPredicate.h"
#include "GeometrySpringGetAngles.h"
#include <algorithm>
#include <iostream>
using namespace std;

SetRigidSpringBetweenUnusedLinksFunctor::SetRigidSpringBetweenUnusedLinksFunctor()
{
	vector<LinkPairType> unUsedPairLinks;
	CrossLinksMap crossLinksMap;
	getCrossLinksMap( crossLinksMap );

	getUnUsedLinksPairs( crossLinksMap, unUsedPairLinks );

	size_t count = unUsedPairLinks.size();
	cout << "count=" << count << endl << flush;
	createRigidSprings( unUsedPairLinks );
}

SetRigidSpringBetweenUnusedLinksFunctor::~SetRigidSpringBetweenUnusedLinksFunctor()
{
}

void SetRigidSpringBetweenUnusedLinksFunctor::getCrossLinksMap( CrossLinksMap & crossLinksMap )
{
	vector<IGeometryObject *> geometryLinks;
	vector<const IGeometryObject *> crossPoints;
	GeometryObjectsManager::getInstance().getLinks( geometryLinks );
	vector<IGeometryObject *>::iterator linksBegin_Level_1 = geometryLinks.begin();
	vector<IGeometryObject *>::iterator linksEnd_Level_1 = geometryLinks.end();
	vector<IGeometryObject *>::iterator linksIter_Level_1 = linksBegin_Level_1;
	for(  ; linksIter_Level_1 != linksEnd_Level_1 ; linksIter_Level_1++ )
	{
		vector<IGeometryObject *>::iterator linksBegin_Level_2 = geometryLinks.begin();
		vector<IGeometryObject *>::iterator linksEnd_Level_2 = geometryLinks.end();
		vector<IGeometryObject *>::iterator linksIter_Level_2 = linksBegin_Level_2;
		for(  ; linksIter_Level_2 != linksEnd_Level_2 ; linksIter_Level_2++ )
		{
			if( linksIter_Level_1 == linksIter_Level_2 )
			{
				continue;
			}

			const GeometryLink * link1 = dynamic_cast<const GeometryLink *>(* linksIter_Level_1);
			const GeometryLink * link2 = dynamic_cast<const GeometryLink *>(* linksIter_Level_2);

			GeometryLinksGetCrossPoint getCrosslink( link1, link2 );

			if( false == getCrosslink.getHasCrosslink() )
			{
				continue;
			}

			crossLinksMap[ getCrosslink.getCrosslink() ].push_back( link1 );
			crossLinksMap[ getCrosslink.getCrosslink() ].push_back( link2 );

			crossPoints.push_back( getCrosslink.getCrosslink() );

		}
	}
}

void SetRigidSpringBetweenUnusedLinksFunctor::createRigidSprings( vector<LinkPairType> & unUsedPairLinks )
{
	vector<LinkPairType>::iterator begin = unUsedPairLinks.begin();
	vector<LinkPairType>::iterator end = unUsedPairLinks.end();
	vector<LinkPairType>::iterator iter = begin;
	for(  ; iter != end ; iter++ )
	{
		IGeometryObject * geometryObject = GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_SPRING );
		GeometrySpring * geometrySpring = dynamic_cast<GeometrySpring *>( geometryObject );
		geometrySpring->setLinkFrom( (* iter).m_Link1 );
		geometrySpring->setLinkTo( (* iter).m_Link2 );
		geometrySpring->setIsRigid( true );

		GeometryObjectsManager::getInstance().addObject( geometrySpring );
	}
}

bool equal_func( const GeometryLink * link1, const GeometryLink * link2 )
{
	if( link1->getId() == link2->getId() )
	{
		return true;
	}
	return false;
}

void SetRigidSpringBetweenUnusedLinksFunctor::getUnUsedLinksPairs( CrossLinksMap & crossLinksMap, vector<LinkPairType> & unUsedPairLinks )
{
	CrossLinksMap::iterator mapBegin = crossLinksMap.begin();
	CrossLinksMap::iterator mapEnd = crossLinksMap.end();
	CrossLinksMap::iterator mapIter = mapBegin;

	SortGeometryLinksPredicate sortPredicate;

	for(  ; mapIter != mapEnd ; mapIter++ )
	{
		vector<const GeometryLink *> savedLinks;
		vector<const GeometryLink *>::iterator it;
		savedLinks = (* mapIter).second;

		std::sort( savedLinks.begin(), savedLinks.end() );
		it = unique_copy( savedLinks.begin(), savedLinks.end(), savedLinks.begin() );
		int distance = std::distance( savedLinks.begin(), it );
		savedLinks.resize( distance );

		std::sort( savedLinks.begin(), savedLinks.end(), sortPredicate );

		vector<const GeometryLink *>::iterator linksBegin = savedLinks.begin();
		vector<const GeometryLink *>::iterator linksEnd = savedLinks.end();
		vector<const GeometryLink *>::iterator linksIter = ( linksBegin + 1 );
		for(  ; linksIter != linksEnd ; linksIter++ )
		{
			const GeometryLink * linkPrev = ( *( linksIter - 1 ) );
			const GeometryLink * linkCurr = ( *( linksIter ) );

			GeometrySpringGetAngles getAngles( linkCurr, linkPrev );

			LinkPairType pair = { linkCurr, linkPrev };

			unUsedPairLinks.push_back( pair );
		}
	}
}


















