
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Tracer
	{
		using namespace DataObjects;

		RAY_API void TracePath::clear()
		{
			if (this->_reflection != 0)
			{
				delete this->_reflection;
				this->_reflection = 0;
			}

			if (this->_passthrough != 0)
			{
				delete this->_passthrough;
				this->_passthrough = 0;
			}
		}

		RAY_API const Fragment TracePath::fragment() const
		{
			return this->_fragment;
		}

		RAY_API void TracePath::operator=(const Fragment& frag)
		{
			this->clear();
			this->_fragment = frag;
		}

	}
}