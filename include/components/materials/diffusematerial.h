#ifndef RAY_DIFFUSEMATERIAL_H
#define RAY_DIFFUSEMATERIAL_H

namespace RAY_NAMESPACE
{
	namespace Components
	{
		namespace Materials
		{

			class RAY_API DiffuseMaterial : public Material
			{
			public:

				inline DiffuseMaterial() :
					Material() {}
				inline virtual ~DiffuseMaterial() {}

				inline DataObjects::Lumination shade(const DataObjects::Lighting& lighting, const DataObjects::Fragment& fragment) const;

				inline DataObjects::Lumination reflection(const DataObjects::Lumination& albedo, const DataObjects::Fragment& fragment) const;

			};

		}
	}
}

#endif