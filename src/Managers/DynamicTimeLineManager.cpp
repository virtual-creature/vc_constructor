/*
 * DynamicTimeLineManager.cpp
 *
 *  Created on: Apr 6, 2015
 *      Author: vostanin
 */

#include "DynamicTimeLineManager.h"

DynamicTimeLineManager::DynamicTimeLineManager() : m_Space( 0 )
{
}

DynamicTimeLineManager::~DynamicTimeLineManager()
{
}

void DynamicTimeLineManager::setSpace( cpSpace * space )
{
	m_Space = space;
}

void DynamicTimeLineManager::stepSpace()
{
	float timeStep = ( 1.0 / 30.0 ) / 12.0;
	const unsigned int steps_count = 20;
	for( unsigned int step_i = 0 ; step_i < steps_count ; step_i++ )
	{
		cpSpaceStep( m_Space, timeStep );
	}
}

DynamicTimeLineManager & DynamicTimeLineManager::getInstance()
{
	static DynamicTimeLineManager instance;
	return instance;
}














