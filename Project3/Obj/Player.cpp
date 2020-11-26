#include<DxLib.h>
#include<functional>
#include"../Netwark/Network.h"
#include"Player.h"
#include"../_debug/_DebugConOut.h"
#include"../input/Keyboard1.h"
#include"../input/Pad.h"

Player::Player()
{
	cdir.first = InputID::Down;
	cdir.second = InputID::Down;
	_state.first = DIR::DOWN;
	_state.second = Animstate::Idel;
	aliveFrag[CheckID()] = true;
	_bpos = { _pos.x,_pos.y + (PL_Y - HBlockSize) };
	animCnt = 0;

	Init();
}

Player::Player(Vector2 vec, int id)
{
	cdir.first = InputID::Down;
	cdir.second = InputID::Down;
	_state.first = DIR::DOWN;
	_state.second = Animstate::Idel;
	aliveFrag[CheckID()] = true;
	_pos = vec;
	_bpos = { _pos.x,_pos.y + (PL_Y - HBlockSize) };
	animCnt = 0;
	SetID(id);
	Init();
}

Player::~Player()
{
}

void Player::Update(void)
{

	if (CheckHitKey(KEY_INPUT_PGUP))
	{
		controller = std::make_unique<Pad>();
		controller->Setup(CheckID());
	}
	else if (CheckHitKey(KEY_INPUT_PGDN))
	{
		controller = std::make_unique<Keyboard1>();
		controller->Setup(CheckID());
	}

	(*controller)();
	if (CheckAlive(playerID))
	{
		Move();
		ChangPosTile(_bpos);
	}

	animCnt++;
}

void Player::DrawObj(void)
{
	DrawBox(_bpos.x, _bpos.y, _bpos.x + PL_X, _bpos.y + HBlockSize, 0xffffff, false);

	for (auto&& bom : _bombvec)
	{
		bom->DrawObj();
	}

	DrawGraph(_pos.x, _pos.y, imagechar[CheckID()][(((animCnt / 10) % 4) * 5) + static_cast<int>(_dir[CheckID()])], true);
}

Vector2 Player::ChangPosTile(Vector2 pos)
{
	_changpos.x = pos.x / HBlockSize;
	_changpos.y = pos.y / HBlockSize;
	return _changpos;
}

void Player::SetMap(void)
{
}

void Player::SetAnimSt(void)
{
}

void Player::Init(void)
{
	std::pair<int, int> data;

	//ホスト時
	data.first = _pos.x;
	data.second = _pos.y;
	NetWorkSend(lpNetwark.GetNetHandle(), &data, sizeof(data));

	//ゲスト時
	if (GetNetWorkDataLength(lpNetwark.GetNetHandle()) >= sizeof(data))
	{
		NetWorkRecv(lpNetwark.GetNetHandle(), &data, sizeof(data));
		_pos.x = data.first;
		_pos.y = data.second;
	}

	LoadDivGraph("image/bomberman.png", 20, 5, 4, 32, 50, imagechar[CheckID()]);
	
	controller = std::make_unique<Keyboard1>();
	//controller = std::make_unique<Pad>();
	controller->Setup(CheckID());
}

void Player::SetID(int num)
{
	playerID = num;
}

int Player::CheckID(void)
{
	return playerID;
}

int Player::CheckDrop(unsigned int time, int num)
{
	return num / (time / 60);
}

bool Player::Alive(void)
{
	return false;
}

void Player::Move(void)
{

	if (CheckMove(_state.first))
	{
		if ((lpNetwark.GetNetWorkMode() == NetworkMode::OFF))
		{
			DefUpdata();
		}
	}
}

void Player::InstanceBomb(int x, int y, int PLID)
{
	Vector2 bombpos = { x,y };

	auto id = PLID;
	_bombvec.emplace(_bombvec.begin(), std::make_unique<Bomb>(bombpos, id));
}

bool Player::hitObject(void)
{
	//if ()
	//{
	//	return true;
	//}
	return false;
}

InputID Player::CheckDIR(void)
{
	for (auto &data : controller->GetCntData())
	{
		if (data.second[static_cast<int>(Trg::Now)] && !data.second[static_cast<int>(Trg::Old)])
		{
			cdir.second = data.first;
			break;
		}
	}
	if (cdir.first != cdir.second)
	{
		cdir.first = cdir.second;
	}

	return cdir.first;
}

bool Player::CheckMove(DIR _dir)
{
	if (static_cast<int>(_dir) > static_cast<int>(DIR::RIGHT))
	{
		return false;
	}
	return true;
}

bool Player::CheckAnimSt(Animstate _as)
{
	if (_as == Animstate::Walk)
	{
		return true;
	}
	return false;
}

void Player::DefUpdata(void)
{
	MesPacket mpacket;
	unionData umdata;

	for (auto& data : controller->GetCntData())
	{
		if ((data.second[static_cast<int>(Trg::Now)]))
		{
			if ((CheckDIR() == InputID::Down) && (data.first == CheckDIR()))
			{
				if (!hitObject())
				{
					_pos.y += 10;
					_bpos.y += 10;
				}
				SetDir(DIR::DOWN);
				break;
			}
			if ((CheckDIR() == InputID::Up) && (data.first == CheckDIR()))
			{
				if (!hitObject())
				{
					_pos.y += -10;
					_bpos.y += -10;
				}
				SetDir(DIR::UP);
				break;
			}
			if ((CheckDIR() == InputID::Left) && (data.first == CheckDIR()))
			{
				if (!hitObject())
				{
					_pos.x += -10;
					_bpos.x += -10;
				}
				SetDir(DIR::LEFT);
				break;
			}
			if ((CheckDIR() == InputID::Right) && (data.first == CheckDIR()))
			{
				if (!hitObject())
				{
					_pos.x += 10;
					_bpos.x += 10;
				}
				SetDir(DIR::RIGHT);
				break;
			}
		}
		umdata.iData[0] = _pos.x;
		umdata.iData[1] = _pos.y;
		//lpNetwark.SendMes(MesType::POS, mpacket);
		//lpNetwark.GetNetHandle(), & data, sizeof(data)

		if ((data.second[static_cast<int>(Trg::Now)])&& !(data.second[static_cast<int>(Trg::Old)]))
		{
			if (data.first == InputID::Btn1)
			{
				//lpNetwark.SendMes(MesType::BOM_SET, mpacket);
				InstanceBomb(_bpos.x, _bpos.y, CheckID());
			}
		}
	}
}

void Player::NetUpdata(void)
{
	std::pair<int, int> data;

		if (!lpNetwark.CheckLost())
	{
		if (GetNetWorkDataLength(lpNetwark.GetNetHandle()) >= sizeof(data))
		{
			NetWorkRecv(lpNetwark.GetNetHandle(), &data, sizeof(data));
			_pos.x += data.first;
			_pos.y += data.second;
		}
	}
	else
	{
		lpNetwark.ChecLink();
	}
}

void Player::AutUpdata(void)
{
}

bool Player::CheckAlive(int pnum)
{
	if (CheckHitKey(KEY_INPUT_O))
	{
		aliveFrag[pnum] = false;
		SetDir(DIR::DEAD);
		//lpNetwark.SendMes(MesType::DETH, mpacket);
	}
	return aliveFrag[pnum];
}

void Player::SetDir(DIR dir)
{
	_dir[CheckID()] = dir;
}
