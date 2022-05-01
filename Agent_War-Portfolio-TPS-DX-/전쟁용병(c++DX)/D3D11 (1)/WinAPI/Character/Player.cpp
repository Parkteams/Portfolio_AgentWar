#include "stdafx.h"
#include "Character.h"
#include "Player.h"
#include "Sniper.h"
#include "Soldier.h"
#include "Storm.h"
#include "Bazooka.h"


Player::Player()
{
    Game_Speed = 1.0f;
    DamagedTime = 0.0f;

    Health = 5;
    Armor = 5;
    Money = 1000;
    MG_Bullet_Num = 30;
    R_Bullet_Num = 10;
    GL_Bullet_Num = 3;
    FT_Bullet_Num = 0;

    P_Range = 300.0f;
    MG_Range = 400.0f;
    R_Range = 500.0f;

    isHit = false;
    Hide = false;

    Move = new ObImage(L"Image/TDS/Player/Move2.png");
    Move->Scale = Vector2(150.0f, 150.0f);
    Move->MaxFrame = Int2(12, 1);
    Move->P = &Root->RT;

    Pistol = new ObImage(L"Image/TDS/Player/P/Hero_Pistol.png");
    Pistol->Scale = Vector2(100.0f, 100.0f);
    Pistol->P = &Root->RT;

    Pistol_Fire = new ObImage(L"Image/TDS/Player/P/Hero_Pistol_Fire.png");
    Pistol_Fire->Scale = Vector2(100.0f, 100.0f);
    Pistol_Fire->MaxFrame = Int2(4, 1);
    Pistol_Fire->P = &Root->RT;

    Pistol_Effect = new ObImage(L"Image/TDS/Player/P/Shot.png");
    Pistol_Effect->Scale = Vector2(50.0f, 50.0f);
    Pistol_Effect->Pivot = Vector2(0.16f, 0.5f);
    Pistol_Effect->MaxFrame = Int2(3, 1);
    Pistol_Effect->P = &Root->RT;

    RIFLE = new ObImage(L"Image/TDS/Player/R/Hero_Rifle.png");
    RIFLE->Scale = Vector2(100.0f, 100.0f);
    RIFLE->P = &Root->RT;

    RIFLE_Fire = new ObImage(L"Image/TDS/Player/R/Hero_Rifle_Fire.png");
    RIFLE_Fire->Scale = Vector2(100.0f, 100.0f);
    RIFLE_Fire->P = &Root->RT;

    RIFLE_Effect = new ObImage(L"Image/TDS/Player/R/Shot.png");
    RIFLE_Effect->Scale = Vector2(50.0f, 50.0f);
    RIFLE_Effect->Pivot = Vector2(0.11f, 0.6f);
    RIFLE_Effect->MaxFrame = Int2(3, 1);
    RIFLE_Effect->P = &Root->RT;

    MG = new ObImage(L"Image/TDS/Player/MG/Hero_MachineGun.png");
    MG->Scale = Vector2(100.0f, 100.0f);
    MG->P = &Root->RT;

    MG_Fire = new ObImage(L"Image/TDS/Player/MG/Hero_MachineGunFire.png");
    MG_Fire->Scale = Vector2(100.0f, 100.0f);
    MG_Fire->P = &Root->RT;

    MG_Effect = new ObImage(L"Image/TDS/Player/MG/Shot.png");
    MG_Effect->Scale = Vector2(50.0f, 50.0f);
    MG_Effect->Pivot = Vector2(0.11f, 0.65f);
    MG_Effect->MaxFrame = Int2(3, 1);
    MG_Effect->P = &Root->RT;

    GL = new ObImage(L"Image/TDS/Player/GL/Hero_GrenadeLauncher.png");
    GL->Scale = Vector2(100.0f, 100.0f);
    GL->P = &Root->RT;

    GL_Fire = new ObImage(L"Image/TDS/Player/GL/Hero_GrenadeLauncher_Fire01.png");
    GL_Fire->Scale = Vector2(100.0f, 100.0f);
    GL_Fire->MaxFrame = Int2(2, 1);
    GL_Fire->P = &Root->RT;

    FT = new ObImage(L"Image/TDS/Player/FT/Hero_Flamethrower.png");
    FT->Scale = Vector2(100.0f, 100.0f);
    FT->P = &Root->RT;

    FT_Fire = new ObImage(L"Image/TDS/Player/FT/Hero_Flamethrower_Fire.png");
    FT_Fire->Scale = Vector2(100.0f, 100.0f);
    FT_Fire->MaxFrame = Int2(3, 1);
    FT_Fire->P = &Root->RT;

    FT_Effect = new ObImage(L"Image/TDS/Player/FT/Flame.png");
    FT_Effect->Scale = Vector2(120.0f, 200.0f);
    FT_Effect->Pivot = Vector2(-0.05f, -0.45f);
    FT_Effect->MaxFrame = Int2(7, 1);
    FT_Effect->P = &Root->RT;

    Dead = new ObImage(L"Image/TDS/Player/Die.png");
    Dead->Scale = Vector2(100.0f, 100.0f);
    Dead->MaxFrame = Int2(4, 1);
    Dead->P = &Root->RT;

    //Player HitBox
    HitBox = new ObRect();
    HitBox->isFill = false;
    HitBox->Scale = Vector2(20.0f, 20.0f);
    HitBox->P = &Root->RT;

    //fire
    Fire_HitBox = new ObRect();
    Fire_HitBox->isFill = false;
    Fire_HitBox->Scale = Vector2(40.0f, 200.0f);
    Fire_HitBox->Pivot = Vector2(-0.05f, -0.45f);
    Fire_HitBox->P = &FT_Effect->RT;
    Fire_HitBox->isActive = false;

    //circle
    Shot_Circle = new ObCircle();
    Shot_Circle->isFill = false;
    Shot_Circle->Scale = Vector2(300.0f, 300.0f);
    Shot_Circle->isActive = false;

    Hit_Circle = new ObCircle();
    Hit_Circle->isFill = false;
    Hit_Circle->Scale = Vector2(300.0f, 300.0f);
    Hit_Circle->isActive = false;

    //bullet
    for (int i = 0; i < 10; i++)
    {
        PB[i].Pistol_Bullet = new ObImage(L"Image/TDS/Player/P/Bullet.png");
        PB[i].Pistol_Bullet->Scale = Vector2(5.0f, 5.0f);
        PB[i].Pistol_Bullet->Pivot = Vector2(0.0f, 0.0f);
        PB[i].Pistol_Bullet->isActive = false;
        PB[i].Hitbox = new ObRect;
        PB[i].Hitbox->Scale = Vector2(5.0f, 5.0f);
        PB[i].Hitbox->Pivot = Vector2(0.0f, 0.0f);
        PB[i].Hitbox->P = &PB[i].Pistol_Bullet->RT;
        PB[i].Hitbox->isFill = false;
        PB[i].Hitbox->isActive = false;
        PB[i].Speed = 400.0f;
        PB[i].Power = 2;
        PB[i].Dir = Vector2(1.0f,0.0f);
    }

    for (int i = 0; i < 50; i++)
    {
        MB[i].MG_Bullet = new ObImage(L"Image/TDS/Player/MG/Bullet.png");
        MB[i].MG_Bullet->Scale = Vector2(5.0f, 5.0f);
        MB[i].MG_Bullet->Pivot = Vector2(0.7f, 8.0f);
        MB[i].MG_Bullet->isActive = false;
        MB[i].Hitbox = new ObRect;
        MB[i].Hitbox->Scale = Vector2(5.0f, 5.0f);
        MB[i].Hitbox->Pivot = Vector2(0.7f, 8.0f);
        MB[i].Hitbox->P = &MB[i].MG_Bullet->RT;
        MB[i].Hitbox->isFill = false;
        MB[i].Hitbox->isActive = false;
        MB[i].Speed = 400.0f;
        MB[i].Power = 1;
        MB[i].Dir = Vector2(1.0f, 0.0f);
    }

    for (int i = 0; i < 30; i++)
    {
        RB[i].RIFLE_Bullet = new ObImage(L"Image/TDS/Player/R/Bullet.png");
        RB[i].RIFLE_Bullet->Scale = Vector2(5.0f, 5.0f);
        RB[i].RIFLE_Bullet->Pivot = Vector2(0.0f, 0.0f);
        RB[i].RIFLE_Bullet->isActive = false;
        RB[i].Hitbox = new ObRect;
        RB[i].Hitbox->Scale = Vector2(5.0f, 5.0f);
        RB[i].Hitbox->Pivot = Vector2(0.0f, 0.0f);
        RB[i].Hitbox->P = &RB[i].RIFLE_Bullet->RT;
        RB[i].Hitbox->isFill = false;
        RB[i].Hitbox->isActive = false;
        RB[i].Speed = 600.0f;
        RB[i].Power = 5;
        RB[i].Dir = Vector2(1.0f, 0.0f);
    }

    for (int i = 0; i < 3; i++)
    {
        GB[i].GL_Shot1 = new ObImage(L"Image/TDS/Player/GL/Shot1.png");
        GB[i].GL_Shot1->Scale = Vector2(50.0f, 50.0f);
        GB[i].GL_Shot1->Pivot = Vector2(0.2f, 0.2f);
        GB[i].GL_Shot1->MaxFrame = Int2(2, 1);
        GB[i].GL_Shot1->isActive = false;


        GB[i].GL_Shot2 = new ObImage(L"Image/TDS/Player/GL/Shot2 (1).png");
        GB[i].GL_Shot2->Scale = Vector2(100.0f, 100.0f);
        GB[i].GL_Shot2->MaxFrame = Int2(2, 1);
        GB[i].GL_Shot2->isActive = false;

        GB[i].GL_HitBox = new ObRect();
        GB[i].GL_HitBox->isFill = false;
        GB[i].GL_HitBox->Scale = Vector2(15.0f, 30.0f);
        GB[i].GL_HitBox->Pivot = Vector2(0.6f, 0.3f);
        GB[i].GL_HitBox->P = &GB[i].GL_Shot1->RT;
        GB[i].GL_HitBox->isActive = false;

        GB[i].GL_HitBox2 = new ObRect();
        GB[i].GL_HitBox2->isFill = false;
        GB[i].GL_HitBox2->Scale = Vector2(100.0f, 100.0f);
        GB[i].GL_HitBox2->Pivot = Vector2(0.0f, 0.0f);
        GB[i].GL_HitBox2->P = &GB[i].GL_Shot2->RT;
        GB[i].GL_HitBox2->isActive = false;

        GB[i].Speed = 300.0f;
        GB[i].Power = 5;
        GB[i].Dir = Vector2(1.0f, 0.0f);
        GB[i].Explode_Time = 0.0f;
        GB[i].Explode = false;
    }

    Player_Speed = 100.0f;
    PlayerSpeed = 100.0f;
    Shooting_Time = 0.0f;
    Reloading_Time = 0.0f;
    Hit_Time = 0.0f;

    PlayerState = PL_PISTOL;
    PlayerMoveState = PL_STAND;
    Gun_Kind = 0;

    //PLAYER
    SOUND->AddSound("Sound/PLAYER/P_FIRE.wav", "PL_PSHOT", false);
    SOUND->AddSound("Sound/PLAYER/R_FIRE.wav", "PL_RSHOT", false);
    SOUND->AddSound("Sound/PLAYER/MG_FIRE.wav", "PL_MGSHOT", false);
    SOUND->AddSound("Sound/PLAYER/GT_FIRE.wav", "PL_GTSHOT", false);
    SOUND->AddSound("Sound/PLAYER/GT_FIRE1.wav", "PL_GTSHOT2", false);
    SOUND->AddSound("Sound/PLAYER/FT_FIRE.wav", "PL_FTSHOT", false);
    SOUND->AddSound("Sound/PLAYER/GT_EXPLODE.wav", "GT_EXPLODE", false);
    SOUND->AddSound("Sound/PLAYER/DAMAGED.wav", "PL_DAMAGED", false);
    SOUND->AddSound("Sound/PLAYER/DEATH.wav", "PL_DEATH", false);
    SOUND->AddSound("Sound/PLAYER/WEAPON_CHANGE.wav", "PL_WEAPON_CHANGE", false);
}

