#include "stdafx.h"
#include "Obstacle.h"
#include "Bush.h"

Bush::Bush()
{
    Bu_sh = new ObImage(L"Image/TDS/Object/TDS04_0012_Bush-01.png");
    Bu_sh->Scale = Vector2(50.0f, 50.0f);
    Bu_sh->P = &Root->RT;

    HitBox = new ObRect();
    HitBox->isFill = false;
    HitBox->Scale = Vector2(50.0f, 50.0f);
    HitBox->Pivot = Vector2(0.0f, 0.0f);
    HitBox->P = &Root->RT;
}

Bush::~Bush()
{
    delete Bu_sh;
    delete HitBox;
}

void Bush::Update()
{
}

void Bush::Render()
{
    Obstacle::Render();
    Bu_sh->Render();
   /* HitBox->Render();*/
}