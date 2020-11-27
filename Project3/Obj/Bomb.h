#pragma once
#include<chrono>
#include<vector>
#include"../Vector2.h"
#include "Obj.h"

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
};