Player::~Player()
{
    delete HitBox;
    delete Fire_HitBox;

    delete Shot_Circle;
    delete Hit_Circle;

    delete Move;
    delete Pistol;
    delete Pistol_Fire;
    delete Pistol_Effect;
    delete RIFLE;
    delete RIFLE_Fire;
    delete RIFLE_Effect;
    delete MG;
    delete MG_Fire;
    delete MG_Effect;
    delete GL;
    delete GL_Fire;
    delete FT;
    delete FT_Fire;
    delete FT_Effect;

    //bullet
    for (int i = 0; i < 10; i++)
    {
        delete PB[i].Pistol_Bullet;
        delete PB[i].Hitbox;
    }
    for (int i = 0; i < 50; i++)
    {
        delete MB[i].MG_Bullet;
        delete MB[i].Hitbox;
    }
    for (int i = 0; i < 30; i++)
    {
        delete RB[i].RIFLE_Bullet;
        delete RB[i].Hitbox;
    }
    for (int i = 0; i < 3; i++)
    {
        delete GB[i].GL_Shot1;
        delete GB[i].GL_Shot2;
        delete GB[i].GL_HitBox;
        delete GB[i].GL_HitBox2;
    }
}
void Player::Update()
{
    //IMGUI
    /*ImGui::SliderFloat("POS_X", &RIFLE_Effect->Pivot.x, 0.0f, 1.0f);
    ImGui::SliderFloat("POS_Y", &RIFLE_Effect->Pivot.y, 0.0f, 1.0f);
    ImGui::SliderFloat("POS_X", &FT_Effect->Pivot.x, -1.0f, 0.0f);
    ImGui::SliderFloat("POS_Y", &FT_Effect->Pivot.y, -1.0f, 0.0f);*/

    //IMGUI
    ImGui::SliderFloat("SPEED_PL", &Player_Speed, 0.0f, 1000.0f);

    //hit circle
    if (Hit_Circle->isActive)
    {
        Hit_Time += DeltaTime;
    }
    if (Hit_Time > 0.05f)
    {
        Hit_Circle->isActive = false;
        Hit_Time = 0.0f;
    }

    //hp
    if (Health > 10)
        Health = 10;
    if (Health < 1)
        Health = 0;
    if (Armor > 10)
        Armor = 10;
    if (Armor < 1)
        Armor = 0;

    if (Health ==0)
    {
        PlayerState = PL_DEAD;
        PlayerMoveState = PL_STAND;
        Dead->ChangeAnim(_ONCE, 0.25f / Game_Speed);
        Health = 1;
    }

    //Weapon
    if (MG_Bullet_Num > 500)
        MG_Bullet_Num = 500;
    if (MG_Bullet_Num < 0)
        MG_Bullet_Num = 0;
    if (R_Bullet_Num > 300)
        R_Bullet_Num = 300;
    if (R_Bullet_Num < 0)
        R_Bullet_Num = 0;
    if (GL_Bullet_Num > 30)
        GL_Bullet_Num = 30;
    if (GL_Bullet_Num < 0)
        GL_Bullet_Num = 0;
    if (FT_Bullet_Num > 500)
        FT_Bullet_Num = 500;
    if (FT_Bullet_Num < 0)
        FT_Bullet_Num = 0;

    //Money
    if (Money > 99999)
        Money = 99999;
    if (Money < 0)
        Money = 0;

    PrevPos = Root->Position;

    switch (PlayerState)
    {
    case PL_PISTOL:
        StatePistol();
        break;
    case PL_PISTOLFIRE:
        StatePistolFire();
        break;
    case PL_MG:
        StateMg();
        break;
    case PL_MGFIRE:
        StateMgFire();
        break;
    case PL_GL:
        StateGl();
        break;
    case PL_GLFIRE:
        StateGlFire();
        break;
    case PL_FT:
        StateFt();
        break;
    case PL_FTFIRE:
        StateFtFire();
        break;
    case PL_RIFLE:
        StateRifle();
        break;
    case PL_RIFLEFIRE:
        StateRifleFire();
        break;
    case PL_DEAD:
        StateDead();
        break;
    case PL_RIDE:
        StateRide();
        break;
    }

    switch (PlayerMoveState)
    {
    case PL_MOVE:
        PlayerMove();
        break;
    case PL_STAND:
        PlayerStand();
        break;
    }

    //fired bullet
    for (int i = 0; i < 10; i++)
    {
        if (PB[i].Pistol_Bullet->isActive)
        {
            PB[i].Pistol_Bullet->Position += DeltaTime * PB[i].Speed * PB[i].Dir * Game_Speed;
        }
    }
    for (int i = 0; i < 50; i++)
    {
        if (MB[i].MG_Bullet->isActive)
        {
            MB[i].MG_Bullet->Position += DeltaTime * MB[i].Speed * MB[i].Dir * Game_Speed;
        }
    }
    for (int i = 0; i < 30; i++)
    {
        if (RB[i].RIFLE_Bullet->isActive)
        {
            RB[i].RIFLE_Bullet->Position += DeltaTime * RB[i].Speed * RB[i].Dir * Game_Speed;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (GB[i].GL_Shot1->isActive)
        {
            GB[i].GL_Shot1->Position += DeltaTime * GB[i].Speed * GB[i].Dir * Game_Speed;
        }
    }

    //bullet out
    for (int i = 0; i < 10; i++)
    {
        if (PB[i].Pistol_Bullet->Position.x > Root->Position.x + P_Range or PB[i].Pistol_Bullet->Position.x < Root->Position.x - P_Range or
            PB[i].Pistol_Bullet->Position.y > Root->Position.y + P_Range or PB[i].Pistol_Bullet->Position.y < Root->Position.y - P_Range)
        {
            PB[i].Pistol_Bullet->isActive = false;
            PB[i].Hitbox->isActive = false;
        }

    }
    for (int i = 0; i < 50; i++)
    {
        if (MB[i].MG_Bullet->Position.x > Root->Position.x + MG_Range or MB[i].MG_Bullet->Position.x < Root->Position.x - MG_Range or
            MB[i].MG_Bullet->Position.y > Root->Position.y + MG_Range or MB[i].MG_Bullet->Position.y < Root->Position.y - MG_Range)
        {
            MB[i].MG_Bullet->isActive = false;
            MB[i].Hitbox->isActive = false;
        }

    }
    for (int i = 0; i < 30; i++)
    {
        if (RB[i].RIFLE_Bullet->Position.x > Root->Position.x + R_Range or RB[i].RIFLE_Bullet->Position.x < Root->Position.x - R_Range or
            RB[i].RIFLE_Bullet->Position.y > Root->Position.y + R_Range or RB[i].RIFLE_Bullet->Position.y < Root->Position.y - R_Range)
        {
            RB[i].RIFLE_Bullet->isActive = false;
            RB[i].Hitbox->isActive = false;
        }

    }
    for (int i = 0; i < 3; i++)
    {
        if (GB[i].GL_Shot1->Position.x > Root->Position.x + 2000.0f or GB[i].GL_Shot1->Position.x < Root->Position.x - 2000.0f or
            GB[i].GL_Shot1->Position.y > Root->Position.y + 2000.0f or GB[i].GL_Shot1->Position.y < Root->Position.y - 2000.0f)
        {
            GB[i].GL_Shot1->isActive = false;
            GB[i].GL_HitBox->isActive = false;
        }

    }
    for (int i = 0; i < 3; i++)
    {
        if (GB[i].GL_Shot2->Position.x > Root->Position.x + 2000.0f or GB[i].GL_Shot2->Position.x < Root->Position.x - 2000.0f or
            GB[i].GL_Shot2->Position.y > Root->Position.y + 2000.0f or GB[i].GL_Shot2->Position.y < Root->Position.y - 2000.0f)
        {
            GB[i].GL_Shot2->isActive = false;
            GB[i].GL_HitBox2->isActive = false;
        }

    }

    //gl explode
    for (int i = 0; i < 3; i++)
    {
        if (GB[i].Explode)
        {
            SOUND->Stop("PL_GTSHOT");
            GB[i].Explode_Time += DeltaTime;
            if (GB[i].Explode_Time > 0.5f / Game_Speed)
            {
                GB[i].Explode_Time = 0.0f;
                GB[i].GL_Shot2->Position = Root->Position + Vector2(-30000.0f, 30000.0f);
                GB[i].Explode = false;
            }
        }
    }

    if (isHit)
    {
        DamagedTime += DeltaTime;
        Move->color = Color(0.5f, 0.5f, 0.5f, RndFloat(0.0f, 0.5f));
        Pistol->color = Color(0.5f, 0.5f, 0.5f, RndFloat(0.0f, 0.5f));
        Pistol_Fire->color = Color(0.5f, 0.5f, 0.5f, RndFloat(0.0f, 0.5f));
        RIFLE->color = Color(0.5f, 0.5f, 0.5f, RndFloat(0.0f, 0.5f));
        RIFLE_Fire->color = Color(0.5f, 0.5f, 0.5f, RndFloat(0.0f, 0.5f));
        MG->color = Color(0.5f, 0.5f, 0.5f, RndFloat(0.0f, 0.5f));
        MG_Fire->color = Color(0.5f, 0.5f, 0.5f, RndFloat(0.0f, 0.5f));
        GL->color = Color(0.5f, 0.5f, 0.5f, RndFloat(0.0f, 0.5f));
        GL_Fire->color = Color(0.5f, 0.5f, 0.5f, RndFloat(0.0f, 0.5f));
        FT->color = Color(0.5f, 0.5f, 0.5f, RndFloat(0.0f, 0.5f));
        FT_Fire->color = Color(0.5f, 0.5f, 0.5f, RndFloat(0.0f, 0.5f));
        if (DamagedTime > 1.0f/Game_Speed)
        {
            Move->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
            Pistol->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
            Pistol_Fire->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
            RIFLE->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
            RIFLE_Fire->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
            MG->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
            MG_Fire->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
            GL->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
            GL_Fire->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
            FT->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
            FT_Fire->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
            DamagedTime = 0.0f;
            isHit = false;
        }
    }
}

void Player::LateUpdate()
{
    //sniper
    for (int i = 0; i <10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (isCollision(HitBox, Sp[i]->SB[j].Hitbox) and !isHit)
            {
                isHit = true;
                SOUND->Stop("PL_DAMAGED");
                SOUND->Play("PL_DAMAGED");
                SOUND->SetVolume("PL_DAMAGED", 0.3f);
                Sp[i]->SB[j].Sniper_Bullet->Position = Sp[i]->GetPos() + Vector2(-30000.0f,30000.0f);
                if (Armor > 0)
                {
                    Health -= Sp[i]->SB[j].Power * 0.5f;
                    Armor -= 1;
                }
                else
                {
                    Health -= Sp[i]->SB[j].Power;
                }
            }
        }
    }
    //soldier
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (isCollision(HitBox, Sd[i]->SB[j].Hitbox) and !isHit)
            {
                isHit = true;
                SOUND->Stop("PL_DAMAGED");
                SOUND->Play("PL_DAMAGED");
                SOUND->SetVolume("PL_DAMAGED", 0.3f);
                Sd[i]->SB[j].Soldier_Bullet->Position = Sd[i]->GetPos() + Vector2(-30000.0f, 30000.0f);
                if (Armor > 0)
                {
                    Health -= Sd[i]->SB[j].Power * 0.5f;
                    Armor -= 1;
                }
                else
                {
                    Health -= Sd[i]->SB[j].Power;
                }
            }
        }
    }
    //storm
    for (int i = 0; i < 18; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (isCollision(HitBox, St[i]->SB[j].Hitbox) and !isHit)
            {
                isHit = true;
                SOUND->Stop("PL_DAMAGED");
                SOUND->Play("PL_DAMAGED");
                SOUND->SetVolume("PL_DAMAGED", 0.3f);
                St[i]->SB[j].Storm_Bullet->Position = St[i]->GetPos() + Vector2(-30000.0f, 30000.0f);
                if (Armor > 0)
                {
                    Health -= St[i]->SB[j].Power * 0.5f;
                    Armor -= 1;
                }
                else
                {
                    Health -= St[i]->SB[j].Power;
                }
            }
        }
    }
    //Bazooka
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (isCollision(HitBox, Bz[i]->SB[j].Hitbox) and !isHit)
            {
                isHit = true;
                SOUND->Stop("PL_DAMAGED");
                SOUND->Play("PL_DAMAGED");
                SOUND->SetVolume("PL_DAMAGED", 0.3f);
                Bz[i]->SB[j].Bazooka_Bullet->Position = Bz[i]->GetPos() + Vector2(-30000.0f, 30000.0f);
                if (Armor > 0)
                {
                    Health -= Bz[i]->SB[j].Power * 0.5f;
                    Armor -= 1;
                }
                else
                {
                    Health -= Bz[i]->SB[j].Power;
                }
            }
        }
    }
}

