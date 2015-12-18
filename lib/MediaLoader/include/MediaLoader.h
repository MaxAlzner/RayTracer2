#ifndef MEDIALOADER_H
#define MEDIALOADER_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// INT32 redefinition error
#include <basetsd.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <encode.hpp>
#include <array.hpp>
#include <list.hpp>

#include <rapidxml.hpp>
#include <png.h>
#include <jpeglib.h>
#include <ogg\ogg.h>
#include <vorbis\vorbisfile.h>

//#define max(x, y) (x > y ? x : y)
//#define min(x, y) (x < y ? x : y)

#define MEDIALOADERAPI __declspec(dllexport)

namespace medialoader
{
	using namespace glm;

	//typedef glm::tvec2<float> vec2;
	//typedef glm::tvec3<float> vec3;
	//typedef glm::tvec4<float> vec4;
	//typedef glm::tvec2<int> ivec2;
	//typedef glm::tvec3<int> ivec3;
	//typedef glm::tvec4<int> ivec4;
	//typedef glm::tmat4x4<float> mat4;

	class MEDIALOADERAPI String
	{
	public:

		String();
		String(const String& str);
		String(const String& str0, const String& str1);
		String(const char* str);
		String(const char* str0, const char* str1);
		~String();

		bool equals(const String& other);
		bool equals(const char* other);
		bool isEmpty();
		bool isWhiteSpaceOrEmpty();
		int compare(const String& other);
		int compare(const char* other);
		bool contains(const String& other);
		bool contains(const char ch);
		bool startsWith(const String& other);
		bool startsWith(const char* other);
		bool endsWith(const String& other);
		bool endsWith(const char* other);

		void append(const String& str);
		void append(const char* str);
		void append(const char ch);
		void trimStart(const char check);
		void trimEnd(const char check);

		String copy();
		void paste(const char* str);
		void paste(const String& str);

		int length();
		int capacity();
		void resize(int bytes);

		void operator=(const String& other);
		void operator=(const char* other);
		void operator=(const char ch);
		operator char*() const;
		String operator+(const String& other);
		String operator+(const char* other);
		String operator+(const char ch);
		bool operator==(const String& other);
		bool operator==(const char* other);
		bool operator!=(const String& other);
		bool operator!=(const char* other);
		bool operator>(const String& other);
		bool operator>(const char* other);
		bool operator<(const String& other);
		bool operator<(const char* other);
		bool operator>=(const String& other);
		bool operator>=(const char* other);
		bool operator<=(const String& other);
		bool operator<=(const char* other);
		void operator+=(const String& other);
		void operator+=(const char* other);
		void operator+=(const char ch);
		char& operator[](const int index);

		static String Empty();

	protected:

		char* source;
		int count;
		int bytes;

	};

	class MEDIALOADERAPI Color
	{
	public:

		inline Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
		inline Color(float r, float g, float b, float a) : r(clamp(r)), g(clamp(g)), b(clamp(b)), a(clamp(a)) {}
		inline Color(float r, float g, float b) : r(clamp(r)), g(clamp(g)), b(clamp(b)), a(1.0f) {}
		inline Color(float gray) : r(clamp(gray)), g(clamp(gray)), b(clamp(gray)), a(1.0f) {}
		inline Color(const Color& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}
		inline ~Color() {}

		inline float luminance();

		inline void operator=(const Color& c);
		inline void operator=(const float scalar);
		inline Color operator+() const;
		inline Color operator-() const;
		inline void operator+=(const Color& c);
		inline void operator+=(const float scalar);
		inline void operator-=(const Color& c);
		inline void operator-=(const float scalar);
		inline void operator*=(const Color& c);
		inline void operator*=(const float scalar);
		inline void operator/=(const Color& c);
		inline void operator/=(const float scalar);
		inline bool operator==(const Color& c) const;
		inline bool operator!=(const Color& c) const;
		inline bool operator>(const Color& c) const;
		inline bool operator<(const Color& c) const;
		inline bool operator>=(const Color& c) const;
		inline bool operator<=(const Color& c) const;
		inline Color operator!() const;
		inline Color operator&&(const Color& c) const;
		inline Color operator||(const Color& c) const;

		float r, g, b, a;

	};

