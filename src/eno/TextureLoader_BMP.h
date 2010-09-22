#pragma once
#include "ITextureLoader.h"

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_CLASS_TYPE_BEGIN

			class CTextureLoader_BMP :
				public interface_type::ITextureLoader
			{
			public:
				CTextureLoader_BMP(void) { }
				/* virtual */ ~CTextureLoader_BMP(void) { }

				/* virtual */ ITexture* load( const EString& path, ITexture** );
			};

		ENO_CLASS_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END