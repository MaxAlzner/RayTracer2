#ifndef RAY_TRANSFORM_H
#define RAY_TRANSFORM_H

namespace RAY_NAMESPACE
{
	namespace Components
	{

		class RAY_API Transform : public Component
		{
		public:

			inline Transform() :
				Component("Transform"),
				parent(0) { this->zero(); }
			inline Transform(Transform* parent) :
				Component(),
				parent(parent != this ? parent : 0) { this->zero(); }
			inline ~Transform() {}

			inline void recalculate();
			inline void zero();

			const Transform* parent;
			mat4 transformation;
			mat4 space;
			vec3 position;
			vec3 rotation;
			vec3 scale;
			vec3 right;
			vec3 up;
			vec3 forward;

		};

	}
}

#endif