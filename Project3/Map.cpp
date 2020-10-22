#include<DxLib.h>
#include <iostream>
#include <string>
#include "Map.h"
#include"rapidxml-1.13/rapidxml.hpp"
#include"rapidxml-1.13/rapidxml_utils.hpp"// rapidxml::file

using namespace std;
namespace rapid = rapidxml;

Map::Map()
{
	/*rapid::xml_document<> doc;
	rapid::file<> input("./map/untitled.tmx");
	doc.parse<0>(input.data());

	rapid::xml_node<>* node = doc.first_node("map");
	for (rapid::xml_node<>* child = node->first_node();
		child != nullptr;
		child = child->next_sibling()) {
		cout << child->name() << " : [" << child->value() << "]\n";
	}*/


	_maplayer = Layer::Bg;
	_mapchip = 32;
	_mapPos.x = 0;
	_mapPos.y = 0;
	Init();
}

Map::~Map()
{
}

void Map::SetMapData()
{
	_tmx.load("map/untitled.tmx");
}

MapData Map::ReturnData(void)
{
	return _mapData;
}

void Map::Init(void)
{
	//_mapData.insert(std::make_pair(Layer::BG, ));
	//_mapData.insert(std::make_pair(Layer::Item, ));
	//_mapData.insert(std::make_pair(Layer::Obj, ));
	//_mapData.insert(std::make_pair(Layer::Char, ));
}
