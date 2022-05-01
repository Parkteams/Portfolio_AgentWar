#include "stdafx.h"
#include "Character/Character.h"
#include "Character/Player.h"
#include "Weapon_Shop.h"

Weapon_Shop::Weapon_Shop()
{
    HUD = new ObImage(L"Image/TDS/UI/Upgrade/Upgrade Preset.png");
    HUD->Scale = Vector2(616.0f, 486.0f);
    HUD->Pivot = OFFSET_LB;

    HitBox_P = new ObRect();
    HitBox_P->Scale = Vector2(20.0f, 20.0f);
    HitBox_P->Pivot = OFFSET_LB;
    HitBox_P->isFill = false;

    HitBox_R = new ObRect();
    HitBox_R->Scale = Vector2(20.0f, 20.0f);
    HitBox_R->Pivot = OFFSET_LB;
    HitBox_R->isFill = false;

    HitBox_MG = new ObRect();
    HitBox_MG->Scale = Vector2(20.0f, 20.0f);
    HitBox_MG->Pivot = OFFSET_LB;
    HitBox_MG->isFill = false;

    HitBox_GT = new ObRect();
    HitBox_GT->Scale = Vector2(20.0f, 20.0f);
    HitBox_GT->Pivot = OFFSET_LB;
    HitBox_GT->isFill = false;

    HitBox_FT = new ObRect();
    HitBox_FT->Scale = Vector2(20.0f, 20.0f);
    HitBox_FT->Pivot = OFFSET_LB;
    HitBox_FT->isFill = false;

    HitBox_R_B = new ObRect();
    HitBox_R_B->Scale = Vector2(15.0f, 15.0f);
    HitBox_R_B->Pivot = OFFSET_LB;
    HitBox_R_B->isFill = false;

    HitBox_MG_B = new ObRect();
    HitBox_MG_B->Scale = Vector2(15.0f, 15.0f);
    HitBox_MG_B->Pivot = OFFSET_LB;
    HitBox_MG_B->isFill = false;

    HitBox_GT_B = new ObRect();
    HitBox_GT_B->Scale = Vector2(15.0f, 15.0f);
    HitBox_GT_B->Pivot = OFFSET_LB;
    HitBox_GT_B->isFill = false;

    HitBox_FT_B = new ObRect();
    HitBox_FT_B->Scale = Vector2(15.0f, 15.0f);
    HitBox_FT_B->Pivot = OFFSET_LB;
    HitBox_FT_B->isFill = false;

    HitBox_HEALTH = new ObRect();
    HitBox_HEALTH->Scale = Vector2(20.0f, 20.0f);
    HitBox_HEALTH->Pivot = OFFSET_LB;
    HitBox_HEALTH->isFill = false;

    HitBox_ARMOR = new ObRect();
    HitBox_ARMOR->Scale = Vector2(20.0f, 20.0f);
    HitBox_ARMOR->Pivot = OFFSET_LB;
    HitBox_ARMOR->isFill = false;

    HitBox_OK = new ObRect();
    HitBox_OK->Scale = Vector2(100.0f, 60.0f);
    HitBox_OK->Pivot = OFFSET_LB;
    HitBox_OK->isFill = false;

    //Mouse
    Click_Num = 0;

    //Gun
    Upgrade_P = 1;
    Upgrade_R = 1;
    Upgrade_MG = 1;
    Upgrade_GT = 1;
    Upgrade_FT = 1;

    //COIN
    SOUND->AddSound("Sound/NPC/COIN.wav", "COIN", false);
}

Weapon_Shop::~Weapon_Shop()
{
    delete HUD;
    delete HitBox_P;
    delete HitBox_R;
    delete HitBox_MG;
    delete HitBox_GT;
    delete HitBox_FT;
    delete HitBox_R_B;
    delete HitBox_MG_B;
    delete HitBox_GT_B;
    delete HitBox_FT_B;
    delete HitBox_HEALTH;
    delete HitBox_ARMOR;
    delete HitBox_OK;
}

void Weapon_Shop::Init()
{
}

