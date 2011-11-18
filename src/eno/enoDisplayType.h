/*
 *  enoTexture.h
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 9. 10..
 *  Copyright 2010 g.passcode@gmail.com . All rights reserved.
 *
 */

#pragma once
#include "enoType.hpp"

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_ENUM_TYPE_BEGIN

			enum EColorFormat {
				ECF_B1, //
				ECF_P4,
				ECF_P8,
				ECF_RGB5,
				ECF_R5G6B5,
				ECF_RGB8,
				ECF_RGBA8,
				ECF_RGBA16,
				ECF_RGBA32F,
			};

		ENO_ENUM_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END

//  [9/10/2010 6:52:35 Ultimate]