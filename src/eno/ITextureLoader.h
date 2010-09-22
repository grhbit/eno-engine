#pragma once
#include "enoType.h"


ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_INTERFACE_TYPE_BEGIN
			interface ITexture;
			
			interface ITextureLoader
			{
			public:
				ITextureLoader(void) { }
				virtual ~ITextureLoader(void) { }

				virtual ITexture* load(const EString& path, ITexture**) = 0;
			};

ENO_INTERFACE_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END