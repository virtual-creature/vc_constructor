/*
 * MainContentMenuParams.h
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#ifndef Toolbar_MainContentMenuParams_H_
#define Toolbar_MainContentMenuParams_H_

#include <Evas.h>
#include <string>
using namespace std;

typedef void (* MenuItemCallback)( void * user_data );

class MainContentMenuParams
{
public:
	MainContentMenuParams();
	MainContentMenuParams( string sTitle, MenuItemCallback callback, void * userData, Evas_Object * parentMenu = NULL );
	virtual ~MainContentMenuParams();


	Evas_Object * getMenuParent() const;
    string getTitle() const;
    MenuItemCallback getCallback() const;
	void * getUserData();

private:

	Evas_Object * m_MenuParent;
	string m_sTitle;
	MenuItemCallback m_Callback;
	void * m_UserData;

};

#endif /* Toolbar_MainContentMenuParams_H_ */
