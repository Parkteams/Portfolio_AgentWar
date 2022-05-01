#include "stdafx.h"
#include "Character/Character.h"
#include "Character/Player.h"
#include "Character/Sniper.h"
#include "Character/Soldier.h"
#include "Character/Storm.h"
#include "Character/Bazooka.h"
#include "Character/ACS.h"
#include "Character/NPC1.h"
#include "Character/NPC2.h"
#include "TileMap/Tile.h"
#include "TileMap/TileMap.h"
#include "HUD/HUD.h"
#include "HUD/Weapon_Shop.h"
#include "Item/Item.h"
#include "Item/HealPack.h"
#include "Item/Ammunition.h"
#include "Item/Money.h"
#include "Item/Armor.h"
#include "Item/Quest_Item.h"
#include "Obstacle/Obstacle.h"
#include "Obstacle/House1.h"
#include "Obstacle/House2.h"
#include "Obstacle/Tree1.h"
#include "Obstacle/Tree2.h"
#include "Obstacle/Rock.h"
#include "Obstacle/Bush.h"
#include "Obstacle/WatchTower.h"
#include "Scene1.h"

Scene1::Scene1()
{
    //tile
    tm = new TileMap();
    tm->Images.push_back(TileImg(L"Image/TDS/Tile/Tiles.png", Int2(1, 5)));

    //player
    pl = new Player();
  
    //ride
    Acs = new ACS();

    Hud = new HUD();
    Hud2 = new Weapon_Shop();

    Huds = new ObImage(L"Image/TDS/UI/Save&Load/Checkbox 01.png");
    Huds->Scale = Vector2(1280.0f, 186.0f);
    Huds->Pivot = OFFSET_LB;

    CheckBox = new ObRect();
    CheckBox->Scale = Vector2(80.0f, 80.0f);
    CheckBox->Pivot = OFFSET_LB;
    CheckBox->isFill = false;

    //enemy
    for (int i = 0; i < SNIPERCOUNT; i++)
    {
        Sp[i] = new Sniper();
        Sp[i]->Setpl(pl);
        Sp[i]->SetAcs(Acs);
    }
    for (int i = 0; i < SOLDIERCOUNT; i++)
    {
        Sd[i] = new Soldier();
        Sd[i]->Setpl(pl);
        Sd[i]->Settm(tm);
        Sd[i]->SetAcs(Acs);
    }
    for (int i = 0; i < STORMCOUNT; i++)
    {
        St[i] = new Storm();
        St[i]->Setpl(pl);
        St[i]->Settm(tm);
        St[i]->SetAcs(Acs);
    }
    for (int i = 0; i < BAZOOKACOUNT; i++)
    {
        Bz[i] = new Bazooka();
        Bz[i]->Setpl(pl);
        Bz[i]->SetAcs(Acs);
    }

    //NPC
    for (int i = 0; i < NPC1COUNT; i++)
    {
        Npc1[i] = new NPC1();
        Npc1[i]->Setpl(pl);
    }
    for (int i = 0; i < NPC2COUNT; i++)
    {
        Npc2[i] = new NPC2();
        Npc2[i]->Setpl(pl);
    }

    //hud
    Hud2->Setpl(pl);

    //ride
    Acs->Setpl(pl);
    Acs->SetSp(Sp);
    Acs->SetSd(Sd);
    Acs->SetSt(St);
    Acs->SetBz(Bz);

    pl->SetSp(Sp);
    pl->SetSd(Sd);
    pl->SetSt(St);
    pl->SetBz(Bz);

    //obstacle
    for (int i = 0; i < HOUSE1COUNT; i++)
    {
        House_1[i] = new House1();
    }


    //item
    for (int i = 0; i < HEALPACKNUM; i++)
    {
        Heal_Pack[i] = new HealPack();
    }
    for (int i = 0; i < AMMUNITIONNUM; i++)
    {
        Ammu_nition[i] = new Ammunition();
    }
    for (int i = 0; i < MONEYNUM; i++)
    {
        Mo_ney[i] = new Money();
    }
    for (int i = 0; i < ARMORNUM; i++)
    {
        Ar_mor[i] = new Armor();
    }
    for (int i = 0; i < QUEST_ITEMNUM; i++)
    {
        QuestItem[i] = new Quest_Item();
    }

    //obstacle
    for (int i = 0; i < HOUSE1COUNT; i++)
    {
        House_1[i] = new House1();
    }
    for (int i = 0; i < HOUSE2COUNT; i++)
    {
        House_2[i] = new House2();
    }
    for (int i = 0; i < TREE1COUNT; i++)
    {
        Tree_1[i] = new Tree1();
    }
    for (int i = 0; i < TREE2COUNT; i++)
    {
        Tree_2[i] = new Tree2();
    }
    for (int i = 0; i < ROCKCOUNT; i++)
    {
        Ro_ck[i] = new Rock();
    }
    for (int i = 0; i < BUSHCOUNT; i++)
    {
        Bu_sh[i] = new Bush();
    }
    for (int i = 0; i < WATCHTOWERCOUNT; i++)
    {
        Watch_Tower[i] = new WatchTower();
    }
    SPRITETEXT->AddFont(L"Font/hand.spritefont", "HAND");

    //SOUND
    SOUND->AddSound("Sound/PLAYER/GT_EXPLODE.wav", "GT_EXPLODE", false);

    //BGM
    SOUND->AddSound("Sound/BGM/1.mp3", "BGM1", false);
    SOUND->AddSound("Sound/BGM/2.mp3", "BGM2", false);
    SOUND->AddSound("Sound/BGM/3.mp3", "BGM3", true);

    //Alert
    SOUND->AddSound("Sound/ENEMY/ALERT.wav", "ALERT", false);
}
   

Scene1::~Scene1()
{
    delete pl;
    //delete enemy;
    for (int i = 0; i < SNIPERCOUNT; i++)
    {
        delete Sp[i];
    }
    for (int i = 0; i < SOLDIERCOUNT; i++)
    {
        delete Sd[i];
    }
    for (int i = 0; i < STORMCOUNT; i++)
    {
        delete St[i];
    }
    for (int i = 0; i < BAZOOKACOUNT; i++)
    {
        delete Bz[i];
    }
    for (int i = 0; i < NPC1COUNT; i++)
    {
        delete Npc1[i];
    }
    for (int i = 0; i < NPC2COUNT; i++)
    {
        delete Npc2[i];
    }
    delete Acs;

    delete tm;
    delete Hud;
    delete Hud2;
    delete Huds;
    delete CheckBox;
    for (int i = 0; i < HEALPACKNUM; i++)
    {
        delete Heal_Pack[i];
    }
    for (int i = 0; i < AMMUNITIONNUM; i++)
    {
        delete Ammu_nition[i];
    }
    for (int i = 0; i < MONEYNUM; i++)
    {
        delete Mo_ney[i];
    }
    for (int i = 0; i < ARMORNUM; i++)
    {
        delete Ar_mor[i];
    }
    for (int i = 0; i < QUEST_ITEMNUM; i++)
    {
        delete QuestItem[i];
    }
    for (int i = 0; i < HOUSE1COUNT; i++)
    {
        delete House_1[i];
    }
    for (int i = 0; i < HOUSE2COUNT; i++)
    {
        delete House_2[i];
    }
    for (int i = 0; i < TREE1COUNT; i++)
    {
        delete Tree_1[i];
    }
    for (int i = 0; i < TREE2COUNT; i++)
    {
        delete Tree_2[i];
    }
    for (int i = 0; i < ROCKCOUNT; i++)
    {
        delete Ro_ck[i];
    }
    for (int i = 0; i < BUSHCOUNT; i++)
    {
        delete Bu_sh[i];
    }
    for (int i = 0; i < WATCHTOWERCOUNT; i++)
    {
        delete Watch_Tower[i];
    }
}

