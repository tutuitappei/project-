#pragma once
#include<map>
#include"Vector2.h"
#include"include/TMXParser.h"

#define MAP_HEIGHT 20;
#define MAP_WIDTH 28;

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
	
private:
	void Init(void);
	TMX::Parser _tmx;
	Layer _maplayer;
	MapData _mapData;

	bool DrawMap(Layer layer);
	MapData SetMapData();

	int _mapchipdata[12];
	int _mapchip;
	Vector2 _mapPos;
};

