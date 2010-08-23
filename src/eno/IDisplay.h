/*
 *  IDisplay.h
 *  eno
 *
 *  Created by 권성광 on 10. 8. 23..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma once
#include "enoType.h"


ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_INTERFACE_TYPE_BEGIN

			interface IDisplay
			{
			public:
				
				virtual ~IDisplay( void ) { }
			};

		ENO_INTERFACE_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END