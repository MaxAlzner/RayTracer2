#ifndef RAY_PHOTO_H
#define RAY_PHOTO_H

namespace RAY_NAMESPACE
{
	namespace Tracer
	{

		class RAY_API Photo : public IObject
		{
		public:

			friend class PhotoEmitter;

			inline Photo() :
				reflectDepth(1),
				multiSampleDepth(1),
				_width(0),
				_height(0) {}
			inline Photo(int width, int height) :
				reflectDepth(1),
				multiSampleDepth(1),
				_width(width),
				_height(height) {}
			inline ~Photo() {}

			virtual void build();
			virtual void dispose();

			virtual bool isEmpty() const;

			Image::Surface* flatten();

			void render(TraceStack* stack);

			int reflectDepth;
			int multiSampleDepth;

		protected:

			static unsigned int _stdcall _renderCallback(void* data);

			int _width;
			int _height;
			Collection::Map<DataObjects::RayHit> _geometrypass;
			Collection::Map<DataObjects::Fragment> _fragmentpass;
			Collection::Map<DataObjects::Lumination> _lightpass;

		};

	}
}


#endif