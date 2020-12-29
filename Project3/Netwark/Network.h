#pragma once
#include<DxLib.h>
#include<memory>
#include<vector>
#include<chrono>
#include<thread>
#include<mutex>
#include<map>
#include<string>
#include<functional>
#include"NetWorkst.h"

#define lpNetwark Netwark::GetInstance()

enum class MesType : unsigned char
{
	NON = 100,
	COUNT_ROOM,			//接続待ちカウントダウン
	ID,					//自分のIDとプレイヤー数
	STANBY_HOST,		//初期化情報送信完了(ホスト)
	STANBY_GEST,		//初期化完了(ゲスト)
	COUNT_GAME,			//全員の初期化完了後のゲーム開始カウントダウン
	TMX_SIZE,			//TMXのサイズの送信(ホスト)
	TMX_DATA,			//TMXのCSVの送信(ホスト)
	POS,				//プレイヤーの座標
	BOM_SET,			//ボムの座標
	DETH,				//死亡情報
	RESULT,				//勝負の結果情報の送信:MAX5人(ホスト)
	LOST,				//切断時に生成
	MAX
};
struct MesData
{
	MesType type;
	unsigned char next;		//データ送信が分割の場合に次があるかないか
	unsigned short sendID;	//分割送信時のナンバリング
	unsigned int length;	//データー長
};
union Header
{
	MesData hd;
	unsigned int hamu[2];
};
union unionData
{
	unsigned int uiData;
	int iData;
	char cData[4];  //cData[0]→横のマス数:cData[1]→縦のマス数:cData[2]→レイヤーID:cData[3]→今は空の容量確保;
	//int iData[2];
	//char cData[8];
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

	//新規作成
	void Thread(void);
	bool GetFrag(void);

	void readtmx(std::string path);

	void SendUpdata(MesType mtype);
	void SendUpdata(MesType mtype, MesPacket _mpacket);
private:
	Netwark();
	~Netwark();
	bool SendWait(void);
	bool IrregularCheck(MesType _mestype);
	void LetterSet(void);
	void LetterReceive(void);
	void SetHeader(Header head, MesPacket pack);
	void SendHeader(void);

	void FuncMode(MesType _mestype);


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


	//新規作成
	void RevUpdata(void);	//受信のアップデート
	void RunUpdata(void);	//スレッドを作る関数

	void Countroom(const MesPacket& mest);			//接続待ちカウントダウン
	void Iddata(const MesPacket& mest);			//自分のIDとプレイヤー数
	void StanbyHost(const MesPacket& mest);		//初期化情報送信完了(ホスト)
	void StanbyGest(const MesPacket& mest);		//初期化完了(ゲスト)
	void Countgame(const MesPacket& mest);			//全員の初期化完了後のゲーム開始カウントダウン
	void TmxSize(const MesPacket& mest);			//TMXのサイズの送信(ホスト)
	void TmxData(const MesPacket& mest);			//TMXのCSVの送信(ホスト)
	void Posd(const MesPacket& mest);				//プレイヤーの座標
	void Bomset(const MesPacket& mest);			//ボムの座標
	void Deth(const MesPacket& mest);				//死亡情報
	void Result(const MesPacket& mest);			//勝負の結果情報の送信:MAX5人(ホスト)
	void LostNet(const MesPacket& mest);			//切断時に生成

	bool startFlag;

	int _width;
	int _hight;
	int _layernum;

	std::thread _thread;
	std::mutex _mute;	//ロックガードに使われるやつ
	MesType keytype;

	std::map<MesType, std::vector<unionData>> _revdata;

	std::map<MesType, std::function<void(const MesPacket&)>> _funcmode;
};

