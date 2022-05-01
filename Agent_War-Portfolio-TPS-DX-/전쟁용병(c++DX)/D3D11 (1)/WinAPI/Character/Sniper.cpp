#include "stdafx.h"
#include "Character.h"
#include "Sniper.h"
#include "Player.h"
#include "ACS.h"

Sniper::Sniper()
{
    isAlarm = false;
    //setting
    Game_Speed = 1.0f;
    Shooting_Time = 0.0f;
    Reloading_Time = 0.0f;
    DamagedTime = 0.0f;
    isHit = false;
    Rotation = 0.0f;
    isDead = false;

    Health = 10;
    SniperState = SS_IDLE;

    Sniper_Idle = new ObImage(L"Image/TDS/Sniper/Sniper.png");
    Sniper_Idle->Scale = Vector2(120.0f, 120.0f);
    Sniper_Idle->P = &Root->RT;

    Sniper_Die = new ObImage(L"Image/TDS/Sniper/Sniper_Die.png");
    Sniper_Die->Scale = Vector2(120.0f, 120.0f);
    Sniper_Die->MaxFrame = Int2(5, 1);
    Sniper_Die->P = &Root->RT;

    Sniper_Shot = new ObImage(L"Image/TDS/Sniper/Shot.png");
    Sniper_Shot->Scale = Vector2(120.0f, 120.0f);
    Sniper_Shot->P = &Root->RT;

    Sniper_Shot_Effect = new ObImage(L"Image/TDS/Sniper/SniperShotEffect.png");
    Sniper_Shot_Effect->Scale = Vector2(50.0f, 50.0f);
    Sniper_Shot_Effect->MaxFrame = Int2(3, 1);
    Sniper_Shot_Effect->Pivot = Vector2(0.16f, 0.5f);
    Sniper_Shot_Effect->P = &Root->RT;

    //Sniper HitBox
    HitBox = new ObRect();
    HitBox->isFill = false;
    HitBox->Scale = Vector2(30.0f, 30.0f);
    HitBox->P = &Root->T;

    //HP
    Hp_Bar = new ObRect();
    Hp_Bar->color = Color(1.0f, 0.0f, 0.0f, 1.0f);
    Hp_Bar->Scale = Vector2(50.0f, 10.0f);
    Hp_Bar->Position = Vector2(-25.0f, 25.0f);
    Hp_Bar->P = &Root->T;
    Hp_Bar->Pivot = OFFSET_LB;

    //Sniper Range
    Shot_Circle = new ObCircle();
    Shot_Circle->isFill = false;
    Shot_Circle->Scale = Vector2(1000.0f, 1000.0f);
    Shot_Circle->P = &Root->RT;

    Shot_Line1 = new ObLine();
    Shot_Line1->Scale = Vector2(500.0f, 0.0f);
    Shot_Line1->color = Color(1.0f, 0.0f,0.0f,0.5f);
    Shot_Line1->Rotation.z = -30.0f*TORADIAN - PI/2.0f + Rotation;
    Shot_Line1->P = &Root->RT;

    Shot_Line2 = new ObLine();
    Shot_Line2->Scale = Vector2(500.0f, 0.0f);
    Shot_Line2->color = Color(1.0f, 0.0f, 0.0f, 0.5f);
    Shot_Line2->Rotation.z = 30.0f * TORADIAN - PI / 2.0f + Rotation;
    Shot_Line2->P = &Root->RT;

    for (int i = 0; i < 10; i++)
    {
        SB[i].Sniper_Bullet = new ObImage(L"Image/TDS/Sniper/SniperBullet.png");
        SB[i].Sniper_Bullet->Scale = Vector2(5.0f, 5.0f);
        SB[i].Sniper_Bullet->Pivot = Vector2(0.0f, 0.0f);
        SB[i].Sniper_Bullet->isActive = false;
        SB[i].Sniper_Bullet->Position = Root->Position;
        SB[i].Hitbox = new ObRect;
        SB[i].Hitbox->Scale = Vector2(5.0f, 5.0f);
        SB[i].Hitbox->Pivot = Vector2(0.0f, 0.0f);
        SB[i].Hitbox->P = &SB[i].Sniper_Bullet->RT;
        SB[i].Hitbox->isFill = false;
        SB[i].Hitbox->isActive = false;
        SB[i].Speed = 400.0f;
        SB[i].Power = 3;
        SB[i].Dir = Vector2(1.0f, 0.0f);
    }

    //SNIPER
    SOUND->AddSound("Sound/ENEMY/SNIPER_FIRE.wav", "SN_SHOT", false);
    SOUND->AddSound("Sound/ENEMY/DEATH.wav", "SN_DEATH", false);
    //SOUND
    SOUND->AddSound("Sound/PLAYER/GT_EXPLODE.wav", "GT_EXPLODE", false);
}

