#include "stdafx.h"
#include "Item.h"
#include "Armor.h"

Armor::Armor()
{
    Ar_mor = new ObImage(L"Image/TDS/Item/Armor.png");
    Ar_mor->Scale = Vector2(50.0f, 50.0f);
    Ar_mor->P = &Root->RT;

    HitBox = new ObRect();
    HitBox->isFill = false;
    HitBox->Scale = Vector2(20.0f, 20.0f);
    HitBox->P = &Root->RT;
}

Armor::~Armor()
{
    delete Ar_mor;
    delete HitBox;
}

void Armor::Update()
{
}

void Armor::Render()
{
    Item::Render();
    Ar_mor->Render();
    /*HitBox->Render();*/
}
