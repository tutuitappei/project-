#include <iostream>
#include<DxLib.h>
#include <string>
#include<sstream>
#include "Title.h"
#include"../Vector2.h"
#include "SceneManager.h"
#include"../Netwark/Netwark.h"
#include"../_debug/_DebugConOut.h"


Title::Title()
{
	Screensizex = 0;
	Screensizey = 0;
	int mode;
	auto ipdata = lpNetwark.GetIp();
	IPDATA hostIp;
	TRACE("������IP�A�h���X.%d.%d.%d.%d\n",ipdata.d1,ipdata.d2,ipdata.d3,ipdata.d4);
	do
	{
		TRACE("���[�h�I���c0:�z�X�g,1:�Q�X�g,2:�I�t���C��\n");
		std::cin >> mode;
		if (mode == 0)
		{
			lpNetwark.SetNetWorkMode(NetworkMode::HOST);
		}
		if (mode == 1)
		{
			lpNetwark.SetNetWorkMode(NetworkMode::GEST);
			std::string ipa;
			std::string ip;
			std::cin >> ip;
			std::stringstream ipb = static_cast<std::stringstream>(ip);
			std::getline(ipb,ipa,'.');
			hostIp.d1 = ipa.;

			lpNetwark.ConnectHost(hostIp);
		}
		if (mode == 2)
		{
			lpNetwark.SetNetWorkMode(NetworkMode::OFF);
		}
	} while (mode < 0 || mode > 2);
	
	Init();
}

Title::~Title()
{
}

void Title::Draw(void)
{
	GetDrawScreenSize(&Screensizex,&Screensizey);
}

void Title::Init(void)
{
}

void Title::Updata(void)
{
}
