
#include "..\include\MediaLoader.h"

namespace medialoader
{
	namespace Image
	{

		class BmpFileStream
		{
		public:

			static void read(Surface* track, String filepath);
			static void write(Surface* track, String filepath);

		};

		class TgaFileStream
		{
		public:

			static void read(Surface* track, String filepath);
			static void write(Surface* track, String filepath);

		};

		class PngFileStream
		{
		public:

			static void read(Surface* track, String filepath);
			static void write(Surface* track, String filepath);

		};

		class JpgFileStream
		{
		public:

			static void read(Surface* track, String filepath);
			static void write(Surface* track, String filepath);

		};

		MEDIALOADERAPI void Surface::release()
		{
			if (this->_map != 0)
			{
				delete[] this->_map;
			}

			this->_map = 0;
		}

		MEDIALOADERAPI void Surface::read(String filepath)
		{
			if (filepath.endsWith(".bmp"))
			{
				BmpFileStream::read(this, filepath);
			}
			else if (filepath.endsWith(".tga"))
			{
				TgaFileStream::read(this, filepath);
			}
			else if (filepath.endsWith(".png"))
			{
				PngFileStream::read(this, filepath);
			}
			else if (filepath.endsWith(".jpg") || filepath.endsWith(".jpeg"))
			{
				JpgFileStream::read(this, filepath);
			}
		}

		MEDIALOADERAPI void Surface::write(String filepath)
		{
			if (filepath.endsWith(".bmp"))
			{
				BmpFileStream::write(this, filepath);
			}
			else if (filepath.endsWith(".tga"))
			{
				TgaFileStream::write(this, filepath);
			}
			else if (filepath.endsWith(".png"))
			{
				PngFileStream::write(this, filepath);
			}
			else if (filepath.endsWith(".jpg") || filepath.endsWith(".jpeg"))
			{
				JpgFileStream::write(this, filepath);
			}
		}

		MEDIALOADERAPI void Surface::blit(void* raw, int width, int height, PIXELFORMAT internalFormat)
		{
			if (this->isEmpty())
			{
				this->_width = width;
				this->_height = height;
				this->_format = internalFormat;
				this->_map = new EncodedPixel[this->_width * this->_height];
				memset(this->_map, 0, sizeof(EncodedPixel) * this->_width * this->_height);
			}

			char* read = (char*)raw;
			int byteCount = ByteCount(internalFormat);
			bool fourChannels = byteCount > 3;
			bool alphaFirst = AlphaFirst(internalFormat);
			width = min(width, this->_width);
			height = min(height, this->_height);
			for (int i = 0; i < height; i++)
			{
				for (int k = 0; k < width; k++)
				{
					unsigned char a = 0xFF;
					if (alphaFirst && fourChannels)
					{
						a = *read;
						read++;
					}

					unsigned char c1 = *read;
					read++;
					unsigned char c2 = *read;
					read++;
					unsigned char c3 = *read;
					read++;
					if (!alphaFirst && fourChannels)
					{
						a = *read;
						read++;
					}

					EncodedPixel packed;
					if (alphaFirst || !fourChannels)
					{
						packed = EncodedPixel(a, c1, c2, c3);
					}
					else
					{
						packed = EncodedPixel(c1, c2, c3, a);
					}

					EncodedPixel* destination = this->_map + ((this->_width * (i % this->_height)) + (k % this->_width));
					if (this->_format == internalFormat)
					{
						*destination = packed;
					}
					else
					{
						*destination = EncodePixel(packed, internalFormat, this->_format);
					}
				}
			}
		}
		MEDIALOADERAPI void Surface::blit(Surface* surface)
		{
			if (surface == 0)
			{
				return;
			}

			if (this->isEmpty())
			{
				this->_width = surface->_width;
				this->_height = surface->_height;
				this->_format = surface->_format;
				this->_map = new EncodedPixel[this->_width * this->_height];
				memset(this->_map, 0, sizeof(EncodedPixel) * this->_width * this->_height);
			}

			int width = min(this->_width, surface->_width);
			int height = min(this->_height, surface->_height);
			for (int i = 0; i < height; i++)
			{
				for (int k = 0; k < width; k++)
				{
					this->_map[(this->_width * (i % this->_height)) + (k % this->_width)] =
						surface->_map[(surface->_width * (i % surface->_height)) + (k % surface->_width)];
				}
			}
		}

