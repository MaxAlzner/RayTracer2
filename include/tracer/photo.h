#ifndef RAY_PHOTO_H
#define RAY_PHOTO_H

namespace RAY_NAMESPACE
{
	namespace Tracer
	{

		class RAY_API Photo : public IObject
		{
		public:

			inline Photo() :
				width(0),
				height(0),
				reflectDepth(1),
				multiSampleDepth(1),
				hits(0) {}
			inline Photo(int width, int height) :
				width(width),
				height(height),
				reflectDepth(1),
				multiSampleDepth(1),
				hits(0) {}
			inline ~Photo() {}

			virtual void build();
			virtual void dispose();

			virtual bool isEmpty() const;

			Image::Surface* flatten() const;

			void emit(TraceStack* stack);

			rayhit trace(int x, int y, TraceStack* stack);

			int width;
			int height;
			int reflectDepth;
			int multiSampleDepth;
			HitBuffer* hits;

		};

	}
}


#endif