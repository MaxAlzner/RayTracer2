
#include "..\include\MediaLoader.h"

namespace medialoader
{
	namespace Sound
	{

		class WavFileStream
		{
		public:

			static void read(Track* track, String filepath);
			static void write(Track* track, String filepath);

		};

		class OggFileStream
		{
		public:

			static void read(Track* track, String filepath);
			static void write(Track* track, String filepath);

		};

		MEDIALOADERAPI void Track::release()
		{
			if (this->_stream != 0)
			{
				delete[] this->_stream;
			}
		}

		MEDIALOADERAPI void Track::read(String filepath)
		{
			if (filepath.endsWith(".wav"))
			{
				WavFileStream::read(this, filepath);
			}
			else if (filepath.endsWith(".ogg"))
			{
				OggFileStream::read(this, filepath);
			}
		}

		MEDIALOADERAPI void Track::write(String filepath)
		{
			if (filepath.endsWith(".wav"))
			{
				WavFileStream::write(this, filepath);
			}
			else if (filepath.endsWith(".ogg"))
			{
				OggFileStream::write(this, filepath);
			}
		}

		MEDIALOADERAPI bool Track::isEmpty() const
		{
			return this->_stream == 0 || this->_channels == 0 || this->_frequency == 0 || this->_samples == 0 || this->_byteDepth == 0 || this->_duration < 0.0f;
		}

		MEDIALOADERAPI const int Track::channels() const { return this->_channels; }
		MEDIALOADERAPI const int Track::frequency() const { return this->_frequency; }
		MEDIALOADERAPI const int Track::samples() const { return this->_samples; }
		MEDIALOADERAPI const int Track::byteDepth() const { return this->_byteDepth; }
		MEDIALOADERAPI const float Track::duration() const { return this->_duration; }
		MEDIALOADERAPI const void* Track::stream() const { return this->_stream; }

		void WavFileStream::read(Track* track, String filepath)
		{
			if (track == 0 || filepath.isWhiteSpaceOrEmpty())
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
				__int8 fileDesc[4];
				__int32 size;
				__int8 waveDesc[4];
				__int8 formatDesc[4];
				__int32 chunkSize;
				__int16 type;
				__int16 channels;
				__int32 frequency;
				__int32 speed;
				__int16 alignment;
				__int16 bitsPerSample;
				__int8 data[4];
				__int32 bytes;
			} header;

			fread(&header, sizeof(header), 1, file);

			if (memcmp(header.fileDesc, "RIFF", 4) != 0 ||
				memcmp(header.waveDesc, "WAVE", 4) != 0 ||
				memcmp(header.formatDesc, "fmt ", 4) != 0 ||
				header.chunkSize != 16 ||
				header.type != 1 ||
				!(header.channels == 1 || header.channels == 2) ||
				!(header.frequency == 44100 || header.frequency == 22050) ||
				memcmp(header.data, "data", 4) != 0)
			{
				fclose(file);
				return;
			}

			track->_channels = header.channels;
			track->_frequency = header.frequency;
			track->_byteDepth = header.bitsPerSample / 8;
			track->_samples = header.bytes / (track->_byteDepth * track->_channels);
			track->_duration = float(track->_samples) / float(track->_frequency);
			track->_stream = new __int8[header.bytes];
			memset(track->_stream, 0, header.bytes);
			fread(track->_stream, 1, header.bytes, file);

			fclose(file);
		}
		void WavFileStream::write(Track* track, String filepath)
		{
			if (track == 0 || filepath.isWhiteSpaceOrEmpty())
			{
				return;
			}

			FILE* file = 0;
			fopen_s(&file, filepath, "wb");
			if (file == 0)
			{
				return;
			}

			__int32 bytes = track->_samples * track->_channels * track->_byteDepth;
			__int32 size = bytes + 36;
			__int32 chunk = 16;
			__int16 pcm = 1;
			__int32 speed = track->_frequency * track->_channels * track->_byteDepth;
			__int16 blockAlign = track->_channels * track->_byteDepth;
			__int16 bitsPerSample = track->_byteDepth * 8;
			fwrite("RIFF", 1, 4, file);
			fwrite(&size, 4, 1, file);
			fwrite("WAVE", 1, 4, file);
			fwrite("fmt ", 1, 4, file);
			fwrite(&chunk, 4, 1, file);
			fwrite(&pcm, 2, 1, file);
			fwrite(&track->_channels, 2, 1, file);
			fwrite(&track->_frequency, 4, 1, file);
			fwrite(&speed, 4, 1, file);
			fwrite(&blockAlign, 2, 1, file);
			fwrite(&bitsPerSample, 2, 1, file);
			fwrite("data", 1, 4, file);
			fwrite(&bytes, 4, 1, file);
			fwrite(track->_stream, track->_byteDepth, track->_samples * track->_channels, file);
			fclose(file);
		}

		void OggFileStream::read(Track* track, String filepath)
		{
			if (track == 0 || filepath.isWhiteSpaceOrEmpty())
			{
				return;
			}

			FILE* file = 0;
			fopen_s(&file, filepath, "rb");
			if (file == 0)
			{
				return;
			}

			fclose(file);
		}
		void OggFileStream::write(Track* track, String filepath)
		{
			if (track == 0 || filepath.isWhiteSpaceOrEmpty())
			{
				return;
			}
		}

	}
}