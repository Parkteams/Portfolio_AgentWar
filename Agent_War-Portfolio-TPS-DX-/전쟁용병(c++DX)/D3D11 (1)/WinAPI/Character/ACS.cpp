#include "stdafx.h"
#include "Character.h"
#include "ACS.h"
#include "Player.h"
#include "Sniper.h"
#include "Soldier.h"
#include "Storm.h"
#include "Bazooka.h"

ACS::ACS()
{
    Game_Speed = 1.0f;
    DamagedTime = 0.0f;

    Health = ACS_Health;
    isHit = false;

    ACS_Move_B = new ObImage(L"Image/TDS/ACS/ACS_move.png");
    ACS_Move_B->Scale = Vector2(200.0f, 200.0f);
    ACS_Move_B->MaxFrame = Int2(5, 1);
    ACS_Move_B->P = &Root->RT;

    ACS_Idle_T = new ObImage(L"Image/TDS/ACS/ACS_Tower.png");
    ACS_Idle_T->Scale = Vector2(200.0f, 200.0f);
    ACS_Idle_T->Pivot = Vector2(0.0f, -0.07f);
    ACS_Idle_T->Position = Vector2(0.0f, 14.0f);
    ACS_Idle_T->P = &Root->RT;

    ACS_Idle_B = new ObImage(L"Image/TDS/ACS/ACS_Base.png");
    ACS_Idle_B->Scale = Vector2(200.0f, 200.0f);
    ACS_Idle_B->P = &Root->RT;

    ACS_Die_T = new ObImage(L"Image/TDS/ACS/ACS_Broken_Tower.png");
    ACS_Die_T->Scale = Vector2(200.0f, 200.0f);
    ACS_Die_T->MaxFrame = Int2(2, 1);
    ACS_Die_T->P = &Root->T;

    ACS_Die_B = new ObImage(L"Image/TDS/ACS/ACS_Broken_Base.png");
    ACS_Die_B->Scale = Vector2(200.0f, 200.0f);
    ACS_Die_B->MaxFrame = Int2(2, 1);
    ACS_Die_B->P = &Root->RT;

    ACS_Shot_Effect = new ObImage(L"Image/TDS/ACS/ACS_Fire.png");
    ACS_Shot_Effect->Scale = Vector2(50.0f, 80.0f);
    ACS_Shot_Effect->Pivot = Vector2(0.0f, 0.0f);
    ACS_Shot_Effect->Position = Vector2(0.0f, -80.0f);
    ACS_Shot_Effect->MaxFrame = Int2(3, 1);
    ACS_Shot_Effect->P = &ACS_Idle_T->RT;
    ACS_Shot_Effect->Rotation.z += 1.0f * PI;

    ACS_Ride = new ObCircle();
    ACS_Ride->isFill = false;
    ACS_Ride->Scale = Vector2(100.0f, 100.0f);
    ACS_Ride->P = &Root->T;

    //HP
    Hp_Bar = new ObRect();
    Hp_Bar->color = Color(1.0f, 0.0f, 0.0f, 1.0f);
    Hp_Bar->Scale = Vector2(100.0f, 10.0f);
    Hp_Bar->Position = Vector2(-50.0f, 50.0f);
    Hp_Bar->P = &Root->T;
    Hp_Bar->Pivot = OFFSET_LB;

    //ACS HitBox
    HitBox = new ObRect();
    HitBox->isFill = false;
    HitBox->Scale = Vector2(70.0f, 70.0f);
    HitBox->P = &Root->RT;

    //bullet
    for (int i = 0; i < 30; i++)
    {
        SB[i].ACS_Bullet = new ObImage(L"Image/TDS/ACS/ACS_Bullet.png");
        SB[i].ACS_Bullet->Scale = Vector2(50.0f, 80.0f);
        SB[i].ACS_Bullet->Pivot = Vector2(0.0f, 0.7f);
        SB[i].ACS_Bullet->isActive = false;

        SB[i].Hitbox = new ObRect;
        SB[i].Hitbox->Scale = Vector2(30.0f, 30.0f);
        SB[i].Hitbox->Pivot = Vector2(0.0f, 2.3f);
        SB[i].Hitbox->P = &SB[i].ACS_Bullet->RT;
        SB[i].Hitbox->isFill = false;
        SB[i].Hitbox->isActive = false;

        SB[i].Hitbox2 = new ObRect;
        SB[i].Hitbox2->Scale = Vector2(100.0f, 100.0f);
        SB[i].Hitbox2->Pivot = Vector2(0.0f, 0.0f);
        SB[i].Hitbox2->isFill = false;
        SB[i].Hitbox2->isActive = false;

        SB[i].Speed = 500.0f;
        SB[i].Power = 5;
        SB[i].Dir = Vector2(1.0f, 0.0f);
        SB[i].Explode_Time = 0.0f;
        SB[i].Explode = false;
    }

    ACSSpeed = 100.0f;
    Tile_Speed = 1.0f;
    ACSRotateSpeed = 30.0f * TORADIAN;
    ACS_TRotateSpeed = 20.0f * TORADIAN;
    Shooting_Time = 0.0f;
    Reloading_Time = 0.0f;
    Input_Power = 0.0f;
    isRide = false;

    ACSState = ACS_EMPTY;
    ACSMoveState = ACS_STAND;

    //ACS
    SOUND->AddSound("Sound/ACS/DAMAGED.wav", "ACS_DAMAGED", false);
    SOUND->AddSound("Sound/ACS/MOVE.wav", "ACS_MOVE", true);
    SOUND->AddSound("Sound/ACS/SHOT.wav", "ACS_SHOT", false);
}

