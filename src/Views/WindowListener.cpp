/*
 * WindowListener.cpp
 *
 *  Created on: Mar 13, 2015
 *      Author: vostanin
 */

#include "WindowListener.h"
#include <Elementary.h>

WindowListener::WindowListener()
{
}

WindowListener::~WindowListener()
{
}

void WindowListener::onExitRequest(Window & win)
{
	elm_exit();
}
