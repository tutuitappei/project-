#pragma once
#include<vector>
#include<chrono>
#include <string>
#include "Obj.h"
#include"../input/Controller.h"
#include"../Map.h"
#include"Bomb.h"
#include"Block.h"
#include"../Vector2.h"


using ShareB = std::shared_ptr<Bomb>;

#define PL_X 32
#define PL_Y 50
#define HBlockSize 32
#define DefSpeed 2
#define MaxSpeed 8

enum class DIR
{
    DOWN,
    LEFT,
    UP,
    RIGHT,
    DEAD,
    MAX
};

enum class Animstate
{
    Idel,
    Walk,
    Max
};

class Player :
    public Obj
{
public:
    Player();
    Player(Vector2 vec, int id);
    ~Player();


    void SetID(int num);
    int CheckID(void);
    int CheckDrop(unsigned int time, int num);

    void Update(void) override;
    void DrawObj(void) override;
    void ChangPosTile(Vector2 pos) override;
private:
    std::unique_ptr<Controller> controller;

    void Init(void);
    void SetMap(void);
    void SetAnimSt(void);
    void SetDir(DIR dir);

    bool Alive(void);
    void Move(void);


    void InstanceBomb(int x, int y, int PLID);
    bool hitObject(void);

    InputID CheckDIR(void);
    bool CheckMove(DIR _dir);
    bool CheckAlive(int pnum);
    bool CheckAnimSt(Animstate _as);

    void DefUpdata(void);
    void NetUpdata(void);
    void AutUpdata(void);

    std::pair<DIR, Animstate> _state;
    int imagechar[2][20];
    int playerID = 0;
    int _speed;
    DIR _dir[2];
    Vector2 _pos = { 0,0 };
    Vector2 _bpos;
    Vector2 _changpos;
    bool aliveFrag[2];

    std::vector<ShareB> _bombvec;
    std::pair<InputID, InputID> cdir;

    std::chrono::system_clock::time_point  start, recently;

    int animCnt;

    Block _block;
    Bomb _bomb;
};