ACS::~ACS()
{
    delete HitBox;
    delete Hp_Bar;
    delete ACS_Ride;

    delete ACS_Idle_T;
    delete ACS_Idle_B;
    delete ACS_Move_B;
    delete ACS_Die_T;
    delete ACS_Die_B;
    delete ACS_Shot_Effect;

    for (int i = 0; i < 30; i++)
    {
        delete SB[i].ACS_Bullet;
        delete SB[i].Hitbox;
        delete SB[i].Hitbox2;
    }
}

void ACS::Update()
{
    //IMGUI
    ImGui::SliderFloat("SPEED_ACS", &ACSSpeed, 0.0f, 500.0f);
    
    //hp
    if (Health > ACS_Health)
        Health = ACS_Health;
    if (Health < 1)
        Health = 0;

    PrevPos = Root->Position;

    switch (ACSState)
    {
    case ACS_EMPTY:
        StateEmpty();
        break;
    case ACS_IDLE:
        StateIdle();
        break;
    case ACS_SHOT:
        StateFire();
        break;
    case ACS_DEAD:
        StateDead();
        break;
    }

    switch (ACSMoveState)
    {
    case ACS_MOVE:
        ACSMove();
        break;
    case ACS_STAND:
        ACSStand();
        break;
    }
    //fired bullet
    for (int i = 0; i < 30; i++)
    {
        if (SB[i].ACS_Bullet->isActive)
        {
            SB[i].ACS_Bullet->Position += DeltaTime * SB[i].Speed * SB[i].Dir * Game_Speed;
        }
    }
    //bullet out
    for (int i = 0; i < 30; i++)
    {
        if (SB[i].ACS_Bullet->Position.x > Root->Position.x + 2000.0f or SB[i].ACS_Bullet->Position.x < Root->Position.x - 2000.0f or
            SB[i].ACS_Bullet->Position.y > Root->Position.y + 2000.0f or SB[i].ACS_Bullet->Position.y < Root->Position.y - 2000.0f)
        {
            SB[i].ACS_Bullet->isActive = false;
            SB[i].Hitbox->isActive = false;
        }

    }

    //explode
    for (int i = 0; i < 30; i++)
    {
        if (SB[i].Explode)
        {
            SB[i].Explode_Time += DeltaTime;
            if (SB[i].Explode_Time > 0.5f / Game_Speed)
            {
                SB[i].Explode_Time = 0.0f;
                SB[i].Hitbox2->Position = Root->Position + Vector2(-30000.0f, 30000.0f);
                SB[i].Explode = false;
            }
        }
    }

    if (isHit)
    {
        DamagedTime += DeltaTime;
        ACS_Idle_T->color = Color(0.5f, 0.5f, 0.5f, RndFloat(0.0f, 0.5f));
        ACS_Idle_B->color = Color(0.5f, 0.5f, 0.5f, RndFloat(0.0f, 0.5f));
        ACS_Move_B->color = Color(0.5f, 0.5f, 0.5f, RndFloat(0.0f, 0.5f));
        if (DamagedTime > 1.0f / Game_Speed)
        {
            ACS_Idle_T->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
            ACS_Idle_B->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
            ACS_Move_B->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
            DamagedTime = 0.0f;
            isHit = false;
        }
    }

    if (ACS_Idle_T->Rotation.z > 30 * TORADIAN)
    {
        ACS_Idle_T->Rotation.z = 30 * TORADIAN;
    }
    if (ACS_Idle_T->Rotation.z < -30 * TORADIAN)
    {
        ACS_Idle_T->Rotation.z = -30 * TORADIAN;
    }
}

