
#include "..\include\MediaLoader.h"

namespace medialoader
{

	MEDIALOADERAPI void File::release()
	{
		if (this->_raw != 0)
		{
			delete[] this->_raw;
		}

		this->_raw = 0;
		this->_bytes = 0;
	}

	MEDIALOADERAPI void File::read(String filepath)
	{
		if (filepath.isWhiteSpaceOrEmpty())
		{
			return;
		}

		FILE* file = 0;

		fopen_s(&file, filepath, "r");
		if (file == 0)
		{
			return;
		}

		if (this->_raw != 0)
		{
			delete[] this->_raw;
		}

		rewind(file);
		int size = 0;
		while (fgetc(file) != EOF)
		{
			size++;
			if (feof(file) != 0)
			{
				break;
			}
		}

		if (size < 1)
		{
			fclose(file);
			return;
		}

		size += 1;
		char* buffer = new char[size];
		memset((void*)buffer, 0, size * sizeof(char));

		rewind(file);
		fread((void*)buffer, 1, size - 1, file);
		fclose(file);

		buffer[size - 1] = '\0';

		this->_raw = buffer;
		this->_bytes = size;
	}

	MEDIALOADERAPI void File::write(String filepath)
	{
		FILE* file = fopen(filepath, "w");
		if (file == 0)
		{
			return;
		}

		if (this->_raw != 0)
		{
			delete[] this->_raw;
		}

		fwrite(this->_raw, sizeof(char), this->_bytes, file);
		fclose(file);
	}

	MEDIALOADERAPI bool File::isEmpty() const
	{
		return this->_raw == 0 || this->_bytes < 1;
	}

	MEDIALOADERAPI const char* File::raw() const
	{
		return this->_raw;
	}
	MEDIALOADERAPI const int File::size() const
	{
		return this->_bytes;
	}

}