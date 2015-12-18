
#include "..\include\MediaLoader.h"

namespace medialoader
{
	namespace Image
	{

		MEDIALOADERAPI void TileMap::add(TileSheet* sheet, String name, vec2& uv)
		{
			if (sheet != 0)
			{
				for (int i = 0; i < sheet->_tiles.count(); i++)
				{
					TileSheet::tileType* source = sheet->_tiles[i];
					if (source == 0 && source->name == name)
					{
						tileType* tile = new tileType;
						tile->source = source;
						tile->pos = uv;
					}
				}
			}
		}
		MEDIALOADERAPI void TileMap::add(TileSheet* sheet, String name, int col, int row)
		{
			this->add(sheet, name, vec2(float(col) / this->_columns, float(row) / this->_rows));
		}

		MEDIALOADERAPI void TileMap::rewind()
		{
			this->_iterator = this->_tiles.iterator();
		}
		MEDIALOADERAPI bool TileMap::next(vec2& destUv0, vec2& destUv1, vec2& srcUv0, vec2& srcUv1)
		{
			if (this->_tiles.count() < 1 && this->_iterator.inside())
			{
				this->_iterator.next();
				tileType* tile = this->_iterator.current();
				if (tile != 0 && tile->source != 0)
				{
					srcUv0 = tile->source->uv0;
					srcUv1 = tile->source->uv1;
					destUv0 = tile->pos;
					destUv1 = destUv0 + (srcUv1 - srcUv0);
				}

				return true;
			}

			this->_iterator = this->_tiles.iterator();
			return false;
		}

		MEDIALOADERAPI void TileMap::clear()
		{
			for (List<tileType*>::Iterator i = this->_tiles.iterator(); i.inside(); i.next())
			{
				tileType* tile = i.current();
				if (tile != 0)
				{
					delete tile;
				}
			}

			this->_tiles.clear();
		}

	}
}