Sniper::~Sniper()
{
    delete Sniper_Idle;
    delete Sniper_Die;
    delete Sniper_Shot;
    delete Sniper_Shot_Effect;
    delete Shot_Circle;
    delete Shot_Line1;
    delete Shot_Line2;
    for (int i = 0; i < 10; i++)
    {
        delete SB[i].Sniper_Bullet;
    }
    delete Hp_Bar;
}

void Sniper::Update()
{
    //health
    if (Health > 10)
        Health = 10;
    if (Health < 1)
        Health = 0;

    switch (SniperState)
    {
    case SS_IDLE:
        StateIdle();
        break;
    case SS_SHOT:
        StateShot();
        break;
    case SS_DEAD:
        StateDead();
        break;
    case SS_ALERT:
        StateAlert();
        break;
    }

    //fired bullet
    for (int i = 0; i < 10; i++)
    {
        if (SB[i].Sniper_Bullet->isActive)
        {
            SB[i].Sniper_Bullet->Position += DeltaTime * SB[i].Speed * SB[i].Dir * Game_Speed;
        }
    }

    //bullet out
    for (int i = 0; i < 10; i++)
    {
        if (SB[i].Sniper_Bullet->Position.x > Root->Position.x + 2000.0f or SB[i].Sniper_Bullet->Position.x < Root->Position.x - 2000.0f or
            SB[i].Sniper_Bullet->Position.y > Root->Position.y + 2000.0f or SB[i].Sniper_Bullet->Position.y < Root->Position.y - 2000.0f)
        {
            SB[i].Sniper_Bullet->isActive = false;
            SB[i].Hitbox->isActive = false;
            SB[i].Sniper_Bullet->Position = Root->Position;
        }
    }
    //hit by ft, gl
    if (isHit)
    {
        DamagedTime += DeltaTime;
        if (DamagedTime > 0.5f / Game_Speed)
        {
            DamagedTime = 0.0f;
            isHit = false;
        }
    }
    if (Sniper_Idle->Rotation.z > 2 * PI)
    {
        Sniper_Idle->Rotation.z -= 2 * PI;
    }
    if (Sniper_Idle->Rotation.z < 0.0f)
    {
        Sniper_Idle->Rotation.z += 2 * PI;
    }
    if (Shot_Line1->Rotation.z > 2 * PI)
    {
        Shot_Line1->Rotation.z -= 2 * PI;
    }
    if (Shot_Line1->Rotation.z < 0.0f)
    {
        Shot_Line1->Rotation.z += 2 * PI;
    }
    if (Shot_Line2->Rotation.z > 2 * PI)
    {
        Shot_Line2->Rotation.z -= 2 * PI;
    }
    if (Shot_Line2->Rotation.z < 0.0f)
    {
        Shot_Line2->Rotation.z += 2 * PI;
    }
    if (Health != 10)
    {
        Sniper_Idle->color = Color(0.7f, 0.5f, 0.5f, 0.5f);
        Sniper_Shot->color = Color(0.7f, 0.5f, 0.5f, 0.5f);
    }
}

