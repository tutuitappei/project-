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

	void SetMapData(void);
	MapData ReturnData(void);
	
private:
	void Init(void);
	TMX::Parser _tmx;
	int _mapchip;
	Layer _maplayer;
	MapData _mapData;


	Vector2 _mapPos;
};

