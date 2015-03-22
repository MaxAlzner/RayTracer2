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
				transform(0),
				material(0),
				meshfilter(0) {}

			virtual void build();
			virtual void dispose();

			virtual bool isEmpty() const;

			void add(Components::Component* component);

			Components::Component* findComponent(String type);

			Components::Transform* transform;
			Components::Material* material;
			Components::MeshFilter* meshfilter;
			Collection::List<Components::Component*> components;

		};

	}
}

#endif