void Scene1::Init()
{
    edit = false;
    Player_Update = true;

    //tile
    tm->Init();
    tm->Load("TileMap1.txt");
    tm->isDebug = false;

    Camera_Speed = 300.0f;

    //item
    Heal_Pack[0]->SetPos(Vector2(tm->IdxToVector(Int2(105, 176))));
    Heal_Pack[1]->SetPos(Vector2(tm->IdxToVector(Int2(116, 121))));
    Heal_Pack[2]->SetPos(Vector2(tm->IdxToVector(Int2(380, 17))));

    Ammu_nition[0]->SetPos(Vector2(tm->IdxToVector(Int2(105, 177))));
    Ammu_nition[1]->SetPos(Vector2(tm->IdxToVector(Int2(128, 114))));
    Ammu_nition[2]->SetPos(Vector2(tm->IdxToVector(Int2(128, 115))));
    Ammu_nition[3]->SetPos(Vector2(tm->IdxToVector(Int2(392, 24))));
    Ammu_nition[4]->SetPos(Vector2(tm->IdxToVector(Int2(372, 8))));

    Mo_ney[0]->SetPos(Vector2(tm->IdxToVector(Int2(105, 180))));
    Mo_ney[1]->SetPos(Vector2(tm->IdxToVector(Int2(128, 120))));
    Mo_ney[2]->SetPos(Vector2(tm->IdxToVector(Int2(128, 119))));
    Mo_ney[3]->SetPos(Vector2(tm->IdxToVector(Int2(128, 118))));
    Mo_ney[4]->SetPos(Vector2(tm->IdxToVector(Int2(373, 21))));
    Mo_ney[5]->SetPos(Vector2(tm->IdxToVector(Int2(374, 21))));
    Mo_ney[6]->SetPos(Vector2(tm->IdxToVector(Int2(385, 9))));
    Mo_ney[7]->SetPos(Vector2(tm->IdxToVector(Int2(386, 9))));

    Ar_mor[0]->SetPos(Vector2(tm->IdxToVector(Int2(105, 175))));
    Ar_mor[1]->SetPos(Vector2(tm->IdxToVector(Int2(394, 17))));

    QuestItem[0]->SetPos(Vector2(tm->IdxToVector(Int2(110, 183))));
    QuestItem[1]->SetPos(Vector2(tm->IdxToVector(Int2(123, 112))));
    QuestItem[2]->SetPos(Vector2(tm->IdxToVector(Int2(397, 6))));

    //obstacle
    House_1[0]->SetPos(Vector2(tm->IdxToVector(Int2(227, 192))));
    House_1[1]->SetPos(Vector2(tm->IdxToVector(Int2(195, 184))));
    House_1[2]->SetPos(Vector2(tm->IdxToVector(Int2(203, 187))));
    House_1[3]->SetPos(Vector2(tm->IdxToVector(Int2(207, 187))));
    House_1[4]->SetPos(Vector2(tm->IdxToVector(Int2(207, 196))));
    House_1[5]->SetPos(Vector2(tm->IdxToVector(Int2(108, 185))));
    House_1[6]->SetPos(Vector2(tm->IdxToVector(Int2(102, 184))));
    House_1[7]->SetPos(Vector2(tm->IdxToVector(Int2(113, 115))));
    House_1[8]->SetPos(Vector2(tm->IdxToVector(Int2(378, 17))));
    House_1[9]->SetPos(Vector2(tm->IdxToVector(Int2(378, 7))));
    House_1[10]->SetPos(Vector2(tm->IdxToVector(Int2(395, 19))));

    House_2[0]->SetPos(Vector2(tm->IdxToVector(Int2(215, 196))));
    House_2[1]->SetPos(Vector2(tm->IdxToVector(Int2(215, 192))));
    House_2[2]->SetPos(Vector2(tm->IdxToVector(Int2(197, 192))));
    House_2[3]->SetPos(Vector2(tm->IdxToVector(Int2(197, 197))));
    House_2[4]->SetPos(Vector2(tm->IdxToVector(Int2(197, 204))));
    House_2[5]->SetPos(Vector2(tm->IdxToVector(Int2(223, 181))));
    House_2[6]->SetPos(Vector2(tm->IdxToVector(Int2(223, 187))));
    House_2[7]->SetPos(Vector2(tm->IdxToVector(Int2(215, 181))));
    House_2[8]->SetPos(Vector2(tm->IdxToVector(Int2(215, 187))));
    House_2[9]->SetPos(Vector2(tm->IdxToVector(Int2(208, 204))));
    House_2[10]->SetPos(Vector2(tm->IdxToVector(Int2(101, 176))));
    House_2[11]->SetPos(Vector2(tm->IdxToVector(Int2(123, 122))));
    House_2[12]->SetPos(Vector2(tm->IdxToVector(Int2(123, 118))));
    House_2[13]->SetPos(Vector2(tm->IdxToVector(Int2(123, 114))));
    House_2[14]->SetPos(Vector2(tm->IdxToVector(Int2(385, 19))));
    House_2[15]->SetPos(Vector2(tm->IdxToVector(Int2(385, 15))));
    House_2[16]->SetPos(Vector2(tm->IdxToVector(Int2(385, 11))));
    House_2[17]->SetPos(Vector2(tm->IdxToVector(Int2(384, 5))));
    House_2[18]->SetPos(Vector2(tm->IdxToVector(Int2(392, 5))));
    House_2[19]->SetPos(Vector2(tm->IdxToVector(Int2(393, 10))));
    House_2[20]->SetPos(Vector2(tm->IdxToVector(Int2(393, 15))));

    Tree_1[0]->SetPos(Vector2(tm->IdxToVector(Int2(373, 13))));
    Tree_1[1]->SetPos(Vector2(tm->IdxToVector(Int2(388, 25))));

    Tree_2[0]->SetPos(Vector2(tm->IdxToVector(Int2(207, 192))));
    Tree_2[1]->SetPos(Vector2(tm->IdxToVector(Int2(375, 18))));

    Ro_ck[0]->SetPos(Vector2(tm->IdxToVector(Int2(209, 191))));
    Ro_ck[1]->SetPos(Vector2(tm->IdxToVector(Int2(225, 200))));
    Ro_ck[2]->SetPos(Vector2(tm->IdxToVector(Int2(110, 182))));
    Ro_ck[3]->SetPos(Vector2(tm->IdxToVector(Int2(108, 128))));
    Ro_ck[4]->SetPos(Vector2(tm->IdxToVector(Int2(109, 126))));
    Ro_ck[5]->SetPos(Vector2(tm->IdxToVector(Int2(111, 125))));
    Ro_ck[6]->SetPos(Vector2(tm->IdxToVector(Int2(379, 13))));
    Ro_ck[7]->SetPos(Vector2(tm->IdxToVector(Int2(373, 20))));
    Ro_ck[8]->SetPos(Vector2(tm->IdxToVector(Int2(391, 19))));
    Ro_ck[9]->SetPos(Vector2(tm->IdxToVector(Int2(396, 5))));
    Ro_ck[10]->SetPos(Vector2(tm->IdxToVector(Int2(397, 5))));

    Bu_sh[0]->SetPos(Vector2(tm->IdxToVector(Int2(218, 203))));
    Bu_sh[1]->SetPos(Vector2(tm->IdxToVector(Int2(219, 201))));
    Bu_sh[2]->SetPos(Vector2(tm->IdxToVector(Int2(223, 203))));
    Bu_sh[3]->SetPos(Vector2(tm->IdxToVector(Int2(107, 178))));
    Bu_sh[4]->SetPos(Vector2(tm->IdxToVector(Int2(108, 178))));
    Bu_sh[5]->SetPos(Vector2(tm->IdxToVector(Int2(109, 178))));
    Bu_sh[6]->SetPos(Vector2(tm->IdxToVector(Int2(110, 178))));
    Bu_sh[7]->SetPos(Vector2(tm->IdxToVector(Int2(111, 178))));
    Bu_sh[8]->SetPos(Vector2(tm->IdxToVector(Int2(112, 178))));
    Bu_sh[9]->SetPos(Vector2(tm->IdxToVector(Int2(113, 178))));
    Bu_sh[10]->SetPos(Vector2(tm->IdxToVector(Int2(114, 178))));
    Bu_sh[11]->SetPos(Vector2(tm->IdxToVector(Int2(115, 178))));
    Bu_sh[12]->SetPos(Vector2(tm->IdxToVector(Int2(116, 178))));
    Bu_sh[13]->SetPos(Vector2(tm->IdxToVector(Int2(117, 178))));

    for (int i = 14; i < 34; i++)
    {
        Bu_sh[i]->SetPos(Vector2(tm->IdxToVector(Int2(370 + i - 14, 3))));
    }

    Watch_Tower[0]->SetPos(Vector2(tm->IdxToVector(Int2(111, 185))));
    Watch_Tower[1]->SetPos(Vector2(tm->IdxToVector(Int2(105, 173))));
    Watch_Tower[2]->SetPos(Vector2(tm->IdxToVector(Int2(98, 184))));
    Watch_Tower[3]->SetPos(Vector2(tm->IdxToVector(Int2(111, 120))));
    Watch_Tower[4]->SetPos(Vector2(tm->IdxToVector(Int2(116, 123))));
    Watch_Tower[5]->SetPos(Vector2(tm->IdxToVector(Int2(374, 23))));
    Watch_Tower[6]->SetPos(Vector2(tm->IdxToVector(Int2(370, 7))));
    Watch_Tower[7]->SetPos(Vector2(tm->IdxToVector(Int2(393, 26))));
    //player
    pl->SetPos(Vector2(Vector2(tm->IdxToVector(Int2(197, 202)))));

    //enemy
    Sp[0]->SetPos(Vector2(tm->IdxToVector(Int2(108, 174))));
    Sp[1]->SetPos(Vector2(tm->IdxToVector(Int2(108, 183))));
    Sp[2]->SetPos(Vector2(tm->IdxToVector(Int2(105, 181))));
    Sp[3]->SetPos(Vector2(tm->IdxToVector(Int2(104, 179))));
    Sp[4]->SetPos(Vector2(tm->IdxToVector(Int2(128, 125))));
    Sp[5]->SetPos(Vector2(tm->IdxToVector(Int2(128, 112))));
    Sp[0]->Rotate_Root(-220.0f * TORADIAN );
    Sp[0]->Rotation = -220.0f * TORADIAN ;
    Sp[1]->Rotate_Root(50.0f * TORADIAN );
    Sp[1]->Rotation = 50.0f * TORADIAN ;
    Sp[2]->Rotate_Root(-180.0f * TORADIAN);
    Sp[2]->Rotation = -180.0f * TORADIAN;
    Sp[3]->Rotate_Root(-90.0f * TORADIAN);
    Sp[3]->Rotation = -90.0f * TORADIAN;
    Sp[4]->Rotate_Root(50.0f * TORADIAN);
    Sp[4]->Rotation = 50.0f * TORADIAN;
    Sp[5]->Rotate_Root(-90.0f * TORADIAN);
    Sp[5]->Rotation = -90.0f * TORADIAN;
    Sp[6]->SetPos(Vector2(tm->IdxToVector(Int2(379, 10))));
    Sp[6]->Rotate_Root(-90.0f * TORADIAN);
    Sp[6]->Rotation = -90.0f * TORADIAN;
    Sp[7]->SetPos(Vector2(tm->IdxToVector(Int2(381, 21))));
    Sp[7]->Rotate_Root(-180.0f * TORADIAN);
    Sp[7]->Rotation = -180.0f * TORADIAN;
    Sp[8]->SetPos(Vector2(tm->IdxToVector(Int2(392, 21))));
    Sp[8]->Rotate_Root(-180.0f * TORADIAN);
    Sp[8]->Rotation = -180.0f * TORADIAN;
    Sp[9]->SetPos(Vector2(tm->IdxToVector(Int2(380, 20))));
    Sp[9]->Rotate_Root(-90.0f * TORADIAN);
    Sp[9]->Rotation = -90.0f * TORADIAN;

    Sd[0]->SetPos(Vector2(tm->IdxToVector(Int2(108, 182))));
    Sd[0]->Rotate_Root(30.0f * TORADIAN);
    Sd[0]->Rotation = 30.0f * TORADIAN;
    Sd[1]->SetPos(Vector2(tm->IdxToVector(Int2(107, 182))));
    Sd[1]->Rotate_Root(30.0f * TORADIAN);
    Sd[1]->Rotation = 30.0f * TORADIAN;
    Sd[2]->SetPos(Vector2(tm->IdxToVector(Int2(114, 182))));
    Sd[2]->Rotate_Root(50.0f * TORADIAN);
    Sd[2]->Rotation = 50.0f * TORADIAN;
    Sd[3]->SetPos(Vector2(tm->IdxToVector(Int2(102, 179))));
    Sd[3]->Rotate_Root(-90.0f * TORADIAN);
    Sd[3]->Rotation = -90.0f * TORADIAN;
    Sd[3]->SetPos(Vector2(tm->IdxToVector(Int2(102, 179))));
    Sd[3]->Rotate_Root(-90.0f * TORADIAN);
    Sd[3]->Rotation = -90.0f * TORADIAN;
    Sd[3]->SetPos(Vector2(tm->IdxToVector(Int2(102, 179))));
    Sd[3]->Rotate_Root(-90.0f * TORADIAN);
    Sd[3]->Rotation = -90.0f * TORADIAN;
    Sd[4]->SetPos(Vector2(tm->IdxToVector(Int2(111, 123))));
    Sd[4]->Rotate_Root(-90.0f * TORADIAN);
    Sd[4]->Rotation = -90.0f * TORADIAN;
    Sd[5]->SetPos(Vector2(tm->IdxToVector(Int2(114, 125))));
    Sd[5]->Rotate_Root(-90.0f * TORADIAN);
    Sd[5]->Rotation = -90.0f * TORADIAN;
    Sd[6]->SetPos(Vector2(tm->IdxToVector(Int2(386, 7))));
    Sd[6]->Rotate_Root(-180.0f * TORADIAN);
    Sd[6]->Rotation = -180.0f * TORADIAN;

    St[0]->SetPos(Vector2(tm->IdxToVector(Int2(106, 131))));
    St[0]->Rotate_Root(-200.0f * TORADIAN);
    St[0]->Rotation = -200.0f * TORADIAN;
    St[0]->isCharge = false;
    St[1]->SetPos(Vector2(tm->IdxToVector(Int2(108, 126))));
    St[1]->Rotate_Root(-200.0f * TORADIAN);
    St[1]->Rotation = -200.0f * TORADIAN;
    St[1]->isCharge = false;
    St[2]->SetPos(Vector2(-20000.0f, 300.0f));
    St[3]->SetPos(Vector2(-20000.0f, 300.0f));
    St[4]->SetPos(Vector2(-20000.0f, 300.0f));
    St[5]->SetPos(Vector2(-20000.0f, 300.0f));
    St[6]->SetPos(Vector2(-20000.0f, 300.0f));
    St[7]->SetPos(Vector2(tm->IdxToVector(Int2(113, 117))));
    St[7]->Rotate_Root(-200.0f * TORADIAN);
    St[7]->Rotation = -200.0f * TORADIAN;
    St[7]->isCharge = false;
    St[8]->SetPos(Vector2(tm->IdxToVector(Int2(115, 117))));
    St[8]->Rotate_Root(-200.0f * TORADIAN);
    St[8]->Rotation = -200.0f * TORADIAN;
    St[8]->isCharge = false;
    St[9]->SetPos(Vector2(tm->IdxToVector(Int2(117, 117))));
    St[9]->Rotate_Root(-200.0f * TORADIAN);
    St[9]->Rotation = -200.0f * TORADIAN;
    St[9]->isCharge = false;
    St[10]->SetPos(Vector2(tm->IdxToVector(Int2(373, 19))));
    St[10]->Rotate_Root(-90.0f * TORADIAN);
    St[10]->Rotation = -90.0f * TORADIAN;
    St[10]->isCharge = false;
    St[11]->SetPos(Vector2(tm->IdxToVector(Int2(396, 21))));
    St[11]->Rotate_Root(-180.0f * TORADIAN);
    St[11]->Rotation = -180.0f * TORADIAN;
    St[11]->isCharge = false;
    St[12]->SetPos(Vector2(tm->IdxToVector(Int2(387, 8))));
    St[12]->Rotate_Root(-90.0f * TORADIAN);
    St[12]->Rotation = -90.0f * TORADIAN;
    St[12]->isCharge = false;
    St[13]->SetPos(Vector2(tm->IdxToVector(Int2(370, 2))));
    St[13]->Rotate_Root(-90.0f * TORADIAN);
    St[13]->Rotation = -90.0f * TORADIAN;
    St[13]->isCharge = false;
    St[14]->SetPos(Vector2(tm->IdxToVector(Int2(375, 10))));
    St[14]->Rotate_Root(-90.0f * TORADIAN);
    St[14]->Rotation = -90.0f * TORADIAN;
    St[14]->isCharge = false;
    St[15]->SetPos(Vector2(-20000.0f, 300.0f));
    St[16]->SetPos(Vector2(-20000.0f, 300.0f));
    St[17]->SetPos(Vector2(-20000.0f, 300.0f));

    Bz[0]->SetPos(Vector2(tm->IdxToVector(Int2(377, 19))));
    Bz[0]->Rotate_Root(-90.0f * TORADIAN);
    Bz[0]->Rotation = -90.0f * TORADIAN;
    Bz[1]->SetPos(Vector2(tm->IdxToVector(Int2(380, 11))));
    Bz[1]->Rotate_Root(-90.0f * TORADIAN);
    Bz[1]->Rotation = -90.0f * TORADIAN;
    Bz[2]->SetPos(Vector2(tm->IdxToVector(Int2(394, 21))));
    Bz[2]->Rotate_Root(-180.0f * TORADIAN);
    Bz[2]->Rotation = -180.0f * TORADIAN;

    //npc
    Npc1[0]->SetPos(Vector2(tm->IdxToVector(Int2(184, 178))));
    Npc1[0]->Rotate_Root(-90.0f * TORADIAN);
    Npc1[0]->Rotation = -90.0f * TORADIAN;

    Npc1[1]->SetPos(Vector2(tm->IdxToVector(Int2(184, 181))));
    Npc1[1]->Rotate_Root(-90.0f * TORADIAN);
    Npc1[1]->Rotation = -90.0f * TORADIAN;

    Npc1[2]->SetPos(Vector2(tm->IdxToVector(Int2(213, 219))));
    Npc1[2]->Rotate_Root(-90.0f * TORADIAN);
    Npc1[2]->Rotation = -90.0f * TORADIAN;

    Npc1[3]->SetPos(Vector2(tm->IdxToVector(Int2(216, 219))));
    Npc1[3]->Rotate_Root(-180.0f * TORADIAN);
    Npc1[3]->Rotation = -180.0f * TORADIAN;

    Npc1[4]->SetPos(Vector2(tm->IdxToVector(Int2(225, 191))));
    Npc1[4]->Rotate_Root(0.0f * TORADIAN);
    Npc1[4]->Rotation = 0.0f * TORADIAN;

    Npc1[5]->SetPos(Vector2(tm->IdxToVector(Int2(224, 191))));
    Npc1[5]->Rotate_Root(0.0f * TORADIAN);
    Npc1[5]->Rotation = 0.0f * TORADIAN;

    Npc2[0]->SetPos(Vector2(tm->IdxToVector(Int2(208, 202))));
    Npc2[0]->Rotate_Root(0.0f * TORADIAN);
    Npc2[0]->Rotation = 0.0f * TORADIAN;
    Npc2[0]->NPC2_Idle->color = Color(0.5f, 0.6f, 0.6f, 0.5f);

    Npc2[1]->SetPos(Vector2(tm->IdxToVector(Int2(221, 204))));
    Npc2[1]->Rotate_Root(0.0f * TORADIAN);
    Npc2[1]->Rotation = 0.0f * TORADIAN;
    Npc2[1]->NPC2_Idle->color = Color(0.6f, 0.5f, 0.6f, 0.5f);

    Npc2[2]->SetPos(Vector2(tm->IdxToVector(Int2(225, 192))));
    Npc2[2]->Rotate_Root(-90.0f * TORADIAN);
    Npc2[2]->Rotation = -90.0f * TORADIAN;
    Npc2[2]->NPC2_Idle->color = Color(0.6f, 0.6f, 0.5f, 0.5f);

    Npc2[3]->SetPos(Vector2(tm->IdxToVector(Int2(206, 185))));
    Npc2[3]->Rotate_Root(0.0f * TORADIAN);
    Npc2[3]->Rotation = 0.0f * TORADIAN;
    Npc2[3]->NPC2_Idle->color = Color(0.6f, 0.6f, 0.6f, 0.5f);

    //ride
    /*Acs->SetPos(Vector2(Vector2(tm->IdxToVector(Int2(203, 184)))));*/
    Acs->SetPos(Vector2(-500.0f,-500.0f));

    //HUD
    Hud->Init();
    Hud2->Init();

    GameTime = -5.0f;
    Game_Speed = 1.0f;

    //Mouse
    Click_Num = 0;

    //quest
    Progress_Num = 0;

    BGMCOUNT = 0;
}

