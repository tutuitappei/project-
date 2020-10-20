#include "Map.h"

Map::Map()
{
	_maplayer = Layer::Bg;
	_mapchip = 32;
	_mapPos.x = 0;
	_mapPos.y = 0;
	Init();
}

Map::~Map()
{
}

int Map::SetMapData(Layer layer)
{
	return 0;
}

void Map::Init(void)
{
	//_mapData.insert(std::make_pair(Layer::BG, ));
	//_mapData.insert(std::make_pair(Layer::Item, ));
	//_mapData.insert(std::make_pair(Layer::Obj, ));
	//_mapData.insert(std::make_pair(Layer::Char, ));
}
