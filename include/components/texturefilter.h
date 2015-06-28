#ifndef RAY_TEXTUREFILTER_H
#define RAY_TEXTUREFILTER_H

namespace RAY_NAMESPACE
{
	namespace Components
	{
		
		class RAY_API TextureFilter : public Component
		{
		public:

			enum TEXTURETYPE
			{
				TEXTURE_NONE,
				TEXTURE_COLOR,
				TEXTURE_NORMAL,
				TEXTURE_SPECULAR,
				TEXTURE_TRANSPARENCY,
				TEXTURE_REFLECT,
				TEXTURE_EMISSIVE,
				TEXTURE_DISPLACEMENT,
			};

			enum SAMPLETYPE
			{
				SAMPLE_NEAREST,
				SAMPLE_LINEAR,
			};

			inline TextureFilter() :
				Component("TextureFilter"),
				type(TEXTURE_NONE),
				surface(0) {}
			inline TextureFilter(Image::Surface* surface, const TEXTURETYPE type) :
				Component("TextureFilter"),
				type(type),
				surface(surface) {}
			inline virtual ~TextureFilter() {}

			inline Color sample(const vec2& texcoord, const SAMPLETYPE type);

			const TEXTURETYPE type;
			Image::Surface* surface;

		};

	}
}

#endif