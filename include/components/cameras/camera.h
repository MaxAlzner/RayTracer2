#ifndef RAY_CAMERA_H
#define RAY_CAMERA_H

namespace RAY_NAMESPACE
{
	namespace Components
	{
		namespace Cameras
		{

			class RAY_API Camera : public Component
			{
			public:

				inline Camera() :
					Component("Camera"),
					aperture(4.0f, 3.0f),
					focalDepth(-1.0f) {}
				inline Camera(const glm::vec2& aperture, const float focalDepth) :
					Component("Camera"),
					aperture(aperture),
					focalDepth(focalDepth) {}
				inline virtual ~Camera() {}

				inline void adjust(float width, float height);
				inline void adjust();

				inline ray getRay(float u, float v);
				inline ray getRay(glm::vec2& uv);

				glm::vec2 aperture;
				float focalDepth;

			protected:

				struct
				{

					glm::vec3 p1;
					glm::vec3 p2;
					glm::vec3 p3;
					glm::vec3 p4;
					glm::vec3 px;
					glm::vec3 py;
					glm::vec3 focal;

				} viewport;

			};

		}
	}
}

#endif