void Player::Render()
{
    Character::Render();
    switch (PlayerMoveState)
    {
    case PL_MOVE:
        Move->Render();
        break;
    case PL_STAND:
        break;
    }

    switch (PlayerState)
    {
    case PL_PISTOL:
        Pistol->Render();
        break;
    case PL_PISTOLFIRE:
        Pistol_Effect->Render();
        Pistol_Fire->Render();
        break;
    case PL_MG:
        MG->Render();
        break;
    case PL_MGFIRE:
        MG_Effect->Render();
        MG_Fire->Render();
        break;
    case PL_GL:
        GL->Render();
        break;
    case PL_GLFIRE:
        GL_Fire->Render();
        break;
    case PL_FT:
        FT->Render();
        break;
    case PL_FTFIRE:
        FT_Effect->Render();
        FT_Fire->Render();
        Fire_HitBox->Render();
        break;
    case PL_RIFLE:
        RIFLE->Render();
        break;
    case PL_RIFLEFIRE:
        RIFLE_Effect->Render();
        RIFLE_Fire->Render();
        break;
    case PL_DEAD:
        Dead->Render();
        break;
    case PL_RIDE:
        break;
    }

    //bullet
    for (int i = 0; i < 10; i++)
    {
        PB[i].Pistol_Bullet->Render();
        /*PB[i].Hitbox->Render();*/
    }
    for (int i = 0; i < 50; i++)
    {
        MB[i].MG_Bullet->Render();
        /*MB[i].Hitbox->Render();*/
    }
    for (int i = 0; i < 30; i++)
    {
        RB[i].RIFLE_Bullet->Render();
        /*RB[i].Hitbox->Render();*/
    }

    for (int i = 0; i < 3; i++)
    {
        GB[i].GL_Shot1->Render();
        GB[i].GL_Shot2->Render();
        /*GB[i].GL_HitBox->Render();
        GB[i].GL_HitBox2->Render();*/
    }

    /*HitBox->Render();
    Shot_Circle->Render();
    Hit_Circle->Render();*/
}

