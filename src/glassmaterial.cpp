
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Components
	{
		namespace Materials
		{
			using namespace DataObjects;
			using namespace Tracer;

			inline RAY_API Lumination GlassMaterial::shade(const Lighting& lighting, const Fragment& fragment) const
			{
				return Lumination(0.0f, 0.0f);
			}

			inline Lumination GlassMaterial::reflection(const Lumination& albedo, const Fragment& fragment) const
			{
				return albedo * fragment.reflectivity;
			}

		}
	}
}