
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Tracer
	{
		using namespace Collection;
		using namespace Image;
		using namespace Primitives;
		using namespace Components;

		RAY_API void Photo::build()
		{
			this->hits = new HitBuffer(this->width, this->height, this->reflectDepth);
		}
		RAY_API void Photo::dispose()
		{
			if (this->hits != 0)
			{
				delete this->hits;
				this->hits = 0;
			}
		}

		RAY_API bool Photo::isEmpty() const
		{
			return this->width < 1 && this->height < 1;
		}

		RAY_API Surface* Photo::flatten() const
		{
			Surface* surface = new Surface;
			surface->build();

			return surface;
		}

		RAY_API void Photo::trace(int x, int y, TraceStack* stack)
		{
			if (stack != 0)
			{
				for (ListIterator<Entity*>* i = stack->stack.iterator(); i->inside(); i->next())
				{
					Entity* entity = i->current();
					if (entity != 0)
					{

					}
				}
			}
		}

	}
}