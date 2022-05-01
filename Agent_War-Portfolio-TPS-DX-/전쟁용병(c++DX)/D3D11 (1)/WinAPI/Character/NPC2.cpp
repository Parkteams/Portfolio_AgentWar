#include "stdafx.h"
#include "Character.h"
#include "Player.h"
#include "NPC2.h"

NPC2::NPC2()
{
    NPC2_Idle = new ObImage(L"Image/TDS/NPC/Gunner.png");
    NPC2_Idle->Scale = Vector2(120.0f, 120.0f);
    NPC2_Idle->P = &Root->RT;

    HitBox = new ObRect();
    HitBox->isFill = false;
    HitBox->Scale = Vector2(30.0f, 30.0f);
    HitBox->P = &Root->T;

    Range = new ObCircle();
    Range->isFill = false;
    Range->Scale = Vector2(120.0f, 120.0f);
    Range->P = &Root->RT;

    Rotation = 0.0f;
    isClick = false;

    //PLAYER
    SOUND->AddSound("Sound/NPC/HELLO.wav", "NPC_HELLO", false);
}

NPC2::~NPC2()
{
    delete NPC2_Idle;
    delete HitBox;
    delete Range;
}

void NPC2::Update()
{
    
}

void NPC2::LateUpdate()
{
    if (isCollision(Range, pl->GetPos()))
    {
        if (isCollision(HitBox, g_WorldMouse))
            if (INPUT->KeyDown(VK_RBUTTON))
            {
                SOUND->Play("NPC_HELLO");
                SOUND->SetVolume("NPC_HELLO", 1.0f);
                LookTarget2(pl->GetPos(), NPC2_Idle, -Rotation);
                isClick = true;
            }
    }
    if (!isCollision(Range, pl->GetPos()))
    {
        isClick = false;
    }
}

void NPC2::Render()
{
    Character::Render();
    NPC2_Idle->Render();
    /*HitBox->Render();
    Range->Render();*/
}