		MEDIALOADERAPI void Surface::resize(int width, int height)
		{
			width = max(width, 1);
			height = max(height, 1);
			EncodedPixel* map = new EncodedPixel[width * height];
			memset(map, 0, sizeof(EncodedPixel) * width * height);

			if (!this->isEmpty())
			{
				for (int i = 0; i < height; i++)
				{
					memcpy(map + (this->_width * i), this->_map + (i * this->_width), sizeof(EncodedPixel) * this->_width);
				}

				delete[] this->_map;
			}

			this->_width = width;
			this->_height = height;
			this->_map = map;
		}
		MEDIALOADERAPI void Surface::reformat(PIXELFORMAT destination)
		{
			if (this->_format == destination)
			{
				return;
			}

			int size = this->_width * this->_height;
			EncodedPixel* read = this->_map;
			for (int i = 0; i < size; i++)
			{
				EncodedPixel source = *read;
				*read = EncodePixel(source, this->_format, destination);
				read++;
			}

			this->_format = destination;
		}

		MEDIALOADERAPI void Surface::put(int x, int y, EncodedPixel& pixel)
		{
			int index = (this->_width * (y % this->_height)) + (x % this->_width);

#if 0
			switch (this->format)
			{
			case PIXELFORMAT_RGB:
			case PIXELFORMAT_BGR:
				this->operator[](index) = pixel;
				break;

			case PIXELFORMAT_RGBA:
			case PIXELFORMAT_ARGB:
			case PIXELFORMAT_BGRA:
			case PIXELFORMAT_ABGR:
				BlendPixel(this->operator[](index), pixel, this->format);
				break;

			default:
				break;
			}
#else
			if (this->_map != 0)
			{
				this->_map[index] = pixel;
			}
#endif
		}
		MEDIALOADERAPI void Surface::put(int x, int y, Color& color)
		{
			this->put(x, y, EncodeColor(color, this->_format));
		}
		MEDIALOADERAPI EncodedPixel& Surface::get(int x, int y)
		{
			if (this->isEmpty())
			{
				this->resize(1, 1);
			}

			return this->_map[(this->_width * (y % this->_height)) + (x % this->_width)];
		}

		MEDIALOADERAPI bool Surface::isEmpty() const
		{
			return this->_map == 0 || this->_format == PIXELFORMAT_NONE || (this->_width < 1 && this->_height < 1);
		}

		MEDIALOADERAPI const int Surface::width() const
		{
			return this->_width;
		}
		MEDIALOADERAPI const int Surface::height() const
		{
			return this->_height;
		}
		MEDIALOADERAPI const PIXELFORMAT Surface::format() const
		{
			return this->_format;
		}
		MEDIALOADERAPI const EncodedPixel* Surface::map() const
		{
			return this->_map;
		}

		MEDIALOADERAPI Surface::operator EncodedPixel*() const
		{
			return this->_map;
		}
		MEDIALOADERAPI EncodedPixel& Surface::operator[](const int index)
		{
			return this->_map[index % (this->_width * this->_height)];
		}

