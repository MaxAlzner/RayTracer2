#ifndef RAY_TRACEPATH_H
#define RAY_TRACEPATH_H

namespace RAY_NAMESPACE
{
	namespace Tracer
	{

		class RAY_API TracePath
		{
		public:

			friend class PhotoEmitter;
			friend class TraceStack;

			inline TracePath() :
				_reflection(0),
				_passthrough(0),
				_depth(0) {}
			inline ~TracePath()
			{
				this->clear();
			}

			void clear();

			const DataObjects::Fragment fragment() const;

			void operator=(const DataObjects::Fragment& frag);

		protected:

			TracePath* _reflection;
			TracePath* _passthrough;
			DataObjects::Fragment _fragment;
			int _depth;

		};

	}
}

#endif