#include "stdafx.h"
#include "Item.h"
#include "Ammunition.h"

Ammunition::Ammunition()
{
    Ammu_nition = new ObImage(L"Image/TDS/Item/Ammo.png");
    Ammu_nition->Scale = Vector2(50.0f, 50.0f);
    Ammu_nition->P = &Root->RT;

    HitBox = new ObRect();
    HitBox->isFill = false;
    HitBox->Scale = Vector2(40.0f, 20.0f);
    HitBox->P = &Root->RT;
}

Ammunition::~Ammunition()
{
    delete Ammu_nition;
    delete HitBox;
}

void Ammunition::Update()
{
}

void Ammunition::Render()
{
    Item::Render();
    Ammu_nition->Render();
    /*HitBox->Render();*/
}
