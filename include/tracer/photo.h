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
				reflectDepth(0),
				multiSampleDepth(0),
				_width(0),
				_height(0) {}
			inline Photo(int width, int height) :
				reflectDepth(0),
				multiSampleDepth(0),
				_width(width),
				_height(height) {}
			inline Photo(int width, int height, int reflectDepth) :
				reflectDepth(reflectDepth),
				multiSampleDepth(0),
				_width(width),
				_height(height) {}
			inline Photo(int width, int height, int reflectDepth, int multiSampleDepth) :
				reflectDepth(reflectDepth),
				multiSampleDepth(multiSampleDepth),
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
			Collection::Map<TracePath> _geometrypass;
			Collection::Map<DataObjects::Lumination> _lightpass;

		};

	}
}


#endif