		void BmpFileStream::read(Surface* surface, String filepath)
		{
			if (surface == 0 || filepath.isWhiteSpaceOrEmpty())
			{
				return;
			}

			FILE* file = 0;

			fopen_s(&file, filepath, "rb");
			if (file == 0)
			{
				return;
			}

			__int16 type;
			struct
			{
				__int32 size;
				__int32 reserved;
				__int32 offset;
				__int32 header;
				__int32 width;
				__int32 height;
				__int16 planes;
				__int16 bitsPerPixel;
				__int32 type;
				__int32 bytes;
				__int32 horizontal;
				__int32 vertical;
				__int32 colors;
				__int32 importantColors;
			} header;

			int h = sizeof(header);
			fread(&type, 1, 2, file);
			fread(&header, 52, 1, file);

			if (memcmp(&type, "BM", 2) != 0 ||
				header.reserved != 0 ||
				header.planes != 1 ||
				header.width < 1 ||
				header.height < 1)
			{
				fclose(file);
				return;
			}

			fseek(file, header.offset, SEEK_SET);

			int byteCount = header.bitsPerPixel / 8;
			PIXELFORMAT format = PIXELFORMAT_NONE;
			switch (byteCount)
			{
			case 3:
				format = PIXELFORMAT_BGR;
				break;
			case 4:
				format = PIXELFORMAT_BGRA;
				break;
			default:
				fclose(file);
				return;
			}

			int bufferSize = header.width * header.height * byteCount;
			char* buffer = new char[bufferSize];
			memset((void*)buffer, 0, bufferSize * sizeof(char));

			fread(buffer, sizeof(char), bufferSize, file);
			fclose(file);

			surface->blit(buffer, header.width, header.height, format);

			delete[] buffer;
		}
		void BmpFileStream::write(Surface* surface, String filepath)
		{
			if (surface == 0 || surface->isEmpty() || filepath.isWhiteSpaceOrEmpty())
			{
				return;
			}

			FILE* file = 0;

			fopen_s(&file, filepath, "wb");
			if (file == 0) return;

			PIXELFORMAT format = surface->_format;
			surface->reformat(PIXELFORMAT_BGRA);

			int byteCount = ByteCount(surface->_format);
			int bufferSize = surface->_width * surface->_height * byteCount;

			char* info = new char[54];
			memset(info, 0, sizeof(char) * 54);

			info[0] = 'B';
			info[1] = 'M';
			*(int*)(&info[2]) = 54 + bufferSize;
			*(int*)(&info[10]) = 54;
			*(int*)(&info[14]) = 40;
			*(int*)(&info[18]) = surface->_width;
			*(int*)(&info[22]) = surface->_height;
			*(int*)(&info[26]) = (short)1;
			*(int*)(&info[28]) = byteCount * 8;
			*(int*)(&info[34]) = bufferSize;

			fwrite(info, sizeof(char), 54, file);
			fwrite(surface->_map, sizeof(char), bufferSize, file);
			fclose(file);

			delete[] info;

			surface->reformat(format);
		}

		void TgaFileStream::read(Surface* surface, String filepath)
		{
			if (surface == 0 || filepath.isWhiteSpaceOrEmpty())
			{
				return;
			}

			FILE* file = 0;

			fopen_s(&file, filepath, "rb");
			if (file == 0)
			{
				return;
			}

			struct
			{
				__int8 indent;
				__int8 mapType;
				__int8 imageType;
				__int8 mapStart[2];
				__int8 mapLength[2];
				__int8 mapDepth;
				__int16 xOffset;
				__int16 yOffset;
				__int16 width;
				__int16 height;
				__int8 bitDepth;
				__int8 descriptor;
			} header;

			fread(&header, 18, 1, file);

			if (header.mapType != 0 || header.imageType != 2 || header.width < 1 || header.height < 1)
			{
				fclose(file);
				return;
			}

			int byteCount = header.bitDepth / 8;
			if (byteCount != 3 && byteCount != 4)
			{
				fclose(file);
				return;
			}

			PIXELFORMAT format = PIXELFORMAT_NONE;
			switch (byteCount)
			{
			case 3:
				format = PIXELFORMAT_BGR;
				break;
			case 4:
				format = PIXELFORMAT_BGRA;
				break;
			default:
				fclose(file);
				return;
			}

			int bufferSize = header.width * header.height * byteCount;
			char* buffer = new char[bufferSize];
			memset(buffer, 0, sizeof(char) * bufferSize);

			fread(buffer, sizeof(char), bufferSize, file);
			fclose(file);

			surface->blit(buffer, header.width, header.height, format);

			delete[] buffer;
		}
		void TgaFileStream::write(Surface* surface, String filepath)
		{
			if (surface == 0 || surface->isEmpty() || filepath.isWhiteSpaceOrEmpty())
			{
				return;
			}

			FILE* file = 0;

			fopen_s(&file, filepath, "wb");
			if (file == 0)
			{
				return;
			}

			PIXELFORMAT format = surface->_format;
			surface->reformat(PIXELFORMAT_BGRA);

			char* type = new char[4];
			char* info = new char[6];
			memset(type, 0, sizeof(char) * 4);
			memset(info, 0, sizeof(char) * 6);

			int byteCount = ByteCount(surface->_format);
			int bufferSize = surface->_width * surface->_height * byteCount;

			type[2] = 2;
			*(int*)(&info[0]) = surface->_width;
			*(int*)(&info[2]) = surface->_height;
			info[4] = byteCount * 8;

			fwrite(type, sizeof(char), 3, file);
			fseek(file, 12, SEEK_SET);
			fwrite(info, sizeof(char), 6, file);

			fwrite(surface->_map, sizeof(char), bufferSize, file);
			fclose(file);

			delete[] info;
			delete[] type;

			surface->reformat(format);
		}

