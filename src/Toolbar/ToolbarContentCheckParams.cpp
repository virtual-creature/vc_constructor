/*
 * ToolbarContentButtonParams.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#include "ToolbarContentCheckParams.h"

ToolbarContentCheckParams::ToolbarContentCheckParams( string & sTitle, bool checked, ToolbarItemCallback callbackChecked, ToolbarItemCallback callbackUnChecked, void * userData ) :
	m_sTitle( sTitle ), m_Checked( checked ), m_CallbackChecked( callbackChecked ), m_CallbackUnChecked( callbackUnChecked ), m_UserData( userData )
{
}

ToolbarContentCheckParams::~ToolbarContentCheckParams()
{
}

string ToolbarContentCheckParams::getTitle() const
{
	return m_sTitle;
}

bool ToolbarContentCheckParams::getChecked() const
{
	return m_Checked;
}

ToolbarItemCallback ToolbarContentCheckParams::getCallbackChecked() const
{
	return m_CallbackChecked;
}

ToolbarItemCallback ToolbarContentCheckParams::getCallbackUnChecked() const
{
	return m_CallbackUnChecked;
}

void * ToolbarContentCheckParams::getUserData()
{
	return m_UserData;
}

ToolbarContentCheckParams::ToolbarContentCheckParams( const ToolbarContentCheckParams & src )
{
	m_sTitle = ((ToolbarContentCheckParams &)src).getTitle();
	m_Checked = ((ToolbarContentCheckParams &)src).getChecked();
	m_CallbackChecked = ((ToolbarContentCheckParams &)src).getCallbackChecked();
	m_CallbackUnChecked = ((ToolbarContentCheckParams &)src).getCallbackUnChecked();
	m_UserData = ((ToolbarContentCheckParams &)src).getUserData();
}

ToolbarContentItemParams & ToolbarContentCheckParams::operator = ( const ToolbarContentItemParams & src )
{
	if( this == &src )
	{
		return *this;
	}

	m_sTitle = ((ToolbarContentCheckParams &)src).getTitle();
	m_Checked = ((ToolbarContentCheckParams &)src).getChecked();
	m_CallbackChecked = ((ToolbarContentCheckParams &)src).getCallbackChecked();
	m_CallbackUnChecked = ((ToolbarContentCheckParams &)src).getCallbackUnChecked();
	m_UserData = ((ToolbarContentCheckParams &)src).getUserData();

	return *this;
}














