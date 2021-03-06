#pragma once
#include<map>
#include"Vector2.h"
#include"include/TMXParser.h"

#define MAP_HEIGHT 17;
#define MAP_WIDTH 21;
#define MAP_CHIP_SIZE 32;

enum class Layer
{
	Bg,
	Item,
	Obj,
	Char,
	MAX
};

using MapData = std::map<Layer, int>;

class Map
{
public:
	Map();
	~Map();

	void SetMapInit(void);
	MapData ReturnData(void);
	bool DrawMap(Layer layer);
private:
	void Init(void);
	TMX::Parser _tmx;
	Layer _maplayer;
	MapData _mapData;
	MapData SetMapData();

	int _mapchipdata[12];
	int _mapchip;
	Vector2 _mapPos;
};

