
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Tracer
	{
		using namespace Components;

		RAY_API void Entity::build()
		{
			this->transform = new Transform;
			this->add(this->transform);
		}
		RAY_API void Entity::dispose()
		{
			for (List<Component*>::Iterator i = this->components.iteratorAtEnd(); i.inside(); i.previous())
			{
				Component* component = i.current();
				if (component != 0)
				{
					delete component;
				}
			}

			this->components.clear();
			this->stack = 0;
			this->transform = 0;
			this->meshfilter = 0;
			this->material = 0;
			this->camera = 0;
			this->light = 0;
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

				if (component->type == "Material")
				{
					this->material = (Materials::Material*)component;
				}
				else if (component->type == "Camera")
				{
					this->camera = (Cameras::Camera*)component;
					this->stack->camera = this->camera;
				}
				else if (component->type == "Light")
				{
					this->light = (Lights::Light*)component;
					this->stack->lights.add(this->light);
				}
			}
		}

		RAY_API void Entity::attach(Shapes::TraceShape* shape)
		{
			if (shape != 0)
			{
				this->meshfilter = new MeshFilter;
				this->add(this->meshfilter);
				this->meshfilter->shape = shape;
			}
		}
		RAY_API void Entity::attach(Image::Surface* surface, TextureFilter::TEXTURETYPE type)
		{
			if (surface != 0 && type != TextureFilter::TEXTURE_NONE && this->material != 0)
			{
				TextureFilter* filter = new TextureFilter(surface, type);
				this->add(filter);
				switch (type)
				{
				case TextureFilter::TEXTURE_COLOR:
					this->material->color = filter;
					break;
				case TextureFilter::TEXTURE_NORMAL:
					this->material->normal = filter;
					break;
				case TextureFilter::TEXTURE_SPECULAR:
					this->material->specular = filter;
					break;
				default:
					break;
				}
			}
		}

		RAY_API Component* Entity::findComponent(String type)
		{
			for (List<Component*>::Iterator i = this->components.iterator(); i.inside(); i.next())
			{
				Component* component = i.current();
				if (component != 0 && component->type == type)
				{
					return component;
				}
			}

			return 0;
		}

	}
}