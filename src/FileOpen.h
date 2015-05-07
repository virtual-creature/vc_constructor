/*
 * FileOpen.h
 *
 *  Created on: 7 мая 2015
 *      Author: vadim
 */

#ifndef FILEOPEN_H_
#define FILEOPEN_H_

#include <Elementary.h>
#include <string>
using namespace std;

typedef void (*FileOpenSuccessCallback)( void * userdata );

class FileOpen
{
public:
	FileOpen();
	virtual ~FileOpen();

	string getFilePath() const;

	void setParent( Evas_Object * parent );
	void setCallback( FileOpenSuccessCallback callback );
	void setUserData( void * userData );

	FileOpenSuccessCallback getCallback() const;
	void * getUserData() const;

	void Open();

	static FileOpen & getInstance();

private:

	static void fs_done( void * data, Evas_Object *obj, void * event_info );
	static void fs_selected( void * data, Evas_Object *obj, void *event_info );

	void setFilePath( const char * filepath );
	void clearResources();

	Evas_Object * m_Parent;
	FileOpenSuccessCallback m_Callback;
	void * m_UserData;
	string m_Filepath;

	Evas_Object * m_Evas;

};

#endif /* FILEOPEN_H_ */
