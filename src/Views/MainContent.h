/*
 * MainContent.h
 *
 *  Created on: Mar 13, 2015
 *      Author: vostanin
 */

#ifndef MAINCONTENT_H_
#define MAINCONTENT_H_

#include "MainContentMenuParams.h"
#include <Evas.h>

class MainContent
{
public:
	MainContent( Evas_Object *parent );
	~MainContent();

	Evas_Object * getLayout() const;

	void addMenu( MainContentMenuParams & menuParams );

	Evas_Object * getMenu() const;
	Evas_Object * getMenu2() const;

private:

	void createLayout();
	Evas_Object * m_Parent;
	Evas_Object * m_MainLayout;

	Evas_Object * m_Menu;
	Evas_Object * m_Menu2;
	Evas_Object * m_Toolbar;
};

#endif /* MAINCONTENT_H_ */
