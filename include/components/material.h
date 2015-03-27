#ifndef RAY_MATERIAL_H
#define RAY_MATERIAL_H

namespace RAY_NAMESPACE
{
	namespace Components
	{

		class RAY_API Material : public Component
		{
		public:

			enum TEXTURETYPE
			{
				TEXTURE_COLOR,
				TEXTURE_NORMAL,
				TEXTURE_SPECULAR,
				TEXTURE_TRANSPARENCY,
				TEXTURE_EMISSIVE,
				TEXTURE_DISPLACEMENT,
			};

			inline Material() :
				Component("Material"),
				color(0) {}
			inline ~Material() {}

			Image::Surface* color;

		};

	}
}

#endif