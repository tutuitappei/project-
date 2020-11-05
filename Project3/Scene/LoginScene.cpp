#include <iostream>
#include<DxLib.h>
#include <string>
#include<sstream>
#include "LoginScene.h"
#include "Title.h"
#include"../Vector2.h"
#include "SceneManager.h"
#include"../Netwark/Network.h"
#include"../_debug/_DebugConOut.h"
#include"../input/Pad.h"


LoginScene::LoginScene()
{
	Screensizex = 0;
	Screensizey = 0;

	_map.SetMapInit();

	int mode;
	auto ipdata = lpNetwark.GetIp();
	IPDATA hostIp;
	IPDATA oldhostIp;
	TRACE("自分のIPアドレス.%d.%d.%d.%d\n", ipdata.d1, ipdata.d2, ipdata.d3, ipdata.d4);
	do
	{
		TRACE("モード選択…\n0:ホスト\n1:ゲスト\n");
		std::ifstream ifs("oldhost.txt");
		if (!ifs) {
			TRACE("前の相手のホストIPがありませんでした\n");
		}
		std::string buf;
		ifs >> buf;
		if (ifs)
		{
			std::string ipfn;
			std::string ip;
			ip = buf;
			std::stringstream ipnum(ip);

			auto GetIpNum = [&]() {
				std::getline(ipnum, ipfn, '.');
				return atoi(ipfn.c_str());
			};


			oldhostIp.d1 = GetIpNum();
			oldhostIp.d2 = GetIpNum();
			oldhostIp.d3 = GetIpNum();
			oldhostIp.d4 = GetIpNum();
			TRACE("2:ゲスト(%d.%d.%d.%d)\n", oldhostIp.d1, oldhostIp.d2, oldhostIp.d3, oldhostIp.d4);
		}
		ifs.close();
		TRACE("3:オフライン\n");
		std::cin >> mode;
		if (mode == 0)
		{
			lpNetwark.SetNetWorkMode(NetworkMode::HOST);
			lpNetwark.ChecLink();
		}
		if (mode == 1)
		{
			lpNetwark.SetNetWorkMode(NetworkMode::GEST);
			std::string ipfn;
			std::string ip;
			std::cin >> ip;
			std::stringstream ipnum(ip);

			auto GetIpNum = [&]() {
				std::getline(ipnum, ipfn, '.');
				return atoi(ipfn.c_str());
			};


			hostIp.d1 = GetIpNum();
			hostIp.d2 = GetIpNum();
			hostIp.d3 = GetIpNum();
			hostIp.d4 = GetIpNum();

			lpNetwark.ConnectHost(hostIp);

			std::ofstream ofs("oldhost.txt");
			if (ofs)
			{
				ofs << ip << std::endl;
			}
			else
			{
				TRACE("ファイルオープンに失敗\n");
			}
			ofs.close();

		}
		if (mode == 2)
		{
			lpNetwark.SetNetWorkMode(NetworkMode::GEST);
			lpNetwark.ConnectHost(oldhostIp);
		}
		if (mode == 3)
		{
			lpNetwark.SetNetWorkMode(NetworkMode::OFF);
		}
	} while (mode < 0 || mode > 4);
	TRACE("%dです\n", lpNetwark.GetActive());


	Init();

}

LoginScene::~LoginScene()
{
}

void LoginScene::Draw(void)
{
	GetDrawScreenSize(&Screensizex, &Screensizey);
	DrawGraph(imagepos.x, imagepos.y, _image, true);
	_map.DrawMap(Layer::Bg);
	_map.DrawMap(Layer::Item);
	_map.DrawMap(Layer::Obj);
	_map.DrawMap(Layer::Char);

	//DrawBox(0, 0, 500, 500, 0xaaaaaa, true);
}

void LoginScene::Init(void)
{
	_image = LoadGraph("image/images.png");

	imagepos.x = 0;
	imagepos.y = 0;
	std::pair<int, int> data;
	data.first = 0;
	data.second = 0;
	if (lpNetwark.GetNetWorkMode() == NetworkMode::HOST)
	{
		lpNetwark.TmxCheck("map/untitled2.tmx");
		lpNetwark.Oneletter();

		data.first = imagepos.x;
		data.second = imagepos.y;
		NetWorkSend(lpNetwark.GetNetHandle(), &data, sizeof(data));

		lpNetwark.SendStanby();
		lpNetwark.GetRevStart();
	}
	else if (lpNetwark.GetNetWorkMode() == NetworkMode::GEST)
	{
		lpNetwark.TmxChat();
		lpNetwark.TmxDataRev();
		if (GetNetWorkDataLength(lpNetwark.GetNetHandle()) >= sizeof(data))
		{
			NetWorkRecv(lpNetwark.GetNetHandle(), &data, sizeof(data));
			imagepos.x = data.first;
			imagepos.y = data.second;
		}
		lpNetwark.SendStart();
	}
	else
	{
		if (lpNetwark.GetNetWorkMode() != NetworkMode::OFF)
		{
			TRACE("初期化中に異常が発生しました\n");
		}
	}
	controller = std::make_unique<Pad>();
	controller->Setup(_id);
}

void LoginScene::Updata(void)
{
	//for (auto data : controller->GetCntData())
	//{

	//	if ((data.first == InputID::Down) && (data.second[static_cast<int>(Trg::Now)]))
	//	{
	//		imagepos.y += 10;
	//	}
	//	if (data.second[static_cast<int>(Trg::Now)] && !data.second[static_cast<int>(Trg::Old)])
	//	{

	//		if ((data.first == InputID::Left))
	//		{
	//			imagepos.x -= 10;
	//		}
	//		if ((data.first == InputID::Right))
	//		{
	//			imagepos.x += 10;
	//		}
	//		if ((data.first == InputID::Up))
	//		{
	//			imagepos.y -= 10;
	//		}
	//		if ((data.first == InputID::Btn1))
	//		{
	//			//Rota(_stage.puyoVec[_targetID]->pos(), _stage.puyoVec[_targetID ^ 1]->pos(), true);
	//		}
	//		if ((data.first == InputID::Btn2))
	//		{
	//			//Rota(_stage.puyoVec[_targetID]->pos(), _stage.puyoVec[_targetID ^ 1]->pos(), false);
	//		}
	//	}

	//}


	

}