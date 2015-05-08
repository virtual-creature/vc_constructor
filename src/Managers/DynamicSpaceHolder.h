/*
 * DynamicSpaceHolder.h
 *
 *  Created on: 8 мая 2015
 *      Author: vadim
 */

#ifndef MANAGERS_DYNAMICSPACEHOLDER_H_
#define MANAGERS_DYNAMICSPACEHOLDER_H_

#include <chipmunk/chipmunk.h>

class DynamicSpaceHolder
{
public:
	DynamicSpaceHolder();
	virtual ~DynamicSpaceHolder();

	cpSpace * getSpace() const;

	void setCanvasWidth( unsigned int width );
	void setCanvasHeight( unsigned int height );
	unsigned int getCanvasWidth() const;
	unsigned int getCanvasHeight() const;

	void init();

	static DynamicSpaceHolder & getInstance();

private:

	void initSpace();
	void initCanvasBorders();

	cpSpace * m_Space;
	cpVect m_Gravity;

	cpShape * m_LeftBorder;
	cpShape * m_RightBorder;
	cpShape * m_TopBorder;
	cpShape * m_BottomBorder;

	unsigned int m_CanvasWidth;
	unsigned int m_CanvasHeight;

	bool m_Inited;

};

#endif /* MANAGERS_DYNAMICSPACEHOLDER_H_ */