void Player::Turnback()
{
    Root->Position = PrevPos;
}

void Player::Input()
{
    MoveDir = Vector2(0.0f, 0.0f);

    if (INPUT->KeyPress('A'))
    {
        MoveDir.x = -1.0f;
    }
    else if (INPUT->KeyPress('D'))
    {
        MoveDir.x = 1.0f;
    }
    if (INPUT->KeyPress('W'))
    {
        MoveDir.y = 1.0f;
    }
    else if (INPUT->KeyPress('S'))
    {
        MoveDir.y = -1.0f;
    }
    MoveDir.Normalize();
    Root->Position += MoveDir * PlayerSpeed * DeltaTime;
}

void Player::StatePistol()
{
    if (!Game_Speed == 0)
    {
        Reloading_Time += DeltaTime;
        LookTarget2(g_WorldMouse, Pistol, 0.0f);
        if (Reloading_Time > 0.0f)
        {
            if (INPUT->KeyDown(VK_LBUTTON))
            {
                PlayerState = PL_PISTOLFIRE;
                Pistol_Fire->ChangeAnim(_ONCE, 0.04f / Game_Speed);
                Pistol_Effect->ChangeAnim(_ONCE, 0.03f / Game_Speed);

                //bullet fire
                for (int i = 0; i < 10; i++)
                {
                    if (!PB[i].Pistol_Bullet->isActive)
                    {
                        SOUND->Stop("PL_PSHOT");
                        SOUND->Play("PL_PSHOT");
                        SOUND->SetVolume("PL_PSHOT", 0.3f);
                        //격발
                        PB[i].Pistol_Bullet->isActive = true;
                        PB[i].Hitbox->isActive = true;

                        Shot_Circle->isActive = true;
                        Shot_Circle->Position = Root->Position;

                        PB[i].Pistol_Bullet->Position = Root->Position;
                        LookTarget(g_WorldMouse, PB[i].Pistol_Bullet, 0.0f);
                        PB[i].Dir = RadianToDir(PB[i].Pistol_Bullet->Rotation.z + 0.5f * PI);

                        

                        break;
                    }
                }
            }
        }
        if (INPUT->KeyDown('Q'))
        {
            PlayerState = PL_FT;
            Reloading_Time = 0.0f;
            Gun_Kind = 4;
            SOUND->Stop("PL_WEAPON_CHANGE");
            SOUND->Play("PL_WEAPON_CHANGE");
            SOUND->SetVolume("PL_WEAPON_CHANGE", 0.3f);
        }
        if (INPUT->KeyDown('E'))
        {
            PlayerState = PL_MG;
            Reloading_Time = 0.0f;
            Gun_Kind = 1;
            SOUND->Stop("PL_WEAPON_CHANGE");
            SOUND->Play("PL_WEAPON_CHANGE");
            SOUND->SetVolume("PL_WEAPON_CHANGE", 0.3f);
        }
    }
}

