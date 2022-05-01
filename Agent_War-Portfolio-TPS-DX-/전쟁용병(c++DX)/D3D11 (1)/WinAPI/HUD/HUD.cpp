#include "stdafx.h"
#include "HUD.h"

HUD::HUD()
{
    Gun_Kind = 0;

    Bar = new ObImage(L"Image/TDS/UI/HUD/HP ARMOR AMMO HUD.png");
    Bar->Scale = Vector2(300.0f, 150.0f);
    Bar->Pivot = OFFSET_LB;

    Hp = new ObImage(L"Image/TDS/UI/HUD/HP Icon.png");
    Hp->Scale = Vector2(30.0f, 30.0f);
    Hp->Pivot = OFFSET_LB;

    Armor = new ObImage(L"Image/TDS/UI/HUD/Armor.png");
    Armor->Scale = Vector2(30.0f, 30.0f);
    Armor->Pivot = OFFSET_LB;

    Pistol = new ObImage(L"Image/TDS/UI/HUD/Weapon/Pistol HUD.png");
    Pistol->Scale = Vector2(139.2f, 68.8f);
    Pistol->Pivot = OFFSET_LB;

    Mg = new ObImage(L"Image/TDS/UI/HUD/Weapon/MG HUD.png");
    Mg->Scale = Vector2(139.2f, 68.8f);
    Mg->Pivot = OFFSET_LB;

    Rifle = new ObImage(L"Image/TDS/UI/HUD/Weapon/SMG HUD.png");
    Rifle->Scale = Vector2(139.2f, 68.8f);
    Rifle->Pivot = OFFSET_LB;

    Gl = new ObImage(L"Image/TDS/UI/HUD/Weapon/RPG HUD.png");
    Gl->Scale = Vector2(139.2f, 68.8f);
    Gl->Pivot = OFFSET_LB;

    Ft = new ObImage(L"Image/TDS/UI/HUD/Weapon/Flamethrower HUD.png");
    Ft->Scale = Vector2(139.2f, 68.8f);
    Ft->Pivot = OFFSET_LB;

    Bullet = new ObImage(L"Image/TDS/UI/HUD/Ammo Icon.png");
    Bullet->Scale = Vector2(20.0f, 20.0f);
    Bullet->Pivot = OFFSET_LB;

    Menu = new ObImage(L"Image/TDS/UI/HUD/BTN MENU HUD.png");
    Menu->Scale = Vector2(85.0f, 40.0f);
    Menu->Pivot = OFFSET_RT;

    Money = new ObImage(L"Image/TDS/UI/HUD/Money Panel HUD.png");
    Money->Scale = Vector2(100.0f, 50.0f);
    Money->Pivot = OFFSET_LB;

    Play = new ObImage(L"Image/TDS/UI/HUD/Icon Speed 02.png");
    Play->Scale = Vector2(50.0f, 50.0f);
    Play->Pivot = OFFSET_LB;

    Play2 = new ObImage(L"Image/TDS/UI/HUD/Iocn_Speed_01.png");
    Play2->Scale = Vector2(50.0f, 50.0f);
    Play2->Pivot = OFFSET_LB;

    Stop = new ObImage(L"Image/TDS/UI/HUD/Icon_Empty.png");
    Stop->Scale = Vector2(50.0f, 50.0f);
    Stop->Pivot = OFFSET_LB;

    Play_Box = new ObRect();
    Play_Box->isFill = false;
    Play_Box->Scale = Vector2(20.0f, 20.0f);

    Play2_Box = new ObRect();
    Play2_Box->isFill = false;
    Play2_Box->Scale = Vector2(20.0f, 20.0f);

    Stop_Box = new ObRect();
    Stop_Box->isFill = false;
    Stop_Box->Scale = Vector2(20.0f, 20.0f);

    Hp_Bar = new ObRect();
    Hp_Bar->color = Color(1.0f,0.0f,0.0f, 1.0f);
    Hp_Bar->Scale = Vector2(70.0f, 20.0f);
    Hp_Bar->Pivot = OFFSET_LB;

    Armor_Bar = new ObRect();
    Armor_Bar->color = Color(1.0f, 1.0f, 1.0f, 0.5f);
    Armor_Bar->Scale = Vector2(70.0f, 20.0f);
    Armor_Bar->Pivot = OFFSET_LB;
}

