/*
 *  DisplayD3D9.h
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 12. 22..
 *  Copyright 2010 g.passcode@gmail.com . All rights reserved.
 *
 */

#include "DisplayNull.h"

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_CLASS_TYPE_BEGIN

			class DisplayD3D9
				: public DisplayNull
			{
			public:
				DisplayD3D9( struct_type::displayParameter& param ):DisplayNull(param) { create(); }
				/* virtual */ ~DisplayD3D9( void ) { destroy(); }

			private:
				/* virtual */ void Create( void ) { create(); }
				/* virtual */ void Destroy( void ) { destroy(); }
				
			// no virtual
			private:
				void create( void ) { }
				void destroy( void ) { }
			};

		ENO_CLASS_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END

// [skop 09:55 am Wednesday. 12.22. 2010. Created]