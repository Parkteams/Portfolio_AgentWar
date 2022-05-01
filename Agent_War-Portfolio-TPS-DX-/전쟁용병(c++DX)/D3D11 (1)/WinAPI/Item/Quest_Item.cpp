#include "stdafx.h"
#include "Item.h"
#include "Quest_Item.h"

Quest_Item::Quest_Item()
{
    QuestItem = new ObImage(L"Image/TDS/Item/Army Box.png");
    QuestItem->Scale = Vector2(50.0f, 50.0f);
    QuestItem->P = &Root->RT;

    HitBox = new ObRect();
    HitBox->isFill = false;
    HitBox->Scale = Vector2(40.0f, 20.0f);
    HitBox->P = &Root->RT;

    isEat = false;
}

Quest_Item::~Quest_Item()
{
    delete QuestItem;
    delete HitBox;
}

void Quest_Item::Update()
{
}

void Quest_Item::Render()
{
    Item::Render();
    QuestItem->Render();
    /*HitBox->Render();*/
}
