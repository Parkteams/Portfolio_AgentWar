#include "stdafx.h"
#include "Character.h"
#include "Bazooka.h"
#include "Player.h"
#include "ACS.h"

Bazooka::Bazooka()
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
    BazookaState = Bz_IDLE;

    Bazooka_Idle = new ObImage(L"Image/TDS/Soldier2/Soldier02.png");
    Bazooka_Idle->Scale = Vector2(120.0f, 120.0f);
    Bazooka_Idle->P = &Root->RT;

    Bazooka_Die = new ObImage(L"Image/TDS/Soldier2/Soldier02_Die.png");
    Bazooka_Die->Scale = Vector2(120.0f, 120.0f);
    Bazooka_Die->MaxFrame = Int2(4, 1);
    Bazooka_Die->P = &Root->RT;

    Bazooka_Shot = new ObImage(L"Image/TDS/Soldier2/Soldier02_Shot.png");
    Bazooka_Shot->Scale = Vector2(120.0f, 120.0f);
    Bazooka_Shot->MaxFrame = Int2(5, 1);
    Bazooka_Shot->P = &Root->RT;

    Bazooka_Shot_Effect = new ObImage(L"Image/TDS/Soldier2/Fire.png");
    Bazooka_Shot_Effect->Scale = Vector2(50.0f, 50.0f);
    Bazooka_Shot_Effect->MaxFrame = Int2(3, 1);
    Bazooka_Shot_Effect->Pivot = Vector2(0.16f, 0.5f);
    Bazooka_Shot_Effect->P = &Root->RT;

    //Bazooka HitBox
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

    //Bazooka Range
    Shot_Circle = new ObCircle();
    Shot_Circle->isFill = false;
    Shot_Circle->Scale = Vector2(900.0f, 900.0f);
    Shot_Circle->P = &Root->RT;

    Shot_Line1 = new ObLine();
    Shot_Line1->Scale = Vector2(250.0f, 0.0f);
    Shot_Line1->color = Color(1.0f, 0.0f, 0.0f, 0.5f);
    Shot_Line1->Rotation.z = -30.0f * TORADIAN - PI / 2.0f + Rotation;
    Shot_Line1->P = &Root->RT;

    Shot_Line2 = new ObLine();
    Shot_Line2->Scale = Vector2(250.0f, 0.0f);
    Shot_Line2->color = Color(1.0f, 0.0f, 0.0f, 0.5f);
    Shot_Line2->Rotation.z = 30.0f * TORADIAN - PI / 2.0f + Rotation;
    Shot_Line2->P = &Root->RT;

    for (int i = 0; i < 10; i++)
    {
        SB[i].Bazooka_Bullet = new ObImage(L"Image/TDS/Soldier2/Bullet.png");
        SB[i].Bazooka_Bullet->Scale = Vector2(50.0f, 50.0f);
        SB[i].Bazooka_Bullet->Pivot = Vector2(0.0f, 0.0f);
        SB[i].Bazooka_Bullet->isActive = false;
        SB[i].Bazooka_Bullet->Position = Root->Position;
        SB[i].Hitbox = new ObRect;
        SB[i].Hitbox->Scale = Vector2(20.0f, 20.0f);
        SB[i].Hitbox->Pivot = Vector2(0.0f, 0.4f);
        SB[i].Hitbox->P = &SB[i].Bazooka_Bullet->RT;
        SB[i].Hitbox->isFill = false;
        SB[i].Hitbox->isActive = false;
        SB[i].Speed = 150.0f;
        SB[i].Power = 5;
        SB[i].Dir = Vector2(1.0f, 0.0f);
    }

    //BAZOOKA
    SOUND->AddSound("Sound/ENEMY/BAZOOKA_FIRE.wav", "BA_SHOT", false);
    SOUND->AddSound("Sound/ENEMY/DEATH.wav", "BA_DEATH", false);
    //SOUND
    SOUND->AddSound("Sound/PLAYER/GT_EXPLODE.wav", "GT_EXPLODE", false);
}

Bazooka::~Bazooka()
{
    delete Bazooka_Idle;
    delete Bazooka_Die;
    delete Bazooka_Shot;
    delete Bazooka_Shot_Effect;
    delete Shot_Circle;
    delete Shot_Line1;
    delete Shot_Line2;
    for (int i = 0; i < 10; i++)
    {
        delete SB[i].Bazooka_Bullet;
    }
    delete Hp_Bar;
}

