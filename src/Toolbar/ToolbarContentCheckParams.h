/*
 * ToolbarContentButtonParams.h
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#ifndef ToolbarContentCheckParams_H_
#define ToolbarContentCheckParams_H_

#include "ToolbarContentItemParams.h"
#include <string>
using namespace std;

class ToolbarContentCheckParams : public ToolbarContentItemParams
{
public:
	ToolbarContentCheckParams( string & sTitle, bool checked, ToolbarItemCallback callbackChecked, ToolbarItemCallback callbackUnChecked, void * userData );
	ToolbarContentCheckParams( const ToolbarContentCheckParams & src );
	virtual ~ToolbarContentCheckParams();

	string getTitle() const;
	bool getChecked() const;
	ToolbarItemCallback getCallbackChecked() const;
	ToolbarItemCallback getCallbackUnChecked() const;
	void * getUserData();
	ToolbarContentItemParams & operator = ( const ToolbarContentItemParams & src );

private:

	string m_sTitle;
	bool m_Checked;
	ToolbarItemCallback m_CallbackChecked;
	ToolbarItemCallback m_CallbackUnChecked;
	void * m_UserData;
};

#endif /* TOOLBARCONTENTBUTTONPARAMS_H_ */
