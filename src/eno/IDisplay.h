/*
 *  IDisplay.h
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 8. 23..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma once
#include "dimension2d.h"

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_STRUCT_TYPE_BEGIN

			struct displayParameter {
			public:
				displayParameter( void ) : windowed(true)
				{ }
				
				boolean windowed;
				core::class_type::position2d_template<u32> pos;	//if windowed is false, ignored.
				core::class_type::size2d_template<u32> resolution;
			};

		ENO_STRUCT_TYPE_END

		ENO_INTERFACE_TYPE_BEGIN

			interface IDisplay
			{
			public:
				virtual ~IDisplay( void ) { }
			};

		ENO_INTERFACE_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END