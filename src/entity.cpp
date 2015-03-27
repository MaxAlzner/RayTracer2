
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

		RAY_API void Entity::attach(Mesh::Shape* shape)
		{
			if (shape != 0)
			{
				this->meshfilter = new MeshFilter;
				this->add(this->meshfilter);
				this->meshfilter->shape = shape;
			}
		}
		RAY_API void Entity::attach(Image::Surface* surface, Material::TEXTURETYPE type)
		{
			if (surface != 0)
			{
				this->material = new Material;
				this->add(this->material);
				switch (type)
				{
				case Material::TEXTURE_COLOR:
					this->material->color = surface;
					break;
				default:
					break;
				}
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