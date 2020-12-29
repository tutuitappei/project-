#include <iostream>
#include<DxLib.h>
#include <string>
#include<sstream>
#include<fstream>
#include "LoginScene.h"
#include "Title.h"
#include "SceneManager.h"
#include"../Netwark/Network.h"
#include"../_debug/_DebugConOut.h"


LoginScene::LoginScene()
{
	Screensizex = 0;
	Screensizey = 0;

	_map.SetMapInit();

	updatefunc[Updatamode::SetNetWork] = std::bind(&LoginScene::SetNetwork, this);
	updatefunc[Updatamode::SetHostIP] = std::bind(&LoginScene::SetHostIP, this);
	updatefunc[Updatamode::SetOldIP] = std::bind(&LoginScene::SetOldIP, this);
	updatefunc[Updatamode::StartInit] = std::bind(&LoginScene::StartInit, this);
	updatefunc[Updatamode::Play] = std::bind(&LoginScene::Played, this);

	key = Updatamode::SetNetWork;

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
	//if (lpNetwark.GetNetWorkMode() == NetworkMode::HOST)
	//{

	//	_map.SetMapInit();

	//	lpNetwark.TmxCheck("map/untitled2.tmx");
	//	lpNetwark.Oneletter();


	//	data.first = imagepos.x;
	//	data.second = imagepos.y;
	//	NetWorkSend(lpNetwark.GetNetHandle(), &data, sizeof(data));

	//	lpNetwark.SendStanby();
	//	//lpNetwark.GetRevStart();
	//}
	//else if (lpNetwark.GetNetWorkMode() == NetworkMode::GEST)
	//{

	//	//lpNetwark.TmxChat();
	//	//lpNetwark.TmxDataRev();

	//	if (GetNetWorkDataLength(lpNetwark.GetNetHandle()) >= sizeof(data))
	//	{
	//		//NetWorkRecv(lpNetwark.GetNetHandle(), &data, sizeof(data));
	//		//imagepos.x = data.first;
	//		//imagepos.y = data.second;
	//	}
	//	//lpNetwark.GetRevStanby();
	//	lpNetwark.SendStart();
	//}
	//else
	//{
	//	if (lpNetwark.GetNetWorkMode() != NetworkMode::OFF)
	//	{
	//		TRACE("���������Ɉُ킪�������܂���\n");
	//	}
	//}
}

void LoginScene::Updata(void)
{
	if (updatefunc[key]())
	{
		lpScene.ChangeScene(SCENE::GAME);

	}
}

bool LoginScene::SetHostIP(void)
{
	std::string ipfn;
	std::string ip;
	/*char s[256];*/
	std::cin >> ip;
	std::istringstream ipnum(ip);

	auto GetIpNum = [&]() {
		std::getline(ipnum, ipfn, '.');
		return atoi(ipfn.c_str());
	};

	hostIp.d1 = GetIpNum();
	hostIp.d2 = GetIpNum();
	hostIp.d3 = GetIpNum();
	hostIp.d4 = GetIpNum();



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

	lpNetwark.ConnectHost(hostIp);

	key = Updatamode::StartInit;

	return false;
}

bool LoginScene::SetNetwork(void)
{

	int mode;

	auto ipdata = lpNetwark.GetIp();


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
			key = Updatamode::StartInit;

		}
		if (mode == 1)
		{
			TRACE("����̃z�X�gIP����͂��Ă�������\n");
			lpNetwark.SetNetWorkMode(NetworkMode::GEST);


			key = Updatamode::SetHostIP;
		}
		if (mode == 2)
		{
			lpNetwark.SetNetWorkMode(NetworkMode::GEST);

			key = Updatamode::SetOldIP;

		}
		if (mode == 3)
		{
			lpNetwark.SetNetWorkMode(NetworkMode::OFF);
			key = Updatamode::Play;
		}
	} while (mode < 0 || mode > 3);
	TRACE("%d�ł�\n", lpNetwark.GetActive());
	return false;
}

bool LoginScene::StartInit(void)
{
	lpNetwark.Thread();
	if (lpNetwark.GetNetWorkMode() == NetworkMode::HOST)
	{
		lpNetwark.SendUpdata(MesType::COUNT_ROOM);
	}
	else
	{
		if (lpNetwark.GetFrag())
		{
			lpNetwark.SendUpdata(MesType::STANBY_GEST);
			key = Updatamode::Play;
		}
	}
	return false;
}

bool LoginScene::Played(void)
{
	return true;
}

bool LoginScene::SetOldIP(void)
{

	lpNetwark.ConnectHost(oldhostIp);
	key = Updatamode::StartInit;
	return false;
}