void Bazooka::Update()
{
    //health
    if (Health > 10)
        Health = 10;
    if (Health < 1)
        Health = 0;

    switch (BazookaState)
    {
    case Bz_IDLE:
        StateIdle();
        break;
    case Bz_SHOT:
        StateShot();
        break;
    case Bz_DEAD:
        StateDead();
        break;
    case Bz_ALERT:
        StateAlert();
        break;
    }

    //fired bullet
    for (int i = 0; i < 10; i++)
    {
        if (SB[i].Bazooka_Bullet->isActive)
        {
            SB[i].Bazooka_Bullet->Position += DeltaTime * SB[i].Speed * SB[i].Dir * Game_Speed;
        }
    }

    //bullet out
    for (int i = 0; i < 10; i++)
    {
        if (SB[i].Bazooka_Bullet->Position.x > Root->Position.x + 2000.0f or SB[i].Bazooka_Bullet->Position.x < Root->Position.x - 2000.0f or
            SB[i].Bazooka_Bullet->Position.y > Root->Position.y + 2000.0f or SB[i].Bazooka_Bullet->Position.y < Root->Position.y - 2000.0f)
        {
            SB[i].Bazooka_Bullet->isActive = false;
            SB[i].Hitbox->isActive = false;
            SB[i].Bazooka_Bullet->Position = Root->Position;
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
    if (Bazooka_Idle->Rotation.z > 2 * PI)
    {
        Bazooka_Idle->Rotation.z -= 2 * PI;
    }
    if (Bazooka_Idle->Rotation.z < 0.0f)
    {
        Bazooka_Idle->Rotation.z += 2 * PI;
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
        Bazooka_Idle->color = Color(0.7f, 0.5f, 0.5f, 0.5f);
        Bazooka_Shot->color = Color(0.7f, 0.5f, 0.5f, 0.5f);
    }
}

void Bazooka::LateUpdate()
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

void Bazooka::Render()
{
    Character::Render();

    /*Shot_Circle->Render();
    Shot_Line1->Render();
    Shot_Line2->Render();*/
    switch (BazookaState)
    {
    case Bz_IDLE:
        Bazooka_Idle->Render();
        break;
    case Bz_SHOT:
        Bazooka_Shot->Render();
        break;
    case Bz_DEAD:
        Bazooka_Die->Render();
        break;
    case Bz_ALERT:
        Bazooka_Idle->Render();
        break;
    }

    //bullet
    for (int i = 0; i < 10; i++)
    {
        SB[i].Bazooka_Bullet->Render();
        /*SB[i].Hitbox->Render();*/
    }
    /*HitBox->Render();*/
    Hp_Bar->Render();
}

void Bazooka::StateIdle()
{
    if (!Game_Speed == 0)
    {
        if (Acs->isRide)
        {
            LookTarget2(Acs->GetPos(), Bazooka_Die, -Rotation);
            Reloading_Time += DeltaTime;
            if (isCollision(Shot_Circle, Acs->GetPos()) and Reloading_Time > 0.0f and Range(Acs->GetPos(), Shot_Line1, Shot_Line2, Rotation, 60.0f))
            {
                BazookaState = Bz_ALERT;
            }
            if (isCollision(Shot_Circle, Acs->GetPos()) and Reloading_Time > 0.0f and Health != 10)
            {
                BazookaState = Bz_ALERT;
            }
        }
        else if(!Acs->isRide)
        {
            LookTarget2(pl->GetPos(), Bazooka_Die, -Rotation);
            Reloading_Time += DeltaTime;
            if (isCollision(Shot_Circle, pl->GetPos()) and Reloading_Time > 0.0f and Range(pl->GetPos(), Shot_Line1, Shot_Line2, Rotation, 60.0f) and !pl->Hide)
            {
                BazookaState = Bz_ALERT;
            }
            if (isCollision(Shot_Circle, pl->GetPos()) and Reloading_Time > 0.0f and Health != 10)
            {
                BazookaState = Bz_ALERT;
            }
        }
        if (isCollision(pl->Shot_Circle, Root->Position) or isCollision(pl->Hit_Circle, Root->Position))
        {
            BazookaState = Bz_ALERT;
        }
        
        if (Health < 1)
        {
            SOUND->Play("BA_DEATH");
            SOUND->SetVolume("BA_DEATH", 0.3f);
            BazookaState = Bz_DEAD;
            Reloading_Time = 0.0f;
            Shooting_Time = 0.0f;
            Bazooka_Die->ChangeAnim(_ONCE, 0.2f / Game_Speed);
        }
    }
}

void Bazooka::StateShot()
{
    if (!Game_Speed == 0)
    {
        if (Acs->isRide)
        {
            LookTarget2(Acs->GetPos(), Bazooka_Shot, -Rotation);
            LookTarget(Acs->GetPos(), Bazooka_Shot_Effect, -Rotation);
            LookTarget2(Acs->GetPos(), Bazooka_Die, -Rotation);
        }
        else if (!Acs->isRide)
        {
            LookTarget2(pl->GetPos(), Bazooka_Shot, -Rotation);
            LookTarget(pl->GetPos(), Bazooka_Shot_Effect, -Rotation);
            LookTarget2(pl->GetPos(), Bazooka_Die, -Rotation);
        }
        Shooting_Time += DeltaTime;
        if (Shooting_Time > 0.2f / Game_Speed)
        {
            Shooting_Time = 0.0f;
            BazookaState = Bz_ALERT;
            Reloading_Time = -5.0f / Game_Speed;
        }
        if (Health < 1)
        {
            SOUND->Play("BA_DEATH");
            SOUND->SetVolume("BA_DEATH", 0.3f);
            BazookaState = Bz_DEAD;
            Reloading_Time = 0.0f;
            Shooting_Time = 0.0f;
            Bazooka_Die->ChangeAnim(_ONCE, 0.2f / Game_Speed);
        }
    }
}

void Bazooka::StateDead()
{
    if (!Game_Speed == 0)
    {
        Hp_Bar->isActive = false;
        Shooting_Time += DeltaTime;
        if (Shooting_Time > 1.0f / Game_Speed)
        {
            Shooting_Time = 0.0f;
            SetPos(Vector2(-2000.0f, 100.0f));
            isDead = true;
        }
    }
}

void Bazooka::StateAlert()
{
    if (Acs->isRide)
    {
        LookTarget2(Acs->GetPos(), Bazooka_Die, -Rotation);
        if (isCollision(Shot_Circle, Acs->GetPos()) and Reloading_Time > 0.0f)
        {
            LookTarget2(Acs->GetPos(), Bazooka_Idle, -Rotation);
            Shot_Line1->Rotation.z = -30.0f * TORADIAN - PI / 2.0f + Bazooka_Idle->Rotation.z;
            Shot_Line2->Rotation.z = 30.0f * TORADIAN - PI / 2.0f + Bazooka_Idle->Rotation.z;
            BazookaState = Bz_SHOT;
            for (int i = 0; i < 10; i++)
            {
                if (!SB[i].Bazooka_Bullet->isActive)
                {
                    SOUND->Stop("BA_SHOT");
                    SOUND->Play("BA_SHOT");
                    SOUND->SetVolume("BA_SHOT", 0.3f);
                    //격발
                    SB[i].Bazooka_Bullet->Position = Root->Position;
                    SB[i].Bazooka_Bullet->isActive = true;
                    SB[i].Hitbox->isActive = true;
                    LookTarget(Acs->GetPos(), SB[i].Bazooka_Bullet, 0.0f);
                    SB[i].Dir = RadianToDir(SB[i].Bazooka_Bullet->Rotation.z + 0.5f * PI);
                    break;
                }
            }
        }
    }
    else if (!Acs->isRide)
    {
        LookTarget2(pl->GetPos(), Bazooka_Die, -Rotation);
        if (isCollision(Shot_Circle, pl->GetPos()) and Reloading_Time > 0.0f)
        {
            LookTarget2(pl->GetPos(), Bazooka_Idle, -Rotation);
            Shot_Line1->Rotation.z = -30.0f * TORADIAN - PI / 2.0f + Bazooka_Idle->Rotation.z;
            Shot_Line2->Rotation.z = 30.0f * TORADIAN - PI / 2.0f + Bazooka_Idle->Rotation.z;
            BazookaState = Bz_SHOT;
            for (int i = 0; i < 10; i++)
            {
                if (!SB[i].Bazooka_Bullet->isActive)
                {
                    SOUND->Stop("BA_SHOT");
                    SOUND->Play("BA_SHOT");
                    SOUND->SetVolume("BA_SHOT", 0.3f);
                    //격발
                    SB[i].Bazooka_Bullet->Position = Root->Position;
                    SB[i].Bazooka_Bullet->isActive = true;
                    SB[i].Hitbox->isActive = true;
                    LookTarget(pl->GetPos(), SB[i].Bazooka_Bullet, 0.0f);
                    SB[i].Dir = RadianToDir(SB[i].Bazooka_Bullet->Rotation.z + 0.5f * PI);
                    break;
                }
            }
        }
    }
    if (!Game_Speed == 0)
    {
        Bazooka_Idle->color = Color(0.7f, 0.5f, 0.5f, 0.5f);
        Bazooka_Shot->color = Color(0.7f, 0.5f, 0.5f, 0.5f);
        
        Reloading_Time += DeltaTime;
        
        if (Health < 1)
        {
            SOUND->Play("BA_DEATH");
            SOUND->SetVolume("BA_DEATH", 0.3f);
            BazookaState = Bz_DEAD;
            Reloading_Time = 0.0f;
            Shooting_Time = 0.0f;
            Bazooka_Die->ChangeAnim(_ONCE, 0.2f / Game_Speed);
        }
    }
}
