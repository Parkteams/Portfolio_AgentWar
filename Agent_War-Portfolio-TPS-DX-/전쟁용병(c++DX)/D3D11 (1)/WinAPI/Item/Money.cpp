#include "stdafx.h"
#include "Item.h"
#include "Money.h"

Money::Money()
{
    Mo_ney = new ObImage(L"Image/TDS/Item/Money Big.png");
    Mo_ney->Scale = Vector2(50.0f, 50.0f);
    Mo_ney->P = &Root->RT;

    HitBox = new ObRect();
    HitBox->isFill = false;
    HitBox->Scale = Vector2(20.0f, 20.0f);
    HitBox->P = &Root->RT;
}

Money::~Money()
{
    delete Mo_ney;
    delete HitBox;
}

void Money::Update()
{
}

void Money::Render()
{
    Item::Render();
    Mo_ney->Render();
   /* HitBox->Render();*/
}