void ACS::LateUpdate()
{
    //sniper
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (isCollision(HitBox, Sp[i]->SB[j].Hitbox) and !isHit and isRide)
            {
                isHit = true;
                SOUND->Stop("ACS_DAMAGED");
                SOUND->Play("ACS_DAMAGED");
                SOUND->SetVolume("ACS_DAMAGED", 0.3f);
                Sp[i]->SB[j].Sniper_Bullet->Position = Sp[i]->GetPos() + Vector2(-30000.0f, 30000.0f);
                Health -= Sp[i]->SB[j].Power;
            }
        }
    }
    //soldier
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (isCollision(HitBox, Sd[i]->SB[j].Hitbox) and !isHit and isRide)
            {
                Sd[i]->SB[j].Soldier_Bullet->Position = Sd[i]->GetPos() + Vector2(-30000.0f, 30000.0f);
            }
        }
    }
    //storm
    for (int i = 0; i < 18; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (isCollision(HitBox, St[i]->SB[j].Hitbox) and !isHit and isRide)
            {
                St[i]->SB[j].Storm_Bullet->Position = St[i]->GetPos() + Vector2(-30000.0f, 30000.0f);
            }
        }
    }
    //Bazooka
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (isCollision(HitBox, Bz[i]->SB[j].Hitbox) and !isHit and isRide)
            {
                SOUND->Stop("ACS_DAMAGED");
                SOUND->Play("ACS_DAMAGED");
                SOUND->SetVolume("ACS_DAMAGED", 0.3f);
                isHit = true;
                Bz[i]->SB[j].Bazooka_Bullet->Position = Bz[i]->GetPos() + Vector2(-30000.0f, 30000.0f);
                Health -= Bz[i]->SB[j].Power;
            }
        }
    }
}

void ACS::Render()
{
    Character::Render();

    //bullet
    for (int i = 0; i < 30; i++)
    {
        SB[i].ACS_Bullet->Render();
        /*SB[i].Hitbox->Render();
        SB[i].Hitbox2->Render();*/
    }

    switch (ACSMoveState)
    {
    case ACS_MOVE:
        ACS_Move_B->Render();
        break;
    case ACS_STAND:
        ACS_Idle_B->Render();
        break;
    }

    switch (ACSState)
    {
    case ACS_EMPTY:
        ACS_Idle_T->Render();
        break;
    case ACS_IDLE:
        ACS_Idle_T->Render();
        break;
    case ACS_SHOT:
        ACS_Shot_Effect->Render();
        ACS_Idle_T->Render();
        break;
    case ACS_DEAD:
        ACS_Die_B->Render();
        ACS_Die_T->Render();
        break;
    }

    /*HitBox->Render();*/
    Hp_Bar->Render();
    /*ACS_Ride->Render();*/
}

void ACS::Input()
{
    if (INPUT->KeyPress('A'))
    {
        Root->Rotation.z += ACSRotateSpeed * Game_Speed * DeltaTime;
    }
    else if (INPUT->KeyPress('D'))
    {
        Root->Rotation.z -= ACSRotateSpeed * Game_Speed * DeltaTime;
    }
    if (INPUT->KeyPress('W'))
    {
        Input_Power += 2.0f * Game_Speed *DeltaTime;
    }
    else if (INPUT->KeyPress('S'))
    {
        Input_Power -= 2.0f * Game_Speed * DeltaTime;
    }
    if (!INPUT->KeyPress('W') and !INPUT->KeyPress('S'))
    {
        if (Input_Power > 0.1f)
        {
            Input_Power -= DeltaTime * 1.0f;
        }
        else if (Input_Power <  -0.1f)
        {
            Input_Power += DeltaTime * 1.0f;
        }
        else
        {
            Input_Power = 0.0f;
        }
    }

    //최소 최대값 설정
    Saturate(Input_Power, -1.0f, 2.0f);
    Root->Position += RadianToDir(Root->Rotation.z - PI * 0.5f) * Input_Power * ACSSpeed * Tile_Speed* Game_Speed * DeltaTime;
}

