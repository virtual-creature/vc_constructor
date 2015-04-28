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

	class LinkPairFindPredicate
	{
	public:
		LinkPairFindPredicate( const LinkPairType & origin ) : m_Origin( origin ){}
		bool operator()( const LinkPairType & origin )
		{
			if( ( m_Origin.m_Link1 != origin.m_Link1 && m_Origin.m_Link1 != origin.m_Link2 )
					||
				( m_Origin.m_Link2 != origin.m_Link1 && m_Origin.m_Link2 != origin.m_Link2 )
			  )
			{
				return false;
			}
			return true;
		}
	private:

		const LinkPairType & m_Origin;

	};
public:
	SetRigidSpringBetweenUnusedLinksFunctor();
	virtual ~SetRigidSpringBetweenUnusedLinksFunctor();

private:

	void getUnUsedLinksPairs( vector<LinkPairType> & unUsedPairLinks );
	void createRigidSprings( vector<LinkPairType> & unUsedPairLinks );

};

#endif /* FUNCTORS_SETRIGIDSPRINGBETWEENUNUSEDLINKSFUNCTOR_H_ */
