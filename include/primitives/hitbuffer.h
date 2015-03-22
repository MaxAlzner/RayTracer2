#ifndef RAY_HITBUFFER_H
#define RAY_HITBUFFER_H

namespace RAY_NAMESPACE
{
	namespace Primitives
	{

		class RAY_API HitBuffer : public IObject
		{
		public:

			inline HitBuffer() :
				width(0),
				height(0),
				depth(0),
				size(0),
				bytes(0),
				buffer(0) {}
			inline HitBuffer(int width, int height, int depth) :
				width(width < 1 ? 1 : width),
				height(height < 1 ? 1 : height),
				depth(depth < 1 ? 1 : depth),
				size(this->width * this->height * this->depth),
				bytes(sizeof(RayHit) * this->size),
				buffer(0) { this->build(); }
			inline ~HitBuffer() { this->dispose(); }

			bool isEmpty() const;

			inline RayHit& get(const int x, const int y);
			inline RayHit& get(const int x, const int y, const int z);

			inline RayHit& operator[](const int index);

			const int width;
			const int height;
			const int depth;
			const int size;
			const int bytes;
			RayHit* buffer;

		protected:

			void build();
			void dispose();

		};

	}
}

#endif