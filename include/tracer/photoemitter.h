#ifndef RAY_PHOTOEMITTER_H
#define RAY_PHOTOEMITTER_H

namespace RAY_NAMESPACE
{
	namespace Tracer
	{

		class RAY_API PhotoEmitter
		{
		public:

			inline PhotoEmitter() :
				_photo(0),
				_stack(0),
				_area() {}
			inline PhotoEmitter(Photo* photo, TraceStack* stack) :
				_photo(photo),
				_stack(stack),
				_area(ivec2(0), ivec2(photo->_width, photo->_height)) {}
			inline PhotoEmitter(Photo* photo, TraceStack* stack, const ibox& area) :
				_photo(photo),
				_stack(stack),
				_area(area) {}
			inline ~PhotoEmitter() {}

			virtual void emit();

			virtual DataObjects::Lumination cast(const float u, const float v);

		protected:

			Photo* _photo;
			TraceStack* _stack;
			ibox _area;

		};

	}
}

#endif