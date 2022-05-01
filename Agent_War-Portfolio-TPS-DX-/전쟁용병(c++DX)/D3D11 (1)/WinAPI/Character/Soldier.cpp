#include "stdafx.h"
#include "Character.h"
#include "Soldier.h"
#include "Player.h"
#include "ACS.h"
#include "TileMap/Tile.h"
#include "TileMap/TileMap.h"

Soldier::Soldier()
{
    isAlarm = false;
    //setting
    Game_Speed = 1.0f;
    Shooting_Time = 0.0f;
    Reloading_Time = 0.0f;
    DamagedTime = 0.0f;
    Refresh_Time = 2.0f;
    isHit = false;
    Rotation = 0.0f;
    g_speed = 1.5f;
    isDead = false;

    Health = 10;
    SoldierState = SD_IDLE;

    Soldier_Idle = new ObImage(L"Image/TDS/Soldier/Soldier.png");
    Soldier_Idle->Scale = Vector2(80.0f, 80.0f);
    Soldier_Idle->P = &Root->RT;

    Soldier_Move = new ObImage(L"Image/TDS/Soldier/Soldier_Leg_Move.png");
    Soldier_Move->Scale = Vector2(120.0f, 120.0f);
    Soldier_Move->MaxFrame = Int2(7, 1);
    Soldier_Move->P = &Root->RT;

    Soldier_Die = new ObImage(L"Image/TDS/Soldier/Soldier_Die.png");
    Soldier_Die->Scale = Vector2(120.0f, 120.0f);
    Soldier_Die->MaxFrame = Int2(4, 1);
    Soldier_Die->P = &Root->RT;

    Soldier_Shot = new ObImage(L"Image/TDS/Soldier/Soldier_Shot.png");
    Soldier_Shot->Scale = Vector2(120.0f, 120.0f);
    Soldier_Shot->P = &Root->RT;

    Soldier_Shot_Effect = new ObImage(L"Image/TDS/Soldier/Soldier_Shot_Effect.png");
    Soldier_Shot_Effect->Scale = Vector2(50.0f, 50.0f);
    Soldier_Shot_Effect->MaxFrame = Int2(3, 1);
    Soldier_Shot_Effect->Pivot = Vector2(0.16f, 0.5f);
    Soldier_Shot_Effect->P = &Root->RT;

    //Soldier HitBox
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

    //Soldier Range
    Shot_Circle = new ObCircle();
    Shot_Circle->isFill = false;
    Shot_Circle->Scale = Vector2(500.0f, 500.0f);
    Shot_Circle->P = &Root->RT;

    Look_Circle = new ObCircle();
    Look_Circle->isFill = false;
    Look_Circle->Scale = Vector2(800.0f, 800.0f);
    Look_Circle->P = &Root->RT;

    Shot_Line1 = new ObLine();
    Shot_Line1->Scale = Vector2(400.0f, 0.0f);
    Shot_Line1->color = Color(1.0f, 0.0f, 0.0f, 0.5f);
    Shot_Line1->Rotation.z = -30.0f * TORADIAN - PI / 2.0f + Rotation;
    Shot_Line1->P = &Root->RT;

    Shot_Line2 = new ObLine();
    Shot_Line2->Scale = Vector2(400.0f, 0.0f);
    Shot_Line2->color = Color(1.0f, 0.0f, 0.0f, 0.5f);
    Shot_Line2->Rotation.z = 30.0f * TORADIAN - PI / 2.0f + Rotation;
    Shot_Line2->P = &Root->RT;

    for (int i = 0; i < 30; i++)
    {
        SB[i].Soldier_Bullet = new ObImage(L"Image/TDS/Soldier/Bullet.png");
        SB[i].Soldier_Bullet->Scale = Vector2(5.0f, 5.0f);
        SB[i].Soldier_Bullet->Pivot = Vector2(0.0f, 0.0f);
        SB[i].Soldier_Bullet->isActive = false;
        SB[i].Soldier_Bullet->Position = Root->Position;
        SB[i].Hitbox = new ObRect;
        SB[i].Hitbox->Scale = Vector2(5.0f, 5.0f);
        SB[i].Hitbox->Pivot = Vector2(0.0f, 0.0f);
        SB[i].Hitbox->P = &SB[i].Soldier_Bullet->RT;
        SB[i].Hitbox->isFill = false;
        SB[i].Hitbox->isActive = false;
        SB[i].Speed = 200.0f;
        SB[i].Power = 1;
        SB[i].Dir = Vector2(1.0f, 0.0f);
    }

    //SOLDIER
    SOUND->AddSound("Sound/ENEMY/SOLDIER_FIRE.wav", "SD_SHOT", false);
    SOUND->AddSound("Sound/ENEMY/DEATH.wav", "SD_DEATH", false);
    //SOUND
    SOUND->AddSound("Sound/PLAYER/GT_EXPLODE.wav", "GT_EXPLODE", false);
}

