/*
 * ToolbarContentButton.h
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#ifndef ToolbarContentCheck_H_
#define ToolbarContentCheck_H_

#include "ToolbarContentItem.h"
#include "ToolbarContentCheckParams.h"
#include <Evas.h>

class ToolbarContentCheck : public ToolbarContentItem
{
	typedef struct
	{
		void * userData;
		ToolbarContentCheck * lpThis;
	} CallbackData;

public:
	ToolbarContentCheck( ToolbarContentCheckParams & params );
	virtual ~ToolbarContentCheck();

	static void on_click( void *data, Evas_Object *e, void *event_info );

	void create( Evas_Object * parent );
	Evas_Object * getEvas() const;

private:

	CallbackData m_callbackData;
};

#endif /* ToolbarContentCheck_H_ */
