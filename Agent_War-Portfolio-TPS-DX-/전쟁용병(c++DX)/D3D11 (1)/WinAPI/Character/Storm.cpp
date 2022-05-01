#include "stdafx.h"
#include "Character.h"
#include "Storm.h"
#include "Player.h"
#include "ACS.h"
#include "TileMap/Tile.h"
#include "TileMap/TileMap.h"

Storm::Storm()
{
    isAlarm = false;
    //setting
    Game_Speed = 1.0f;
    Shooting_Time = 0.0f;
    Reloading_Time = 0.0f;
    DamagedTime = 0.0f;
    Refresh_Time = 2.0f;
    isHit = false;
    isCharge = true;
    Rotation = 0.0f;
    g_speed = 2.0f;
    isDead = false;

    Health = 20;
    StormState = ST_IDLE;

    Storm_Idle = new ObImage(L"Image/TDS/Soldier3/Gunner.png");
    Storm_Idle->Scale = Vector2(120.0f, 120.0f);
    Storm_Idle->P = &Root->RT;

    Storm_Move = new ObImage(L"Image/TDS/Soldier3/GunnerWalk_01.png");
    Storm_Move->Scale = Vector2(150.0f, 150.0f);
    Storm_Move->MaxFrame = Int2(7, 1);
    Storm_Move->P = &Root->RT;

    Storm_Die = new ObImage(L"Image/TDS/Soldier3/Gunner_Die.png");
    Storm_Die->Scale = Vector2(120.0f, 120.0f);
    Storm_Die->MaxFrame = Int2(5, 1);
    Storm_Die->P = &Root->RT;

    Storm_Shot = new ObImage(L"Image/TDS/Soldier3/GunnerShot.png");
    Storm_Shot->Scale = Vector2(120.0f, 120.0f);
    Storm_Shot->P = &Root->RT;

    Storm_Shot_Effect = new ObImage(L"Image/TDS/Soldier3/GunnerShotEffect.png");
    Storm_Shot_Effect->Scale = Vector2(50.0f, 50.0f);
    Storm_Shot_Effect->MaxFrame = Int2(3, 1);
    Storm_Shot_Effect->Pivot = Vector2(0.16f, 0.5f);
    Storm_Shot_Effect->P = &Root->RT;

    //Storm HitBox
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

    //Storm Range
    Shot_Circle = new ObCircle();
    Shot_Circle->isFill = false;
    Shot_Circle->Scale = Vector2(300.0f, 300.0f);
    Shot_Circle->P = &Root->RT;

    Look_Circle = new ObCircle();
    Look_Circle->isFill = false;
    Look_Circle->Scale = Vector2(300.0f, 300.0f);
    Look_Circle->P = &Root->RT;

    Shot_Line1 = new ObLine();
    Shot_Line1->Scale = Vector2(150.0f, 0.0f);
    Shot_Line1->color = Color(1.0f, 0.0f, 0.0f, 0.5f);
    Shot_Line1->Rotation.z = -60.0f * TORADIAN - PI / 2.0f + Rotation;
    Shot_Line1->P = &Root->RT;

    Shot_Line2 = new ObLine();
    Shot_Line2->Scale = Vector2(150.0f, 0.0f);
    Shot_Line2->color = Color(1.0f, 0.0f, 0.0f, 0.5f);
    Shot_Line2->Rotation.z = 60.0f * TORADIAN - PI / 2.0f + Rotation;
    Shot_Line2->P = &Root->RT;

    for (int i = 0; i < 30; i++)
    {
        SB[i].Storm_Bullet = new ObImage(L"Image/TDS/Soldier3/GunnerBullet.png");
        SB[i].Storm_Bullet->Scale = Vector2(5.0f, 5.0f);
        SB[i].Storm_Bullet->Pivot = Vector2(0.0f, 0.0f);
        SB[i].Storm_Bullet->isActive = false;
        SB[i].Storm_Bullet->Position = Root->Position;
        SB[i].Hitbox = new ObRect;
        SB[i].Hitbox->Scale = Vector2(5.0f, 5.0f);
        SB[i].Hitbox->Pivot = Vector2(0.0f, 0.0f);
        SB[i].Hitbox->P = &SB[i].Storm_Bullet->RT;
        SB[i].Hitbox->isFill = false;
        SB[i].Hitbox->isActive = false;
        SB[i].Speed = 200.0f;
        SB[i].Power = 2;
        SB[i].Dir = Vector2(1.0f, 0.0f);
    }

    //STORM
    SOUND->AddSound("Sound/ENEMY/STORM_FIRE.wav", "ST_SHOT", false);
    SOUND->AddSound("Sound/ENEMY/DEATH.wav", "ST_DEATH", false);
    //SOUND
    SOUND->AddSound("Sound/PLAYER/GT_EXPLODE.wav", "GT_EXPLODE", false);
}

