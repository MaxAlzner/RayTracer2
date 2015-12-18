
#include "..\include\MediaLoader.h"

namespace medialoader
{
	
	MEDIALOADERAPI String::String()
	{
		this->source = 0;
		this->count = 0;
		this->bytes = 0;
	}
	MEDIALOADERAPI String::String(const String& str)
	{
		this->source = 0;
		this->count = 0;
		this->bytes = 0;
		this->paste(str);
	}
	MEDIALOADERAPI String::String(const String& str0, const String& str1)
	{
		this->source = 0;
		this->count = 0;
		this->bytes = 0;
		this->paste(str0);
		this->append(str1);
	}
	MEDIALOADERAPI String::String(const char* str)
	{
		this->source = 0;
		this->count = 0;
		this->bytes = 0;
		this->paste(str);
	}
	MEDIALOADERAPI String::String(const char* str0, const char* str1)
	{
		this->source = 0;
		this->count = 0;
		this->bytes = 0;
		this->paste(str0);
		this->append(str1);
	}
	MEDIALOADERAPI String::~String()
	{
		this->resize(0);
	}

	MEDIALOADERAPI bool String::equals(const String& other)
	{
		if (this->count != other.count)
		{
			return false;
		}

		return memcmp(this->source, other.source, sizeof(char) * this->count) == 0;
	}
	MEDIALOADERAPI bool String::equals(const char* other)
	{
		if (other == 0)
		{
			return false;
		}

		int length = strlen(other);
		if (this->count != length)
		{
			return false;
		}

		return memcmp(this->source, other, sizeof(char) * this->count) == 0;
	}
	MEDIALOADERAPI bool String::isEmpty()
	{
		return this->count < 1;
	}
	MEDIALOADERAPI bool String::isWhiteSpaceOrEmpty()
	{
		if (!this->isEmpty())
		{
			char* read = this->source;
			for (int i = 0; i < this->count; i++)
			{
				if (*read != ' ' || *read != '\n')
				{
					return false;
				}

				read++;
			}
		}

		return true;
	}
	MEDIALOADERAPI int String::compare(const String& other)
	{
		int l0 = this->count;
		int l1 = other.count;
		if (l0 < 1 && l1 < 1) return 0;
		if (l0 > 1 && l1 < 1) return 1;
		if (l0 < 1 && l1 > 1) return -1;
		char* read0 = this->source;
		const char* read1 = other;
		for (int i = 0; i < l0 && i < l1; i++)
		{
			if (*read0 < *read1) return -1;
			if (*read0 > *read1) return 1;
			read0++;
			read1++;
		}
		return 0;
	}
	MEDIALOADERAPI int String::compare(const char* other)
	{
		if (other == 0)
		{
			return false;
		}

		int l0 = this->count;
		int l1 = strlen(other);
		if (l0 < 1 && l1 < 1) return 0;
		if (l0 > 1 && l1 < 1) return 1;
		if (l0 < 1 && l1 > 1) return -1;
		char* read0 = this->source;
		const char* read1 = other;
		for (int i = 0; i < l0 && i < l1; i++)
		{
			if (*read0 < *read1) return -1;
			if (*read0 > *read1) return 1;
			read0++;
			read1++;
		}
		return 0;
	}
	MEDIALOADERAPI bool String::contains(const String& other)
	{
		char* read = this->source;
		int compared = 0;
		for (int i = 0; i < this->count; i++)
		{
			if (*read == other[compared])
			{
				compared++;
				if (compared >= other.count)
				{
					return true;
				}
			}
			else if (compared > 0)
			{
				compared = 0;
			}

			read++;
		}
		return false;
	}
	MEDIALOADERAPI bool String::contains(const char ch)
	{
		char* read = this->source;
		for (int i = 0; i < this->count; i++)
		{
			if (*read == ch)
			{
				return true;
			}

			read++;
		}

		return false;
	}
	MEDIALOADERAPI bool String::startsWith(const String& other)
	{
		char* read = this->source;
		if (other.count > this->count)
		{
			return false;
		}

		int compared = 0;
		for (int i = 0; i < this->count; i++)
		{
			if (*read == other[compared])
			{
				compared++;
				if (compared >= other.count)
				{
					return true;
				}
			}
			else
			{
				return false;
			}

			read++;
		}
		return false;
	}
	MEDIALOADERAPI bool String::startsWith(const char* other)
	{
		if (other == 0)
		{
			return false;
		}

		int l = strlen(other);
		char* read = this->source;
		if (l > this->count)
		{
			return false;
		}

		int compared = 0;
		for (int i = 0; i < this->count; i++)
		{
			if (*read == other[compared])
			{
				compared++;
				if (compared >= l)
				{
					return true;
				}
			}
			else
			{
				return false;
			}

			read++;
		}
		return false;
	}
	MEDIALOADERAPI bool String::endsWith(const String& other)
	{
		char* read = this->source + (this->count - 1);
		if (other.count > this->count)
		{
			return false;
		}

		int compared = other.count - 1;
		for (int i = this->count - 1; i >= 0; i--)
		{
			if (*read == other[compared])
			{
				compared--;
				if (compared < 0)
				{
					return true;
				}
			}
			else
			{
				return false;
			}

			read--;
		}
		return false;
	}
	MEDIALOADERAPI bool String::endsWith(const char* other)
	{
		if (other == 0)
		{
			return false;
		}

		int l = strlen(other);
		char* read = this->source + (this->count - 1);
		if (l > this->count)
		{
			return false;
		}

		int compared = l - 1;
		for (int i = this->count - 1; i >= 0; i--)
		{
			if (*read == other[compared])
			{
				compared--;
				if (compared < 0)
				{
					return true;
				}
			}
			else
			{
				return false;
			}

			read--;
		}

		return false;
	}
	//MEDIALOADERAPI int String::indexOf(char ch)
	//{
	//	return 0;
	//}
	//MEDIALOADERAPI int String::indexOf(const String& other)
	//{
	//	return 0;
	//}
	//MEDIALOADERAPI int String::indexOfAny(const String& check)
	//{
	//	return 0;
	//}
	//MEDIALOADERAPI int String::lastIndexOf(char ch)
	//{
	//	return 0;
	//}
	//MEDIALOADERAPI int String::lastIndexOf(const String& other)
	//{
	//	return 0;
	//}
	//MEDIALOADERAPI int String::lastIndexOfAny(const String& check)
	//{
	//	return 0;
	//}
	//
	//MEDIALOADERAPI void String::format(const char*, ... )
	//{
	//	return;
	//}
	MEDIALOADERAPI void String::append(const String& str)
	{
		if (this->count + str.count > this->bytes)
		{
			this->resize(this->count + str.count);
		}

		char* read = this->source + this->count;
		memcpy(this->source + this->count, (const char*)str, sizeof(char) * str.count);
		this->count += str.count;
		this->source[this->count] = '\0';
	}
	MEDIALOADERAPI void String::append(const char* str)
	{
		if (str == 0)
		{
			return;
		}

		int l = strlen(str);
		if (this->count + l >= this->bytes)
		{
			this->resize(this->count + l);
		}

		char* read = this->source + this->count;
		memcpy(this->source + this->count, (const char*)str, sizeof(char) * l);
		this->count += l;
		this->source[this->count] = '\0';
	}
	MEDIALOADERAPI void String::append(const char ch)
	{
		if (this->count + 1 >= this->bytes)
		{
			this->resize(this->count + 1);
		}

		this->source[this->count] = ch;
		this->source[this->count + 1] = '\0';
		this->count++;
	}
	//MEDIALOADERAPI void String::append(const int value)
	//{
	//}
	//MEDIALOADERAPI void String::append(const float value)
	//{
	//}
	//MEDIALOADERAPI void String::remove(const char ch)
	//{
	//	int skip = 0;
	//	for (int i = 0; i < this->count; i++)
	//	{
	//		char read = this->source[i];
	//		if (read == ch) skip++;
	//		if (i < 1) continue;
	//		this->source[i - skip] = read;
	//	}
	//}
	//MEDIALOADERAPI void String::remove(const String& str)
	//{
	//	int skip = 0;
	//	int compared = 0;
	//	for (int i = 0; i < this->count; i++)
	//	{
	//		char read = this->source[i];
	//		if (read == str[compared])
	//		{
	//			skip++;
	//			compared++;
	//			if (compared >= str.length()) compared = 0;
	//		}
	//		if (i < 1) continue;
	//		this->source[i - skip] = read;
	//	}
	//}
	//MEDIALOADERAPI void String::insert(const int start, const char ch)
	//{
	//	if (this->count < 1) return;
	//	if (this->count + 1 > this->bytes) this->resize(this->count + 1);
	//	int index = start % this->count;
	//	char* read0 = this->source + this->count;
	//	char* read1 = read0 + 1;
	//	for (int i = this->count - 1; i >= index; i--)
	//	{
	//		*read1 = *read0;
	//		read0--;
	//		read1--;
	//	}
	//	*read0 = ch;
	//	this->count++;
	//}
	//MEDIALOADERAPI void String::insert(const int start, const String& source)
	//{
	//	if (this->count < 1) return;
	//	if (this->count + source.length() > this->bytes) this->resize(this->count + source.length());
	//	int index = start % this->count;
	//	if (this->count < source.length() + index) return;
	//	char* read0 = this->source + this->count;
	//	char* read1 = read0 + source.length();
	//	for (int i = this->count - 1; i >= index; i--)
	//	{
	//		*read1 = *read0;
	//		read0--;
	//		read1--;
	//	}
	//	memcpy(read0, (const char*)source, sizeof(char) * source.length());
	//	this->count += source.length();
	//}
	//MEDIALOADERAPI void String::replace(const char find, const char add)
	//{
	//	char* read = this->source;
	//	for (int i = 0; i < this->count; i++)
	//	{
	//		if (*read == find) *read = add;
	//		read++;
	//	}
	//}
	//MEDIALOADERAPI void String::replace(const String& find, const String& add)
	//{
	//}
	//MEDIALOADERAPI void String::invert()
	//{
	//	char* read0 = this->source;
	//	char* read1 = this->source + this->count;
	//	int half = this->count / 2;
	//	for (int i = 0; i < half; i++)
	//	{
	//		Math::Swap(*read0, *read1);
	//		read0++;
	//		read1--;
	//	}
	//}
	//MEDIALOADERAPI void String::toLower()
	//{
	//	return;
	//}
	//MEDIALOADERAPI void String::toUpper()
	//{
	//	return;
	//}
	//MEDIALOADERAPI void String::padLeft(const int width)
	//{
	//	return;
	//}
	//MEDIALOADERAPI void String::padLeft(const int width, char pad)
	//{
	//	return;
	//}
	//MEDIALOADERAPI void String::padRight(const int width)
	//{
	//	return;
	//}
	//MEDIALOADERAPI void String::padRight(const int width, char pad)
	//{
	//	return;
	//}
	//MEDIALOADERAPI void String::trim()
	//{
	//	return;
	//}
	//MEDIALOADERAPI void String::trim(const String& check)
	//{
	//	return;
	//}
	MEDIALOADERAPI void String::trimStart(const char check)
	{
		if (this->count > 0)
		{
			char* read = this->source;
			char* trimmed = strchr(read, check);
			this->count = 0;
			while (*read != '\0' && *trimmed != '\0')
			{
				*read = *trimmed;
				read++;
				trimmed++;
				this->count++;
			}

			this->source[this->count] = '\0';
		}
	}
	MEDIALOADERAPI void String::trimEnd(const char check)
	{
		if (this->count > 0)
		{
			char* read = this->source + (this->count - 1);
			for (int i = this->count - 1; i >= 0; i--)
			{
				read--;
				if (*read == check)
				{
					read[1] = '\0';
					this->count = i;
					return;
				}
			}
		}
	}
	//MEDIALOADERAPI void String::removeAfter(int width)
	//{
	//	return;
	//}
	//
	//MEDIALOADERAPI void String::join(const String* list, const int num)
	//{
	//	return;
	//}
	//MEDIALOADERAPI void String::join(const String& separator, const String* list, const int num)
	//{
	//	return;
	//}
	//MEDIALOADERAPI void String::substring(const String* destination, const int start)
	//{
	//	return;
	//}
	//MEDIALOADERAPI void String::substring(const String* destination, const int start, const int end)
	//{
	//	return;
	//}
	//MEDIALOADERAPI void String::split(const String* buffer, int size, const String& seperator)
	//{
	//	return;
	//}