	inline MEDIALOADERAPI Color operator+(const Color& c0, const Color& c1);
	inline MEDIALOADERAPI Color operator+(const Color& c, const float v);
	inline MEDIALOADERAPI Color operator+(const float v, const Color& c);
	inline MEDIALOADERAPI Color operator-(const Color& c0, const Color& c1);
	inline MEDIALOADERAPI Color operator-(const Color& c, const float v);
	inline MEDIALOADERAPI Color operator-(const float v, const Color& c);
	inline MEDIALOADERAPI Color operator*(const Color& c0, const Color& c1);
	inline MEDIALOADERAPI Color operator*(const Color& c, const float v);
	inline MEDIALOADERAPI Color operator*(const float v, const Color& c);
	inline MEDIALOADERAPI Color operator/(const Color& c0, const Color& c1);
	inline MEDIALOADERAPI Color operator/(const Color& c, const float v);
	inline MEDIALOADERAPI Color operator/(const float v, const Color& c);

	class MEDIALOADERAPI Media
	{
	public:

		virtual void release() = 0;

		virtual void read(String filepath) = 0;

		virtual void write(String filepath) = 0;

	};

	class MEDIALOADERAPI File : public Media
	{
	public:

		File() : _raw(0), _bytes(0) {}
		~File() {}

		virtual void release();

		virtual void read(String filepath);

		virtual void write(String filepath);

		virtual bool isEmpty() const;

		const char* raw() const;
		const int size() const;

	protected:

		char* _raw;
		unsigned int _bytes;

	};

	typedef rapidxml::xml_document<char> XmlDocument;
	typedef rapidxml::xml_node<char> XmlNode;
	typedef rapidxml::xml_attribute<char> XmlAttribute;

	class MEDIALOADERAPI XmlFile : public File
	{
	public:

		XmlFile() :
			File(),
			document(0),
			root(0) {}
		~XmlFile() {}

		virtual void release();

		virtual void read(String filepath);

		XmlDocument* document;
		XmlNode* root;

		static int ParseInt(XmlNode* node, int defaultValue = 0);
		static int ParseInt(XmlAttribute* attr, int defaultValue = 0);
		static float ParseFloat(XmlNode* node, float defaultValue = 0.0f);
		static float ParseFloat(XmlAttribute* attr, float defaultValue = 0.0f);
		static bool ParseBool(XmlNode* node, bool defaultValue = false);
		static bool ParseBool(XmlAttribute* attr, bool defaultValue = false);
		static Color ParseColor(XmlNode* node);
		static String Value(XmlAttribute* attr);

	protected:

		virtual void _parse();

	};

	namespace Image
	{

		struct MEDIALOADERAPI EncodedPixel
		{

			EncodedPixel() : full(0) {}
			EncodedPixel(__int32 p) : full(p) {}
			EncodedPixel(__int8 c0, __int8 c1, __int8 c2, __int8 c3) : byte0(c0), byte1(c1), byte2(c2), byte3(c3) {}
			~EncodedPixel() {}

			operator const __int32() const { return this->full; }

			union
			{
				__int32 full;
				__int8 bytes[4];
				struct
				{
					__int8 byte0, byte1, byte2, byte3;
				};
			};

		};

		enum PIXELFORMAT
		{
			PIXELFORMAT_NONE = 0x00000000,
			PIXELFORMAT_RGB = 0x00000001,
			PIXELFORMAT_RGBA = 0x00000002,
			PIXELFORMAT_ARGB = 0x00000003,
			PIXELFORMAT_BGR = 0x00000004,
			PIXELFORMAT_BGRA = 0x00000005,
			PIXELFORMAT_ABGR = 0x00000006,
		};

		extern inline MEDIALOADERAPI int ByteCount(const PIXELFORMAT format);
		extern inline MEDIALOADERAPI bool AlphaFirst(const PIXELFORMAT format);
		extern inline MEDIALOADERAPI bool HasAlpha(const PIXELFORMAT format);
		extern inline MEDIALOADERAPI EncodedPixel EncodeColor(const Color& color, const PIXELFORMAT format);
		extern inline MEDIALOADERAPI EncodedPixel EncodePixel(const EncodedPixel& pixel, const PIXELFORMAT internalFormat, const PIXELFORMAT destinationFormat);
		extern inline MEDIALOADERAPI Color PackPixel(const EncodedPixel& pixel, const PIXELFORMAT format);

		class BmpFileStream;
		class TgaFileStream;
		class PngFileStream;
		class JpgFileStream;

		class MEDIALOADERAPI Surface : public Media
		{
		public:

			Surface() :
				_width(0),
				_height(0),
				_format(PIXELFORMAT_NONE),
				_map(0) {}
			~Surface() {}