Storm::~Storm()
{
    delete Storm_Idle;
    delete Storm_Move;
    delete Storm_Die;
    delete Storm_Shot;
    delete Storm_Shot_Effect;
    delete Shot_Circle;
    delete Look_Circle;
    delete Shot_Line1;
    delete Shot_Line2;
    for (int i = 0; i < 30; i++)
    {
        delete SB[i].Storm_Bullet;
    }
    delete Hp_Bar;
}

void Storm::Update()
{
    //health
    if (Health > 20)
        Health = 20;
    if (Health < 1)
        Health = 0;

    if (Game_Speed > 0.0f)
    {
        switch (StormState)
        {
        case ST_IDLE:
            StateIdle();
            break;
        case ST_MOVE:
            StateMove();
            break;
        case ST_SHOT:
            StateShot();
            break;
        case ST_DEAD:
            StateDead();
            break;
        case ST_ALERT:
            StateAlert();
            break;
        case ST_BACK:
            StateBack();
            break;
        }
    }
    

    //fired bullet
    for (int i = 0; i < 30; i++)
    {
        if (SB[i].Storm_Bullet->isActive)
        {
            SB[i].Storm_Bullet->Position += DeltaTime * SB[i].Speed * SB[i].Dir * Game_Speed;
        }
    }

    //bullet out
    for (int i = 0; i < 30; i++)
    {
        if (SB[i].Storm_Bullet->Position.x > Root->Position.x + 1000.0f or SB[i].Storm_Bullet->Position.x < Root->Position.x - 1000.0f or
            SB[i].Storm_Bullet->Position.y > Root->Position.y + 1000.0f or SB[i].Storm_Bullet->Position.y < Root->Position.y - 1000.0f)
        {
            SB[i].Storm_Bullet->isActive = false;
            SB[i].Hitbox->isActive = false;
            SB[i].Storm_Bullet->Position = Root->Position;
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
    if (Storm_Idle->Rotation.z > 2 * PI)
    {
        Storm_Idle->Rotation.z -= 2 * PI;
    }
    if (Storm_Idle->Rotation.z < 0.0f)
    {
        Storm_Idle->Rotation.z += 2 * PI;
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

    if (Health != 20)
    {
        Storm_Idle->color = Color(0.7f, 0.5f, 0.5f, 0.5f);
        Storm_Shot->color = Color(0.7f, 0.5f, 0.5f, 0.5f);
        Storm_Move->color = Color(0.7f, 0.5f, 0.5f, 0.5f);
    }
}

void Storm::LateUpdate()
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

    //walking sand
    {
        Int2 idx;
        Vector2 foot = Root->Position + Vector2(0.0f, -12.0f);

        if (tm->VectorToIdx(foot, idx))
        {
            if (tm->Tiles[idx.x][idx.y].state == TILE_SAND)
            {
                g_speed = 1.5f;
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
                g_speed = 2.0f;
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
                g_speed = 3.0f;
            }
        }
    }
}

void Storm::Render()
{
    Character::Render();

    /*Shot_Circle->Render();
    Look_Circle->Render();
    Shot_Line1->Render();
    Shot_Line2->Render();*/
    switch (StormState)
    {
    case ST_IDLE:
        Storm_Idle->Render();
        break;
    case ST_MOVE:
        Storm_Move->Render();
        Storm_Idle->Render();
        break;
    case ST_SHOT:
        Storm_Shot_Effect->Render();
        Storm_Shot->Render();
        break;
    case ST_DEAD:
        Storm_Die->Render();
        break;
    case ST_ALERT:
        Storm_Idle->Render();
        break;
    case ST_BACK:
        Storm_Move->Render();
        Storm_Idle->Render();
        break;
    }

    //bullet
    for (int i = 0; i < 30; i++)
    {
        SB[i].Storm_Bullet->Render();
        /*SB[i].Hitbox->Render();*/
    }
    /*HitBox->Render();*/
    Hp_Bar->Render();
}

void Storm::StateIdle()
{
    if (!Game_Speed == 0)
    {
        if (Acs->isRide)
        {
            LookTarget2(Acs->GetPos(), Storm_Die, -Rotation);
            Reloading_Time += DeltaTime;
            if (isCollision(Look_Circle, Acs->GetPos()) and Reloading_Time > 0.0f and Range(Acs->GetPos(), Shot_Line1, Shot_Line2, Rotation, 60.0f))
            {
                StormState = ST_ALERT;
            }
            if (Health != 20)
            {
                StormState = ST_ALERT;
            }
        }
        else if (!Acs->isRide)
        {
            LookTarget2(pl->GetPos(), Storm_Die, -Rotation);
            Reloading_Time += DeltaTime;
            if (isCollision(Look_Circle, pl->GetPos()) and Reloading_Time > 0.0f and Range(pl->GetPos(), Shot_Line1, Shot_Line2, Rotation, 60.0f) and !pl->Hide)
            {
                StormState = ST_ALERT;
            }
            if (Health != 20)
            {
                StormState = ST_ALERT;
            }
        }
        if (isCollision(pl->Shot_Circle, Root->Position) or isCollision(pl->Hit_Circle, Root->Position))
        {
            StormState = ST_ALERT;
        }
        
        if (Health < 1)
        {
            SOUND->Play("ST_DEATH");
            SOUND->SetVolume("ST_DEATH", 0.3f);
            StormState = ST_DEAD;
            Reloading_Time = 0.0f;
            Shooting_Time = 0.0f;
            Storm_Die->ChangeAnim(_ONCE, 0.2f / Game_Speed);
        }
    }
}
void Storm::StateMove()
{
    if (Acs->isRide)
    {
        if (sqrt(pow((Acs->GetPos() - Root->Position).x, 2) + pow((Acs->GetPos() - Root->Position).y, 2)) > 1000.0f)
        {
            StormState = ST_BACK;
            Storm_Move->ChangeAnim(_LOOP, 0.1f / Game_Speed);
        }
        Shot_Line1->Rotation.z = -30.0f * TORADIAN - PI / 2.0f + Storm_Idle->Rotation.z;
        Shot_Line2->Rotation.z = 30.0f * TORADIAN - PI / 2.0f + Storm_Idle->Rotation.z;
        LookTarget2(Acs->GetPos(), Storm_Idle, -Rotation);
        LookTarget2(Acs->GetPos(), Storm_Move, -Rotation);
        LookTarget2(Acs->GetPos(), Storm_Die, -Rotation);
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

        if (isCollision(Shot_Circle, Acs->GetPos()))
        {
            StormState = ST_ALERT;
        }
    }
    else if (!Acs->isRide)
    {
        if (sqrt(pow((pl->GetPos() - Root->Position).x, 2) + pow((pl->GetPos() - Root->Position).y, 2)) > 1000.0f)
        {
            StormState = ST_BACK;
            Storm_Move->ChangeAnim(_LOOP, 0.1f / Game_Speed);
        }
        Shot_Line1->Rotation.z = -30.0f * TORADIAN - PI / 2.0f + Storm_Idle->Rotation.z;
        Shot_Line2->Rotation.z = 30.0f * TORADIAN - PI / 2.0f + Storm_Idle->Rotation.z;
        LookTarget2(pl->GetPos(), Storm_Idle, -Rotation);
        LookTarget2(pl->GetPos(), Storm_Move, -Rotation);
        LookTarget2(pl->GetPos(), Storm_Die, -Rotation);
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

        if (isCollision(Shot_Circle, pl->GetPos()))
        {
            StormState = ST_ALERT;
        }
    }
    
    if (Health < 1)
    {
        SOUND->Play("ST_DEATH");
        SOUND->SetVolume("ST_DEATH", 0.3f);
        StormState = ST_DEAD;
        Reloading_Time = 0.0f;
        Shooting_Time = 0.0f;
        Storm_Die->ChangeAnim(_ONCE, 0.2f / Game_Speed);
    }
}

void Storm::StateShot()
{
    if (!Game_Speed == 0)
    {
        if (Acs->isRide)
        {
            LookTarget2(Acs->GetPos(), Storm_Shot, -Rotation);
            LookTarget(Acs->GetPos(), Storm_Shot_Effect, -Rotation);
            LookTarget2(Acs->GetPos(), Storm_Die, -Rotation);
        }
        else if (!Acs->isRide)
        {
            LookTarget2(pl->GetPos(), Storm_Shot, -Rotation);
            LookTarget(pl->GetPos(), Storm_Shot_Effect, -Rotation);
            LookTarget2(pl->GetPos(), Storm_Die, -Rotation);
        }
        
        Shooting_Time += DeltaTime;
        if (Shooting_Time > 0.2f / Game_Speed)
        {
            Shooting_Time = 0.0f;
            StormState = ST_ALERT;
            Reloading_Time = -0.6f / Game_Speed;
        }
        if (Health < 1)
        {
            SOUND->Play("ST_DEATH");
            SOUND->SetVolume("ST_DEATH", 0.3f);
            StormState = ST_DEAD;
            Reloading_Time = 0.0f;
            Shooting_Time = 0.0f;
            Storm_Die->ChangeAnim(_ONCE, 0.2f / Game_Speed);
        }
    }
}

void Storm::StateDead()
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

void Storm::StateAlert()
{
    if (!Game_Speed == 0)
    {
        if (Acs->isRide)
        {
            LookTarget2(Acs->GetPos(), Storm_Die, -Rotation);
            if (!isCollision(Shot_Circle, Acs->GetPos()) and Reloading_Time > 0.0f)
            {
                StormState = ST_MOVE;
                Storm_Move->ChangeAnim(_LOOP, 0.1f / Game_Speed);
            }
            if (isCollision(Shot_Circle, Acs->GetPos()) and Reloading_Time > 0.0f)
            {
                LookTarget2(Acs->GetPos(), Storm_Idle, -Rotation);
                Shot_Line1->Rotation.z = -30.0f * TORADIAN - PI / 2.0f + Storm_Idle->Rotation.z;
                Shot_Line2->Rotation.z = 30.0f * TORADIAN - PI / 2.0f + Storm_Idle->Rotation.z;
                StormState = ST_SHOT;
                Storm_Shot_Effect->ChangeAnim(_ONCE, 0.03f / Game_Speed);
                for (int i = 0; i < 30; i++)
                {
                    if (!SB[i].Storm_Bullet->isActive)
                    {
                        SOUND->Stop("ST_SHOT");
                        SOUND->Play("ST_SHOT");
                        SOUND->SetVolume("ST_SHOT", 0.3f);
                        //°Ý¹ß
                        SB[i].Storm_Bullet->Position = Root->Position;
                        SB[i].Storm_Bullet->isActive = true;
                        SB[i].Hitbox->isActive = true;
                        LookTarget(Acs->GetPos(), SB[i].Storm_Bullet, 0.0f);
                        SB[i].Dir = RadianToDir(SB[i].Storm_Bullet->Rotation.z + 0.5f * PI);
                        break;
                    }
                }
            }
        }
        else if (!Acs->isRide)
        {
            LookTarget2(pl->GetPos(), Storm_Die, -Rotation);
            if (!isCollision(Shot_Circle, pl->GetPos()) and Reloading_Time > 0.0f)
            {
                StormState = ST_MOVE;
                Storm_Move->ChangeAnim(_LOOP, 0.1f / Game_Speed);
            }
            if (isCollision(Shot_Circle, pl->GetPos()) and Reloading_Time > 0.0f)
            {
                LookTarget2(pl->GetPos(), Storm_Idle, -Rotation);
                Shot_Line1->Rotation.z = -30.0f * TORADIAN - PI / 2.0f + Storm_Idle->Rotation.z;
                Shot_Line2->Rotation.z = 30.0f * TORADIAN - PI / 2.0f + Storm_Idle->Rotation.z;
                StormState = ST_SHOT;
                Storm_Shot_Effect->ChangeAnim(_ONCE, 0.03f / Game_Speed);
                for (int i = 0; i < 30; i++)
                {
                    if (!SB[i].Storm_Bullet->isActive)
                    {
                        SOUND->Stop("ST_SHOT");
                        SOUND->Play("ST_SHOT");
                        SOUND->SetVolume("ST_SHOT", 0.3f);
                        //°Ý¹ß
                        SB[i].Storm_Bullet->Position = Root->Position;
                        SB[i].Storm_Bullet->isActive = true;
                        SB[i].Hitbox->isActive = true;
                        LookTarget(pl->GetPos(), SB[i].Storm_Bullet, 0.0f);
                        SB[i].Dir = RadianToDir(SB[i].Storm_Bullet->Rotation.z + 0.5f * PI);
                        break;
                    }
                }
            }
            
        }
        Storm_Idle->color = Color(0.7f, 0.5f, 0.5f, 0.5f);
        Storm_Shot->color = Color(0.7f, 0.5f, 0.5f, 0.5f);
        Storm_Move->color = Color(0.7f, 0.5f, 0.5f, 0.5f);
        
        Reloading_Time += DeltaTime;
        
        if (Health < 1)
        {
            SOUND->Play("ST_DEATH");
            SOUND->SetVolume("ST_DEATH", 0.3f);
            StormState = ST_DEAD;
            Reloading_Time = 0.0f;
            Shooting_Time = 0.0f;
            Storm_Die->ChangeAnim(_ONCE, 0.2f / Game_Speed);
        }
    }
}

void Storm::StateBack()
{
    if (sqrt(pow((Selected_Pos - Root->Position).x, 2) + pow((Selected_Pos - Root->Position).y, 2)) < 5.0f)
    {
        Storm_Move->ChangeAnim(_STOP, 0.1f / Game_Speed);
    }

    // shot by player
    for (int j = 0; j < 10; j++)
    {
        if (isCollision(HitBox, pl->PB[j].Hitbox))
        {
            StormState = ST_ALERT;
        }
    }
    for (int j = 0; j < 50; j++)
    {
        if (isCollision(HitBox, pl->MB[j].Hitbox))
        {
            StormState = ST_ALERT;
        }
    }
    for (int j = 0; j < 30; j++)
    {
        if (isCollision(HitBox, pl->RB[j].Hitbox))
        {
            StormState = ST_ALERT;
        }
    }
    if (isCollision(HitBox, pl->Fire_HitBox) and !isHit)
    {
        StormState = ST_ALERT;
    }
    //shot by player gl
    for (int j = 0; j < 3; j++)
    {
        if (isCollision(HitBox, pl->GB[j].GL_HitBox))
        {
            StormState = ST_ALERT;

        }
    }
    for (int j = 0; j < 3; j++)
    {
        if (isCollision(HitBox, pl->GB[j].GL_HitBox2) and !isHit)
        {
            StormState = ST_ALERT;
        }
    }

    //shot by ACS
    for (int j = 0; j < 30; j++)
    {
        if (isCollision(HitBox, Acs->SB[j].Hitbox))
        {
            StormState = ST_ALERT;
        }
    }
    for (int j = 0; j < 30; j++)
    {
        if (isCollision(HitBox, Acs->SB[j].Hitbox2) and !isHit)
        {
            StormState = ST_ALERT;
        }
    }

    Shot_Line1->Rotation.z = -30.0f * TORADIAN - PI / 2.0f + Storm_Idle->Rotation.z;
    Shot_Line2->Rotation.z = 30.0f * TORADIAN - PI / 2.0f + Storm_Idle->Rotation.z;
    LookTarget2(Selected_Pos, Storm_Idle, -Rotation);
    LookTarget2(Selected_Pos, Storm_Move, -Rotation);
    LookTarget2(Selected_Pos, Storm_Die, -Rotation);
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
        /*PlSour = Selected_Pos;*/
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

    //go back alert
    if (Acs->isRide)
    {
        if (isCollision(Shot_Circle, Acs->GetPos()))
        {
            StormState = ST_ALERT;
        }
    }
    else if (!Acs->isRide)
    {
        if (isCollision(Shot_Circle, pl->GetPos()))
        {
            StormState = ST_ALERT;
        }
    }

    if (Health < 1)
    {
        SOUND->Play("ST_DEATH");
        SOUND->SetVolume("ST_DEATH", 0.3f);
        StormState = ST_DEAD;
        Reloading_Time = 0.0f;
        Shooting_Time = 0.0f;
        Storm_Die->ChangeAnim(_ONCE, 0.2f / Game_Speed);
    }
}

