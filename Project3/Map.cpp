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

void Map::SetMapInit()
{
	_tmx.load("map/untitled2.tmx");
}

MapData Map::ReturnData(void)
{
	return _mapData;
}

void Map::Init(void)
{
	LoadDivGraph("image/map.png",12,4,3,_mapchip,_mapchip,_mapchipdata);
}

bool Map::DrawMap(Layer layer)
{
	_maplayer = layer;
	//for (auto& _num : _mapchipdata)
//{
//}
	return true;
}

MapData Map::SetMapData()
{
	//lpNetwark.SetNetWorkMode(NetworkMode::GEST);
	//std::string ipfn;
	//std::string ip;
	//std::cin >> ip;
	//std::stringstream ipnum(ip);

	//auto GetIpNum = [&]() {
	//	std::getline(ipnum, ipfn, '.');
	//	return atoi(ipfn.c_str());
	//};


	//hostIp.d1 = GetIpNum();
	//hostIp.d2 = GetIpNum();
	//hostIp.d3 = GetIpNum();
	//hostIp.d4 = GetIpNum();

	//lpNetwark.ConnectHost(hostIp);

	return MapData();
}
