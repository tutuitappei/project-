#pragma once
#include<chrono>
#include<vector>
#include"../Vector2.h"
#include "Obj.h"

#define MaxBombID 4

class Bomb :
    public Obj
{
public:
    Bomb();
    Bomb(Vector2 vec, int id);
    ~Bomb();

    void Update(void) override;
    void DrawObj(void) override;
    void ChangPosTile(Vector2 pos) override;
private:
    void Init(void);
    bool BomClash(void);

    Vector2 bpos;
    Vector2 _changpos;

    bool bomflag;
    int bombimage[14];

    int playerID;
    int hostID;
    int bomdid = 0;

    std::chrono::system_clock::time_point  start, end;
};