	MEDIALOADERAPI String String::copy()
	{
		return String(this->source);
	}
	//MEDIALOADERAPI void String::copyTo(const int sourceStart, const String& source, const int destinationStart, const int count)
	//{
	//	return;
	//}
	MEDIALOADERAPI void String::paste(const char* str)
	{
		if (str == 0)
		{
			return;
		}

		int length = strlen(str);
		if (this->bytes < length)
		{
			this->resize(length);
		}

		memset(this->source, 0, sizeof(char) * this->bytes);
		memcpy(this->source, str, sizeof(char) * length);
		this->count = length;
	}
	MEDIALOADERAPI void String::paste(const String& str)
	{
		if (this->bytes < str.count)
		{
			this->resize(str.count);
		}

		memset(this->source, 0, sizeof(char) * this->bytes);
		memcpy(this->source, str, sizeof(char) * str.count);
		this->count = str.count;
	}

	MEDIALOADERAPI int String::length()
	{
		return this->count;
	}
	MEDIALOADERAPI int String::capacity()
	{
		return this->bytes;
	}
	MEDIALOADERAPI void String::resize(int bytes)
	{
		if (bytes < 1)
		{
			if (this->source != 0)
			{
				delete[] this->source;
			}

			this->source = 0;
			this->count = 0;
			this->bytes = 0;
			return;
		}

		this->bytes = bytes + 1;
		if (this->count > this->bytes)
		{
			this->count = this->bytes;
		}

		char* old = this->source;
		this->source = new char[this->bytes];
		memset(this->source, 0, sizeof(char) * this->bytes);

		if (old == 0)
		{
			return;
		}

		memcpy(this->source, old, sizeof(char) * this->count);
		delete [] old;
	}
		
