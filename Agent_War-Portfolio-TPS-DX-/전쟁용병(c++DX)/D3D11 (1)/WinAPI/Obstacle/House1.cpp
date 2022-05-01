#include "stdafx.h"
#include "Obstacle.h"
#include "House1.h"

House1::House1()
{
    House = new ObImage(L"Image/TDS/Object/TDS04_0000_House01.png");
    House->Scale = Vector2(150.0f, 150.0f);
    House->P = &Root->RT;

    HitBox = new ObRect();
    HitBox->isFill = false;
    HitBox->Scale = Vector2(150.0f, 150.0f);
    HitBox->Pivot = Vector2(0.0f, 0.0f);
    HitBox->P = &Root->RT;
}

House1::~House1()
{
    delete House;
    delete HitBox;
}

void House1::Update()
{
}

void House1::Render()
{
    Obstacle::Render();
    House->Render();
    /*HitBox->Render();*/
}
