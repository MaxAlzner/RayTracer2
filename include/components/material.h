#ifndef RAY_MATERIAL_H
#define RAY_MATERIAL_H

namespace RAY_NAMESPACE
{
	namespace Components
	{

		class RAY_API Material : public Component
		{
		public:

			inline Material() :
				Component("Material"),
				color(0) {}
			inline Material(Image::Surface* color) :
				Component(),
				color(color) {}
			inline ~Material() {}

			const Image::Surface* color;

		};

	}
}

#endif