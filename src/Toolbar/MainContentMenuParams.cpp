/*
 * ToolbarContentRadioParams.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#include "MainContentMenuParams.h"
#include <elementary-1/Elementary.h>

MainContentMenuParams::MainContentMenuParams( string sTitle, MenuItemCallback callback, void * userData, Evas_Object * parentMenu ) :
				m_MenuParent( parentMenu ), m_sTitle( sTitle ), m_Callback( callback ), m_UserData( userData )
{
}

MainContentMenuParams::~MainContentMenuParams()
{
}

Evas_Object * MainContentMenuParams::getMenuParent() const
{
	return m_MenuParent;
}

string MainContentMenuParams::getTitle() const
{
    return m_sTitle;
}

MenuItemCallback MainContentMenuParams::getCallback() const
{
	return m_Callback;
}

void * MainContentMenuParams::getUserData()
{
	return m_UserData;
}











