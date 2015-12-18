
#include "..\include\MediaLoader.h"

namespace medialoader
{
	namespace Image
	{

		MEDIALOADERAPI void TileSheet::release()
		{
			for (int i = 0; i < this->_tiles.count(); i++)
			{
				delete this->_tiles[i];
			}

			this->_tiles.clear();
			XmlFile::release();
		}

		MEDIALOADERAPI bool TileSheet::isEmpty() const
		{
			return XmlFile::isEmpty() || this->_tiles.count() < 1;
		}

		MEDIALOADERAPI void TileSheet::_parse()
		{
			int columns = 0;
			int rows = 0;

			XmlNode* node = 0;
			node = this->root->last_node("sheet");
			if (node != 0)
			{
				XmlNode* child = 0;
				child = node->last_node("columns");
				if (child != 0)
				{
					columns = XmlFile::ParseInt(child);
				}

				child = node->last_node("rows");
				if (child != 0)
				{
					rows = XmlFile::ParseInt(child);
				}
			}

			node = root->first_node();
			while (node != 0)
			{
				if (strstr(node->name(), "tiles") != 0)
				{
					XmlNode* child = node->first_node("add");
					XmlAttribute* attribute = 0;
					while (child != 0)
					{
						const char* name = 0;
						int column = 0;
						int row = 0;
						int columnSpan = 1;
						int rowSpan = 1;

						attribute = child->first_attribute("name");
						if (attribute != 0)
						{
							name = attribute->value();
						}

						attribute = child->first_attribute("col");
						if (attribute != 0)
						{
							column = XmlFile::ParseInt(attribute);
						}

						attribute = child->first_attribute("row");
						if (attribute != 0)
						{
							row = rows - XmlFile::ParseInt(attribute);
						}

						attribute = child->first_attribute("colspan");
						if (attribute != 0)
						{
							columnSpan = XmlFile::ParseInt(attribute);
						}

						attribute = child->first_attribute("rowspan");
						if (attribute != 0)
						{
							rowSpan = XmlFile::ParseInt(attribute);
						}

						tileType* tile = new tileType;
						tile->name = name;
						tile->uv0 = vec2(float(column) / float(columns), float(row) / float(rows));
						tile->uv1 = vec2(float(column + columnSpan) / float(columns), float(row + rowSpan) / float(rows));
						this->_tiles.add(tile);

						child = child->next_sibling("add");
					}
				}

				node = node->next_sibling();
			}
		}

	}
}