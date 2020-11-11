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
	TRACE("������IP�A�h���X.%d.%d.%d.%d\n", ipdata.d1, ipdata.d2, ipdata.d3, ipdata.d4);
	do
	{
		TRACE("���[�h�I���c\n0:�z�X�g\n1:�Q�X�g\n");
		std::ifstream ifs("ini/oldhost.txt");
		if (!ifs) {
			TRACE("�O�̑���̃z�X�gIP������܂���ł���\n");
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
			TRACE("2:�Q�X�g(%d.%d.%d.%d)\n", oldhostIp.d1, oldhostIp.d2, oldhostIp.d3, oldhostIp.d4);
		}
		ifs.close();
		TRACE("3:�I�t���C��\n");
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

			std::ofstream ofs("ini/oldhost.txt");
			if (ofs)
			{
				ofs << ip << std::endl;
			}
			else
			{
				TRACE("�t�@�C���I�[�v���Ɏ��s\n");
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
	TRACE("%d�ł�\n", lpNetwark.GetActive());


	Init();


	lpScene.ChangeScene(SCENE::GAME);
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
		//lpNetwark.TmxCheck("map/movetest.tmx");
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
		lpNetwark.GetRevStanby();
		lpNetwark.SendStart();
	}
	else
	{
		if (lpNetwark.GetNetWorkMode() != NetworkMode::OFF)
		{
			TRACE("���������Ɉُ킪�������܂���\n");
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