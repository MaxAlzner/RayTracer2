#ifndef RAY_FRAGMENT_H
#define RAY_FRAGMENT_H

namespace RAY_NAMESPACE
{
	namespace DataObjects
	{

		class RAY_API Fragment
		{
		public:

			inline Fragment() :
				position(0.0f),
				texcoord(0.0f),
				normal(0.0f, 0.0f, 1.0f),
				tangent(1.0f, 0.0f, 0.0f),
				binormal(0.0f, 1.0f, 0.0f),
				view(0.0f, 0.0f, 1.0f),
				transparency(0.0f),
				reflectivity(1.0f),
				color(1.0f),
				specular(1.0f),
				emissive(0.0f),
				material(0) {}
			inline Fragment(
				const RayHit& hit,
				const Components::Materials::Material* material
				) :
				position(hit.intersection),
				texcoord(hit.texcoord),
				normal(hit.normal),
				tangent(hit.tangent),
				binormal(hit.binormal),
				view(0.0f, 0.0f, 1.0f),
				transparency(0.0f),
				reflectivity(1.0f),
				color(1.0f),
				specular(1.0f),
				emissive(0.0f),
				material(material)
			{
				this->adjust(hit);
				this->resample();
			}
			inline ~Fragment() {}

			inline void resample();
			inline void adjust(const RayHit& hit);

			inline ray reflect(const ray& r);

			vec3 position;
			vec2 texcoord;
			vec3 normal;
			vec3 tangent;
			vec3 binormal;
			vec3 view;
			float transparency;
			float reflectivity;
			Color color;
			Color specular;
			Color emissive;
			const Components::Materials::Material* material;

		};

	}
}

#endif