
#include "..\include\MediaLoader.h"

namespace medialoader
{
	namespace Image
	{

		inline MEDIALOADERAPI int ByteCount(const PIXELFORMAT format)
		{
			switch (format)
			{
			case PIXELFORMAT_RGB:
			case PIXELFORMAT_BGR:
				return 3;
				break;
			case PIXELFORMAT_RGBA:
			case PIXELFORMAT_ARGB:
			case PIXELFORMAT_BGRA:
			case PIXELFORMAT_ABGR:
				return 4;
				break;

			default:
				return 0;
				break;
			}
		}
		inline MEDIALOADERAPI bool AlphaFirst(const PIXELFORMAT format)
		{
			switch (format)
			{
			case PIXELFORMAT_ARGB:
			case PIXELFORMAT_ABGR:
				return true;
				break;

			default:
				return false;
				break;
			}
		}
		inline MEDIALOADERAPI bool HasAlpha(const PIXELFORMAT format)
		{
			switch (format)
			{
			case PIXELFORMAT_RGBA:
			case PIXELFORMAT_ARGB:
			case PIXELFORMAT_BGRA:
			case PIXELFORMAT_ABGR:
				return true;
				break;

			default:
				return false;
				break;
			}
		}
		inline MEDIALOADERAPI EncodedPixel EncodeColor(const Color& color, const PIXELFORMAT format)
		{
			unsigned char r = unsigned char(color.r * 255.0f);
			unsigned char g = unsigned char(color.g * 255.0f);
			unsigned char b = unsigned char(color.b * 255.0f);
			unsigned char a = unsigned char(color.a * 255.0f);
			EncodedPixel pixel;

			switch (format)
			{
			case PIXELFORMAT_RGB:
				return EncodedPixel(r, g, b, 0x00);
				break;
			case PIXELFORMAT_BGR:
				return EncodedPixel(b, g, r, 0x00);
				break;

			case PIXELFORMAT_RGBA:
				return EncodedPixel(r, g, b, a);
				break;
			case PIXELFORMAT_ARGB:
				return EncodedPixel(a, r, g, b);
				break;
			case PIXELFORMAT_BGRA:
				return EncodedPixel(b, g, r, a);
				break;
			case PIXELFORMAT_ABGR:
				return EncodedPixel(a, b, g, r);
				break;

			default:
				return (EncodedPixel)0x00000000;
			}
		}
		inline MEDIALOADERAPI EncodedPixel EncodePixel(const EncodedPixel& pixel, const PIXELFORMAT internalFormat, const PIXELFORMAT destinationFormat)
		{
			unsigned char r = 0xFF;
			unsigned char g = 0xFF;
			unsigned char b = 0xFF;
			unsigned char a = 0xFF;

			switch (internalFormat)
			{
			case PIXELFORMAT_RGB:
				r = pixel.bytes[1];
				g = pixel.bytes[2];
				b = pixel.bytes[3];
				break;
			case PIXELFORMAT_BGR:
				b = pixel.bytes[1];
				g = pixel.bytes[2];
				r = pixel.bytes[3];
				break;

			case PIXELFORMAT_RGBA:
				r = pixel.bytes[0];
				g = pixel.bytes[1];
				b = pixel.bytes[2];
				a = pixel.bytes[3];
				break;
			case PIXELFORMAT_ARGB:
				a = pixel.bytes[0];
				r = pixel.bytes[1];
				g = pixel.bytes[2];
				b = pixel.bytes[3];
				break;
			case PIXELFORMAT_BGRA:
				b = pixel.bytes[0];
				g = pixel.bytes[1];
				r = pixel.bytes[2];
				a = pixel.bytes[3];
				break;
			case PIXELFORMAT_ABGR:
				a = pixel.bytes[0];
				b = pixel.bytes[1];
				g = pixel.bytes[2];
				r = pixel.bytes[3];
				break;

			default:
				break;
			}
			switch (destinationFormat)
			{
			case PIXELFORMAT_RGB:
			case PIXELFORMAT_ARGB:
				return EncodedPixel(a, r, g, b);
				break;
			case PIXELFORMAT_BGR:
			case PIXELFORMAT_ABGR:
				return EncodedPixel(a, b, g, r);
				break;

			case PIXELFORMAT_RGBA:
				return EncodedPixel(r, g, b, a);
				break;
			case PIXELFORMAT_BGRA:
				return EncodedPixel(b, g, r, a);
				break;

			default:
				return EncodedPixel();
				break;
			}
		}
		inline MEDIALOADERAPI Color PackPixel(const EncodedPixel& pixel, const PIXELFORMAT format)
		{
			unsigned char a = 0xFF;
			unsigned char r = 0xFF;
			unsigned char g = 0xFF;
			unsigned char b = 0xFF;

			switch (format)
			{
			case PIXELFORMAT_RGB:
				r = pixel.bytes[1];
				g = pixel.bytes[2];
				b = pixel.bytes[3];
				break;
			case PIXELFORMAT_BGR:
				b = pixel.bytes[1];
				g = pixel.bytes[2];
				r = pixel.bytes[3];
				break;

			case PIXELFORMAT_RGBA:
				r = pixel.bytes[0];
				g = pixel.bytes[1];
				b = pixel.bytes[2];
				a = pixel.bytes[3];
				break;
			case PIXELFORMAT_ARGB:
				a = pixel.bytes[0];
				r = pixel.bytes[1];
				g = pixel.bytes[2];
				b = pixel.bytes[3];
				break;
			case PIXELFORMAT_BGRA:
				b = pixel.bytes[0];
				g = pixel.bytes[1];
				r = pixel.bytes[2];
				a = pixel.bytes[3];
				break;
			case PIXELFORMAT_ABGR:
				a = pixel.bytes[0];
				b = pixel.bytes[1];
				g = pixel.bytes[2];
				r = pixel.bytes[3];
				break;

			default:
				break;
			}

			return Color(float(r) / 255.0f, float(g) / 255.0f, float(b) / 255.0f, float(a) / 255.0f);
		}

	}
}