void Player::StatePistolFire()
{
    if (!Game_Speed == 0)
    {
        LookTarget2(g_WorldMouse, Pistol_Fire, 0.0f);
        LookTarget(g_WorldMouse, Pistol_Effect, 0.0f);
        Shooting_Time += DeltaTime;
        if (Shooting_Time > 0.2f / Game_Speed)
        {
            Shot_Circle->isActive = false;
            Shooting_Time = 0.0f;
            PlayerState = PL_PISTOL;
            Reloading_Time = -1.0f / Game_Speed;
        }
    }
}

void Player::StateMg()
{
    if (!Game_Speed == 0)
    {
        Reloading_Time += DeltaTime;
        LookTarget2(g_WorldMouse, MG, 0.0f);
        if (MG_Bullet_Num > 0)
        {
            if (Reloading_Time > 0.0f)
            {
                if (INPUT->KeyPress(VK_LBUTTON))
                {
                    PlayerState = PL_MGFIRE;
                    MG_Effect->ChangeAnim(_ONCE, 0.03f / Game_Speed);

                    //bullet fire
                    for (int i = 0; i < 50; i++)
                    {
                        if (!MB[i].MG_Bullet->isActive)
                        {
                            SOUND->Stop("PL_MGSHOT");
                            SOUND->Play("PL_MGSHOT");
                            SOUND->SetVolume("PL_MGSHOT", 0.3f);
                            MG_Bullet_Num -= 1;
                            //격발
                            MB[i].MG_Bullet->isActive = true;
                            MB[i].Hitbox->isActive = true;

                            Shot_Circle->isActive = true;
                            Shot_Circle->Position = Root->Position;

                            MB[i].MG_Bullet->Position = Root->Position;
                            LookTarget(g_WorldMouse, MB[i].MG_Bullet, 0.0f);
                            MB[i].Dir = RadianToDir(MB[i].MG_Bullet->Rotation.z + 0.5f * PI);
                            break;
                        }
                    }
                }
            }
        }
        if (INPUT->KeyDown('Q'))
        {
            PlayerState = PL_PISTOL;
            Reloading_Time = 0.0f;
            Gun_Kind = 0;
            SOUND->Stop("PL_WEAPON_CHANGE");
            SOUND->Play("PL_WEAPON_CHANGE");
            SOUND->SetVolume("PL_WEAPON_CHANGE", 0.3f);
        }
        if (INPUT->KeyDown('E'))
        {
            PlayerState = PL_RIFLE;
            Reloading_Time = 0.0f;
            Gun_Kind = 2;
            SOUND->Stop("PL_WEAPON_CHANGE");
            SOUND->Play("PL_WEAPON_CHANGE");
            SOUND->SetVolume("PL_WEAPON_CHANGE", 0.3f);
        }
    }
}

