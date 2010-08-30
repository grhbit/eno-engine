#pragma once
#include "ITextureLoader.h"

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_CLASS_TYPE_BEGIN

			class CTextureLoader_BMP :
				public interface_type::ITextureLoader
			{
			public:
				CTextureLoader_BMP(void);
				~CTextureLoader_BMP(void);
			};

		ENO_CLASS_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END