/*
 *  IImageLoader.h
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 11. 23..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma once
#include "IReferenceCounter.h"

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_INTERFACE_TYPE_BEGIN

			interface IImageLoader : public IReferenceCounter
			{
			public:
				
				virtual ~IImageLoader( void ) { }
			};

		ENO_INTERFACE_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END