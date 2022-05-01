#include "stdafx.h"
#include "Obstacle.h"
#include "Rock.h"

Rock::Rock()
{
    Ro_ck = new ObImage(L"Image/TDS/Object/TDS04_0003_Rock03.png");
    Ro_ck->Scale = Vector2(50.0f, 50.0f);
    Ro_ck->P = &Root->RT;

    HitBox = new ObRect();
    HitBox->isFill = false;
    HitBox->Scale = Vector2(50.0f, 50.0f);
    HitBox->Pivot = Vector2(0.0f, 0.0f);
    HitBox->P = &Root->RT;
}

Rock::~Rock()
{
    delete Ro_ck;
    delete HitBox;
}

void Rock::Update()
{
}

void Rock::Render()
{
    Obstacle::Render();
    Ro_ck->Render();
    /*HitBox->Render();*/
}