void Weapon_Shop::Update()
{
    ////IMGUI
    //ImGui::SliderFloat("POS_X", &a, 0.0f, 800.0f);
    //ImGui::SliderFloat("POS_Y", &b, 0.0f, 800.0f);

    HUD->Position = MAINCAM->Pos + Vector2(50.0f, 200.0f);
    HitBox_P->Position = MAINCAM->Pos + Vector2(185.0f, 500.0f);
    HitBox_R->Position = MAINCAM->Pos + Vector2(386.0f, 500.0f);
    HitBox_MG->Position = MAINCAM->Pos + Vector2(591.0f, 500.0f);
    HitBox_GT->Position = MAINCAM->Pos + Vector2(185.0f, 370.0f);
    HitBox_FT ->Position = MAINCAM->Pos + Vector2(386.0f, 370.0f);
    HitBox_MG_B ->Position = MAINCAM->Pos + Vector2(617.0f, 442.0f);
    HitBox_R_B ->Position = MAINCAM->Pos + Vector2(617.0f, 422.0f);
    HitBox_GT_B ->Position = MAINCAM->Pos + Vector2(617.0f, 395.0f);
    HitBox_FT_B ->Position = MAINCAM->Pos + Vector2(617.0f, 375.0f);
    HitBox_HEALTH ->Position = MAINCAM->Pos + Vector2(185.0f, 250.0f);
    HitBox_ARMOR ->Position = MAINCAM->Pos + Vector2(386.0f, 250.0f);
    HitBox_OK->Position = MAINCAM->Pos + Vector2(513.0f, 253.0f);

    if (Upgrade_P < 3 and pl->Money >= 300)
    {
        if (isCollision(HitBox_P, g_WorldMouse))
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                SOUND->Stop("COIN");
                SOUND->Play("COIN");
                SOUND->SetVolume("COIN", 0.8f);
                Click_Num = 0;
                pl->Money -= 300;
                Upgrade_P += 1;
                for (int i = 0; i < 10; i++)
                {
                    pl->PB[i].Power += 1;
                    pl->PB[i].Pistol_Bullet->color.y += 0.2f;
                }

            }
        }
    }
    if (Upgrade_R < 3 and pl->Money >= 500)
    {
        if (isCollision(HitBox_R, g_WorldMouse))
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                SOUND->Stop("COIN");
                SOUND->Play("COIN");
                SOUND->SetVolume("COIN", 0.8f);
                Click_Num = 0;
                pl->Money -= 500;
                Upgrade_R += 1;
                for (int i = 0; i < 30; i++)
                {
                    pl->RB[i].Power += 1;
                    pl->RB[i].RIFLE_Bullet->color.x += 0.2f;
                }

            }
        }
    }
    if (Upgrade_MG < 3 and pl->Money >= 500)
    {
        if (isCollision(HitBox_MG, g_WorldMouse))
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                SOUND->Stop("COIN");
                SOUND->Play("COIN");
                SOUND->SetVolume("COIN", 0.8f);
                Click_Num = 0;
                pl->Money -= 500;
                Upgrade_MG += 1;
                for (int i = 0; i < 50; i++)
                {
                    pl->MB[i].Power += 1;
                    pl->MB[i].MG_Bullet->color.z += 0.2f;
                }

            }
        }
    }
    if (Upgrade_GT < 3 and pl->Money >= 800)
    {
        if (isCollision(HitBox_GT, g_WorldMouse))
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                SOUND->Stop("COIN");
                SOUND->Play("COIN");
                SOUND->SetVolume("COIN", 0.8f);
                Click_Num = 0;
                pl->Money -= 800;
                Upgrade_GT += 1;
                for (int i = 0; i < 3; i++)
                {
                    pl->GB[i].Power += 1;
                    pl->GB[i].GL_Shot1->color.z += 0.2f;
                    pl->GB[i].GL_Shot2->color.z += 0.2f;
                }

            }
        }
    }
    if (Upgrade_FT < 3 and pl->Money >= 800)
    {
        if (isCollision(HitBox_FT, g_WorldMouse))
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                SOUND->Stop("COIN");
                SOUND->Play("COIN");
                SOUND->SetVolume("COIN", 0.8f);
                Click_Num = 0;
                pl->Money -= 800;
                Upgrade_FT += 1;
                pl->FT_Effect->color.x += 0.2f;
                pl->FT_Effect->Scale.y += 30.0f;
                pl->Fire_HitBox->Scale.y += 30.0f;

            }
        }
    }
    if (pl->R_Bullet_Num < 300 and pl->Money >= 100)
    {
        if (isCollision(HitBox_R_B, g_WorldMouse))
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                SOUND->Stop("COIN");
                SOUND->Play("COIN");
                SOUND->SetVolume("COIN", 0.8f);
                Click_Num = 0;
                pl->Money -= 100;
                pl->R_Bullet_Num += 30;
            }
        }
    }
    if (pl->MG_Bullet_Num < 500 and pl->Money >= 100)
    {
        if (isCollision(HitBox_MG_B, g_WorldMouse))
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                SOUND->Stop("COIN");
                SOUND->Play("COIN");
                SOUND->SetVolume("COIN", 0.8f);
                Click_Num = 0;
                pl->Money -= 100;
                pl->MG_Bullet_Num += 50;
            }
        }
    }
    if (pl->GL_Bullet_Num < 30 and pl->Money >= 100)
    {
        if (isCollision(HitBox_GT_B, g_WorldMouse))
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                SOUND->Stop("COIN");
                SOUND->Play("COIN");
                SOUND->SetVolume("COIN", 0.8f);
                Click_Num = 0;
                pl->Money -= 100;
                pl->GL_Bullet_Num += 3;
            }
        }
    }
    if (pl->FT_Bullet_Num < 500 and pl->Money >= 100)
    {
        if (isCollision(HitBox_FT_B, g_WorldMouse))
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                SOUND->Stop("COIN");
                SOUND->Play("COIN");
                SOUND->SetVolume("COIN", 0.8f);
                Click_Num = 0;
                pl->Money -= 100;
                pl->FT_Bullet_Num += 50;
            }
        }
    }
    if (pl->Money >= 300)
    {
        if (isCollision(HitBox_HEALTH, g_WorldMouse))
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                SOUND->Stop("COIN");
                SOUND->Play("COIN");
                SOUND->SetVolume("COIN", 0.8f);
                Click_Num = 0;
                pl->Money -= 300;
                pl->Health += 5;
            }
        }
    }
    if (pl->Money >= 300)
    {
        if (isCollision(HitBox_ARMOR, g_WorldMouse))
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                SOUND->Stop("COIN");
                SOUND->Play("COIN");
                SOUND->SetVolume("COIN", 0.8f);
                Click_Num = 0;
                pl->Money -= 300;
                pl->Armor += 5;
            }
        }
    }
    
}
void Weapon_Shop::Render()
{
    HUD->Render();
    /*HitBox_P->Render();
    HitBox_R->Render();
    HitBox_MG->Render();
    HitBox_GT->Render();
    HitBox_FT->Render();
    HitBox_R_B->Render();
    HitBox_MG_B->Render();
    HitBox_GT_B->Render();
    HitBox_FT_B->Render();
    HitBox_HEALTH->Render();
    HitBox_ARMOR->Render();
    HitBox_OK->Render();*/
}
