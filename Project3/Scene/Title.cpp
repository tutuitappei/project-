#include <iostream>
#include<DxLib.h>
#include <string>
#include<sstream>
#include "Title.h"
#include"../Vector2.h"
#include "SceneManager.h"
#include"../Netwark/Network.h"
#include"../_debug/_DebugConOut.h"
#include"../input/Pad.h"


Title::Title()
{
	Screensizex = 0;
	Screensizey = 0;

	_map.SetMapData();

	int mode;
	auto ipdata = lpNetwark.GetIp();
	IPDATA hostIp;
	TRACE("自分のIPアドレス.%d.%d.%d.%d\n",ipdata.d1,ipdata.d2,ipdata.d3,ipdata.d4);
	do
	{
		TRACE("モード選択…\n0:ホスト\n1:ゲスト\n");
		//TRACE("2:ゲスト(%d.%d.%d.%d)\n3:オフライン\n",);
		TRACE("\n3:オフライン\n");
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
			hostIp.d2= GetIpNum();
			hostIp.d3 = GetIpNum();
			hostIp.d4 = GetIpNum();

			lpNetwark.ConnectHost(hostIp);
		}
		//if ()
		//{
		//	if (mode == 2)
		//	{
		//		lpNetwark.SetNetWorkMode(NetworkMode::GEST);
		//		std::string ipfn;
		//		std::string ip;
		//		std::cin >> ip;
		//		std::stringstream ipnum(ip);

		//		auto GetIpNum = [&]() {
		//			std::getline(ipnum, ipfn, '.');
		//			return atoi(ipfn.c_str());
		//		};


		//		hostIp.d1 = GetIpNum();
		//		hostIp.d2 = GetIpNum();
		//		hostIp.d3 = GetIpNum();
		//		hostIp.d4 = GetIpNum();

		//		lpNetwark.ConnectHost(hostIp);
		//	}
		//}
		if (mode == 3)
		{

			lpNetwark.SetNetWorkMode(NetworkMode::OFF);
		}
	} while (mode < 0 || mode > 3);
	TRACE("%dです\n", lpNetwark.GetActive());


	Init();
	
}

Title::~Title()
{
}

void Title::Draw(void)
{
	GetDrawScreenSize(&Screensizex,&Screensizey);
	DrawGraph(imagepos.x,imagepos.y,_image,true);
}

void Title::Init(void)
{
	_image = LoadGraph("image/images.png");

	imagepos.x = 0;
	imagepos.y = 0;
	std::pair<int, int> data;
	data.first = 0;
	data.second = 0;
	if (lpNetwark.GetNetWorkMode() == NetworkMode::HOST)
	{


		data.first = imagepos.x;
		data.second = imagepos.y;
		NetWorkSend(lpNetwark.GetNetHandle(), &data, sizeof(data));

	}
	else if (lpNetwark.GetNetWorkMode() == NetworkMode::GEST)
	{
		if (GetNetWorkDataLength(lpNetwark.GetNetHandle()) >= sizeof(data))
		{
			NetWorkRecv(lpNetwark.GetNetHandle(), &data, sizeof(data));
			imagepos.x = data.first;
			imagepos.y = data.second;
		}

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

void Title::Updata(void)
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
	int lendx = 0;
	int lengy = 0;
	std::pair<int, int> data;
	data.first = 0;
	data.second = 0;
	if (lpNetwark.GetNetWorkMode() == NetworkMode::HOST)
	{
		if (!lpNetwark.CheckLost())
		{
			if (GetNetWorkDataLength(lpNetwark.GetNetHandle()) >= sizeof(data))
			{
				NetWorkRecv(lpNetwark.GetNetHandle(), &data, sizeof(data));
				imagepos.x += data.first;
				imagepos.y += data.second;
			}
		}
		else
		{
			lpNetwark.ChecLink();
		}
	}
	else if(lpNetwark.GetNetWorkMode() == NetworkMode::GEST)
	{
		if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)
		{
			lengy = 10;
		}
		if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)
		{
			lengy = -10;
		}
		if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)
		{
			lendx = -10;
		}
		if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT)
		{
			lendx = 10;
		}
		data.first = lendx;
		data.second = lengy;
		NetWorkSend(lpNetwark.GetNetHandle(), &data, sizeof(data));
	}
	else if (lpNetwark.GetNetWorkMode() == NetworkMode::OFF)
	{
		if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)
		{
			imagepos.y += 10;
		}
		if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)
		{
			imagepos.y -= 10;
		}
		if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)
		{
			imagepos.x -= 10;
		}
		if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT)
		{
			imagepos.x += 10;
		}
	}
	else
	{
		TRACE("ゲーム中に異常が発生しました\n");
	}
	
}
