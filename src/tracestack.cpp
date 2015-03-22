
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Tracer
	{
		using namespace Collection;
		using namespace Components;

		RAY_API void TraceStack::build()
		{

		}
		RAY_API void TraceStack::dispose()
		{
			for (ListIterator<Entity*>* i = this->stack.iteratorAtEnd(); i->inside(); i->previous())
			{
				Entity* entity = i->current();
				if (entity != 0)
				{
					delete entity;
				}
			}

			this->stack.clear();
		}

		RAY_API bool TraceStack::isEmpty() const
		{
			return this->stack.count() < 1;
		}

		RAY_API void TraceStack::add(Entity* entity)
		{
			if (entity != 0)
			{
				this->stack.add(entity);
			}
		}

	}
}