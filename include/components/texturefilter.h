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

			inline TextureFilter() :
				Component("TextureFilter"),
				type(TEXTURE_NONE),
				surface(0) {}
			inline TextureFilter(Image::Surface* surface, TEXTURETYPE type) :
				Component("TextureFilter"),
				type(type),
				surface(surface) {}
			inline ~TextureFilter() {}

			inline Color sample(const vec2& texcoord);

			TEXTURETYPE type;
			Image::Surface* surface;

		};

	}
}

#endif