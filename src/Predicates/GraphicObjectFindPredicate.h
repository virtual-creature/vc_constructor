/*
 * GraphicObjectFindPredicate.h
 *
 *  Created on: Mar 25, 2015
 *      Author: vostanin
 */

#ifndef GRAPHICOBJECTFINDPREDICATE_H_
#define GRAPHICOBJECTFINDPREDICATE_H_

#include "IGraphicObject.h"

class GraphicObjectFindPredicate
{
public:
	GraphicObjectFindPredicate( IGraphicObject * origin );
	~GraphicObjectFindPredicate();
	bool operator()( IGraphicObject * object );
private:
	IGraphicObject * m_Origin;
};

#endif /* GRAPHICOBJECTFINDPREDICATE_H_ */
