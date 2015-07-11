#ifndef RAY_OBJECT_H
#define RAY_OBJECT_H

namespace RAY_NAMESPACE
{
	namespace Tracer
	{

		class RAY_API Object
		{
		public:

			virtual void build() = 0;
			virtual void dispose() = 0;

			virtual bool isEmpty() const = 0;

		};

	}
}

#endif