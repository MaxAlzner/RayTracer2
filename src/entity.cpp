
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Tracer
	{
		using namespace Collection;
		using namespace Components;

		RAY_API void Entity::build()
		{
			this->transform = new Transform;
			this->add(this->transform);
			this->material = new Material;
			this->add(this->material);
			this->meshfilter = new MeshFilter;
			this->add(this->meshfilter);
		}
		RAY_API void Entity::dispose()
		{
			for (ListIterator<Component*>* i = this->components.iteratorAtEnd(); i->inside(); i->previous())
			{
				Component* component = i->current();
				if (component != 0)
				{
					delete component;
				}
			}

			this->components.clear();
			this->transform = 0;
			this->material = 0;
			this->meshfilter = 0;
		}

		RAY_API bool Entity::isEmpty() const
		{
			return this->transform == 0 && this->material == 0 && this->meshfilter == 0 && this->components.count() < 1;
		}

		RAY_API void Entity::add(Components::Component* component)
		{
			if (component != 0)
			{
				component->object = this;
				this->components.add(component);
			}
		}

		RAY_API Component* Entity::findComponent(String type)
		{
			for (ListIterator<Component*>* i = this->components.iterator(); i->inside(); i->next())
			{
				Component* component = i->current();
				if (component != 0 && component->type == type)
				{
					return component;
				}
			}

			return 0;
		}

	}
}