void Sniper::LateUpdate()
{
    // shot by player
    for (int j = 0; j < 10; j++)
    {
        if (isCollision(HitBox, pl->PB[j].Hitbox))
        {
            pl->Hit_Circle->isActive = true;
            pl->Hit_Circle->Position = pl->PB[j].Pistol_Bullet->Position;
            pl->PB[j].Pistol_Bullet->Position = pl->GetPos() + Vector2(-30000.0f, 30000.0f);
            Health -= pl->PB[j].Power;
        }
    }
    for (int j = 0; j < 50; j++)
    {
        if (isCollision(HitBox, pl->MB[j].Hitbox))
        {
            pl->Hit_Circle->isActive = true;
            pl->Hit_Circle->Position = pl->MB[j].MG_Bullet->Position;
            pl->MB[j].MG_Bullet->Position = pl->GetPos() + Vector2(-30000.0f, 30000.0f);
            Health -= pl->MB[j].Power;
        }
    }
    for (int j = 0; j < 30; j++)
    {
        if (isCollision(HitBox, pl->RB[j].Hitbox))
        {
            pl->Hit_Circle->isActive = true;
            pl->Hit_Circle->Position = pl->RB[j].RIFLE_Bullet->Position;
            pl->RB[j].RIFLE_Bullet->Position = pl->GetPos() + Vector2(-30000.0f, 30000.0f);
            Health -= pl->RB[j].Power;
        }
    }
    if (isCollision(HitBox, pl->Fire_HitBox) and !isHit)
    {
        pl->Hit_Circle->isActive = true;
        pl->Hit_Circle->Position = Root->Position;
        Health -= 3.0f;
        isHit = true;
    }
    //shot by player gl
    for (int j = 0; j < 3; j++)
    {
        if (isCollision(HitBox, pl->GB[j].GL_HitBox))
        {
            pl->Hit_Circle->isActive = true;
            pl->Hit_Circle->Position = pl->GB[j].GL_Shot1->Position;
            Vector2 temp = pl->GB[j].GL_Shot1->Position;
            pl->GB[j].GL_Shot1->Position = pl->GetPos() + Vector2(-30000.0f, 30000.0f);
            pl->GB[j].GL_Shot2->ChangeAnim(_ONCE, 0.25f / Game_Speed);
            pl->GB[j].GL_Shot2->Position = temp;
            pl->GB[j].GL_Shot2->isActive = true;
            pl->GB[j].GL_HitBox2->isActive = true;
            pl->GB[j].Explode = true;
            SOUND->Stop("GT_EXPLODE");
            SOUND->Play("GT_EXPLODE");
            SOUND->SetVolume("GT_EXPLODE", 0.3f);
        }
    }
    for (int j = 0; j < 3; j++)
    {
        if (isCollision(HitBox, pl->GB[j].GL_HitBox2) and !isHit)
        {
            Health -= pl->GB[j].Power;
            isHit = true;
        }
    }
    //shot by ACS
    for (int j = 0; j < 30; j++)
    {
        if (isCollision(HitBox, Acs->SB[j].Hitbox))
        {
            pl->Hit_Circle->isActive = true;
            pl->Hit_Circle->Position = Acs->SB[j].ACS_Bullet->Position;
            Acs->SB[j].ACS_Bullet->Position = Acs->GetPos() + Vector2(-30000.0f, 30000.0f);
            Acs->SB[j].Hitbox2->Position = Root->Position;
            Acs->SB[j].Hitbox2->isActive = true;
            Acs->SB[j].Explode = true;
        }
    }
    for (int j = 0; j < 30; j++)
    {
        if (isCollision(HitBox, Acs->SB[j].Hitbox2) and !isHit)
        {
            Health -= Acs->SB[j].Power;
            isHit = true;
        }
    }
}

