/*
 * MainContent.cpp
 *
 *  Created on: Mar 13, 2015
 *      Author: vostanin
 */

#include "MainContent.h"

#include <Elementary.h>

#include <Evas_Engine_Buffer.h>
#include <iostream>
using namespace std;

//#define MAIN_EDJ "/opt/usr/apps/org.tizen.tizen_porting/res/edje/main.edj"
#define MAIN_EDJ "./main.edj"

void on_button_click( void * user_data )
{
	cout << "on_button_click" << endl << flush;
}

static bool _show( void *data )
{
	MainContent * lpThis = (MainContent *)data;

	evas_object_show((Evas_Object *)lpThis->getMenu());

	return true;
}

static void _show2( void *data, Evas *e, Evas_Object *obj, void *event_info )
{
	MainContent * lpThis = (MainContent *)data;
//
//	Evas_Event_Mouse_Down *ev = (Evas_Event_Mouse_Down *)event_info;
//
//	elm_menu_move((Evas_Object *)lpThis->getMenu(), ev->canvas.x, ev->canvas.y);

	evas_object_show((Evas_Object *)lpThis->getMenu());

	static int i = 0;
	cout << "show=" << i << endl << flush;
	i++;
}

static void _toolbar_item1_click( void *data, Evas_Object *obj, void *event_info )
{
	MainContent * lpThis = (MainContent *)data;

	Evas_Coord x, y, w, h;

	evas_object_geometry_get( obj, &x, &y, &w, &h );

	elm_menu_move( (Evas_Object *)lpThis->getMenu(), x, y + 40 );

	evas_object_show((Evas_Object *)lpThis->getMenu());

	Elm_Object_Item * item1 = elm_toolbar_item_find_by_label( obj, "File" );

	elm_toolbar_item_selected_set( item1, EINA_FALSE );
}

static void _toolbar_item2_click( void *data, Evas_Object *obj, void *event_info )
{
	MainContent * lpThis = (MainContent *)data;

	Evas_Coord x, y, w, h;

	evas_object_geometry_get( obj, &x, &y, &w, &h );

	elm_menu_move( (Evas_Object *)lpThis->getMenu2(), x, y + 40 );

	evas_object_show((Evas_Object *)lpThis->getMenu2());

	Elm_Object_Item * item2 = elm_toolbar_item_find_by_label( obj, "Edit" );

	elm_toolbar_item_selected_set( item2, EINA_FALSE );
}

static void _toolbar_menu_onhide( void *data, Evas * evas, Evas_Object *obj, void *event_info )
{
	MainContent * lpThis = (MainContent *)data;

	Elm_Object_Item * item1 = elm_toolbar_item_find_by_label( obj, "File" );
	Elm_Object_Item * item2 = elm_toolbar_item_find_by_label( obj, "Edit" );

	elm_toolbar_item_selected_set( item1, EINA_FALSE );
	elm_toolbar_item_selected_set( item2, EINA_FALSE );
}

Evas_Object * MainContent::getMenu() const
{
	return m_Menu;
}

Evas_Object * MainContent::getMenu2() const
{
	return m_Menu2;
}

MainContent::MainContent( Evas_Object *parent ) : m_Parent( parent ), m_MainLayout( NULL )
{
	createLayout();

	{
		m_Toolbar = elm_toolbar_add( m_MainLayout );
		elm_toolbar_horizontal_set( m_Toolbar, EINA_TRUE );
		evas_object_size_hint_align_set( m_Toolbar, EVAS_HINT_FILL, EVAS_HINT_FILL );
		evas_object_size_hint_weight_set( m_Toolbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND );
		Elm_Object_Item * toolbaritem1 = elm_toolbar_item_append( m_Toolbar, NULL, "File", _toolbar_item1_click, this );
		Elm_Object_Item * toolbaritem2 = elm_toolbar_item_append( m_Toolbar, NULL, "Edit", _toolbar_item2_click, this );

		elm_toolbar_align_set( m_Toolbar, 0.0 );

		elm_object_part_content_set( m_MainLayout, "part.main_layout.main_menu", m_Toolbar );

		m_Menu = elm_menu_add( m_Parent );

		elm_menu_item_add( m_Menu, NULL, NULL, "Open", NULL, NULL );
		elm_menu_item_add( m_Menu, NULL, NULL, "Save", NULL, NULL );

		evas_object_show( m_Toolbar );
		evas_object_hide( m_Menu );

		m_Menu2 = elm_menu_add( m_Parent );

		elm_menu_item_add( m_Menu2, NULL, NULL, "Open", NULL, NULL );

		evas_object_event_callback_add( m_Menu, EVAS_CALLBACK_HIDE, _toolbar_menu_onhide, this );
		evas_object_event_callback_add( m_Menu2, EVAS_CALLBACK_HIDE, _toolbar_menu_onhide, this );

		evas_object_hide( m_Menu2 );
	}
}

void MainContent::addMenu( MainContentMenuParams & menuParams )
{
	;
}

MainContent::~MainContent()
{

}

Evas_Object * MainContent::getLayout() const
{
	return m_MainLayout;
}

void MainContent::createLayout()
{
	Evas_Object *layout = elm_layout_add( m_Parent );
	elm_layout_file_set(layout, MAIN_EDJ, "main_layout");
	evas_object_show(layout);

	m_MainLayout = layout;
}


















