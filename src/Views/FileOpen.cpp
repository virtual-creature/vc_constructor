/*
 * FileOpen.cpp
 *
 *  Created on: 7 мая 2015
 *      Author: vadim
 */

#include "FileOpen.h"

void FileOpen::fs_selected( void * data, Evas_Object *obj, void *event_info )
{
	FileOpen * lpThis = (FileOpen *)data;
	const char *selected_filepath = (const char *)event_info;

	do
	{
		struct stat st;
		stat( selected_filepath, &st );
		if( NULL != selected_filepath )
		{
			if( ( st.st_mode & S_IFREG ) != S_IFREG )
			{
				break;
			}
			else
			{
				lpThis->setFilePath( selected_filepath );

				lpThis->getCallback()( lpThis->getUserData() );
			}
		}

		if( lpThis->m_Evas != NULL )
		{
			Evas_Object * content = elm_win_inwin_content_unset( lpThis->m_Evas );

			evas_object_del( content );
			evas_object_del( lpThis->m_Evas );

			lpThis->m_Evas = NULL;
		}

	}while( false );
}

void FileOpen::fs_done( void * data, Evas_Object *obj, void * event_info )
{
	FileOpen * lpThis = (FileOpen *)data;
	const char *selected_filepath = (const char *)event_info;

	do
	{
		struct stat st;
		stat( selected_filepath, &st );
		if( NULL == selected_filepath )
		{
			lpThis->clearResources();
			break;
		}
		if( ( st.st_mode & S_IFREG ) != S_IFREG )
		{
			break;
		}
		else
		{
			lpThis->setFilePath( selected_filepath );

			lpThis->clearResources();

			lpThis->getCallback()( lpThis->getUserData() );
		}

	}while( false );
}

FileOpen::FileOpen() : m_Parent( NULL ), m_Callback( NULL ), m_UserData( NULL ), m_Evas( NULL )
{

}

FileOpen::~FileOpen()
{
}

void FileOpen::Open()
{
	Evas_Object * inwin = elm_win_inwin_add( m_Parent );

	Evas_Object * fs = elm_fileselector_add( inwin );
	evas_object_size_hint_align_set( fs, EVAS_HINT_FILL, EVAS_HINT_FILL );
	evas_object_size_hint_weight_set( fs, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND );
	elm_fileselector_button_inwin_mode_set( fs, EINA_TRUE );
	elm_fileselector_expandable_set( fs, EINA_FALSE);
	elm_fileselector_path_set( fs, "./");
	elm_fileselector_mode_set( fs, ELM_FILESELECTOR_LIST);
	evas_object_smart_callback_add( fs, "done", fs_done, this );
	evas_object_smart_callback_add( fs, "selected", fs_selected, this );

	Evas_Object * bx = elm_box_add( inwin );
	elm_box_horizontal_set( bx, EINA_FALSE );
	evas_object_size_hint_weight_set( bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND );
	elm_win_resize_object_add( inwin, bx );

	elm_box_pack_end( bx, fs );

	evas_object_show( bx );
	evas_object_show( fs );

	elm_win_inwin_content_set( inwin, bx );
	evas_object_show( inwin );

	m_Evas = inwin;
}

void FileOpen::clearResources()
{
	if( m_Evas != NULL )
	{
		Evas_Object * content = elm_win_inwin_content_unset( m_Evas );

		evas_object_del( content );
		evas_object_del( m_Evas );

		m_Evas = NULL;
	}
}

string FileOpen::getFilePath() const
{
	return m_Filepath;
}

FileOpenSuccessCallback FileOpen::getCallback() const
{
	return m_Callback;
}

void * FileOpen::getUserData() const
{
	return m_UserData;
}

void FileOpen::setFilePath( const char * filepath )
{
	m_Filepath = filepath;
}

void FileOpen::setParent( Evas_Object * parent )
{
	m_Parent = parent;
}

void FileOpen::setCallback( FileOpenSuccessCallback callback )
{
	m_Callback = callback;
}

void FileOpen::setUserData( void * userData )
{
	m_UserData = userData;
}

FileOpen & FileOpen::getInstance()
{
	static FileOpen instance;
	return instance;
}