void Sniper::Render()
{
    Character::Render();

    /*Shot_Circle->Render();
    Shot_Line1->Render();
    Shot_Line2->Render();*/
    switch (SniperState)
    {
    case SS_IDLE:
        Sniper_Idle->Render();
        break;
    case SS_SHOT:
        Sniper_Shot_Effect->Render();
        Sniper_Shot->Render();
        break;
    case SS_DEAD:
        Sniper_Die->Render();
        break;
    case SS_ALERT:
        Sniper_Idle->Render();
        break;
    }

    //bullet
    for (int i = 0; i < 10; i++)
    {
        SB[i].Sniper_Bullet->Render();
        /*SB[i].Hitbox->Render();*/
    }
    /*HitBox->Render();*/
    Hp_Bar->Render();
}

void Sniper::StateIdle()
{
    if (!Game_Speed == 0)
    {
        if (Acs->isRide)
        {
            LookTarget2(Acs->GetPos(), Sniper_Die, -Rotation);
            Reloading_Time += DeltaTime;
            if (isCollision(Shot_Circle, Acs->GetPos()) and Reloading_Time > 0.0f and Range(Acs->GetPos(), Shot_Line1, Shot_Line2, Rotation, 60.0f))
            {
                SniperState = SS_ALERT;
            }
            if (isCollision(Shot_Circle, Acs->GetPos()) and Reloading_Time > 0.0f and Health != 10)
            {
                SniperState = SS_ALERT;
            }
        }
        else
        {
            LookTarget2(pl->GetPos(), Sniper_Die, -Rotation);
            Reloading_Time += DeltaTime;
            if (isCollision(Shot_Circle, pl->GetPos()) and Reloading_Time > 0.0f and Range(pl->GetPos(), Shot_Line1, Shot_Line2, Rotation, 60.0f) and !pl->Hide)
            {
                SniperState = SS_ALERT;
            }
            if (isCollision(Shot_Circle, pl->GetPos()) and Reloading_Time > 0.0f and Health != 10)
            {
                SniperState = SS_ALERT;
            }
        }
        if (isCollision(pl->Shot_Circle, Root->Position) or isCollision(pl->Hit_Circle, Root->Position))
        {
            SniperState = SS_ALERT;
        }
        if (Health < 1)
        {
            SOUND->Play("SN_DEATH");
            SOUND->SetVolume("SN_DEATH", 0.3f);
            SniperState = SS_DEAD;
            Reloading_Time = 0.0f;
            Shooting_Time = 0.0f;
            Sniper_Die->ChangeAnim(_ONCE, 0.2f / Game_Speed);
        }
    }
}

void Sniper::StateShot()
{
    if (!Game_Speed == 0)
    {
        if (Acs->isRide)
        {
            LookTarget2(Acs->GetPos(), Sniper_Shot, -Rotation);
            LookTarget(Acs->GetPos(), Sniper_Shot_Effect, -Rotation);
            LookTarget2(Acs->GetPos(), Sniper_Die, -Rotation);
        }
        else
        {
            LookTarget2(pl->GetPos(), Sniper_Shot, -Rotation);
            LookTarget(pl->GetPos(), Sniper_Shot_Effect, -Rotation);
            LookTarget2(pl->GetPos(), Sniper_Die, -Rotation);
        }
        Shooting_Time += DeltaTime;
        if (Shooting_Time > 0.2f / Game_Speed)
        {
            Shooting_Time = 0.0f;
            SniperState = SS_ALERT;
            Reloading_Time = -7.0f / Game_Speed;
        }
        if (Health < 1)
        {
            SOUND->Play("SN_DEATH");
            SOUND->SetVolume("SN_DEATH", 0.3f);
            SniperState = SS_DEAD;
            Reloading_Time = 0.0f;
            Shooting_Time = 0.0f;
            Sniper_Die->ChangeAnim(_ONCE, 0.2f / Game_Speed);
        }
    }
}