void Scene1::Update()
{ 
    //BGM CONTROL
    if (GameTime > 0.0f and BGMCOUNT == 0)
    {
        SOUND->Stop("BGM1");
        SOUND->Play("BGM1");
        SOUND->SetVolume("BGM1", 0.2f);
        BGMCOUNT += 1;
    }
    if (GameTime > 350.0f and BGMCOUNT == 1)
    {
        SOUND->Stop("BGM1");
        SOUND->Play("BGM2");
        SOUND->SetVolume("BGM2", 0.2f);
        BGMCOUNT += 1;
    }
    if (GameTime > 350.0f and BGMCOUNT == 2)
    {
        SOUND->Stop("BGM2");
        SOUND->Play("BGM3");
        SOUND->SetVolume("BGM3", 0.2f);
        BGMCOUNT += 1;
    }

    //Edit
    if (edit)
    {
        if (INPUT->KeyDown(VK_F7))
        {
            cout << g_WorldMouse.x << 't' << g_WorldMouse.y << endl;
        }
        if (INPUT->KeyDown(VK_F8))
        {
            Int2 idx;
            tm->VectorToIdx(g_WorldMouse, idx);
            cout << idx.x << 't' << idx.y << endl;
        }
        if (INPUT->KeyDown(VK_F1))
        {
            SCENE->ChangeScene("Edit")->Init();
        }
        if (INPUT->KeyDown(VK_F2))
        {
            Camera_Speed = 100.0f;
        }
        if (INPUT->KeyDown(VK_F3))
        {
            Camera_Speed = 300.0f;
        }
        if (INPUT->KeyDown(VK_F4))
        {
            Camera_Speed = 600.0f;
        }
        if (INPUT->KeyDown(VK_F5))
        {
            Camera_Speed = 2000.0f;
        }
        if (INPUT->KeyDown(VK_F6))
        {
            Camera_Speed = 5000.0f;
        }

        //cam move
        if (INPUT->KeyPress('W'))
        {
            MAINCAM->Pos += UP * Camera_Speed * DeltaTime;
        }
        if (INPUT->KeyPress('S'))
        {
            MAINCAM->Pos += DOWN * Camera_Speed * DeltaTime;
        }
        if (INPUT->KeyPress('A'))
        {
            MAINCAM->Pos += LEFT * Camera_Speed * DeltaTime;
        }
        if (INPUT->KeyPress('D'))
        {
            MAINCAM->Pos += RIGHT * Camera_Speed * DeltaTime;
        }

        ImGui::Begin("TileMapEditer");
        tm->Update();
        ImGui::End();
    }
    if (INPUT->KeyDown('9'))
    {
        if (edit)
        {
            edit = false;
            Player_Update = true;
        }
        else
        {
            edit = true;
            Player_Update = false;
        }
    }

    //Imgui
    ImGui::Text("StageTime: %f", GameTime);

    //IMGUI
    /*ImGui::SliderFloat("POS_X", &Huds->Position.x, 0.0f, 2000.0f);
    ImGui::SliderFloat("POS_Y", &Huds->Position.y, 0.0f, 800.0f);*/

    //update
    if (GameTime > 1.0f)
    {
        Hud->Update();
        Hud2->Update();
        Huds->Position = MAINCAM->Pos;
        CheckBox->Position = MAINCAM->Pos + Vector2(1130.0f,50.0f);
        for (int i = 0; i < SNIPERCOUNT; i++)
        {
            Sp[i]->Update();
        }
        for (int i = 0; i < SOLDIERCOUNT; i++)
        {
            Sd[i]->Update();
        }
        for (int i = 0; i < STORMCOUNT; i++)
        {
            St[i]->Update();
        }
        for (int i = 0; i < BAZOOKACOUNT; i++)
        {
            Bz[i]->Update();
        }
        for (int i = 0; i < NPC1COUNT; i++)
        {
            Npc1[i]->Update();
        }
        for (int i = 0; i < NPC2COUNT; i++)
        {
            Npc2[i]->Update();
        }

        //ride
        Acs->Update();

        for (int i = 0; i < HOUSE1COUNT; i++)
        {
            House_1[i]->Update();
        }
        for (int i = 0; i < HOUSE2COUNT; i++)
        {
            House_2[i]->Update();
        }
        for (int i = 0; i < TREE1COUNT; i++)
        {
            Tree_1[i]->Update();
        }
        for (int i = 0; i < TREE2COUNT; i++)
        {
            Tree_2[i]->Update();
        }
        for (int i = 0; i < ROCKCOUNT; i++)
        {
            Ro_ck[i]->Update();
        }
        for (int i = 0; i < BUSHCOUNT; i++)
        {
            Bu_sh[i]->Update();
        }
        for (int i = 0; i < WATCHTOWERCOUNT; i++)
        {
            Watch_Tower[i]->Update();
        }
    }

    //Gametime
    GameTime += DeltaTime;
    
    //WeaponChange
    switch(pl->Gun_Kind)
    {
    case 0:
        Hud->Gun_Kind =0;
        break;
    case 1:
        Hud->Gun_Kind = 1;
        break;
    case 2:
        Hud->Gun_Kind = 2;
        break;
    case 3:
        Hud->Gun_Kind = 3;
        break;
    case 4:
        Hud->Gun_Kind = 4;
        break;
    }

    //acs placed
    if (Npc2[0]->isClick and Progress_Num == 16)
    {
        Acs->SetPos(Vector2(Vector2(tm->IdxToVector(Int2(203, 184)))));
    }

    //watch tower
    for (int i = 0; i < WATCHTOWERCOUNT; i++)
    {
        for (int j = 0; j < STORMCOUNT; j++)
        {
            if (Watch_Tower[i]->isHit and Watch_Tower[i]->isCharge and St[j]->isCharge)
            {
                Watch_Tower[i]->isCharge = false;
                St[j]->SetPos(Watch_Tower[i]->GetPos() - Vector2(0.0f, 80.0f));
                St[j]->isCharge = false;
                St[j]->StormState = ST_ALERT;
                break;
            }
        }

    }
    
}