	MEDIALOADERAPI void String::operator=(const String& other)
	{
		this->paste(other.source);
	}
	MEDIALOADERAPI void String::operator=(const char* str)
	{
		this->paste(str);
	}
	MEDIALOADERAPI void String::operator=(const char ch)
	{
		this->resize(1);
		this->source[0] = ch;
		this->source[1] = '\0';
	}
	MEDIALOADERAPI String::operator char*() const
	{
		return this->source;
	}
	MEDIALOADERAPI String String::operator+(const String& other)
	{
		return String(*this, other);
	}
	MEDIALOADERAPI String String::operator+(const char* other)
	{
		String clone(*this);
		clone.append(String(other));
		return clone;
	}
	MEDIALOADERAPI String String::operator+(const char ch)
	{
		String clone(*this);
		clone.append(ch);
		return clone;
	}
	//MEDIALOADERAPI String String::operator-(const String& other)
	//{
	//	String clone(*this);
	//	clone.remove(other);
	//	return clone;
	//}
	//MEDIALOADERAPI String String::operator-(const char* other)
	//{
	//	String clone(*this);
	//	clone.remove(String(other));
	//	return clone;
	//}
	//MEDIALOADERAPI String String::operator-(const char ch)
	//{
	//	String clone(*this);
	//	clone.remove(ch);
	//	return clone;
	//}
	MEDIALOADERAPI bool String::operator==(const String& other)
	{
		return this->equals(other);
	}
	MEDIALOADERAPI bool String::operator==(const char* other)
	{
		return this->equals(other);
	}
	MEDIALOADERAPI bool String::operator!=(const String& other)
	{
		return !this->equals(other);
	}
	MEDIALOADERAPI bool String::operator!=(const char* other)
	{
		return !this->equals(other);
	}
	MEDIALOADERAPI bool String::operator>(const String& other)
	{
		return this->compare(other) > 0;
	}
	MEDIALOADERAPI bool String::operator>(const char* other)
	{
		return this->compare(other) > 0;
	}
	MEDIALOADERAPI bool String::operator<(const String& other)
	{
		return this->compare(other) < 0;
	}
	MEDIALOADERAPI bool String::operator<(const char* other)
	{
		return this->compare(other) < 0;
	}
	MEDIALOADERAPI bool String::operator>=(const String& other)
	{
		return this->compare(other) >= 0;
	}
	MEDIALOADERAPI bool String::operator>=(const char* other)
	{
		return this->compare(other) >= 0;
	}
	MEDIALOADERAPI bool String::operator<=(const String& other)
	{
		return this->compare(other) <= 0;
	}
	MEDIALOADERAPI bool String::operator<=(const char* other)
	{
		return this->compare(other) <= 0;
	}
	//MEDIALOADERAPI String String::operator!()
	//{
	//	String clone(*this);
	//	clone.invert();
	//	return clone;
	//}
	//MEDIALOADERAPI bool String::operator&&(const String& other)
	//{
	//	return this->isWhiteSpaceOrEmpty() && other.isWhiteSpaceOrEmpty();
	//}
	//MEDIALOADERAPI bool String::operator&&(const char* str)
	//{
	//	String other(str);
	//	return this->isWhiteSpaceOrEmpty() && other.isWhiteSpaceOrEmpty();
	//}
	//MEDIALOADERAPI bool String::operator||(const String& other)
	//{
	//	return this->isWhiteSpaceOrEmpty() || other.isWhiteSpaceOrEmpty();
	//}
	//MEDIALOADERAPI bool String::operator||(const char* str)
	//{
	//	String other(str);
	//	return this->isWhiteSpaceOrEmpty() || other.isWhiteSpaceOrEmpty();
	//}
	MEDIALOADERAPI void String::operator+=(const String& other)
	{
		this->append(other);
	}
	MEDIALOADERAPI void String::operator+=(const char* other)
	{
		this->append(String(other));
	}
	MEDIALOADERAPI void String::operator+=(const char ch)
	{
		this->append(ch);
	}
	//MEDIALOADERAPI void String::operator-=(const String& other)
	//{
	//}
	//MEDIALOADERAPI void String::operator-=(const char* other)
	//{
	//}
	//MEDIALOADERAPI void String::operator-=(const char ch)
	//{
	//}
	MEDIALOADERAPI char& String::operator[](const int index)
	{
		if (this->count < 1)
		{
			this->resize(1);
		}

		return this->source[index % this->count];
	}

	MEDIALOADERAPI String String::Empty()
	{
		return String(0);
	}

}