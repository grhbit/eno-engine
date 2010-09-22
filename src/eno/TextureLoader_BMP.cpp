#include "TextureLoader_BMP.h"
#include "Texture.h"
#include "enoDisplayType.h"

#include <fstream>

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_STRUCT_TYPE_BEGIN

			struct BitmapHeader
			{
				union {
					struct {
						c8 packing_dummy[2];
						c8 buffer[14];
					};

					struct {
						u16 dummy;
						u16 magic_number;
						u32 bmpfile_size;
						u16 reserve1;
						u16 reserve2;
						u32 offset;
					};
				};

				enum {
					buffer_size = sizeof(c8[14])
				};

				BitmapHeader(void) {
					memset(packing_dummy, 0, sizeof(packing_dummy));
				}
			};

			struct BitmapInfo {
				union {
					c8 buffer[124];

					struct {
						u32	structSize;
						s32	width;
						s32	height;
						u16	colorPlanes;
						u16	colorDepth;
						u32	compression;
						u32	sizeImage;
						s32	xPelsPerMeter;
						s32	yPelsPerMeter;
						u32	colorUsed;
						u32	colorImportant;
						/*
						u32	redMask;
						u32	greenMask;
						u32	blueMask;
						u32	alphaMask;
						u32	CSType;
						struct endpoints {
							typedef struct colorXYZ{ u32 x, y, z; };
							colorXYZ red;
							colorXYZ green;
							colorXYZ blue;
						};
						u32	gammaRed;
						u32	gammaGreen;
						u32	gammaBlue;
						u32	intent;
						u32	profileData;
						u32	profileSize;
						u32	reserved;
						*/
					};
				};

				enum {
					/*
					struct_size_v1 = 12,
					struct_size_v2 = 64,
					*/
					struct_size_v3 = 40,
					/*
					struct_size_v4 = 108,
					struct_size_v5 = 124,
					*/
					buffer_size = 124
				};
			};

		ENO_STRUCT_TYPE_END
		ENO_CLASS_TYPE_BEGIN

		ITexture* class_type::CTextureLoader_BMP::load( const EString& path, ITexture** tex )
		{
			ITexture* ret = nullptr;

			if (tex == nullptr || *tex == nullptr)
				ret = new CTexture;
			else
				ret = *tex;

			std::ifstream filein;
			filein.open(path, std::ios::binary);

			BitmapHeader header;
			header.buffer;

			filein.read(header.buffer, struct_type::BitmapHeader::buffer_size);

			if (filein.gcount() != struct_type::BitmapHeader::buffer_size) {
			}

			u32 structsize = 0;
			filein.read(reinterpret_cast<c8*>(&structsize), sizeof(structsize));

			if (filein.gcount() != sizeof(structsize)) {
			}

			filein.seekg(-static_cast<std::ifstream::off_type>(sizeof(structsize)), std::ios::cur);

			s32 width = 0, height = 0;
			u16 colorDepth = 0;

			if (structsize > BitmapInfo::struct_size_v3)
				structsize = BitmapInfo::struct_size_v3;

			BitmapInfo info;
			filein.read(info.buffer, structsize);

			width = info.width;
			height = info.height;
			colorDepth = info.colorDepth;

			ret->init(width, height);

			if (colorDepth < 4)
				return nullptr;

			const u16 pitch = (colorDepth < 4)? colorDepth:colorDepth/6;
 			u8* buffer = new u8[width * height * pitch];
			ret->bind(buffer);

			u32* dst = reinterpret_cast<u32*>(buffer);
			s32 extraPixel = width % 4;
			s32 widthPixel = (width - extraPixel)/4;

			for (s32 y = 0; y<height; y++) {
				for (s32 x = 0; x<widthPixel; x++) {
/*
					*dst = 0xffffffff;
					++dst;
					*dst = 0xffffffff;
					++dst;
					*dst = 0xffffffff;
					++dst;
					*dst = 0xffffffff;
					++dst;
*/
					dst[0] = 0xffffffff;
					dst[1] = 0xffffffff;
					dst[2] = 0xffffffff;
					dst[3] = 0xffffffff;
					dst += pitch;
				}

				for (s32 x = 0; x<extraPixel; x++) {
					*dst = 0xffffffff;
					++dst;
				}
			}

			filein.close();
/*//
			std::ifstream filein;
			
			filein.open(path, std::ios::binary);

			struct_type::BitmapHeader header;

			filein.read(header.buffer, 
				struct_type::BitmapHeader::buffer_size);

			BitmapInfo_V3 info;
			filein.read(info.buffer,
				struct_type::BitmapInfo_V3::buffer_size);

			filein.seekg(header.offset);

			if (tex != nullptr)
				*tex = ret;

			ret->setWidth(info.width);
			ret->setHeight(info.height);

			u8* buffer = ret->lock();
			buffer = new u8[info.width * info.height * 4];
			ret->bind(buffer);

			for (u32 y = 0; y < info.height; y++) {
				u8 buf[4];

				for (u32 x = 0; x < info.width; x++) {
					filein.read(reinterpret_cast<c8*>(buf), 3);

					buffer[0] = buf[0];
					buffer[1] = buf[1];
					buffer[2] = buf[2];
					buffer[3] = 0xff;

					buffer += 4;
				}
			}

//			delete []buffer;
//*/
			return ret;
		}

		ENO_CLASS_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END
