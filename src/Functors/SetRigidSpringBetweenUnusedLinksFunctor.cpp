/*
 * SetRigidSpringBetweenUnusedLinksFunctor.cpp
 *
 *  Created on: 27 апр. 2015
 *      Author: vadim
 */

#include "SetRigidSpringBetweenUnusedLinksFunctor.h"
#include "GeometryObjectsManager.h"
#include "GeometrySpringFindPredicate.h"
#include "GeometryLinksGetCrossPoint.h"
#include <algorithm>
#include <iostream>
using namespace std;

SetRigidSpringBetweenUnusedLinksFunctor::SetRigidSpringBetweenUnusedLinksFunctor()
{
	vector<LinkPairType> unUsedPairLinks;
	getUnUsedLinksPairs( unUsedPairLinks );

	size_t count = unUsedPairLinks.size();
	cout << "count=" << count << endl << flush;
}

SetRigidSpringBetweenUnusedLinksFunctor::~SetRigidSpringBetweenUnusedLinksFunctor()
{
}

void SetRigidSpringBetweenUnusedLinksFunctor::getUnUsedLinksPairs( vector<LinkPairType> & unUsedPairLinks )
{
	vector<IGeometryObject *> geometryObjects;
	vector<IGeometryObject *> geometryPoints;
	vector<IGeometryObject *> geometryLinks;
	vector<IGeometryObject *> geometrySprings;
	GeometryObjectsManager::getInstance().getObjects( geometryObjects );

	vector<IGeometryObject *>::iterator begin = geometryObjects.begin();
	vector<IGeometryObject *>::iterator end = geometryObjects.end();
	vector<IGeometryObject *>::iterator iter = begin;
	for(  ; iter != end ; iter++ )
	{
		switch( (* iter)->getType() )
		{
			case GEOMETRYOBJECT_POINT:
					geometryPoints.push_back( (* iter) );
				break;
			case GEOMETRYOBJECT_LINK:
					geometryLinks.push_back( (* iter) );
				break;
			case GEOMETRYOBJECT_SPRING:
					geometrySprings.push_back( (* iter) );
				break;
			default:
				break;
		}
	}
//TODO : make smarter
	vector<IGeometryObject *>::const_iterator linksBegin_Level_1 = geometryLinks.begin();
	vector<IGeometryObject *>::const_iterator linksEnd_Level_1 = geometryLinks.end();
	vector<IGeometryObject *>::const_iterator linksIter_Level_1 = linksBegin_Level_1;
	for(  ; linksIter_Level_1 != linksEnd_Level_1 ; linksIter_Level_1++ )
	{
		vector<IGeometryObject *>::const_iterator linksBegin_Level_2 = geometryLinks.begin();
		vector<IGeometryObject *>::const_iterator linksEnd_Level_2 = geometryLinks.end();
		vector<IGeometryObject *>::const_iterator linksIter_Level_2 = linksBegin_Level_2;
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

			GeometrySpringFindPredicate springFindPredicate( link1, link2 );
			vector<IGeometryObject *>::iterator found_iter = find_if( geometrySprings.begin(), geometrySprings.end(), springFindPredicate );
			if( found_iter != geometrySprings.end() )// combination no found
			{
				continue;
			}
			LinkPairType pair = { link1, link2 };
			unUsedPairLinks.push_back( pair );
		}
	}
}


















