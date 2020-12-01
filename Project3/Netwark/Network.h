#pragma once
#include<DxLib.h>
#include<memory>
#include<vector>
#include<chrono>
#include<thread>
#include"NetWorkst.h"

#define lpNetwark Netwark::GetInstance()

enum class MesType : unsigned char
{
	NON = 100,
	COUNT_ROOM,			//�ڑ��҂��J�E���g�_�E��
	ID,					//������ID�ƃv���C���[��
	STANBY_HOST,		//��������񑗐M����(�z�X�g)
	STANBY_GEST,		//����������(�Q�X�g)
	COUNT_GAME,			//�S���̏�����������̃Q�[���J�n�J�E���g�_�E��
	TMX_SIZE,			//TMX�̃T�C�Y�̑��M(�z�X�g)
	TMX_DATA,			//TMX��CSV�̑��M(�z�X�g)
	POS,				//�v���C���[�̍��W
	BOM_SET,			//�{���̍��W
	DETH,				//���S���
	LOST,				//�ؒf���ɐ���
	MAX
};
struct MesData
{
	MesType type;
	unsigned char next;		//�f�[�^���M�������̏ꍇ�Ɏ������邩�Ȃ���
	unsigned short sendID;	//�������M���̃i���o�����O
	//unsigned int length;
	int data[2];
};
union Header
{
	MesData hd;
	unsigned int hamu[2];
};
union unionData
{
	unsigned int uiData;
	//int iData;
	//char cData[4];   //cData[0]�����̃}�X��:cData[1]���c�̃}�X��:cData[2]�����C���[ID:cData[3]�����͋�̗e�ʊm��;
	int iData[2];
	char cData[8];
};

using MesPacket = std::vector<unionData>;
using RevPacket = std::pair<MesType, MesPacket>;
using MesPacketList = std::vector<RevPacket>;
using TmxBox = std::vector<char>;

class Netwark
{
public:
	static Netwark& GetInstance(void)
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new Netwark();
		}
		return *s_Instance;
	}

	void Updata(void);
	void Thread(void);

	IPDATA GetIp(void);
	bool SetNetWorkMode(NetworkMode mode);
	NetworkMode GetNetWorkMode(void);
	int GetNetHandle(void);
	bool GetActive(void);
	bool SendMes(MesType _mtype);
	bool SendMes(MesType _mtype, MesPacket _mpacket);
	void RecvMes(void);
	void GetRevStanby(void);
	void GetRevStart(void);
	void SendStanby(void);
	void SendStart(void);
	ActivState GetActiveST(void);
	ActivState ConnectHost(IPDATA hostip);
	bool ChecLink(void);
	bool CheckLost(void);

	void Oneletter(void);

	void TmxChat(void);
	void TmxCheck(const char* filename);
	void TmxDataSend(void);
	void TmxDataRev(void);

	void SetPlayerNum(int id);
	int GetPlayerID(void);
	int GetPlayerMAX(void);
private:
	Netwark();
	~Netwark();
	bool SendWait(void);
	void LetterSet(void);
	void LetterReceive(void);
	void SetHeader(Header head, MesPacket pack);
	void SendHeader(void);

	int playerID = 0;
	int maxplayer = 0;

	//unsigned int lengthd;
	//int count;
	//int volume;
	MesPacketList list;
	TmxBox _box;
	int bot = 0;
	std::unique_ptr <NetWorkst> _state;

	std::chrono::system_clock::time_point  start, end;

	static Netwark* s_Instance;
};

