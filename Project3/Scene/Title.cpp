#include <iostream>
#include<DxLib.h>
#include <string>
#include<sstream>
#include "Title.h"
#include"../Vector2.h"
#include "SceneManager.h"
#include"../Netwark/Netwark.h"
#include"../_debug/_DebugConOut.h"
#include"../input/Pad.h"


Title::Title()
{
	Screensizex = 0;
	Screensizey = 0;
	imagepos.x = 0;
	imagepos.y = 0;

	Init();

	int mode;
	auto ipdata = lpNetwark.GetIp();
	IPDATA hostIp;
	TRACE("自分のIPアドレス.%d.%d.%d.%d\n",ipdata.d1,ipdata.d2,ipdata.d3,ipdata.d4);
	do
	{
		TRACE("モード選択…0:ホスト,1:ゲスト,2:オフライン\n");
		std::cin >> mode;
		if (mode == 0)
		{
			lpNetwark.SetNetWorkMode(NetworkMode::HOST);
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
		if (mode == 2)
		{
			lpNetwark.SetNetWorkMode(NetworkMode::OFF);
		}
	} while (mode < 0 || mode > 2);
	
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
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1)& PAD_INPUT_DOWN)
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