void ACS::StateEmpty()
{
    if (isCollision( ACS_Ride, pl->GetPos()))
    {
        if (INPUT->KeyDown(VK_SPACE))
        {
            pl->PlayerState = PL_RIDE;
            pl->PlayerMoveState = PL_STAND;
            ACSState = ACS_IDLE;
            isRide = true;
        }
    }
    
}

void ACS::StateIdle()
{
    if (!Game_Speed == 0)
    {
        Reloading_Time += DeltaTime;
        if (INPUT->KeyPress('Q'))
        {
            ACS_Idle_T->Rotation.z += ACS_TRotateSpeed * Game_Speed * DeltaTime;
        }
        else if (INPUT->KeyPress('E'))
        {
            ACS_Idle_T->Rotation.z -= ACS_TRotateSpeed * Game_Speed * DeltaTime;
        }
        if (Reloading_Time > 0.0f)
        {
            if (INPUT->KeyDown(VK_LBUTTON))
            {
                ACSState = ACS_SHOT;
                ACS_Shot_Effect->ChangeAnim(_ONCE, 0.03f / Game_Speed);

                //bullet fire
                for (int i = 0; i < 30; i++)
                {
                    if (!SB[i].ACS_Bullet->isActive)
                    {
                        SOUND->Stop("ACS_SHOT");
                        SOUND->Play("ACS_SHOT");
                        SOUND->SetVolume("ACS_SHOT", 0.5f);
                        //격발
                        SB[i].ACS_Bullet->isActive = true;
                        SB[i].Hitbox->isActive = true;
                        SB[i].ACS_Bullet->Position = Root->Position + Vector2(0.0f,14.0f) * RadianToDir(Root->Rotation.z + ACS_Idle_T->Rotation.z) ;
                        SB[i].ACS_Bullet->Rotation.z = ACS_Idle_T->Rotation.z - PI * 1.0f + Root->Rotation.z;
                        SB[i].Dir = RadianToDir(SB[i].ACS_Bullet->Rotation.z + 0.5f * PI);
                        break;
                    }
                }
            }
        }
        if (Input_Power == 0)
        {
            if (INPUT->KeyDown('0'))
            {
                pl->PlayerState = PL_PISTOL;
                pl->PlayerMoveState = PL_STAND;
                ACSState = ACS_EMPTY;
                isRide = false;
                pl->SetPos(Root->Position - Vector2(0.0f, 50.0f));
            }
        }
        
    }
}

void ACS::StateFire()
{
    if (!Game_Speed == 0)
    {
        Shooting_Time += DeltaTime;
        if (Shooting_Time > 0.3f / Game_Speed)
        {
            Shooting_Time = 0.0f;
            ACSState = ACS_IDLE;
            Reloading_Time = -4.0f / Game_Speed;
        }
    }
}

void ACS::StateDead()
{
}


void ACS::ACSStand()
{
    SOUND->Stop("ACS_MOVE");
    if (!Game_Speed == 0 and isRide)
    {
        if (INPUT->KeyPress('A') or INPUT->KeyPress('W') or INPUT->KeyPress('S') or INPUT->KeyPress('D'))
        {
            ACSMoveState = ACS_MOVE;
            ACS_Move_B->ChangeAnim(_LOOP, 0.1f / Game_Speed);
        }
    }
}

void ACS::ACSMove()
{
    SOUND->Play("ACS_MOVE");
    SOUND->SetVolume("ACS_MOVE", 0.3f);
    if (isRide)
    {
        Input();
    }
    if (!Game_Speed == 0 and Input_Power==0)
    {
        if (!INPUT->KeyPress('A') and !INPUT->KeyPress('W') and !INPUT->KeyPress('S') and !INPUT->KeyPress('D'))
        {
            ACSMoveState = ACS_STAND;
        }
    }
    if (Game_Speed == 0)
    {
        ACSMoveState = ACS_STAND;
    }
    
}

void ACS::Turnback()
{
    Root->Position = PrevPos;
}
