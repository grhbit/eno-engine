/*
 *  CDisplayNull.h
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 8. 22..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma once
#include "IDisplay.h"

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_CLASS_TYPE_BEGIN

			class CDisplayNull
				: public IDisplay
			{
			public:
				virtual ~CDisplayNull( void ) { }
			protected:
			};

		ENO_CLASS_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END

// [skop 7:21 pm Sunday. 8.22. 2010. Created.]
