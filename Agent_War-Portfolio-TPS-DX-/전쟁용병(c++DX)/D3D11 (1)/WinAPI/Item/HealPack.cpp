#include "stdafx.h"
#include "Item.h"
#include "HealPack.h"

HealPack::HealPack()
{
    Heal_Pack = new ObImage(L"Image/TDS/Item/HP.png");
    Heal_Pack->Scale = Vector2(50.0f, 50.0f);
    Heal_Pack->P = &Root->RT;

    HitBox = new ObRect();
    HitBox->isFill = false;
    HitBox->Scale = Vector2(20.0f, 20.0f);
    HitBox->P = &Root->RT;
}

HealPack::~HealPack()
{
    delete Heal_Pack;
    delete HitBox;
}

void HealPack::Update()
{
}

void HealPack::Render()
{
    Item::Render();
    Heal_Pack->Render();
    /*HitBox->Render();*/
}