		void PngFileStream::read(Surface* surface, String filepath)
		{
			if (surface == 0 || filepath.isWhiteSpaceOrEmpty())
			{
				return;
			}

			FILE* file = fopen(filepath, "rb");
			if (file == 0)
			{
				return;
			}

			char* header = new char[8];
			fread(header, 1, 8, file);

			if (png_sig_cmp((png_const_bytep)header, 0, 8) == 0)
			{
				png_struct* data = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
				if (data != 0)
				{
					png_info* info = png_create_info_struct(data);
					if (info != 0)
					{
						if (setjmp(png_jmpbuf(data)) == 0)
						{
							png_init_io(data, file);
							png_set_sig_bytes(data, 8);
							png_read_info(data, info);

							png_uint_32 width = png_get_image_width(data, info);
							png_uint_32 height = png_get_image_height(data, info);
							png_byte colorType = png_get_color_type(data, info);
							png_byte bitDepth = png_get_bit_depth(data, info);

							int passes = png_set_interlace_handling(data);
							png_read_update_info(data, info);

							if (setjmp(png_jmpbuf(data)) == 0)
							{
								png_size_t stride = png_get_rowbytes(data, info);
								png_byte* buffer = new png_byte[height * stride];
								png_bytep* rows = new png_bytep[height];
								for (png_uint_32 k = 0; k < height; k++)
								{
									rows[k] = buffer + (stride * (height - (k + 1)));
								}

								png_read_image(data, rows);

								PIXELFORMAT format = PIXELFORMAT::PIXELFORMAT_NONE;
								switch (colorType)
								{
								case PNG_COLOR_TYPE_RGB:
									format = PIXELFORMAT::PIXELFORMAT_RGB;
									break;
								case PNG_COLOR_TYPE_RGBA:
									format = PIXELFORMAT::PIXELFORMAT_RGBA;
									break;
								default:
									break;
								}

								surface->blit(buffer, (int)width, (int)height, format);

								delete[] rows;
								delete[] buffer;
							}
						}
					}
				}
			}

			delete[] header;
			fclose(file);
		}
		void PngFileStream::write(Surface* surface, String filepath)
		{
			if (surface == 0 || surface->isEmpty() || filepath.isWhiteSpaceOrEmpty())
			{
				return;
			}

			FILE* file = fopen(filepath, "wb");
			if (file == 0)
			{
				return;
			}

			PIXELFORMAT format = surface->_format;
			surface->reformat(PIXELFORMAT_RGBA);

			png_struct* data = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
			if (data != 0)
			{
				png_info* info = png_create_info_struct(data);
				if (info != 0)
				{
					if (setjmp(png_jmpbuf(data)) == 0)
					{
						png_init_io(data, file);

						if (setjmp(png_jmpbuf(data)) == 0)
						{
							png_set_IHDR(data, info, surface->_width, surface->_height, 8,
								PNG_COLOR_TYPE_RGBA,
								PNG_INTERLACE_NONE,
								PNG_COMPRESSION_TYPE_BASE,
								PNG_FILTER_TYPE_BASE);
							png_write_info(data, info);

							if (setjmp(png_jmpbuf(data)) == 0)
							{
								png_size_t stride = png_get_rowbytes(data, info);
								png_bytep* rows = new png_bytep[surface->_height];
								for (int k = 0; k < surface->_height; k++)
								{
									rows[k] = (png_bytep)(surface->_map + (surface->_width * (surface->_height - (k + 1))));
								}

								png_write_image(data, rows);

								if (setjmp(png_jmpbuf(data)) == 0)
								{
									png_write_end(data, info);
								}

								delete[] rows;
							}
						}
					}
				}
			}

			surface->reformat(format);
			fclose(file);
		}

		void JpgFileStream::read(Surface* surface, String filepath)
		{
			if (surface == 0 || filepath.isWhiteSpaceOrEmpty())
			{
				return;
			}

			throw std::exception("not implemented");
		}
		void JpgFileStream::write(Surface* surface, String filepath)
		{
			if (surface == 0 || filepath.isWhiteSpaceOrEmpty())
			{
				return;
			}

			throw std::exception("not implemented");
		}

	}
}