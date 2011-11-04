/*
 *  enoImageLoader.hpp
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 11. 23..
 *  Copyright 2010 g.passcode@gmail.com . All rights reserved.
 *
 */

#pragma once
#include "enoReferenceCounter.hpp"

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_INTERFACE_TYPE_BEGIN

			interface enoImageLoader : public enoReferenceCounter
			{
			protected:
				virtual ~enoImageLoader( void ) { }
			};

typedef enoImageLoader IImageLoader;

		ENO_INTERFACE_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END