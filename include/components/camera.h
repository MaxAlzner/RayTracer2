#ifndef RAY_CAMERA_H
#define RAY_CAMERA_H

namespace RAY_NAMESPACE
{
	namespace Components
	{

		class RAY_API Camera : public Component
		{
		public:

			inline Camera() :
				Component("Camera"),
				focalDepth(-1.0f),
				aperture(4.0f, 3.0f) {}
			inline ~Camera() {}

			inline void adjust(float width, float height);
			inline void adjust();

			inline ray getRay(float u, float v);
			inline ray getRay(vec2& uv);

			vec2 aperture;
			float focalDepth;

		protected:

			struct
			{

				vec3 p1;
				vec3 p2;
				vec3 p3;
				vec3 p4;
				vec3 px;
				vec3 py;
				vec3 focal;

			} viewport;

		};

	}
}

#endif