
#include "..\include\MediaLoader.h"

namespace medialoader
{
	namespace Image
	{

		MEDIALOADERAPI void AnimSheet::release()
		{
			for (int i = 0; i < this->_animations.count(); i++)
			{
				delete this->_animations[i];
			}

			this->_animations.clear();
			XmlFile::release();
		}

		MEDIALOADERAPI bool AnimSheet::isEmpty() const
		{
			return XmlFile::isEmpty() || this->_animations.count() < 1;
		}

		MEDIALOADERAPI void AnimSheet::_parse()
		{
			int columns = 0;
			int rows = 0;

			XmlNode* node = 0;
			node = this->root->last_node("sheet");
			if (node != 0)
			{
				XmlNode* child = 0;
				child = node->last_node("columns");
				if (child != 0) columns = XmlFile::ParseInt(child);
				child = node->last_node("rows");
				if (child != 0) rows = XmlFile::ParseInt(child);
			}

			node = root->first_node();
			while (node != 0)
			{
				if (strstr(node->name(), "sequence") != 0)
				{
					const char* name = 0;
					bool playOnce = false;
					bool pingPong = false;
					bool flipped = false;

					XmlAttribute* attribute = 0;
					attribute = node->last_attribute("name");
					if (attribute != 0) name = attribute->value();
					attribute = node->last_attribute("playOnce");
					if (attribute != 0) playOnce = XmlFile::ParseBool(attribute);
					attribute = node->last_attribute("pingPong");
					if (attribute != 0) pingPong = XmlFile::ParseBool(attribute);
					attribute = node->last_attribute("flipped");
					if (attribute != 0) flipped = XmlFile::ParseBool(attribute);

					sequenceType* sequence = new sequenceType;
					sequence->name.paste(name);
					sequence->frames = 0;
					sequence->playOnce = playOnce;
					sequence->pingPong = pingPong;

					XmlNode* child = node->first_node("add");
					while (child != 0)
					{
						int column = 0;
						int row = 0;
						attribute = child->first_attribute("col");
						if (attribute != 0)
						{
							column = XmlFile::ParseInt(attribute);
						}

						attribute = child->first_attribute("row");
						if (attribute != 0)
						{
							row = XmlFile::ParseInt(attribute);
						}

						frameType frame;
						frame.uv0.x = float(column) / float(columns);
						frame.uv0.y = 1.0f - (float(row + 1) / float(rows));
						frame.uv1.x = float(column + 1) / float(columns);
						frame.uv1.y = 1.0f - (float(row) / float(rows));
						sequence->frames++;
						sequence->sequence.add(frame);

						if (flipped)
						{
							float temp = frame.uv0.x;
							frame.uv0.x = frame.uv1.x;
							frame.uv1.x = temp;
							temp = frame.uv0.y;
							frame.uv0.y = frame.uv1.y;
							frame.uv1.y = temp;
						}

						child = child->next_sibling("add");
					}

					this->_animations.add(sequence);
				}

				node = node->next_sibling();
			}
		}

	}
}