void Player::StateMgFire()
{
    if (!Game_Speed == 0)
    {
        LookTarget2(g_WorldMouse, MG_Fire, 0.0f);
        LookTarget(g_WorldMouse, MG_Effect, 0.0f);
        Shooting_Time += DeltaTime;
        if (Shooting_Time > 0.09f / Game_Speed)
        {
            Shot_Circle->isActive = false;
            Shooting_Time = 0.0f;
            PlayerState = PL_MG;
            Reloading_Time = -0.05f / Game_Speed;
        }
    }
}

void Player::StateRifle()
{
    if (!Game_Speed == 0)
    {
        Reloading_Time += DeltaTime;
        LookTarget2(g_WorldMouse, RIFLE, 0.0f);
        if (R_Bullet_Num > 0)
        {
            if (Reloading_Time > 0.0f)
            {
                if (INPUT->KeyDown(VK_LBUTTON))
                {
                    PlayerState = PL_RIFLEFIRE;
                    RIFLE_Effect->ChangeAnim(_ONCE, 0.05f / Game_Speed);
                    //bullet fire
                    for (int i = 0; i < 30; i++)
                    {
                        if (!RB[i].RIFLE_Bullet->isActive)
                        {
                            SOUND->Stop("PL_RSHOT");
                            SOUND->Play("PL_RSHOT");
                            SOUND->SetVolume("PL_RSHOT", 0.3f);
                            R_Bullet_Num -= 1;
                            //격발
                            RB[i].RIFLE_Bullet->isActive = true;
                            RB[i].Hitbox->isActive = true;

                            Shot_Circle->isActive = true;
                            Shot_Circle->Position = Root->Position;

                            RB[i].RIFLE_Bullet->Position = Root->Position;
                            LookTarget(g_WorldMouse, RB[i].RIFLE_Bullet, 0.0f);
                            RB[i].Dir = RadianToDir(RB[i].RIFLE_Bullet->Rotation.z + 0.5f * PI);
                            break;
                        }
                    }
                }
            }
        }
        if (INPUT->KeyDown('Q'))
        {
            PlayerState = PL_MG;
            Reloading_Time = 0.0f;
            Gun_Kind = 1;
            SOUND->Stop("PL_WEAPON_CHANGE");
            SOUND->Play("PL_WEAPON_CHANGE");
            SOUND->SetVolume("PL_WEAPON_CHANGE", 0.3f);
        }
        if (INPUT->KeyDown('E'))
        {
            PlayerState = PL_GL;
            Reloading_Time = 0.0f;
            Gun_Kind = 3;
            SOUND->Stop("PL_WEAPON_CHANGE");
            SOUND->Play("PL_WEAPON_CHANGE");
            SOUND->SetVolume("PL_WEAPON_CHANGE", 0.3f);
        }
    }
}

