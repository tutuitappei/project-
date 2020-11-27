#pragma once
#include "Obj.h"
#include"../Map.h"
#include"../Vector2.h"

class Block :
    public Obj
{
public:
    Block();
    ~Block();

    void Update(void) override;
    void DrawObj(void) override;
    void ChangPosTile(Vector2 pos) override;
private:
    void Init(void);
    void SetMap(void);

    bool Alive(void);
    void Break(void);

    Vector2 _changpos;
};

