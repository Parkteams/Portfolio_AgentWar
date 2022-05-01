#include "stdafx.h"
#include "Character.h"
#include "Player.h"
#include "NPC1.h"

NPC1::NPC1()
{
    NPC1_Idle = new ObImage(L"Image/TDS/NPC/Gunner2.png");
    NPC1_Idle->Scale = Vector2(120.0f, 120.0f);
    NPC1_Idle->P = &Root->RT;

    HitBox = new ObRect();
    HitBox->isFill = false;
    HitBox->Scale = Vector2(30.0f, 30.0f);
    HitBox->P = &Root->T;

    Range = new ObCircle();
    Range->isFill = false;
    Range->Scale = Vector2(120.0f, 120.0f);
    Range->P = &Root->RT;

    Rotation = 0.0f;
}

NPC1::~NPC1()
{
    delete NPC1_Idle;
    delete HitBox;
    delete Range;
}

void NPC1::Update()
{
    
}

void NPC1::LateUpdate()
{
    //if (isCollision(Range, pl->GetPos()))
    //{
    //    if(isCollision(HitBox, g_WorldMouse))
    //    if (INPUT->KeyDown(VK_LBUTTON))
    //    {
    //        LookTarget2(pl->GetPos(), NPC1_Idle, -Rotation);
    //    }
    //}
}

void NPC1::Render()
{
    Character::Render();
    NPC1_Idle->Render();
    /*HitBox->Render();
    Range->Render();*/
}
