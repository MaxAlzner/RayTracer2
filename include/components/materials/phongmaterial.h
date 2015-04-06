#ifndef RAY_PHONGMATERIAL_H
#define RAY_PHONGMATERIAL_H

namespace RAY_NAMESPACE
{
	namespace Components
	{
		namespace Materials
		{

			class RAY_API PhongMaterial : public Material
			{
			public:

				inline PhongMaterial() :
					Material(),
					exponent(16.0f) {}
				inline PhongMaterial(const float exponent) :
					Material(),
					exponent(exponent) {}
				inline ~PhongMaterial() {}

				inline DataObjects::Lumination shade(const DataObjects::Lighting& lighting, const DataObjects::Fragment& fragment) const;

				float exponent;

			};

		}
	}
}

#endif