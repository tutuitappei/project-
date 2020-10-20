#pragma once
#include<map>
#include"Vector2.h"

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

class Map
{
public:
	Map();
	~Map();

	int SetMapData(Layer layer);
private:
	void Init(void);


	int _mapchip;
	Layer _maplayer;


	std::map<Layer, int> _mapData;

	Vector2 _mapPos;
};

