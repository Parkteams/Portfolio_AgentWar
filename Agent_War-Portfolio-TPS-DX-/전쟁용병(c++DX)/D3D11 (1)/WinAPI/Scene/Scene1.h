#pragma once
class Player;
class Sniper;
class Soldier;
class Storm;
class Bazooka;
class ACS;
class NPC1;
class NPC2;
class HealPack;
class Ammunition;
class Money;
class Armor;
class Quest_Item;
class House1;
class House2;
class Tree1;
class Tree2;
class Rock;
class Bush;
class WatchTower;
class TileMap;
class Tile;
class HUD;
class Weapon_Shop;

#define HEALPACKNUM 3
#define AMMUNITIONNUM 5
#define ARMORNUM 2
#define MONEYNUM 8
#define QUEST_ITEMNUM 3
#define SNIPERCOUNT 10
#define SOLDIERCOUNT 7
#define STORMCOUNT 18
#define BAZOOKACOUNT 3
#define NPC1COUNT 6
#define NPC2COUNT 4
#define HOUSE1COUNT 11
#define HOUSE2COUNT 21
#define TREE1COUNT 2
#define TREE2COUNT 2
#define ROCKCOUNT 11
#define BUSHCOUNT 34
#define WATCHTOWERCOUNT 8

class Scene1 : public Scene
{
private:
    float Camera_Speed;

    ObImage* Huds;
    ObRect* CheckBox;
    TileMap*    tm;
    HUD*                Hud;
    Weapon_Shop*        Hud2;
    Player*     pl;
    //enemy
    Sniper* Sp[SNIPERCOUNT];
    Soldier* Sd[SOLDIERCOUNT];
    Storm* St[STORMCOUNT];
    Bazooka* Bz[BAZOOKACOUNT];

    //NPC
    NPC1* Npc1[NPC1COUNT];
    NPC2* Npc2[NPC2COUNT];

    //ride
    ACS* Acs;

    //item
    HealPack*   Heal_Pack[HEALPACKNUM];
    Ammunition* Ammu_nition[AMMUNITIONNUM];
    Money*      Mo_ney[MONEYNUM];
    Armor* Ar_mor[ARMORNUM];
    Quest_Item* QuestItem[QUEST_ITEMNUM];

    //obstacle
    House1*     House_1[HOUSE1COUNT];
    House2*     House_2[HOUSE2COUNT];
    Tree1*      Tree_1[TREE1COUNT];
    Tree2*      Tree_2[TREE2COUNT];
    Rock* Ro_ck[ROCKCOUNT];
    Bush* Bu_sh[BUSHCOUNT];
    WatchTower* Watch_Tower[WATCHTOWERCOUNT];

    //Speed
    float Game_Speed;

    //Mouse
    int Click_Num;

    //Quest
    int Progress_Num;

    bool edit;
    bool Player_Update;

    int BGMCOUNT;
   
public:
    Scene1();
    ~Scene1();
    //순수가상함수는 반드 자식클래스에서 정의해야함
   void Init() override;
   void Update() override;
   void LateUpdate() override;
   void Render() override;
   void TextRender() override;
};