void Player::StateRifleFire()
{
    if (!Game_Speed == 0)
    {
        LookTarget2(g_WorldMouse, RIFLE_Fire, 0.0f);
        LookTarget(g_WorldMouse, RIFLE_Effect, 0.0f);
        Shooting_Time += DeltaTime;
        if (Shooting_Time > 0.15f / Game_Speed)
        {
            Shot_Circle->isActive = false;
            Shooting_Time = 0.0f;
            PlayerState = PL_RIFLE;
            Reloading_Time = -1.5f / Game_Speed;
        }
    }
}

void Player::StateGl()
{
    if (!Game_Speed == 0)
    {
        LookTarget2(g_WorldMouse, GL, 0.0f);
        Reloading_Time += DeltaTime;
        if (GL_Bullet_Num > 0)
        {
            if (Reloading_Time > 0.0f)
            {
                if (INPUT->KeyDown(VK_LBUTTON))
                {
                    PlayerState = PL_GLFIRE;
                    GL_Fire->ChangeAnim(_ONCE, 0.1f / Game_Speed);
                    //bullet fire
                    for (int i = 0; i < 3; i++)
                    {
                        if (!GB[i].GL_Shot1->isActive)
                        {
                            SOUND->Stop("PL_GTSHOT");
                            SOUND->Play("PL_GTSHOT");
                            SOUND->SetVolume("PL_GTSHOT", 0.3f);
                            SOUND->Stop("PL_GTSHOT2");
                            SOUND->Play("PL_GTSHOT2");
                            SOUND->SetVolume("PL_GTSHOT2", 0.3f);
                            GB[i].GL_Shot1->ChangeAnim(_ONCE, 0.5f / Game_Speed);
                            GL_Bullet_Num -= 1;
                            //격발
                            GB[i].GL_Shot1->isActive = true;
                            GB[i].GL_HitBox->isActive = true;

                            Shot_Circle->isActive = true;
                            Shot_Circle->Position = Root->Position;

                            GB[i].GL_Shot1->Position = Root->Position;
                            LookTarget(g_WorldMouse, GB[i].GL_Shot1, 0.0f);
                            GB[i].Dir = RadianToDir(GB[i].GL_Shot1->Rotation.z + 0.5f * PI);
                            break;
                        }
                    }
                }
            }
        }
        if (INPUT->KeyDown('Q'))
        {
            PlayerState = PL_RIFLE;
            Reloading_Time = 0.0f;
            Gun_Kind = 2;
            SOUND->Stop("PL_WEAPON_CHANGE");
            SOUND->Play("PL_WEAPON_CHANGE");
            SOUND->SetVolume("PL_WEAPON_CHANGE", 0.3f);
        }
        if (INPUT->KeyDown('E'))
        {
            PlayerState = PL_FT;
            Reloading_Time = 0.0f;
            Gun_Kind = 4;
            SOUND->Stop("PL_WEAPON_CHANGE");
            SOUND->Play("PL_WEAPON_CHANGE");
            SOUND->SetVolume("PL_WEAPON_CHANGE", 0.3f);
        }
    }
}

