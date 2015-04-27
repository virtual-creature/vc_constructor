/*
 * ToolbarContentButton.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#include "ToolbarContentCheck.h"
#include "ToolbarContentTypes.h"
#include <elementary-1/Elementary.h>
#include <Evas.h>

ToolbarContentCheck::ToolbarContentCheck( ToolbarContentCheckParams & params ) : ToolbarContentItem( TOOLBARCONTENT_BUTTON, params )
{
}

ToolbarContentCheck::~ToolbarContentCheck()
{
	evas_object_del( m_Evas );
}

void ToolbarContentCheck::create( Evas_Object * parent )
{
	m_Evas = elm_check_add( parent );
	evas_object_size_hint_align_set( m_Evas, EVAS_HINT_FILL, EVAS_HINT_FILL );
    evas_object_size_hint_weight_set( m_Evas, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND );
    string title = ((ToolbarContentCheckParams &)m_Params).getTitle();
    bool checked = ((ToolbarContentCheckParams &)m_Params).getChecked();
    elm_object_text_set( m_Evas, title.c_str() );
    elm_check_state_set( m_Evas, checked );
	evas_object_show( m_Evas );

	evas_object_smart_callback_add( m_Evas, "changed", on_click, &m_callbackData );

//	Elm_Theme * theme = elm_theme_new();
//	elm_theme_ref_set( theme, NULL );
//
//	elm_theme_extension_add( theme, MAIN_EDJ );
//	elm_object_theme_set( m_Evas, theme  );
//	Eina_Bool applied = elm_object_style_set( m_Evas, "button_custom_my" );


	m_callbackData.lpThis = this;
	m_callbackData.userData = ((ToolbarContentCheckParams &)m_Params).getUserData();
}

Evas_Object * ToolbarContentCheck::getEvas() const
{
	return m_Evas;
}

void ToolbarContentCheck::on_click( void *data, Evas_Object *e, void *event_info )
{
	CallbackData * callbackData = (CallbackData *)data;
	ToolbarContentCheckParams & params = (ToolbarContentCheckParams &)callbackData->lpThis->m_Params;
	ToolbarItemCallback callbackCheck = params.getCallbackChecked();
	ToolbarItemCallback callbackUnCheck = params.getCallbackUnChecked();
	if( elm_check_state_get( callbackData->lpThis->getEvas() ) == true )
	{
		callbackCheck( callbackData->userData );
	}
	else
	{
		callbackUnCheck( callbackData->userData );
	}
}
















