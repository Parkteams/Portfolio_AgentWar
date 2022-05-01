#include "stdafx.h"
#include "Obstacle.h"
#include "House2.h"

House2::House2()
{
    House = new ObImage(L"Image/TDS/Object/TDS04_House02.png");
    House->Scale = Vector2(350.0f, 150.0f);
    House->P = &Root->RT;

    HitBox = new ObRect();
    HitBox->isFill = false;
    HitBox->Scale = Vector2(350.0f, 150.0f);
    HitBox->Pivot = Vector2(0.0f, 0.0f);
    HitBox->P = &Root->RT;
}

House2::~House2()
{
    delete House;
    delete HitBox;
}

void House2::Update()
{
}

void House2::Render()
{
    Obstacle::Render();
    House->Render();
    /*HitBox->Render();*/
}