			friend class BmpFileStream;
			friend class TgaFileStream;
			friend class PngFileStream;
			friend class JpgFileStream;

			virtual void release();

			virtual void read(String filepath);

			virtual void write(String filepath);

			void blit(void* raw, int width, int height, PIXELFORMAT internalFormat);
			void blit(Surface* surface);

			void resize(int width, int height);
			void reformat(PIXELFORMAT destination);

			void put(int x, int y, EncodedPixel& pixel);
			void put(int x, int y, Color& color);
			EncodedPixel& get(int x, int y);

			virtual bool isEmpty() const;

			const int width() const;
			const int height() const;
			const PIXELFORMAT format() const;
			const EncodedPixel* map() const;

			operator EncodedPixel*() const;
			EncodedPixel& operator[](const int index);

		protected:

			int _width;
			int _height;
			PIXELFORMAT _format;
			EncodedPixel* _map;

		};

		class MEDIALOADERAPI AnimSequence;

		class MEDIALOADERAPI AnimSheet : public XmlFile
		{
		public:

			AnimSheet() : XmlFile(), _playing(0), _paused(true) { this->_animations.resize(8); }
			~AnimSheet() {}

			friend class AnimSequence;

			void release();

			bool isEmpty() const;

		protected:

			typedef struct frameType
			{

				frameType() : uv0(vec2(0.0f)), uv1(vec2(1.0f)) {}
				~frameType() {}

				vec2 uv0;
				vec2 uv1;

			} frameType;

			typedef struct sequenceType
			{

				sequenceType() { this->sequence.resize(8); }
				~sequenceType() { this->sequence.clear(); }

				String name;
				Array<frameType> sequence;
				int frames;
				bool playOnce;
				bool pingPong;

			} sequenceType;

			void _parse();

			Array<sequenceType*> _animations;
			sequenceType* _playing;
			bool _paused;

		};

		class MEDIALOADERAPI AnimSequence
		{
		public:

			AnimSequence() : _sheet(0), _playing(0), _current(-1), _increment(0), _paused(true) {}
			AnimSequence(AnimSheet* sheet) : _sheet(sheet), _playing(0), _current(-1), _increment(0), _paused(true) {}
			~AnimSequence() {}

			void play(String name);
			void stop();
			void rewind();

			void nextFrame();

			void setSheet(AnimSheet* sheet);
			void getFrame(vec2& uv0, vec2& uv1) const;

		protected:

			AnimSheet* _sheet;
			AnimSheet::sequenceType* _playing;
			int _current;
			int _increment;
			bool _paused;

		};

		class MEDIALOADERAPI TileMap;

		class MEDIALOADERAPI TileSheet : public XmlFile
		{
		public:

			TileSheet() {}
			~TileSheet() {}

			friend class TileMap;

			void release();

			bool isEmpty() const;

		protected:

			typedef struct tileType
			{

				tileType() : uv0(0.0f), uv1(1.0f) {}
				~tileType() {}

				String name;
				vec2 uv0;
				vec2 uv1;

			} tileType;

			void _parse();

			Array<tileType*> _tiles;

		};

		class MEDIALOADERAPI TileMap
		{
		public:

			TileMap() : _columns(0), _rows(0) { this->_iterator = this->_tiles.iterator(); }
			TileMap(int columns, int rows) : _columns(columns), _rows(rows) { this->_iterator = this->_tiles.iterator(); }
			~TileMap() { this->clear(); }

			void add(TileSheet* sheet, String name, vec2& uv);
			void add(TileSheet* sheet, String name, int col, int row);

			void rewind();
			bool next(vec2& destUv0, vec2& destUv1, vec2& srcUv0, vec2& srcUv1);

			void clear();

		protected:

			typedef struct tileType
			{

				tileType() : source(0), pos(0.0f) {}
				~tileType() {}

				TileSheet::tileType* source;
				vec2 pos;

			} tileType;

			int _columns;
			int _rows;
			List<tileType*> _tiles;
			List<tileType*>::Iterator _iterator;

		};

	}

	namespace Mesh
	{

