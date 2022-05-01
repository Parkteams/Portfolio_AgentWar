#pragma once
class Player;
class ACS;
class TileMap;
class Tile;

enum SoldierState
{
    SD_IDLE,
    SD_MOVE,
    SD_SHOT,
    SD_DEAD,
    SD_ALERT,
    SD_BACK

};

struct Soldier_Bullet
{
    ObImage* Soldier_Bullet;
    ObRect* Hitbox;
    float Speed;
    int Power;
    Vector2 Dir;
};

class Soldier : public Character
{
private:
    TileMap* tm;

    ObImage* Soldier_Idle;
    ObImage* Soldier_Move;
    ObImage* Soldier_Die;
    ObImage* Soldier_Shot;
    ObImage* Soldier_Shot_Effect;
    

    ObCircle* Shot_Circle;
    ObCircle* Look_Circle;
    ObLine* Shot_Line1;
    ObLine* Shot_Line2;

    //길찾기용 변수
    vector<Tile*> PlWay;
    //이동시킬 위치
    Vector2 PlDest;
    Vector2 PlSour;
    //비율
    float   g;

    //Player
    Player* pl;

    //Ride
    ACS* Acs;

    //time
    float    Shooting_Time;
    float    Reloading_Time;
    float    Refresh_Time;

    //function
    void StateIdle();
    void StateMove();
    void StateShot();
    void StateDead();
    void StateAlert();
    void StateBack();

public:
    int      SoldierState;
    //bullet
    Soldier_Bullet SB[30];

    //Rotate
    float Rotation;

    //time
    float   g_speed;

    //Stat
    int Health;

    bool isAlarm;

    ObRect* HitBox;
    ObRect* Hp_Bar;
    Soldier();
    ~Soldier();

    void Update();
    void LateUpdate();
    void Render();
    MAKESET(Player*, pl)
    MAKESET(TileMap*, tm)
        MAKESET(ACS*, Acs)
};

