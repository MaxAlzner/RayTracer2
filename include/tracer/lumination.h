#ifndef RAY_LUMINATION_H
#define RAY_LUMINATION_H

namespace RAY_NAMESPACE
{
	namespace Tracer
	{

		class RAY_API Lumination
		{

			inline Lumination() {}
			inline ~Lumination() {}

			Color color;
			float diffuse;
			float specular;
			float brdf;
			float attenuation;

		};

	}
}

#endif