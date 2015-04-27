/*
 * SetRigidSpringBetweenUnusedLinksFunctor.h
 *
 *  Created on: 27 апр. 2015
 *      Author: vadim
 */

#ifndef FUNCTORS_SETRIGIDSPRINGBETWEENUNUSEDLINKSFUNCTOR_H_
#define FUNCTORS_SETRIGIDSPRINGBETWEENUNUSEDLINKSFUNCTOR_H_

#include "GeometryLink.h"
#include <vector>
using namespace std;

class SetRigidSpringBetweenUnusedLinksFunctor
{
	typedef struct
	{

		const GeometryLink * m_Link1;
		const GeometryLink * m_Link2;

	}LinkPairType;
public:
	SetRigidSpringBetweenUnusedLinksFunctor();
	virtual ~SetRigidSpringBetweenUnusedLinksFunctor();

private:

	void getUnUsedLinksPairs( vector<LinkPairType> & unUsedPairLinks );

};

#endif /* FUNCTORS_SETRIGIDSPRINGBETWEENUNUSEDLINKSFUNCTOR_H_ */