		template <typename T> struct MEDIALOADERAPI component
		{

			inline component() :
				buffer(0),
				elements(0),
				offset(0),
				stride(sizeof(T)),
				size(0) {}
			inline component(const T* buffer, const int elements, const int offset) :
				buffer(buffer),
				elements(elements),
				offset(offset),
				stride(sizeof(T)),
				size(elements * sizeof(T)) {}
			inline component(const component<T>& b) :
				buffer(b.buffer),
				elements(b.elements),
				offset(b.offset),
				stride(sizeof(T)),
				size(elements * sizeof(T)) {}
			inline ~component() {}

			inline void operator=(const component<T>& b)
			{
				memcpy(this, &b, sizeof(component<T>));
			}
			inline T* operator+(const int index)
			{
				return (T*)this->buffer + index;
			}
			inline T* operator-(const int index)
			{
				return (T*)this->buffer - index;
			}
			inline T& operator[](const int index)
			{
				return (T&)this->buffer[index % this->elements];
			}

			const T* buffer;
			const int elements;
			const int offset;
			const int stride;
			const int size;

		};

		template <typename T> struct MEDIALOADERAPI transformation
		{

			inline transformation() :
				translation((T)0),
				scale((T)1),
				rotation((T)1),
				space((T)1) {}
			inline transformation(const tvec3<T>& translation, const tvec3<T>& scale, const tvec3<T>& rotation) :
				translation(translation),
				scale(scale),
				rotation(gmath::rotate(mat4(), rotation)),
				space(this->rotation) {}
			inline transformation(const tvec3<T>& translation, const tvec3<T>& scale, const tmat3x3<T>& space) :
				translation(translation),
				scale(scale),
				rotation(space),
				space(space) {}
			inline transformation(const tvec3<T>& translation, const tvec3<T>& scale, const tmat4x4<T>& space) :
				translation(translation),
				scale(scale),
				rotation(space),
				space(space) {}
			inline ~transformation() {}

			tvec3<T> translation;
			tvec3<T> scale;
			tmat4x4<T> rotation;
			tmat3x3<T> space;

		};

		class MEDIALOADERAPI Bone
		{
		public:

			Bone() : _parent(0) {}
			~Bone() {}

			const Bone* parent() const;

			void operator=(const mat4& m);

		protected:

			Bone* _parent;
			mat4 _local;

		};

		class ObjFileStream;

		class MEDIALOADERAPI Shape : public Media
		{
		public:

			Shape() : _buffer(0), _size(0) {}
			~Shape() {}

			friend class ObjFileStream;

			virtual void release();

			virtual void read(String filepath);

			virtual void write(String filepath);

			virtual void clear();

			virtual void normalize();

			virtual void putFace(const int index, const ivec3& face);
			virtual void putVertex(const int index, const vec4& v);
			virtual void putTexcoord(const int index, const vec2& uv);
			virtual void putNormal(const int index, const vec3& n);
			virtual void putTangent(const int index, const vec3& t);
			virtual void putBinormal(const int index, const vec3& b);
			virtual void putWeights(const int index, const ivec4& w);
			virtual void putBoneIndices(const int index, const ivec4& bi);
			virtual ivec3& getFace(const int index);
			virtual vec4& getVertex(const int index);
			virtual vec2& getTexcoord(const int index);
			virtual vec3& getNormal(const int index);
			virtual vec3& getTangent(const int index);
			virtual vec3& getBinormal(const int index);
			virtual ivec4& getWeights(const int index);
			virtual ivec4& getBoneIndices(const int index);

			virtual bool isEmpty() const;

			virtual const int elements() const;
			virtual const int components() const;
			virtual const void* buffer() const;

			component<int> indices;
			component<ivec3> faceIndices;

			component<vec4> vertices;
			component<vec2> texcoords;
			component<vec3> normals;
			component<vec3> binormals;
			component<vec3> tangents;
			component<ivec4> weights;
			component<ivec4> boneIndices;

			component<mat4> bones;

		protected:

			void* _buffer;
			unsigned int _size;

		};

	}

	namespace Sound
	{

		class WavFileStream;
		class OggFileStream;

		class MEDIALOADERAPI Track : public Media
		{
		public:

			Track() :
				_channels(0),
				_frequency(0),
				_samples(0),
				_byteDepth(0),
				_duration(0.0f),
				_stream(0) {}
			~Track() {}

			friend class WavFileStream;
			friend class OggFileStream;

			virtual void release();

			virtual void read(String filepath);

			virtual void write(String filepath);

			virtual bool isEmpty() const;

			const int channels() const;
			const int frequency() const;
			const int samples() const;
			const int byteDepth() const;
			const float duration() const;
			const void* stream() const;

		protected:

			int _channels;
			int _frequency;
			int _samples;
			int _byteDepth;
			float _duration;
			void* _stream;

		};

	}
}

#endif