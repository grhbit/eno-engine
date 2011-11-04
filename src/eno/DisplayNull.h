/*
 *  DisplayNull.h
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 8. 22..
 *  Copyright 2010 g.passcode@gmail.com . All rights reserved.
 *
 */

#pragma once
#include "enoDisplay.h"

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_CLASS_TYPE_BEGIN

			class DisplayNull
				: public enoDisplay
			{
			public:
				DisplayNull( struct_type::displayParameter& param ):enoDisplay(param) { }
				virtual ~DisplayNull( void ) { }
			protected:
				virtual void Create( void ) { }
				virtual void Destroy( void ) { }
			};

		ENO_CLASS_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END

// [skop 7:21 pm Sunday. 8.22. 2010. Created.]