void Player::StateGlFire()
{
    if (!Game_Speed == 0)
    {
        LookTarget2(g_WorldMouse, GL_Fire, 0.0f);
        Shooting_Time += DeltaTime;
        if (Shooting_Time > 0.2f / Game_Speed)
        {
            Shot_Circle->isActive = false;
            Shooting_Time = 0.0f;
            PlayerState = PL_GL;
            Reloading_Time = -5.0f / Game_Speed;
        }
    }
}

void Player::StateFt()
{
    if (!Game_Speed == 0)
    {
        LookTarget2(g_WorldMouse, FT, 0.0f);
        if (FT_Bullet_Num > 0)
        {
            if (INPUT->KeyPress(VK_LBUTTON))
            {
                SOUND->Stop("PL_FTSHOT");
                SOUND->Play("PL_FTSHOT");
                SOUND->SetVolume("PL_FTSHOT", 0.3f);
                Shot_Circle->isActive = true;
                Shot_Circle->Position = Root->Position;
                FT_Bullet_Num -= 1;
                PlayerState = PL_FTFIRE;
                FT_Fire->ChangeAnim(_ONCE, 0.07f / Game_Speed);
                FT_Effect->ChangeAnim(_ONCE, 0.03f / Game_Speed);
            }
        }
        if (INPUT->KeyDown('Q'))
        {
            PlayerState = PL_GL;
            Gun_Kind = 3;
            SOUND->Stop("PL_WEAPON_CHANGE");
            SOUND->Play("PL_WEAPON_CHANGE");
            SOUND->SetVolume("PL_WEAPON_CHANGE", 0.3f);
        }
        if (INPUT->KeyDown('E'))
        {
            PlayerState = PL_PISTOL;
            Gun_Kind = 0;
            SOUND->Stop("PL_WEAPON_CHANGE");
            SOUND->Play("PL_WEAPON_CHANGE");
            SOUND->SetVolume("PL_WEAPON_CHANGE", 0.3f);
        }
    }
}

void Player::StateFtFire()
{
    if (!Game_Speed == 0)
    {
        Fire_HitBox->isActive = true;
        LookTarget2(g_WorldMouse, FT_Fire, 0.0f);
        LookTarget2(g_WorldMouse, FT_Effect, 0.0f);
        Shooting_Time += DeltaTime;
        if (Shooting_Time > 0.21f / Game_Speed)
        {
            Shot_Circle->isActive = false;
            Shooting_Time = 0.0f;
            PlayerState = PL_FT;
            Fire_HitBox->isActive = false;
        }
    }
}

void Player::StateDead()
{
    SOUND->Play("PL_DEATH");
    SOUND->SetVolume("PL_DEATH", 0.3f);
    Shooting_Time += DeltaTime;
    if (Shooting_Time > 1.0f / Game_Speed)
    {
        Shooting_Time = 0.0f;
        PlayerState = PL_PISTOL;
        PlayerMoveState = PL_STAND;
        SetPos(Vector2(9850.0f, 10100.0f));
        Health = 5;
        Money -= 500;
    }
}

void Player::StateRide()
{
    if (!Game_Speed == 0)
    {
        Shooting_Time += DeltaTime;
        SetPos(Vector2(-20000.0f, -20000.0f));
    }
}


void Player::PlayerStand()
{
    //stand->move
    if (!Game_Speed == 0 and PlayerState != PL_DEAD and PlayerState != PL_RIDE)
    {
        if (INPUT->KeyPress('A') or INPUT->KeyPress('W') or INPUT->KeyPress('S') or INPUT->KeyPress('D'))
        {
            PlayerMoveState = PL_MOVE;
            Move->ChangeAnim(_LOOP, 0.1f / Game_Speed);
        }
    }
}

void Player::PlayerMove()
{
    //move->stand
    if (!Game_Speed == 0)
    {
        LookTarget(g_WorldMouse, Move,0.0f);
        if (!INPUT->KeyPress('A') and !INPUT->KeyPress('W') and !INPUT->KeyPress('S') and !INPUT->KeyPress('D'))
        {
            PlayerMoveState = PL_STAND;
        }
    }
    if (Game_Speed == 0)
    {
        PlayerMoveState = PL_STAND;
    }
    Input();
}