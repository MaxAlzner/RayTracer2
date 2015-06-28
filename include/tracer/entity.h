#ifndef RAY_ENTITY_H
#define RAY_ENTITY_H

namespace RAY_NAMESPACE
{
	namespace Tracer
	{

		class RAY_API Entity : public IObject
		{
		public:

			inline Entity() :
				stack(0),
				transform(0),
				meshfilter(0),
				material(0),
				camera(0),
				light(0) {}
			inline ~Entity() {}

			virtual void build();
			virtual void dispose();

			virtual bool isEmpty() const;

			void add(Components::Component* component);

			void attach(Shapes::TraceShape* shape);
			void attach(Image::Surface* surface, Components::TextureFilter::TEXTURETYPE type);

			Components::Component* findComponent(String type);

			TraceStack* stack;
			Components::Transform* transform;
			Components::MeshFilter* meshfilter;
			Components::Materials::Material* material;
			Components::Cameras::Camera* camera;
			Components::Lights::Light* light;
			Collection::List<Components::Component*> components;

		};

	}
}

#endif