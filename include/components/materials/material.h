#ifndef RAY_MATERIAL_H
#define RAY_MATERIAL_H

namespace RAY_NAMESPACE
{
	namespace Components
	{
		namespace Materials
		{

			class RAY_API Material : public Component
			{
			public:

				inline Material() :
					Component("Material"),
					color(0),
					normal(0),
					specular(0),
					transparency(0),
					reflect(0),
					emissive(0),
					displacement(0) {}
				inline virtual ~Material() {}

				virtual inline DataObjects::Lumination shade(const DataObjects::Lighting& lighting, const DataObjects::Fragment& fragment) const = 0;

				virtual inline DataObjects::Lumination reflection(const DataObjects::Lumination& albedo, const DataObjects::Fragment& fragment) const = 0;

				virtual inline Color surfaceColor(const glm::vec2& texcoord) const;
				virtual inline glm::vec3 surfaceNormal(const glm::vec2& texcoord) const;
				virtual inline Color surfaceSpecular(const glm::vec2& texcoord) const;
				virtual inline float surfaceTransparency(const glm::vec2& texcoord) const;
				virtual inline float surfaceReflectivity(const glm::vec2& texcoord) const;
				virtual inline Color surfaceEmissive(const glm::vec2& texcoord) const;

				TextureFilter* color;
				TextureFilter* normal;
				TextureFilter* specular;
				TextureFilter* transparency;
				TextureFilter* reflect;
				TextureFilter* emissive;
				TextureFilter* displacement;

			};

		}
	}
}

#endif