void Sniper::StateDead()
{
    if (!Game_Speed == 0)
    {
        Hp_Bar->isActive = false;
        Shooting_Time += DeltaTime;
        if (Shooting_Time > 1.0f / Game_Speed)
        {
            isDead = true;
            Shooting_Time = 0.0f;
            SetPos(Vector2(-2000.0f, 100.0f));
        }
    }
}

void Sniper::StateAlert()
{
    if (!Game_Speed == 0)
    {
        if (Acs->isRide)
        {
            LookTarget2(Acs->GetPos(), Sniper_Die, -Rotation);
            if (isCollision(Shot_Circle, Acs->GetPos()) and Reloading_Time > 0.0f)
            {
                LookTarget2(Acs->GetPos(), Sniper_Idle, -Rotation);
                Shot_Line1->Rotation.z = -30.0f * TORADIAN - PI / 2.0f + Sniper_Idle->Rotation.z;
                Shot_Line2->Rotation.z = 30.0f * TORADIAN - PI / 2.0f + Sniper_Idle->Rotation.z;
                SniperState = SS_SHOT;
                Sniper_Shot_Effect->ChangeAnim(_ONCE, 0.03f / Game_Speed);
                for (int i = 0; i < 10; i++)
                {
                    if (!SB[i].Sniper_Bullet->isActive)
                    {
                        SOUND->Stop("SN_SHOT");
                        SOUND->Play("SN_SHOT");
                        SOUND->SetVolume("SN_SHOT", 0.3f);
                        //격발
                        SB[i].Sniper_Bullet->Position = Root->Position;
                        SB[i].Sniper_Bullet->isActive = true;
                        SB[i].Hitbox->isActive = true;
                        LookTarget(Acs->GetPos(), SB[i].Sniper_Bullet, 0.0f);
                        SB[i].Dir = RadianToDir(SB[i].Sniper_Bullet->Rotation.z + 0.5f * PI);
                        break;
                    }
                }
            }
        }
        else
        {
            LookTarget2(pl->GetPos(), Sniper_Die, -Rotation);
            if (isCollision(Shot_Circle, pl->GetPos()) and Reloading_Time > 0.0f)
            {
                LookTarget2(pl->GetPos(), Sniper_Idle, -Rotation);
                Shot_Line1->Rotation.z = -30.0f * TORADIAN - PI / 2.0f + Sniper_Idle->Rotation.z;
                Shot_Line2->Rotation.z = 30.0f * TORADIAN - PI / 2.0f + Sniper_Idle->Rotation.z;
                SniperState = SS_SHOT;
                Sniper_Shot_Effect->ChangeAnim(_ONCE, 0.03f / Game_Speed);
                for (int i = 0; i < 10; i++)
                {
                    if (!SB[i].Sniper_Bullet->isActive)
                    {
                        SOUND->Stop("SN_SHOT");
                        SOUND->Play("SN_SHOT");
                        SOUND->SetVolume("SN_SHOT", 0.3f);
                        //격발
                        SB[i].Sniper_Bullet->Position = Root->Position;
                        SB[i].Sniper_Bullet->isActive = true;
                        SB[i].Hitbox->isActive = true;
                        LookTarget(pl->GetPos(), SB[i].Sniper_Bullet, 0.0f);
                        SB[i].Dir = RadianToDir(SB[i].Sniper_Bullet->Rotation.z + 0.5f * PI);
                        break;
                    }
                }
            }
        }
        Sniper_Idle->color = Color(0.7f, 0.5f, 0.5f, 0.5f);
        Sniper_Shot->color = Color(0.7f, 0.5f, 0.5f, 0.5f);

        Reloading_Time += DeltaTime;

        if (Health < 1)
        {
            SOUND->Play("SN_DEATH");
            SOUND->SetVolume("SN_DEATH", 0.3f);
            SniperState = SS_DEAD;
            Reloading_Time = 0.0f;
            Shooting_Time = 0.0f;
            Sniper_Die->ChangeAnim(_ONCE, 0.2f / Game_Speed);
        }
     }
    
}
