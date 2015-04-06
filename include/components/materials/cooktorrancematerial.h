#ifndef RAY_COOKTORRANCEMATERIAL_H
#define RAY_COOKTORRANCEMATERIAL_H

namespace RAY_NAMESPACE
{
	namespace Components
	{
		namespace Materials
		{

			class RAY_API CookTorranceMaterial : public Material
			{
			public:

				inline CookTorranceMaterial() :
					Material(),
					roughness(1.0f),
					refractionIndex(1.3f) {}
				inline CookTorranceMaterial(const float roughness, const float refractionIndex) :
					Material(),
					roughness(roughness),
					refractionIndex(refractionIndex) {}
				inline ~CookTorranceMaterial() {}

				inline DataObjects::Lumination shade(const DataObjects::Lighting& lighting, const DataObjects::Fragment& fragment) const;

				float roughness;
				float refractionIndex;

			};

		}
	}
}

#endif