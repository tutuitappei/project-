#pragma once
#include <string>
#include "Obj.h"
#include"Block.h"
#include"../input/Controller.h"
#include"../Map.h"
#include"../Vector2.h"

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
    ~Player();


    void SetID(int num);
    int CheckID(void);
    int CheckDrop(unsigned int time, int num);

    void Update(void) override;
    void DrawObj(void) override;
private:
    void Init(void);
    void SetMap(void);
    void SetAnimSt(void);

    bool Alive(void);
    void Move(void);

    bool CheckMove(DIR _dir);
    bool CheckAlive(int pnum);
    bool CheckAnimSt(Animstate _as);

    void HostUpdata(void);
    void GestUpdata(void);
    void OffLineUpdata(void);

    std::pair<DIR, Animstate> _state;
    int playerID = 0;
    Vector2 _pos = { 0,0 };
    bool aliveFrag[2];
};