Soldier::~Soldier()
{
    delete Soldier_Idle;
    delete Soldier_Move;
    delete Soldier_Die;
    delete Soldier_Shot;
    delete Soldier_Shot_Effect;
    delete Shot_Circle;
    delete Look_Circle;
    delete Shot_Line1;
    delete Shot_Line2;
    for (int i = 0; i < 30; i++)
    {
        delete SB[i].Soldier_Bullet;
    }
    delete Hp_Bar;
}

void Soldier::Update()
{
    //health
    if (Health > 10)
        Health = 10;
    if (Health < 1)
        Health = 0;

    if (Game_Speed > 0.0f)
    {
        switch (SoldierState)
        {
        case SD_IDLE:
            StateIdle();
            break;
        case SD_MOVE:
            StateMove();
            break;
        case SD_SHOT:
            StateShot();
            break;
        case SD_DEAD:
            StateDead();
            break;
        case SD_ALERT:
            StateAlert();
            break;
        case SD_BACK:
            StateBack();
            break;
        }
    }

    //fired bullet
    for (int i = 0; i < 30; i++)
    {
        if (SB[i].Soldier_Bullet->isActive)
        {
            SB[i].Soldier_Bullet->Position += DeltaTime * SB[i].Speed * SB[i].Dir * Game_Speed;
        }
    }

    //bullet out
    for (int i = 0; i < 30; i++)
    {
        if (SB[i].Soldier_Bullet->Position.x > Root->Position.x + 1000.0f or SB[i].Soldier_Bullet->Position.x < Root->Position.x - 1000.0f or
            SB[i].Soldier_Bullet->Position.y > Root->Position.y + 1000.0f or SB[i].Soldier_Bullet->Position.y < Root->Position.y - 1000.0f)
        {
            SB[i].Soldier_Bullet->isActive = false;
            SB[i].Hitbox->isActive = false;
            SB[i].Soldier_Bullet->Position = Root->Position;
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
    if (Soldier_Idle->Rotation.z > 2 * PI)
    {
        Soldier_Idle->Rotation.z -= 2 * PI;
    }
    if (Soldier_Idle->Rotation.z < 0.0f)
    {
        Soldier_Idle->Rotation.z += 2 * PI;
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
        Soldier_Idle->color = Color(0.7f, 0.5f, 0.5f, 0.5f);
        Soldier_Shot->color = Color(0.7f, 0.5f, 0.5f, 0.5f);
        Soldier_Move->color = Color(0.7f, 0.5f, 0.5f, 0.5f);
    }
}

void Soldier::LateUpdate()
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
            pl->GB[j].GL_Shot1->Position = Vector2(3000.0f, 0.0f);
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

    //walking sand
    {
        Int2 idx;
        Vector2 foot = Root->Position + Vector2(0.0f, -12.0f);

        if (tm->VectorToIdx(foot, idx))
        {
            if (tm->Tiles[idx.x][idx.y].state == TILE_SAND)
            {
                g_speed = 1.2f;
            }
        }
    }
    //walking dirt, grass
    {
        Int2 idx;
        Vector2 foot = Root->Position + Vector2(0.0f, -12.0f);

        if (tm->VectorToIdx(foot, idx))
        {
            if (tm->Tiles[idx.x][idx.y].state == TILE_NONE)
            {
                g_speed = 1.5f;
            }
        }
    }
    //walking asphalt
    {
        Int2 idx;
        Vector2 foot = Root->Position + Vector2(0.0f, -12.0f);

        if (tm->VectorToIdx(foot, idx))
        {
            if (tm->Tiles[idx.x][idx.y].state == TILE_ASPHALT)
            {
                g_speed = 2.5f;
            }
        }
    }

}

void Soldier::Render()
{
    Character::Render();

    /*Shot_Circle->Render();
    Look_Circle->Render();
    Shot_Line1->Render();
    Shot_Line2->Render();*/
    switch (SoldierState)
    {
    case SD_IDLE:
        Soldier_Idle->Render();
        break;
    case SD_MOVE:
        Soldier_Move->Render();
        Soldier_Idle->Render();
        break;
    case SD_SHOT:
        Soldier_Shot_Effect->Render();
        Soldier_Shot->Render();
        break;
    case SD_DEAD:
        Soldier_Die->Render();
        break;
    case SD_ALERT:
        Soldier_Idle->Render();
        break;
    case SD_BACK:
        Soldier_Move->Render();
        Soldier_Idle->Render();
        break;
    }

    //bullet
    for (int i = 0; i < 30; i++)
    {
        SB[i].Soldier_Bullet->Render();
        /*SB[i].Hitbox->Render();*/
    }
    /*HitBox->Render();*/
    Hp_Bar->Render();
}

void Soldier::StateIdle()
{
    if (!Game_Speed == 0)
    {
        if (Acs->isRide)
        {
            LookTarget2(Acs->GetPos(), Soldier_Die, -Rotation);
            Reloading_Time += DeltaTime;
            if (isCollision(Look_Circle, Acs->GetPos()) and Reloading_Time > 0.0f and Range(Acs->GetPos(), Shot_Line1, Shot_Line2, Rotation, 60.0f))
            {
                SoldierState = SD_ALERT;
            }
            if (Health != 10)
            {
                SoldierState = SD_ALERT;
            }
        }
        else if (!Acs->isRide)
        {
            LookTarget2(pl->GetPos(), Soldier_Die, -Rotation);
            Reloading_Time += DeltaTime;
            if (isCollision(Look_Circle, pl->GetPos()) and Reloading_Time > 0.0f and Range(pl->GetPos(), Shot_Line1, Shot_Line2, Rotation, 60.0f) and !pl->Hide)
            {
                SoldierState = SD_ALERT;
            }
            if (Health != 10)
            {
                SoldierState = SD_ALERT;
            }
        }
        if (isCollision(pl->Shot_Circle, Root->Position) or isCollision(pl->Hit_Circle, Root->Position))
        {
            SoldierState = SD_ALERT;
        }
        
        if (Health < 1)
        {
            SOUND->Play("SD_DEATH");
            SOUND->SetVolume("SD_DEATH", 0.3f);
            Health = 10;
            SoldierState = SD_DEAD;
            Reloading_Time = 0.0f;
            Shooting_Time = 0.0f;
            Soldier_Die->ChangeAnim(_ONCE, 0.2f / Game_Speed);
        }
    }
}
void Soldier::StateMove()
{
    if (Acs->isRide)
    {
        if (sqrt(pow((Acs->GetPos() - Root->Position).x, 2) + pow((Acs->GetPos() - Root->Position).y, 2)) > 1000.0f)
        {
            SoldierState = SD_BACK;
            Soldier_Move->ChangeAnim(_LOOP, 0.1f / Game_Speed);
        }
        Shot_Line1->Rotation.z = -30.0f * TORADIAN - PI / 2.0f + Soldier_Idle->Rotation.z;
        Shot_Line2->Rotation.z = 30.0f * TORADIAN - PI / 2.0f + Soldier_Idle->Rotation.z;
        LookTarget2(Acs->GetPos(), Soldier_Idle, -Rotation);
        LookTarget2(Acs->GetPos(), Soldier_Move, -Rotation);
        LookTarget2(Acs->GetPos(), Soldier_Die, -Rotation);
        Refresh_Time += DeltaTime;
        if (Refresh_Time > 1.0f)
        {
            Refresh_Time = 0.0f;
            Int2 sour, dest;
            bool isFind;
            isFind = tm->VectorToIdx(Root->Position, sour);
            isFind = isFind && tm->VectorToIdx(Acs->GetPos(), dest);
            if (isFind)
            {
                if (tm->PathFinding(sour, dest, PlWay))
                {
                    g = 0.0f;
                    PlSour = Root->Position;
                    PlWay.pop_back();
                    PlDest = tm->IdxToVector(PlWay.back()->idx);
                }
            }
        }
        if (!PlWay.empty())
        {
            /*PlSour = pl->GetPos();*/
            Root->Position = Lerp(PlSour, PlDest, g);
            g += DeltaTime * g_speed;
            if (g > 1.0f)
            {
                g = 0.0f;
                PlSour = PlDest;
                PlWay.pop_back(); //¸ÇµÞ±æ »©±â
                if (!PlWay.empty())
                    PlDest = tm->IdxToVector(PlWay.back()->idx);
            }
        }

        if (isCollision(Shot_Circle, Acs->GetPos()))
        {
            SoldierState = SD_ALERT;
        }
    }
    else if (!Acs->isRide)
    {
        if (sqrt(pow((pl->GetPos() - Root->Position).x, 2) + pow((pl->GetPos() - Root->Position).y, 2)) > 1000.0f)
        {
            SoldierState = SD_BACK;
            Soldier_Move->ChangeAnim(_LOOP, 0.1f / Game_Speed);
        }
        Shot_Line1->Rotation.z = -30.0f * TORADIAN - PI / 2.0f + Soldier_Idle->Rotation.z;
        Shot_Line2->Rotation.z = 30.0f * TORADIAN - PI / 2.0f + Soldier_Idle->Rotation.z;
        LookTarget2(pl->GetPos(), Soldier_Idle, -Rotation);
        LookTarget2(pl->GetPos(), Soldier_Move, -Rotation);
        LookTarget2(pl->GetPos(), Soldier_Die, -Rotation);
        Refresh_Time += DeltaTime;
        if (Refresh_Time > 1.0f)
        {
            Refresh_Time = 0.0f;
            Int2 sour, dest;
            bool isFind;
            isFind = tm->VectorToIdx(Root->Position, sour);
            isFind = isFind && tm->VectorToIdx(pl->GetPos(), dest);
            if (isFind)
            {
                if (tm->PathFinding(sour, dest, PlWay))
                {
                    g = 0.0f;
                    PlSour = Root->Position;
                    PlWay.pop_back();
                    PlDest = tm->IdxToVector(PlWay.back()->idx);
                }
            }
        }
        if (!PlWay.empty())
        {
            /*PlSour = pl->GetPos();*/
            Root->Position = Lerp(PlSour, PlDest, g);
            g += DeltaTime * g_speed * Game_Speed;
            if (g > 1.0f)
            {
                g = 0.0f;
                PlSour = PlDest;
                PlWay.pop_back(); //¸ÇµÞ±æ »©±â
                if (!PlWay.empty())
                    PlDest = tm->IdxToVector(PlWay.back()->idx);
            }
        }

        if (isCollision(Shot_Circle, pl->GetPos()))
        {
            SoldierState = SD_ALERT;
        }
    }
    
    if (Health < 1)
    {
        SOUND->Play("SD_DEATH");
        SOUND->SetVolume("SD_DEATH", 0.3f);
        Health = 10;
        SoldierState = SD_DEAD;
        Reloading_Time = 0.0f;
        Shooting_Time = 0.0f;
        Soldier_Die->ChangeAnim(_ONCE, 0.2f / Game_Speed);
    }
}

void Soldier::StateShot()
{
    if (!Game_Speed == 0)
    {
        if (Acs->isRide)
        {
            LookTarget2(Acs->GetPos(), Soldier_Shot, -Rotation);
            LookTarget(Acs->GetPos(), Soldier_Shot_Effect, -Rotation);
            LookTarget2(Acs->GetPos(), Soldier_Die, -Rotation);
        }
        else if (!Acs->isRide)
        {
            LookTarget2(pl->GetPos(), Soldier_Shot, -Rotation);
            LookTarget(pl->GetPos(), Soldier_Shot_Effect, -Rotation);
            LookTarget2(pl->GetPos(), Soldier_Die, -Rotation);
        }
        
        Shooting_Time += DeltaTime;
        if (Shooting_Time > 0.2f / Game_Speed)
        {
            Shooting_Time = 0.0f;
            SoldierState = SD_ALERT;
            Reloading_Time = -1.0f / Game_Speed;
        }
        if (Health < 1)
        {
            SOUND->Play("SD_DEATH");
            SOUND->SetVolume("SD_DEATH", 0.3f);
            Health = 10;
            SoldierState = SD_DEAD;
            Reloading_Time = 0.0f;
            Shooting_Time = 0.0f;
            Soldier_Die->ChangeAnim(_ONCE, 0.2f / Game_Speed);
        }
    }
}

void Soldier::StateDead()
{
    if (!Game_Speed == 0)
    {
        Hp_Bar->isActive = false;
        Shooting_Time += DeltaTime;
        if (Shooting_Time > 0.8f / Game_Speed)
        {
            Shooting_Time = 0.0f;
            SetPos(Vector2(-2000.0f, 100.0f));
            isDead = true;
        }
    }
}

void Soldier::StateAlert()
{
    if (!Game_Speed == 0)
    {
        if (Acs->isRide)
        {
            LookTarget2(Acs->GetPos(), Soldier_Die, -Rotation);
            if (!isCollision(Shot_Circle, Acs->GetPos()) and Reloading_Time > 0.0f)
            {
                SoldierState = SD_MOVE;
                Soldier_Move->ChangeAnim(_LOOP, 0.1f / Game_Speed);
            }
            if (isCollision(Shot_Circle, Acs->GetPos()) and Reloading_Time > 0.0f)
            {
                LookTarget2(Acs->GetPos(), Soldier_Idle, -Rotation);
                Shot_Line1->Rotation.z = -30.0f * TORADIAN - PI / 2.0f + Soldier_Idle->Rotation.z;
                Shot_Line2->Rotation.z = 30.0f * TORADIAN - PI / 2.0f + Soldier_Idle->Rotation.z;
                SoldierState = SD_SHOT;
                Soldier_Shot_Effect->ChangeAnim(_ONCE, 0.03f / Game_Speed);
                for (int i = 0; i < 30; i++)
                {
                    if (!SB[i].Soldier_Bullet->isActive)
                    {
                        SOUND->Stop("SD_SHOT");
                        SOUND->Play("SD_SHOT");
                        SOUND->SetVolume("SD_SHOT", 0.3f);
                        //°Ý¹ß
                        SB[i].Soldier_Bullet->Position = Root->Position;
                        SB[i].Soldier_Bullet->isActive = true;
                        SB[i].Hitbox->isActive = true;
                        LookTarget(Acs->GetPos(), SB[i].Soldier_Bullet, 0.0f);
                        SB[i].Dir = RadianToDir(SB[i].Soldier_Bullet->Rotation.z + 0.5f * PI);
                        break;
                    }
                }
            }
            
        }
        else if (!Acs->isRide)
        {
            LookTarget2(pl->GetPos(), Soldier_Die, -Rotation);
            if (!isCollision(Shot_Circle, pl->GetPos()) and Reloading_Time > 0.0f)
            {
                SoldierState = SD_MOVE;
                Soldier_Move->ChangeAnim(_LOOP, 0.1f / Game_Speed);
            }
            if (isCollision(Shot_Circle, pl->GetPos()) and Reloading_Time > 0.0f)
            {
                LookTarget2(pl->GetPos(), Soldier_Idle, -Rotation);
                Shot_Line1->Rotation.z = -30.0f * TORADIAN - PI / 2.0f + Soldier_Idle->Rotation.z;
                Shot_Line2->Rotation.z = 30.0f * TORADIAN - PI / 2.0f + Soldier_Idle->Rotation.z;
                SoldierState = SD_SHOT;
                Soldier_Shot_Effect->ChangeAnim(_ONCE, 0.03f / Game_Speed);
                for (int i = 0; i < 30; i++)
                {
                    if (!SB[i].Soldier_Bullet->isActive)
                    {
                        SOUND->Stop("SD_SHOT");
                        SOUND->Play("SD_SHOT");
                        SOUND->SetVolume("SD_SHOT", 0.3f);
                        //°Ý¹ß
                        SB[i].Soldier_Bullet->Position = Root->Position;
                        SB[i].Soldier_Bullet->isActive = true;
                        SB[i].Hitbox->isActive = true;
                        LookTarget(pl->GetPos(), SB[i].Soldier_Bullet, 0.0f);
                        SB[i].Dir = RadianToDir(SB[i].Soldier_Bullet->Rotation.z + 0.5f * PI);
                        break;
                    }
                }
            }
            
        }
        Soldier_Idle->color = Color(0.7f, 0.5f, 0.5f, 0.5f);
        Soldier_Shot->color = Color(0.7f, 0.5f, 0.5f, 0.5f);
        Soldier_Move->color = Color(0.7f, 0.5f, 0.5f, 0.5f);
        
        Reloading_Time += DeltaTime;
        
        if (Health < 1)
        {
            SOUND->Play("SD_DEATH");
            SOUND->SetVolume("SD_DEATH", 0.3f);
            Health = 10;
            SoldierState = SD_DEAD;
            Reloading_Time = 0.0f;
            Shooting_Time = 0.0f;
            Soldier_Die->ChangeAnim(_ONCE, 0.2f / Game_Speed);
        }
    }
}

void Soldier::StateBack()
{
    if (sqrt(pow((Selected_Pos - Root->Position).x, 2) + pow((Selected_Pos - Root->Position).y, 2)) < 5.0f)
    {
        Soldier_Move->ChangeAnim(_STOP, 0.1f / Game_Speed);
    }

    // shot by player
    for (int j = 0; j < 10; j++)
    {
        if (isCollision(HitBox, pl->PB[j].Hitbox))
        {
            SoldierState = SD_ALERT;
        }
    }
    for (int j = 0; j < 50; j++)
    {
        if (isCollision(HitBox, pl->MB[j].Hitbox))
        {
            SoldierState = SD_ALERT;
        }
    }
    for (int j = 0; j < 30; j++)
    {
        if (isCollision(HitBox, pl->RB[j].Hitbox))
        {
            SoldierState = SD_ALERT;
        }
    }
    if (isCollision(HitBox, pl->Fire_HitBox) and !isHit)
    {
        SoldierState = SD_ALERT;
    }
    //shot by player gl
    for (int j = 0; j < 3; j++)
    {
        if (isCollision(HitBox, pl->GB[j].GL_HitBox))
        {
            SoldierState = SD_ALERT;

        }
    }
    for (int j = 0; j < 3; j++)
    {
        if (isCollision(HitBox, pl->GB[j].GL_HitBox2) and !isHit)
        {
            SoldierState = SD_ALERT;
        }
    }

    //shot by ACS
    for (int j = 0; j < 30; j++)
    {
        if (isCollision(HitBox, Acs->SB[j].Hitbox))
        {
            SoldierState = SD_ALERT;
        }
    }
    for (int j = 0; j < 30; j++)
    {
        if (isCollision(HitBox, Acs->SB[j].Hitbox2) and !isHit)
        {
            SoldierState = SD_ALERT;
        }
    }

    Shot_Line1->Rotation.z = -30.0f * TORADIAN - PI / 2.0f + Soldier_Idle->Rotation.z;
    Shot_Line2->Rotation.z = 30.0f * TORADIAN - PI / 2.0f + Soldier_Idle->Rotation.z;
    LookTarget2(Selected_Pos, Soldier_Idle, -Rotation);
    LookTarget2(Selected_Pos, Soldier_Move, -Rotation);
    LookTarget2(Selected_Pos, Soldier_Die, -Rotation);
    Refresh_Time += DeltaTime;
    if (Refresh_Time > 1.0f)
    {
        Refresh_Time = 0.0f;
        Int2 sour, dest;
        bool isFind;
        isFind = tm->VectorToIdx(Root->Position, sour);
        isFind = isFind && tm->VectorToIdx(Selected_Pos, dest);
        if (isFind)
        {
            if (tm->PathFinding(sour, dest, PlWay))
            {
                g = 0.0f;
                PlSour = Root->Position;
                PlWay.pop_back();
                PlDest = tm->IdxToVector(PlWay.back()->idx);
            }
        }
    }
    if (!PlWay.empty())
    {
        /*PlSour = pl->GetPos();*/
        Root->Position = Lerp(PlSour, PlDest, g);
        g += DeltaTime * g_speed* Game_Speed;
        if (g > 1.0f)
        {
            g = 0.0f;
            PlSour = PlDest;
            PlWay.pop_back(); //¸ÇµÞ±æ »©±â
            if (!PlWay.empty())
                PlDest = tm->IdxToVector(PlWay.back()->idx);
        }
    }

    //go back alert
    if (Acs->isRide)
    {
        if (isCollision(Shot_Circle, Acs->GetPos()))
        {
            SoldierState = SD_ALERT;
        }
    }
    else if (!Acs->isRide)
    {
        if (isCollision(Shot_Circle, pl->GetPos()))
        {
            SoldierState = SD_ALERT;
        }
    }

    if (Health < 1)
    {
        SOUND->Play("SD_DEATH");
        SOUND->SetVolume("SD_DEATH", 0.3f);
        Health = 10;
        SoldierState = SD_DEAD;
        Reloading_Time = 0.0f;
        Shooting_Time = 0.0f;
        Soldier_Die->ChangeAnim(_ONCE, 0.2f / Game_Speed);
    }
}

