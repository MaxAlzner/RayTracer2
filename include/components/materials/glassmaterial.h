#ifndef RAY_GLASSMATERIAL_H
#define RAY_GLASSMATERIAL_H

namespace RAY_NAMESPACE
{
	namespace Components
	{
		namespace Materials
		{

			class RAY_API GlassMaterial : public Material
			{
			public:

				inline GlassMaterial() :
					Material() {}
				inline virtual ~GlassMaterial() {}

				inline DataObjects::Lumination shade(const DataObjects::Lighting& lighting, const DataObjects::Fragment& fragment) const;

				inline DataObjects::Lumination reflection(const DataObjects::Lumination& albedo, const DataObjects::Fragment& fragment) const;

			};

		}
	}
}

#endif