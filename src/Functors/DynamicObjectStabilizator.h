/*
 * DynamicObjectStabilizator.h
 *
 *  Created on: 7 мая 2015
 *      Author: vadim
 */

#ifndef FUNCTORS_DYNAMICOBJECTSTABILIZATOR_H_
#define FUNCTORS_DYNAMICOBJECTSTABILIZATOR_H_

#include "IDynamicObject.h"
#include <chipmunk/chipmunk.h>
#include <vector>
using namespace std;

class DynamicObjectStabilizator
{
public:
	DynamicObjectStabilizator( cpSpace * space, vector<IDynamicObject *> & geometryObjects );
	virtual ~DynamicObjectStabilizator();

	void stabilize();

private:

	void fixatePoints();
	void fixateCrossPoints();
	void runTimeLine();
	void clearResources();

	cpSpace * m_Space;

	vector<IDynamicObject *> & m_DynamicObjects;
	vector<cpBody *> m_KineticBodies;
	vector<cpConstraint *> m_Joints;

};

#endif /* FUNCTORS_DYNAMICOBJECTSTABILIZATOR_H_ */
