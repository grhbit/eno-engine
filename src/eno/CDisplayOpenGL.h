/*
 *  CDisplayOpenGL.h
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 8. 23..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#include "CDisplayNull.h"

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_CLASS_TYPE_BEGIN
	
			class CDisplayOpenGL
				: public CDisplayNull
			{
			public:
				virtual ~CDisplayOpenGL( void ) { }
				
			protected:
			};

		ENO_CLASS_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END

// [skop 7:40 pm Monday. 8.23. 2010. Created.]