HUD::~HUD()
{
    delete Bar;
    delete Hp;
    delete Armor;
    delete Pistol;
    delete Mg;
    delete Rifle;
    delete Gl;
    delete Ft;
    delete Bullet;
    delete Menu;
    delete Money;
    delete Play;
    delete Play2;
    delete Stop;
    delete Play_Box;
    delete Play2_Box;
    delete Stop_Box;
    delete Hp_Bar;
    delete Armor_Bar;
}

void HUD::Init()
{

}

void HUD::Update()
{
    //IMGUI
    //ImGui::SliderFloat("POS_X", &Armor_Bar->Position.x, 0.0f, 300.0f);
    //ImGui::SliderFloat("POS_Y", &Armor_Bar->Position.y, -100.0f, 300.0f);
    //ImGui::SliderFloat("SCALE_X", &Armor_Bar->Scale.x, 0.0f, 200.0f);
    //ImGui::SliderFloat("SCALE_Y", &Armor_Bar->Scale.y, 0.0f, 100.0f);

    
}

void HUD::Render()
{
    Bar->Position = MAINCAM->Pos + Vector2(0.0f, 0.0f);
    Hp->Position = MAINCAM->Pos + Vector2(185.0f, 21.0f);
    Armor->Position = MAINCAM->Pos + Vector2(184.0f, 70.0f);
    Pistol->Position = MAINCAM->Pos + Vector2(14.5f, 25.6f);
    Mg->Position = MAINCAM->Pos + Vector2(14.5f, 25.6f);
    Rifle->Position = MAINCAM->Pos + Vector2(14.5f, 25.6f);
    Gl->Position = MAINCAM->Pos + Vector2(14.5f, 25.6f);
    Ft->Position = MAINCAM->Pos + Vector2(14.5f, 25.6f);
    Bullet->Position = MAINCAM->Pos + Vector2(30.0f, 119.0f);
    Menu->Position = MAINCAM->Pos + Vector2(WINSIZEX, WINSIZEY);
    Money->Position = MAINCAM->Pos + Vector2(300.0f, 0.0f);
    Play->Position = MAINCAM->Pos + Vector2(800.0f + 350.0f, 0.0f);
    Play2->Position = MAINCAM->Pos + Vector2(850.0f + 350.0f, 0.0f);
    Stop->Position = MAINCAM->Pos + Vector2(750.0f + 350.0f, 0.0f);
    Play_Box->Position = MAINCAM->Pos + Vector2(825.0f + 350.0f, 25.0f);
    Play2_Box->Position = MAINCAM->Pos + Vector2(875.0f + 350.0f, 25.0f);
    Stop_Box->Position = MAINCAM->Pos + Vector2(775.0f + 350.0f, 25.0f);
    Hp_Bar->Position = MAINCAM->Pos + Vector2(218.0f, 25.0f);
    Armor_Bar->Position = MAINCAM->Pos + Vector2(218.0f, 73.0f);
    Bar->Render();
    Hp->Render();
    Armor->Render();
    switch (Gun_Kind)
    {
    case 0:
        Pistol->Render();
        break;
    case 1:
        Mg->Render();
        break;
    case 2:
        Rifle->Render();
        break;
    case 3:
        Gl->Render();
        break;
    case 4:
        Ft->Render();
        break;
    }
    Bullet->Render();
    /*Menu->Render();*/
    Money->Render();
    Play->Render();
    Play2->Render();
    Stop->Render();

    /*Play_Box->Render();
    Play2_Box->Render();
    Stop_Box->Render();*/
    Hp_Bar->Render();
    Armor_Bar->Render();
}
