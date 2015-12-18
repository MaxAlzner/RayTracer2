
#include "..\include\MediaLoader.h"

namespace medialoader
{
	namespace Image
	{

		MEDIALOADERAPI void AnimSequence::play(String name)
		{
			this->_current = 0;
			this->_increment = 1;
			if (this->_sheet != 0)
			{
				if (this->_playing != 0 && this->_playing->name == name)
				{
					return;
				}

				for (int i = 0; i < this->_sheet->_animations.count(); i++)
				{
					AnimSheet::sequenceType* sequence = this->_sheet->_animations[i];

					if (sequence != 0 && sequence->name == name)
					{
						this->_playing = sequence;
						this->_paused = false;
					}
				}
			}
		}
		MEDIALOADERAPI void AnimSequence::stop()
		{
			this->rewind();
			this->_paused = true;
		}
		MEDIALOADERAPI void AnimSequence::rewind()
		{
			if (this->_playing != 0)
			{
				this->_current = 0;
				this->_increment = 1;
			}

		}

		MEDIALOADERAPI void AnimSequence::nextFrame()
		{
			if (this->_playing != 0 && !this->_paused)
			{
				this->_current = (this->_current + this->_increment) % this->_playing->frames;

				if (this->_playing->playOnce && (this->_current < 1 || this->_current >= this->_playing->frames - 1))
				{
					this->rewind();
					return;
				}

				if (this->_playing->pingPong && (this->_current < 1 || this->_current >= this->_playing->frames - 1))
				{
					this->_increment *= -1;
				}
			}
		}

		MEDIALOADERAPI void AnimSequence::setSheet(AnimSheet* sheet)
		{
			this->_sheet = sheet;
			this->_playing = 0;
			this->_current = 0;
			this->_increment = 1;
			this->_paused = true;
		}
		MEDIALOADERAPI void AnimSequence::getFrame(vec2& uv0, vec2& uv1) const
		{
			if (this->_playing != 0)
			{
				AnimSheet::frameType frame = this->_playing->sequence[this->_current];
				uv0.x = frame.uv0.x;
				uv0.y = frame.uv0.y;
				uv1.x = frame.uv1.x;
				uv1.y = frame.uv1.y;
			}
		}

	}
}