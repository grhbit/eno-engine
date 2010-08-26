#include "Texture_BMP.h"

#include <fstream>

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_STRUCT_TYPE_BEGIN

			struct BMPHeader 
			{
				union {
					struct {
						u8 packing_dummy[2];
						u8 magic_number[2];
						u8 bmpfile_size[4];
						u8 reserve1[2];
						u8 reserve2[2];
						u8 offsetdata[4];

						u8 headersize[4];
						u8 width[4];
						u8 height[4];
						u8 colorplane[2];
						u8 colordepth[2];

						u8 compress[4];
						u8 bmpdata_size[4];
						u8 width_res[4];
						u8 height_res[4];
					};

					struct {
						u16 i_packing_dummy;
						u16 i_magic_number;
						u32 i_bmpfile_size;
						u16 i_reserve1;
						u16 i_reserve2;
						u32 i_offsetdata;

						u32 i_headersize;
						u32 i_width;
						u32 i_height;
						u16 i_colorplane;
						u16 i_colordepth;
						u32 i_compress;
						u32 i_bmpdata_size;
						u32 i_width_res;
						u32 i_height_res;
					};
				};
			};

		ENO_STRUCT_TYPE_END
		ENO_CLASS_TYPE_BEGIN
			
			CTexture_BMP::CTexture_BMP(void)
			{
			}
			
			
			CTexture_BMP::~CTexture_BMP(void)
			{
			}

			void CTexture_BMP::load( char* path, u8* buffer )
			{
				std::ifstream fin;
				fin.open(path, std::ios::in);
				BMPHeader header;
				fin.read((c8*)(header.magic_number), sizeof(header));

				fin.close();
			}


		ENO_CLASS_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END