#ifndef RAY_BLINNMATERIAL_H
#define RAY_BLINNMATERIAL_H

namespace RAY_NAMESPACE
{
	namespace Components
	{
		namespace Materials
		{

			class RAY_API BlinnMaterial : public Material
			{
			public:

				inline BlinnMaterial() :
					Material(),
					exponent(32.0f) {}
				inline BlinnMaterial(const float exponent) :
					Material(),
					exponent(exponent) {}
				inline ~BlinnMaterial() {}

				inline DataObjects::Lumination shade(const DataObjects::Lighting& lighting, const DataObjects::Fragment& fragment) const;

				float exponent;

			};

		}
	}
}

#endif