void Scene1::LateUpdate()
{
    //hud
    if (isCollision(CheckBox, g_WorldMouse))
    {
        if (Npc2[0]->isClick and Progress_Num == 0)
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                Click_Num = 0;
                Progress_Num = 1;
            }
        }
        if (Npc2[0]->isClick and Progress_Num ==1)
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                Click_Num = 0;
                Progress_Num = 2;
            }
        }
        if (Npc2[1]->isClick and Progress_Num == 2)
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                Click_Num = 0;
                Progress_Num = 3;
            }
        }
        if (Npc2[1]->isClick and Progress_Num == 3)
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                Click_Num = 0;
                Progress_Num = 4;
            }
        }
        if (Npc2[1]->isClick and Progress_Num == 4)
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                Click_Num = 0;
                Progress_Num = 5;
            }
        }
        if (Npc2[1]->isClick and Progress_Num == 5)
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                Click_Num = 0;
                Progress_Num = 6;
            }
        }
        if (Npc2[1]->isClick and Progress_Num == 6)
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                Click_Num = 0;
                Progress_Num = 7;
            }
        }
        if (Npc2[1]->isClick and Progress_Num == 7)
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                Click_Num = 0;
                Progress_Num = 8;
            }
        }
        if (Npc2[1]->isClick and Progress_Num == 8)
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                Click_Num = 0;
                Progress_Num = 9;
            }
        }
        if (Npc2[1]->isClick and Progress_Num == 9)
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                Click_Num = 0;
                Progress_Num = 10;
            }
        }
        if (Npc2[0]->isClick and Progress_Num ==10)
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                Click_Num = 0;
                Progress_Num = 11;
            }
        }
        if (Npc2[0]->isClick and Progress_Num == 11)
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                Click_Num = 0;
                Progress_Num = 12;
            }
        }
        if (Npc2[0]->isClick and Progress_Num == 12 and QuestItem[0]->isEat)
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                Click_Num = 0;
                Progress_Num = 13;
                pl->Money += 1000;
            }
        }
        if (Npc2[0]->isClick and Progress_Num == 13)
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                Click_Num = 0;
                Progress_Num = 14;
            }
        }
        if (Npc2[0]->isClick and Progress_Num == 14)
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                Click_Num = 0;
                Progress_Num = 15;
            }
        }
        if (Npc2[0]->isClick and Progress_Num == 15 and QuestItem[1]->isEat)
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                Click_Num = 0;
                Progress_Num = 16;
                pl->Money += 2000;
            }
        }
        if (Npc2[0]->isClick and Progress_Num == 16)
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                Click_Num = 0;
                Progress_Num = 17;
            }
        }
        if (Npc2[0]->isClick and Progress_Num == 17)
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                Click_Num = 0;
                Progress_Num = 18;
            }
        }
        if (Npc2[0]->isClick and Progress_Num == 18 and QuestItem[2]->isEat)
        {
            if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
                Click_Num = -1;
            if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
            {
                Click_Num = 0;
                Progress_Num = 19;
                pl->Money += 5000;
            }
        }
    }

    if (GameTime > 1.0f)
    {
        pl->LateUpdate();
        for (int i = 0; i < SNIPERCOUNT; i++)
        {
            Sp[i]->LateUpdate();
        }
        for (int i = 0; i < SOLDIERCOUNT; i++)
        {
            Sd[i]->LateUpdate();
        }
        for (int i = 0; i < STORMCOUNT; i++)
        {
            St[i]->LateUpdate();
        }
        for (int i = 0; i < BAZOOKACOUNT; i++)
        {
            Bz[i]->LateUpdate();
        }
        for (int i = 0; i < NPC1COUNT; i++)
        {
            Npc1[i]->LateUpdate();
        }
        for (int i = 0; i < NPC2COUNT; i++)
        {
            Npc2[i]->LateUpdate();
        }
        Acs->LateUpdate();
    }
    if (Player_Update)
    {
        //camera move
        if (!Acs->isRide and GameTime > 1.0f)
        {
            if (pl->GetPos().x < 20000.0f - 600.0f)
            {
                if (WorldToScreen(MAINCAM->Pos, pl->GetPos()).x > WINSIZEX / 5.0f * 3.0f/* and pl->GetPos().x < */)
                {
                    MAINCAM->Pos.x = pl->GetPos().x - WINSIZEX / 5.0f * 3.0f;
                }
            }

            if (pl->GetPos().x > 600.0f)
            {
                if (WorldToScreen(MAINCAM->Pos, pl->GetPos()).x < WINSIZEX / 5.0f * 2.0f/* and pl->GetPos().x < */)
                {
                    MAINCAM->Pos.x = pl->GetPos().x - WINSIZEX / 5.0f * 2.0f;
                }
            }
            if (pl->GetPos().x > 19950.0f)
            {
                pl->SetPosX(Vector2(19950.0f, 0.0f));
            }

            if (pl->GetPos().y > 340.0f)
            {
                if (WorldToScreen(MAINCAM->Pos, pl->GetPos()).y > WINSIZEY / 5.0f * 3.0f/* and pl->GetPos().y < */)
                {
                    MAINCAM->Pos.y = pl->GetPos().y - WINSIZEY / 5.0f * 2.0f;
                }
            }

            if (pl->GetPos().y < 20000.0f - 340.0f)
            {
                if (WorldToScreen(MAINCAM->Pos, pl->GetPos()).y < WINSIZEY / 5.0f * 2.0f/* and pl->GetPos().y < */)
                {
                    MAINCAM->Pos.y = pl->GetPos().y - WINSIZEY / 5.0f * 3.0f;
                }
            }
            if (pl->GetPos().y > 19950.0f)
            {
                pl->SetPosY(Vector2(19950.0f, 0.0f));
            }
        }

        if (Acs->isRide)
        {
            //about x
            if (Acs->GetPos().x < 50.0f)
            {
                Acs->SetPosX(Vector2(50.0f, 0.0f));
            }
            if (Acs->GetPos().x < (20000.0f - 500.0f))
            {
                if (WorldToScreen(MAINCAM->Pos, Acs->GetPos()).x > WINSIZEX / 5.0f * 3.0f/* and Acs->GetPos().x < */)
                {
                    MAINCAM->Pos.x = Acs->GetPos().x - WINSIZEX / 5.0f * 3.0f;
                }
            }

            if (Acs->GetPos().x > 600.0f)
            {
                if (WorldToScreen(MAINCAM->Pos, Acs->GetPos()).x < WINSIZEX / 5.0f * 2.0f/* and Acs->GetPos().x < */)
                {
                    MAINCAM->Pos.x = Acs->GetPos().x - WINSIZEX / 5.0f * 2.0f;
                }
            }
            if (Acs->GetPos().x > 19950.0f)
            {
                Acs->SetPosX(Vector2(19950.0f, 0.0f));
            }

            //about y
            if (Acs->GetPos().y < 50.0f)
            {
                Acs->SetPosY(Vector2(0.0f, 50.0f));
            }
            if (Acs->GetPos().y > 340.0f)
            {
                if (WorldToScreen(MAINCAM->Pos, Acs->GetPos()).y > WINSIZEY / 5.0f * 3.0f/* and Acs->GetPos().y < */)
                {
                    MAINCAM->Pos.y = Acs->GetPos().y - WINSIZEY / 5.0f * 2.0f;
                }
            }

            if (Acs->GetPos().y < (20000.0f - 340.0f))
            {
                if (WorldToScreen(MAINCAM->Pos, Acs->GetPos()).y < WINSIZEY / 5.0f * 2.0f/* and Acs->GetPos().y < */)
                {
                    MAINCAM->Pos.y = Acs->GetPos().y - WINSIZEY / 5.0f * 3.0f;
                }
            }
            if (Acs->GetPos().y > 19950.0f)
            {
                Acs->SetPosY(Vector2(19950.0f, 0.0f));
            }
        }
        pl->Update();
    }
    

    //collision wall
    {
        Int2 idx;
        Vector2 foot = pl->GetPos() + Vector2(0.0f, -12.0f);

        if (tm->VectorToIdx(foot + pl->MoveDir * 10.0f, idx))
        {
            if (tm->Tiles[idx.x][idx.y].state == TILE_WALL)
            {
                pl->Turnback();
            }
        }
    }
    {
        Int2 idx;
        Vector2 foot = Acs->GetPos() + Vector2(0.0f, -20.0f);

        if (Acs->Input_Power >= 0)
        {
            if (tm->VectorToIdx(foot + RadianToDir(Acs->GetRotate() - PI * 0.5f) * 30.0f, idx))
            {
                if (tm->Tiles[idx.x][idx.y].state == TILE_WALL)
                {
                    Acs->Turnback();
                    return;
                }
            }
        }
        else if (Acs->Input_Power <= 0)
        {
            if (tm->VectorToIdx(foot - RadianToDir(Acs->GetRotate() - PI * 0.5f) * 30.0f, idx))
            {
                if (tm->Tiles[idx.x][idx.y].state == TILE_WALL)
                {
                    Acs->Turnback();
                    return;
                }
            }
        }
    }
    //walking sand
    {
        Int2 idx;
        Vector2 foot = pl->GetPos() + Vector2(0.0f, -12.0f);

        if (tm->VectorToIdx(foot + pl->MoveDir * 10.0f, idx))
        {
            if (tm->Tiles[idx.x][idx.y].state == TILE_SAND)
            {
                pl->PlayerSpeed = pl->Player_Speed * Game_Speed * 0.75f;
            }
        }
    }
    {
        Int2 idx;
        Vector2 foot = Acs->GetPos() + Vector2(0.0f, -20.0f);

        if (Acs->Input_Power >= 0)
        {
            if (tm->VectorToIdx(foot + RadianToDir(Acs->GetRotate() - PI * 0.5f) * 30.0f, idx))
            {
                if (tm->Tiles[idx.x][idx.y].state == TILE_SAND)
                {
                    Acs->Tile_Speed = 0.75f;
                }
            }
        }
        else if (Acs->Input_Power <= 0)
        {
            if (tm->VectorToIdx(foot - RadianToDir(Acs->GetRotate() - PI * 0.5f) * 30.0f, idx))
            {
                if (tm->Tiles[idx.x][idx.y].state == TILE_SAND)
                {
                    Acs->Tile_Speed = 0.75f;
                }
            }
        }
    }
    //walking dirt, grass
    {
        Int2 idx;
        Vector2 foot = pl->GetPos() + Vector2(0.0f, -12.0f);

        if (tm->VectorToIdx(foot + pl->MoveDir * 10.0f, idx))
        {
            if (tm->Tiles[idx.x][idx.y].state == TILE_NONE)
            {
                pl->PlayerSpeed = pl->Player_Speed * Game_Speed * 1.0f;
            }
        }
    }
    {
        Int2 idx;
        Vector2 foot = Acs->GetPos() + Vector2(0.0f, -20.0f);
        if (Acs->Input_Power >= 0)
        {
            if (tm->VectorToIdx(foot + RadianToDir(Acs->GetRotate() - PI * 0.5f) * 30.0f, idx))
            {
                if (tm->Tiles[idx.x][idx.y].state == TILE_NONE)
                {
                    Acs->Tile_Speed = 1.0f;
                }
            }
        }
        else if (Acs->Input_Power <= 0)
        {
            if (tm->VectorToIdx(foot - RadianToDir(Acs->GetRotate() - PI * 0.5f) * 30.0f, idx))
            {
                if (tm->Tiles[idx.x][idx.y].state == TILE_NONE)
                {
                    Acs->Tile_Speed = 1.0f;
                }
            }
        }
    }
    //walking asphalt
    {
        Int2 idx;
        Vector2 foot = pl->GetPos() + Vector2(0.0f, -12.0f);

        if (tm->VectorToIdx(foot + pl->MoveDir * 10.0f, idx))
        {
            if (tm->Tiles[idx.x][idx.y].state == TILE_ASPHALT)
            {
                pl->PlayerSpeed = pl->Player_Speed * Game_Speed * 1.5f;
            }
        }
    }
    {
        Int2 idx;
        Vector2 foot = Acs->GetPos() + Vector2(0.0f, -20.0f);
        if (Acs->Input_Power >= 0)
        {
            if (tm->VectorToIdx(foot + RadianToDir(Acs->GetRotate() - PI * 0.5f) * 30.0f, idx))
            {
                if (tm->Tiles[idx.x][idx.y].state == TILE_ASPHALT)
                {
                    Acs->Tile_Speed = 1.5f;
                }
            }
        }
        else if (Acs->Input_Power <= 0)
        {
            if (tm->VectorToIdx(foot - RadianToDir(Acs->GetRotate() - PI * 0.5f) * 30.0f, idx))
            {
                if (tm->Tiles[idx.x][idx.y].state == TILE_ASPHALT)
                {
                    Acs->Tile_Speed = 1.5f;
                }
            }
        }
    }

    //hide bush
    {
        Int2 idx;
        Vector2 foot = pl->GetPos() + Vector2(0.0f, -12.0f);

        if (tm->VectorToIdx(foot + pl->MoveDir * 10.0f, idx))
        {
            if (tm->Tiles[idx.x][idx.y].state == TILE_BUSH)
            {
                pl->Hide = true;
            }
            else
            {
                pl->Hide = false;
            }
        }
    }

    //Alarm(Watchtower)
    for (int i = 0; i < WATCHTOWERCOUNT; i++)
    {
        for (int j = 0; j < SNIPERCOUNT; j++)
        {
            if (isCollision(Watch_Tower[i]->Alarm, Sp[j]->GetPos()) and !Sp[j]->isAlarm)
            {
                Sp[j]->SniperState = SS_ALERT;
                Sp[j]->isAlarm = true;
            }
        }
    }
    for (int i = 0; i < WATCHTOWERCOUNT; i++)
    {
        for (int j = 0; j < SOLDIERCOUNT; j++)
        {
            if (isCollision(Watch_Tower[i]->Alarm, Sd[j]->GetPos()) and !Sd[j]->isAlarm)
            {
                Sd[j]->SoldierState = SD_ALERT;
                Sd[j]->isAlarm = true;
            }
        }
    }
    for (int i = 0; i < WATCHTOWERCOUNT; i++)
    {
        for (int j = 0; j < STORMCOUNT; j++)
        {
            if (isCollision(Watch_Tower[i]->Alarm, St[j]->GetPos()) and !St[j]->isAlarm)
            {
                St[j]->StormState = ST_ALERT;
                St[j]->isAlarm = true;
            }
        }
    }
    for (int i = 0; i < WATCHTOWERCOUNT; i++)
    {
        for (int j = 0; j < BAZOOKACOUNT; j++)
        {
            if (isCollision(Watch_Tower[i]->Alarm, Bz[j]->GetPos()) and !Bz[j]->isAlarm)
            {
                Bz[j]->BazookaState = Bz_ALERT;
                Bz[j]->isAlarm = true;
            }
        }
    }

    //eat item
    for (int i = 0; i < HEALPACKNUM; i++)
    {
        if (isCollision(Heal_Pack[i]->HitBox, pl->HitBox) and GameTime>1.0f)
        {
            Heal_Pack[i]->SetPos(Vector2(-3000.0f, 100.0f));
            pl->Health += 5;
        }
    }
    for (int i = 0; i < AMMUNITIONNUM; i++)
    {
        if (isCollision(Ammu_nition[i]->HitBox, pl->HitBox) and GameTime > 1.0f)
        {
            Ammu_nition[i]->SetPos(Vector2(-3000.0f, 100.0f));
            Ammu_nition[i]->Kind = RndInt(0, 3);
            switch (Ammu_nition[i]->Kind)
            {
            case MG:
                pl->MG_Bullet_Num += 50;
                break;
            case RIFLE:
                pl->R_Bullet_Num += 30;
                break;
            case GL:
                pl->GL_Bullet_Num += 3;
                break;
            case FT:
                pl->FT_Bullet_Num += 50;
                break;
            }
        }
    }
    for (int i = 0; i < ARMORNUM; i++)
    {
        if (isCollision(Ar_mor[i]->HitBox, pl->HitBox) and GameTime > 1.0f)
        {
            Ar_mor[i]->SetPos(Vector2(-3000.0f, 100.0f));
            pl->Armor += 5;
        }
    }
    for (int i = 0; i < MONEYNUM; i++)
    {
        if (isCollision(Mo_ney[i]->HitBox, pl->HitBox) and GameTime > 1.0f)
        {
            Mo_ney[i]->SetPos(Vector2(-3000.0f, 100.0f));
            pl->Money += 500;
        }
    }
    for (int i = 0; i < QUEST_ITEMNUM; i++)
    {
        if (isCollision(QuestItem[i]->HitBox, pl->HitBox) and GameTime > 1.0f)
        {
            QuestItem[i]->SetPos(Vector2(-3000.0f, 100.0f));
            QuestItem[i]->isEat = true;
        }
    }
    //hit
    //obstacle shot by bullet
    //house1
    for (int i = 0; i < HOUSE1COUNT; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (isCollision(House_1[i]->HitBox, pl->PB[j].Hitbox))
            {
                pl->PB[j].Pistol_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    for (int i = 0; i < HOUSE1COUNT; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if (isCollision(House_1[i]->HitBox, pl->MB[j].Hitbox))
            {
                pl->MB[j].MG_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    for (int i = 0; i < HOUSE1COUNT; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (isCollision(House_1[i]->HitBox, pl->RB[j].Hitbox))
            {
                pl->RB[j].RIFLE_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    for (int i = 0; i < HOUSE1COUNT; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (isCollision(House_1[i]->HitBox, pl->GB[j].GL_HitBox))
            {
                Vector2 temp = pl->GB[j].GL_Shot1->Position;
                pl->GB[j].GL_Shot1->Position = Vector2(-3000.0f, 0.0f);
                pl->GB[j].GL_Shot2->ChangeAnim(_ONCE, 0.25f / pl->Game_Speed);
                pl->GB[j].GL_Shot2->Position = temp;
                pl->GB[j].GL_Shot2->isActive = true;
                pl->GB[j].GL_HitBox2->isActive = true;
                pl->GB[j].Explode = true;
                SOUND->Stop("GT_EXPLODE");
                SOUND->Play("GT_EXPLODE");
                SOUND->SetVolume("GT_EXPLODE", 0.3f);
            }
        }
    }
    for (int i = 0; i < HOUSE1COUNT; i++)
    {
        for (int e = 0; e < SNIPERCOUNT; e++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (isCollision(House_1[i]->HitBox, Sp[e]->SB[j].Hitbox))
                {
                    Sp[e]->SB[j].Sniper_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    for (int i = 0; i < HOUSE1COUNT; i++)
    {
        for (int e = 0; e < SOLDIERCOUNT; e++)
        {
            for (int j = 0; j < 30; j++)
            {
                if (isCollision(House_1[i]->HitBox, Sd[e]->SB[j].Hitbox))
                {
                    Sd[e]->SB[j].Soldier_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    for (int i = 0; i < HOUSE1COUNT; i++)
    {
        for (int e = 0; e < STORMCOUNT; e++)
        {
            for (int j = 0; j < 30; j++)
            {
                if (isCollision(House_1[i]->HitBox, St[e]->SB[j].Hitbox))
                {
                    St[e]->SB[j].Storm_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    for (int i = 0; i < HOUSE1COUNT; i++)
    {
        for (int e = 0; e < BAZOOKACOUNT; e++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (isCollision(House_1[i]->HitBox, Bz[e]->SB[j].Hitbox))
                {
                    Bz[e]->SB[j].Bazooka_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    for (int i = 0; i < HOUSE1COUNT; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (isCollision(House_1[i]->HitBox, Acs->SB[j].Hitbox))
            {
                Acs->SB[j].ACS_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    //house2
    for (int i = 0; i < HOUSE2COUNT; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (isCollision(House_2[i]->HitBox, pl->PB[j].Hitbox))
            {
                pl->PB[j].Pistol_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    for (int i = 0; i < HOUSE2COUNT; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if (isCollision(House_2[i]->HitBox, pl->MB[j].Hitbox))
            {
                pl->MB[j].MG_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    for (int i = 0; i < HOUSE2COUNT; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (isCollision(House_2[i]->HitBox, pl->RB[j].Hitbox))
            {
                pl->RB[j].RIFLE_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    for (int i = 0; i < HOUSE2COUNT; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (isCollision(House_2[i]->HitBox, pl->GB[j].GL_HitBox))
            {
                Vector2 temp = pl->GB[j].GL_Shot1->Position;
                pl->GB[j].GL_Shot1->Position = Vector2(-3000.0f, 0.0f);
                pl->GB[j].GL_Shot2->ChangeAnim(_ONCE, 0.25f / pl->Game_Speed);
                pl->GB[j].GL_Shot2->Position = temp;
                pl->GB[j].GL_Shot2->isActive = true;
                pl->GB[j].GL_HitBox2->isActive = true;
                pl->GB[j].Explode = true;
                SOUND->Stop("GT_EXPLODE");
                SOUND->Play("GT_EXPLODE");
                SOUND->SetVolume("GT_EXPLODE", 0.3f);
            }
        }
    }
    for (int i = 0; i < HOUSE2COUNT; i++)
    {
        for (int e = 0; e < SNIPERCOUNT; e++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (isCollision(House_2[i]->HitBox, Sp[e]->SB[j].Hitbox))
                {
                    Sp[e]->SB[j].Sniper_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    for (int i = 0; i < HOUSE2COUNT; i++)
    {
        for (int e = 0; e < SOLDIERCOUNT; e++)
        {
            for (int j = 0; j < 30; j++)
            {
                if (isCollision(House_2[i]->HitBox, Sd[e]->SB[j].Hitbox))
                {
                    Sd[e]->SB[j].Soldier_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    for (int i = 0; i < HOUSE2COUNT; i++)
    {
        for (int e = 0; e < STORMCOUNT; e++)
        {
            for (int j = 0; j < 30; j++)
            {
                if (isCollision(House_2[i]->HitBox, St[e]->SB[j].Hitbox))
                {
                    St[e]->SB[j].Storm_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    for (int i = 0; i < HOUSE2COUNT; i++)
    {
        for (int e = 0; e < BAZOOKACOUNT; e++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (isCollision(House_2[i]->HitBox, Bz[e]->SB[j].Hitbox))
                {
                    Bz[e]->SB[j].Bazooka_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    for (int i = 0; i < HOUSE2COUNT; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (isCollision(House_2[i]->HitBox, Acs->SB[j].Hitbox))
            {
                Acs->SB[j].ACS_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    //Tree1
    for (int i = 0; i < TREE1COUNT; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (isCollision(Tree_1[i]->HitBox, pl->PB[j].Hitbox))
            {
                pl->PB[j].Pistol_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    for (int i = 0; i < TREE1COUNT; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if (isCollision(Tree_1[i]->HitBox, pl->MB[j].Hitbox))
            {
                pl->MB[j].MG_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    for (int i = 0; i < TREE1COUNT; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (isCollision(Tree_1[i]->HitBox, pl->RB[j].Hitbox))
            {
                pl->RB[j].RIFLE_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    for (int i = 0; i < TREE1COUNT; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (isCollision(Tree_1[i]->HitBox, pl->GB[j].GL_HitBox))
            {
                Vector2 temp = pl->GB[j].GL_Shot1->Position;
                pl->GB[j].GL_Shot1->Position = Vector2(-3000.0f, 0.0f);
                pl->GB[j].GL_Shot2->ChangeAnim(_ONCE, 0.25f / pl->Game_Speed);
                pl->GB[j].GL_Shot2->Position = temp;
                pl->GB[j].GL_Shot2->isActive = true;
                pl->GB[j].GL_HitBox2->isActive = true;
                pl->GB[j].Explode = true;
                SOUND->Stop("GT_EXPLODE");
                SOUND->Play("GT_EXPLODE");
                SOUND->SetVolume("GT_EXPLODE", 0.3f);
            }
        }
    }
    for (int i = 0; i < TREE1COUNT; i++)
    {
        for (int e = 0; e < SNIPERCOUNT; e++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (isCollision(Tree_1[i]->HitBox, Sp[e]->SB[j].Hitbox))
                {
                    Sp[e]->SB[j].Sniper_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    for (int i = 0; i < TREE1COUNT; i++)
    {
        for (int e = 0; e < SOLDIERCOUNT; e++)
        {
            for (int j = 0; j < 30; j++)
            {
                if (isCollision(Tree_1[i]->HitBox, Sd[e]->SB[j].Hitbox))
                {
                    Sd[e]->SB[j].Soldier_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    for (int i = 0; i < TREE1COUNT; i++)
    {
        for (int e = 0; e < STORMCOUNT; e++)
        {
            for (int j = 0; j < 30; j++)
            {
                if (isCollision(Tree_1[i]->HitBox, St[e]->SB[j].Hitbox))
                {
                    St[e]->SB[j].Storm_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    for (int i = 0; i < TREE1COUNT; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (isCollision(Tree_1[i]->HitBox, Acs->SB[j].Hitbox))
            {
                Acs->SB[j].ACS_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    //Tree2
    for (int i = 0; i < TREE2COUNT; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (isCollision(Tree_2[i]->HitBox, pl->PB[j].Hitbox))
            {
                pl->PB[j].Pistol_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    for (int i = 0; i < TREE2COUNT; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if (isCollision(Tree_2[i]->HitBox, pl->MB[j].Hitbox))
            {
                pl->MB[j].MG_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    for (int i = 0; i < TREE2COUNT; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (isCollision(Tree_2[i]->HitBox, pl->RB[j].Hitbox))
            {
                pl->RB[j].RIFLE_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    for (int i = 0; i < TREE2COUNT; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (isCollision(Tree_2[i]->HitBox, pl->GB[j].GL_HitBox))
            {
                Vector2 temp = pl->GB[j].GL_Shot1->Position;
                pl->GB[j].GL_Shot1->Position = Vector2(-3000.0f, 0.0f);
                pl->GB[j].GL_Shot2->ChangeAnim(_ONCE, 0.25f / pl->Game_Speed);
                pl->GB[j].GL_Shot2->Position = temp;
                pl->GB[j].GL_Shot2->isActive = true;
                pl->GB[j].GL_HitBox2->isActive = true;
                pl->GB[j].Explode = true;
                SOUND->Stop("GT_EXPLODE");
                SOUND->Play("GT_EXPLODE");
                SOUND->SetVolume("GT_EXPLODE", 0.3f);
            }
        }
    }
    for (int i = 0; i < TREE2COUNT; i++)
    {
        for (int e = 0; e < SNIPERCOUNT; e++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (isCollision(Tree_2[i]->HitBox, Sp[e]->SB[j].Hitbox))
                {
                    Sp[e]->SB[j].Sniper_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    for (int i = 0; i < TREE2COUNT; i++)
    {
        for (int e = 0; e < SOLDIERCOUNT; e++)
        {
            for (int j = 0; j < 30; j++)
            {
                if (isCollision(Tree_2[i]->HitBox, Sd[e]->SB[j].Hitbox))
                {
                    Sd[e]->SB[j].Soldier_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    for (int i = 0; i < TREE2COUNT; i++)
    {
        for (int e = 0; e < STORMCOUNT; e++)
        {
            for (int j = 0; j < 30; j++)
            {
                if (isCollision(Tree_2[i]->HitBox, St[e]->SB[j].Hitbox))
                {
                    St[e]->SB[j].Storm_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    for (int i = 0; i < TREE2COUNT; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (isCollision(Tree_2[i]->HitBox, Acs->SB[j].Hitbox))
            {
                Acs->SB[j].ACS_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    //ROCK
    for (int i = 0; i < ROCKCOUNT; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (isCollision(Ro_ck[i]->HitBox, pl->PB[j].Hitbox))
            {
                pl->PB[j].Pistol_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    for (int i = 0; i < ROCKCOUNT; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if (isCollision(Ro_ck[i]->HitBox, pl->MB[j].Hitbox))
            {
                pl->MB[j].MG_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    for (int i = 0; i < ROCKCOUNT; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (isCollision(Ro_ck[i]->HitBox, pl->RB[j].Hitbox))
            {
                pl->RB[j].RIFLE_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    for (int i = 0; i < ROCKCOUNT; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (isCollision(Ro_ck[i]->HitBox, pl->GB[j].GL_HitBox))
            {
                Vector2 temp = pl->GB[j].GL_Shot1->Position;
                pl->GB[j].GL_Shot1->Position = Vector2(-3000.0f, 0.0f);
                pl->GB[j].GL_Shot2->ChangeAnim(_ONCE, 0.25f / pl->Game_Speed);
                pl->GB[j].GL_Shot2->Position = temp;
                pl->GB[j].GL_Shot2->isActive = true;
                pl->GB[j].GL_HitBox2->isActive = true;
                pl->GB[j].Explode = true;
                SOUND->Stop("GT_EXPLODE");
                SOUND->Play("GT_EXPLODE");
                SOUND->SetVolume("GT_EXPLODE", 0.3f);
            }
        }
    }
    for (int i = 0; i < ROCKCOUNT; i++)
    {
        for (int e = 0; e < SNIPERCOUNT; e++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (isCollision(Ro_ck[i]->HitBox, Sp[e]->SB[j].Hitbox))
                {
                    Sp[e]->SB[j].Sniper_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    for (int i = 0; i < ROCKCOUNT; i++)
    {
        for (int e = 0; e < SOLDIERCOUNT; e++)
        {
            for (int j = 0; j < 30; j++)
            {
                if (isCollision(Ro_ck[i]->HitBox, Sd[e]->SB[j].Hitbox))
                {
                    Sd[e]->SB[j].Soldier_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    for (int i = 0; i < ROCKCOUNT; i++)
    {
        for (int e = 0; e < STORMCOUNT; e++)
        {
            for (int j = 0; j < 30; j++)
            {
                if (isCollision(Ro_ck[i]->HitBox, St[e]->SB[j].Hitbox))
                {
                    St[e]->SB[j].Storm_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    for (int i = 0; i < ROCKCOUNT; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (isCollision(Ro_ck[i]->HitBox, Acs->SB[j].Hitbox))
            {
                Acs->SB[j].ACS_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    for (int i = 0; i < ROCKCOUNT; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (isCollision(Ro_ck[i]->HitBox, Acs->SB[j].Hitbox))
            {
                Acs->SB[j].ACS_Bullet->Position = Vector2(-3000.0f, 0.0f);
            }
        }
    }
    //watchtower
    //sight
    for (int i = 0; i < WATCHTOWERCOUNT; i++)
    {
        if (isCollision(Watch_Tower[i]->Sight, pl->GetPos())and GameTime > 1.0f and !Watch_Tower[i]->isHit)
        {
            Watch_Tower[i]->isHit = true;
            SOUND->Stop("ALERT");
            SOUND->Play("ALERT");
            SOUND->SetVolume("ALERT", 1.0f);
        }
        
    }
    for (int i = 0; i < WATCHTOWERCOUNT; i++)
    {
        if (isCollision(Watch_Tower[i]->Sight, Acs->GetPos()) and GameTime > 1.0f and !Watch_Tower[i]->isHit)
        {
            Watch_Tower[i]->isHit = true;
            SOUND->Stop("ALERT");
            SOUND->Play("ALERT");
            SOUND->SetVolume("ALERT", 1.0f);
        }

    }
    for (int i = 0; i < WATCHTOWERCOUNT; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (isCollision(Watch_Tower[i]->HitBox, pl->PB[j].Hitbox) and GameTime > 1.0f and !Watch_Tower[i]->isHit)
            {
                pl->PB[j].Pistol_Bullet->Position = Vector2(-3000.0f, 0.0f);
                Watch_Tower[i]->isHit = true;
                SOUND->Stop("ALERT");
                SOUND->Play("ALERT");
                SOUND->SetVolume("ALERT", 1.0f);
            }
        }
    }
    for (int i = 0; i < WATCHTOWERCOUNT; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if (isCollision(Watch_Tower[i]->HitBox, pl->MB[j].Hitbox) and GameTime > 1.0f and !Watch_Tower[i]->isHit)
            {
                pl->MB[j].MG_Bullet->Position = Vector2(-3000.0f, 0.0f);
                Watch_Tower[i]->isHit = true;
                SOUND->Stop("ALERT");
                SOUND->Play("ALERT");
                SOUND->SetVolume("ALERT", 1.0f);
            }
        }
    }
    for (int i = 0; i < WATCHTOWERCOUNT; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (isCollision(Watch_Tower[i]->HitBox, pl->RB[j].Hitbox) and GameTime > 1.0f and !Watch_Tower[i]->isHit)
            {
                pl->RB[j].RIFLE_Bullet->Position = Vector2(-3000.0f, 0.0f);
                Watch_Tower[i]->isHit = true;
                SOUND->Stop("ALERT");
                SOUND->Play("ALERT");
                SOUND->SetVolume("ALERT", 1.0f);
            }
        }
    }
    for (int i = 0; i < WATCHTOWERCOUNT; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (isCollision(Watch_Tower[i]->HitBox, pl->GB[j].GL_HitBox) and GameTime > 1.0f and !Watch_Tower[i]->isHit)
            {
                Vector2 temp = pl->GB[j].GL_Shot1->Position;
                pl->GB[j].GL_Shot1->Position = Vector2(-3000.0f, 0.0f);
                pl->GB[j].GL_Shot2->ChangeAnim(_ONCE, 0.25f / pl->Game_Speed);
                pl->GB[j].GL_Shot2->Position = temp;
                pl->GB[j].GL_Shot2->isActive = true;
                pl->GB[j].GL_HitBox2->isActive = true;
                pl->GB[j].Explode = true;
                Watch_Tower[i]->isHit = true;
                SOUND->Stop("GT_EXPLODE");
                SOUND->Play("GT_EXPLODE");
                SOUND->SetVolume("GT_EXPLODE", 0.3f);
                SOUND->Stop("ALERT");
                SOUND->Play("ALERT");
                SOUND->SetVolume("ALERT", 1.0f);
            }
        }
    }
    for (int i = 0; i < WATCHTOWERCOUNT; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (isCollision(Watch_Tower[i]->HitBox, Acs->SB[j].Hitbox) and GameTime > 1.0f and !Watch_Tower[i]->isHit)
            {
                Acs->SB[j].ACS_Bullet->Position = Vector2(-3000.0f, 0.0f);
                Watch_Tower[i]->isHit = true;
                SOUND->Stop("ALERT");
                SOUND->Play("ALERT");
                SOUND->SetVolume("ALERT", 1.0f);
            }
        }
    }
    for (int i = 0; i < WATCHTOWERCOUNT; i++)
    {
        for (int e = 0; e < SNIPERCOUNT; e++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (isCollision(Watch_Tower[i]->HitBox, Sp[e]->SB[j].Hitbox))
                {
                    Sp[e]->SB[j].Sniper_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    for (int i = 0; i < WATCHTOWERCOUNT; i++)
    {
        for (int e = 0; e < SOLDIERCOUNT; e++)
        {
            for (int j = 0; j < 30; j++)
            {
                if (isCollision(Watch_Tower[i]->HitBox, Sd[e]->SB[j].Hitbox))
                {
                    Sd[e]->SB[j].Soldier_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    for (int i = 0; i < WATCHTOWERCOUNT; i++)
    {
        for (int e = 0; e < STORMCOUNT; e++)
        {
            for (int j = 0; j < 30; j++)
            {
                if (isCollision(Watch_Tower[i]->HitBox, St[e]->SB[j].Hitbox))
                {
                    St[e]->SB[j].Storm_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    for (int i = 0; i < WATCHTOWERCOUNT; i++)
    {
        for (int e = 0; e < BAZOOKACOUNT; e++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (isCollision(Watch_Tower[i]->HitBox, Bz[e]->SB[j].Hitbox))
                {
                    Bz[e]->SB[j].Bazooka_Bullet->Position = Vector2(-3000.0f, 0.0f);
                }
            }
        }
    }
    
    //HUD
    if (isCollision(Hud->Play_Box, g_WorldMouse))
    {
        if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
            Click_Num = -1;
        if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
        {
            Click_Num = 0;
            Game_Speed = 1.0f;
            pl->Game_Speed = 1.0f;
            for (int i = 0; i < SNIPERCOUNT; i++)
            {
                Sp[i]->Game_Speed = 1.0f;
            }
            for (int i = 0; i < SOLDIERCOUNT; i++)
            {
                Sd[i]->Game_Speed = 1.0f;
            }
            for (int i = 0; i < STORMCOUNT; i++)
            {
                St[i]->Game_Speed = 1.0f;
            }
            for (int i = 0; i < BAZOOKACOUNT; i++)
            {
                Bz[i]->Game_Speed = 1.0f;
            }
            Acs->Game_Speed = 1.0f;
        }
    }
    if (isCollision(Hud->Play2_Box, g_WorldMouse))
    {
        if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
            Click_Num = -1;
        if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
        {
            Click_Num = 0;
            Game_Speed = 2.0f;
            pl->Game_Speed = 2.0f;
            for (int i = 0; i < SNIPERCOUNT; i++)
            {
                Sp[i]->Game_Speed = 2.0f;
            }
            for (int i = 0; i < SOLDIERCOUNT; i++)
            {
                Sd[i]->Game_Speed = 2.0f;
            }
            for (int i = 0; i < STORMCOUNT; i++)
            {
                St[i]->Game_Speed = 2.0f;
            }
            for (int i = 0; i < BAZOOKACOUNT; i++)
            {
                Bz[i]->Game_Speed = 2.0f;
            }
            Acs->Game_Speed = 2.0f;
        }
    }
    if (isCollision(Hud->Stop_Box, g_WorldMouse))
    {
        if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
            Click_Num = -1;
        if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
        {
            Click_Num = 0;
            Game_Speed = 0.0f;
            pl->Game_Speed = 0.0f;
            for (int i = 0; i < SNIPERCOUNT; i++)
            {
                Sp[i]->Game_Speed = 0.0f;
            }
            for (int i = 0; i < SOLDIERCOUNT; i++)
            {
                Sd[i]->Game_Speed = 0.0f;
            }
            for (int i = 0; i < STORMCOUNT; i++)
            {
                St[i]->Game_Speed = 0.0f;
            }
            for (int i = 0; i < BAZOOKACOUNT; i++)
            {
                Bz[i]->Game_Speed = 0.0f;
            }
            Acs->Game_Speed = 0.0f;
        }
    }

    //hud2
    if (isCollision(Hud2->HitBox_OK, g_WorldMouse))
    {
        if (INPUT->KeyDown(VK_RBUTTON) and Click_Num == 0)
            Click_Num = -1;
        if (INPUT->KeyUp(VK_RBUTTON) and Click_Num == -1)
        {
            Click_Num = 0;
            Npc2[2]->isClick = false;
        }
    }

    //Bar
    Hud->Hp_Bar->Scale.x = 70.0f / 10.0f * pl->Health;
    Hud->Armor_Bar->Scale.x = 70.0f / 10.0f * pl->Armor;
    for (int i = 0; i < SNIPERCOUNT; i++)
    {
        Sp[i]->Hp_Bar->Scale.x = 50.0f / 10.0f * Sp[i]->Health;
    }
    for (int i = 0; i < SOLDIERCOUNT; i++)
    {
        Sd[i]->Hp_Bar->Scale.x = 50.0f / 10.0f * Sd[i]->Health;
    }
    for (int i = 0; i < STORMCOUNT; i++)
    {
        St[i]->Hp_Bar->Scale.x = 50.0f / 20.0f * St[i]->Health;
    }
    for (int i = 0; i < BAZOOKACOUNT; i++)
    {
        Bz[i]->Hp_Bar->Scale.x = 50.0f / 10.0f * Bz[i]->Health;
    }
    Acs->Hp_Bar->Scale.x = 100.0f / ACS_Health * Acs->Health;
}

void Scene1::Render()
{
    //tile
    tm->Render();

    //item
    for (int i = 0; i < HEALPACKNUM; i++)
    {
        Heal_Pack[i]->Render();
    }
    for (int i = 0; i < AMMUNITIONNUM; i++)
    {
        Ammu_nition[i]->Render();
    }
    for (int i = 0; i < MONEYNUM; i++)
    {
        Mo_ney[i]->Render();
    }
    for (int i = 0; i < ARMORNUM; i++)
    {
        Ar_mor[i]->Render();
    }
    for (int i = 0; i < QUEST_ITEMNUM; i++)
    {
        QuestItem[i]->Render();
    }

    //obstacle
    for (int i = 0; i < HOUSE1COUNT; i++)
    {
        House_1[i]->Render();
    }
    for (int i = 0; i < HOUSE2COUNT; i++)
    {
        House_2[i]->Render();
    }
    for (int i = 0; i < TREE1COUNT; i++)
    {
        Tree_1[i]->Render();
    }
    for (int i = 0; i < TREE2COUNT; i++)
    {
        Tree_2[i]->Render();
    }
    for (int i = 0; i < ROCKCOUNT; i++)
    {
        Ro_ck[i]->Render();
    }
    for (int i = 0; i < WATCHTOWERCOUNT; i++)
    {
        Watch_Tower[i]->Render();
    }

    

    //enemy
    for (int i = 0; i < SNIPERCOUNT; i++)
    {
        Sp[i]->Render();
    }
    for (int i = 0; i < SOLDIERCOUNT; i++)
    {
        Sd[i]->Render();
    }
    for (int i = 0; i < STORMCOUNT; i++)
    {
        St[i]->Render();
    }
    for (int i = 0; i < BAZOOKACOUNT; i++)
    {
        Bz[i]->Render();
    }

    for (int i = 0; i < NPC1COUNT; i++)
    {
        Npc1[i]->Render();
    }
    for (int i = 0; i < NPC2COUNT; i++)
    {
        Npc2[i]->Render();
    }

    //ride
    Acs->Render();

    //player
    pl->Render();

    //bush
    for (int i = 0; i < BUSHCOUNT; i++)
    {
        Bu_sh[i]->Render();
    }

    //HUD
    Hud->Render();
    if (Npc2[2]->isClick == true)
    {
        Hud2->Render();
    }
    if (Npc2[0]->isClick or Npc2[1]->isClick or Npc2[3]->isClick)
    {
        Huds->Render();
        /*CheckBox->Render();*/
    }
}

void Scene1::TextRender()
{
    //text
    if (Npc2[0]->isClick == false and Npc2[1]->isClick == false and Npc2[3]->isClick == false)
    {
        switch (pl->Gun_Kind)
        {
        case 0:
            SPRITETEXT->RenderText("HAND", L"MAX",
                WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(60.0f, 145.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.8f);
            break;
        case 1:
            SPRITETEXT->RenderText("HAND", to_wstring(pl->MG_Bullet_Num) + L"/" + to_wstring(500),
                WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(60.0f, 145.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.8f);
            break;
        case 2:
            SPRITETEXT->RenderText("HAND", to_wstring(pl->R_Bullet_Num) + L"/" + to_wstring(300),
                WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(60.0f, 145.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.8f);
            break;
        case 3:
            SPRITETEXT->RenderText("HAND", to_wstring(pl->GL_Bullet_Num) + L"/" + to_wstring(30),
                WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(60.0f, 145.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.8f);
            break;
        case 4:
            SPRITETEXT->RenderText("HAND", to_wstring(pl->FT_Bullet_Num) + L"/" + to_wstring(500),
                WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(60.0f, 145.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.8f);
            break;
        }
        SPRITETEXT->RenderText("HAND", to_wstring(pl->Money),
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(335.0f, 35.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.6f);
    }
    
    
    SPRITETEXT->RenderText("HAND", L"Quest",
        WorldToScreen(MAINCAM->Pos, Npc2[0]->GetPos()) + Vector2(-28.0f,-40.0f), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.6f);
    SPRITETEXT->RenderText("HAND", L"Practice",
        WorldToScreen(MAINCAM->Pos, Npc2[1]->GetPos()) + Vector2(-32.0f, -40.0f), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.6f);
    SPRITETEXT->RenderText("HAND", L"Weapon",
        WorldToScreen(MAINCAM->Pos, Npc2[2]->GetPos()) + Vector2(-28.0f, -40.0f), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.6f);
    SPRITETEXT->RenderText("HAND", L"Vehicle",
        WorldToScreen(MAINCAM->Pos, Npc2[3]->GetPos()) + Vector2(-28.0f, -40.0f), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.6f);

    //Gunshop
    if (Npc2[2]->isClick == true)
    {
        //upgrade
        SPRITETEXT->RenderText("HAND", to_wstring(Hud2->Upgrade_P),
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(185.0f, 500.0f)), Color(1.0f - Hud2->Upgrade_P * 0.2f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.6f);
        SPRITETEXT->RenderText("HAND", to_wstring(Hud2->Upgrade_R),
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(386.0f, 500.0f)), Color(1.0f - Hud2->Upgrade_R * 0.2f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.6f);
        SPRITETEXT->RenderText("HAND", to_wstring(Hud2->Upgrade_MG),
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(591.0f, 500.0f)), Color(1.0f - Hud2->Upgrade_MG * 0.2f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.6f);
        SPRITETEXT->RenderText("HAND", to_wstring(Hud2->Upgrade_GT),
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(185.0f, 370.0f)), Color(1.0f - Hud2->Upgrade_GT * 0.2f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.6f);
        SPRITETEXT->RenderText("HAND", to_wstring(Hud2->Upgrade_FT),
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(386.0f, 370.0f)), Color(1.0f - Hud2->Upgrade_FT * 0.2f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.6f);
        SPRITETEXT->RenderText("HAND", L"300G",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(120.0f, 522.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.6f);
        SPRITETEXT->RenderText("HAND", L"800G",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(120.0f, 392.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.6f);
        SPRITETEXT->RenderText("HAND", L"500G",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(320.0f, 522.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.6f);
        SPRITETEXT->RenderText("HAND", L"800G",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(320.0f, 392.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.6f);
        SPRITETEXT->RenderText("HAND", L"500G",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(520.0f, 522.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.6f);
        SPRITETEXT->RenderText("HAND", L"300G",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(320.0f, 277.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.6f);
        SPRITETEXT->RenderText("HAND", L"300G",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(120.0f, 277.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.6f);
        SPRITETEXT->RenderText("HAND", L"MG BULLET",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(510.0f, 462.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.5f);
        SPRITETEXT->RenderText("HAND", L"R BULLET",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(510.0f, 440.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.5f);
        SPRITETEXT->RenderText("HAND", L"GL BULLET",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(510.0f, 415.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.5f);
        SPRITETEXT->RenderText("HAND", L"FT BULLET",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(510.0f, 395.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 0.5f);

        //SPRITETEXT->RenderText("HAND", L"Well, Hello?... Do you want to buy?",
        //    WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }

    //Vechicle Shop
    if (Npc2[3]->isClick == true and !QuestItem[1]->isEat)
    {
        SPRITETEXT->RenderText("HAND", L"Hi! Do you need something?",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }
    if (Npc2[3]->isClick == true and QuestItem[1]->isEat)
    {
        SPRITETEXT->RenderText("HAND", L"I've been ordered to give the tank to Captain Mac.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 120.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
        SPRITETEXT->RenderText("HAND", L"Tank rides into SPACE and descends to '0'. You can also adjust the barrel angle with Q and E.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }

    //Quest
    if (Npc2[0]->isClick == true and Progress_Num == 0)
    {
        SPRITETEXT->RenderText("HAND", L"nice to meet you I'm Mac the captain of this military base.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 100.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }
    if (Npc2[0]->isClick == true and Progress_Num == 1)
    {
        SPRITETEXT->RenderText("HAND", L"You must be a mercenary.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 120.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
        SPRITETEXT->RenderText("HAND", L"Come and receive training from the training instructor on the right.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }
    if (Npc2[1]->isClick == true and Progress_Num == 2)
    {
        SPRITETEXT->RenderText("HAND", L"Hey, are you here for new training?",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 120.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
        SPRITETEXT->RenderText("HAND", L"I'll teach you a simple way to fight",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }
    if (Npc2[1]->isClick == true and Progress_Num == 3)
    {
        SPRITETEXT->RenderText("HAND", L"Press Q to switch to the next weapon and E to switch to the previous weapon.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 120.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
        SPRITETEXT->RenderText("HAND", L"Each weapon has different damage and range. Upgrades can be done in the shop below.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }
    if (Npc2[1]->isClick == true and Progress_Num == 4)
    {
        SPRITETEXT->RenderText("HAND", L"Press Q to switch to the next weapon and E to switch to the previous weapon.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 120.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
        SPRITETEXT->RenderText("HAND", L"Each weapon has different damage and range. Upgrades can be done in the shop below.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }
    if (Npc2[1]->isClick == true and Progress_Num == 5)
    {
        SPRITETEXT->RenderText("HAND", L"Each enemy has a different field of vision depending on which direction you look.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 120.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
        SPRITETEXT->RenderText("HAND", L"If you don't see it, you won't be noticed, so you have to use it wisely.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }
    if (Npc2[1]->isClick == true and Progress_Num == 6)
    {
        SPRITETEXT->RenderText("HAND", L"Also, even if you enter the field of vision,",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 120.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
        SPRITETEXT->RenderText("HAND", L" the enemy won't find you if you're in the bush you see below.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }
    if (Npc2[1]->isClick == true and Progress_Num ==7)
    {
        SPRITETEXT->RenderText("HAND", L"If you get caught, be careful because hiding is meaningless.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 120.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
        SPRITETEXT->RenderText("HAND", L"When you shoot, you and the enemy you hit can recognize you.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }
    if (Npc2[1]->isClick == true and Progress_Num == 8)
    {
        SPRITETEXT->RenderText("HAND", L"Enemies' bullets cannot penetrate the rocky object below.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 120.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
        SPRITETEXT->RenderText("HAND", L"So, when a melee starts, cover up behind a place like that and fight.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }
    if (Npc2[1]->isClick == true and Progress_Num == 9)
    {
        SPRITETEXT->RenderText("HAND", L"train below",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 120.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
        SPRITETEXT->RenderText("HAND", L"When you're ready, go back to General Mac.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }
    if (Npc2[0]->isClick == true and Progress_Num == 10)
    {
        SPRITETEXT->RenderText("HAND", L"Looks like you got all the basic training",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 120.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
        SPRITETEXT->RenderText("HAND", L"I'll give you the first task.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }
    if (Npc2[0]->isClick == true and Progress_Num == 11)
    {
        SPRITETEXT->RenderText("HAND", L"Follow the road to the west and you'll see a rebel base.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 120.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
        SPRITETEXT->RenderText("HAND", L"There are supplies the rebels stole from us. bring it.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }
    if (Npc2[0]->isClick == true and Progress_Num == 12 and QuestItem[0]->isEat)
    {
        SPRITETEXT->RenderText("HAND", L"oh i got. it good job. here's the reward.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 120.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
        SPRITETEXT->RenderText("HAND", L"Money can be used in the shop on the lower right.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }
    if (Npc2[0]->isClick == true and Progress_Num == 13)
    {
        SPRITETEXT->RenderText("HAND", L"oh i got. it good job. here's the reward.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 120.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
        SPRITETEXT->RenderText("HAND", L"Money can be used in the shop on the lower right.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }
    if (Npc2[0]->isClick == true and Progress_Num == 14)
    {
        SPRITETEXT->RenderText("HAND", L"You should follow the road leading down to the rebel base we just went to.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 120.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
        SPRITETEXT->RenderText("HAND", L"He defended it quite well. Get supplies from there.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }
    if (Npc2[0]->isClick == true and Progress_Num == 15 and QuestItem[1]->isEat)
    {
        SPRITETEXT->RenderText("HAND", L"It must have been difficult to sneak in, but that's great.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 120.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
        SPRITETEXT->RenderText("HAND", L"here's the reward. I added some more this time.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }
    if (Npc2[0]->isClick == true and Progress_Num == 16)
    {
        SPRITETEXT->RenderText("HAND", L"There's a sizable rebel base on the southeast coast.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 120.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
        SPRITETEXT->RenderText("HAND", L"Kill all the enemies there and bring the supplies.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }
    if (Npc2[0]->isClick == true and Progress_Num == 17)
    {
        SPRITETEXT->RenderText("HAND", L"Before you go, get a tank from the Quartermaster south of our base.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 120.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
        SPRITETEXT->RenderText("HAND", L"Powerful but very vulnerable to certain enemies, so be careful. Good luck.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }
    if (Npc2[0]->isClick == true and Progress_Num == 18 and QuestItem[2]->isEat)
    {
        SPRITETEXT->RenderText("HAND", L"Brilliant! Get this.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 120.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
        SPRITETEXT->RenderText("HAND", L"Now go free. thank you again.",
            WorldToScreen(MAINCAM->Pos, MAINCAM->Pos + Vector2(50.0f, 80.0f)), Color(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f), 1.0f);
    }
}
