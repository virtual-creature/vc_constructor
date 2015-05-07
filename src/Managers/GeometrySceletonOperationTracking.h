/*
 * GeometrySceletonOperationTracking.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYSCELETONOPERATIONTRACKING_H_
#define GEOMETRYSCELETONOPERATIONTRACKING_H_

#include "IGeometryObjectTracker.h"
#include "ObjectOperationStatus.h"
#include "GeometryMouseTrackingModes.h"
#include "DrawingContent.h"
#include "GeometryPoint.h"

#include <vector>
using namespace std;

class GeometrySceletonOperationTracking : public IGeometryObjectTracker
{
public:
	GeometrySceletonOperationTracking( DrawingContent & viewUpdater );
	virtual ~GeometrySceletonOperationTracking();

	GeometryMouseTrackingModes getType() const;

	void trackerBegin( int x, int y );
	void trackerContinue( int x, int y );
	void trackerEnd( int x, int y );

	void deleteObject( int x, int y );

private:

	void clearTrackingStack();

	void constructGraphicObjects( vector<IGraphicObject *> & graphicObjects );
	void constructGraphicObject( IGeometryObject * geometryObject, IGraphicObject ** graphicObject );

	DrawingContent & m_ViewUpdater;
	IGeometryObject * m_GeometryObjectTracking;
};

#endif /* GEOMETRYSCELETONOPERATIONTRACKING_H_ */
