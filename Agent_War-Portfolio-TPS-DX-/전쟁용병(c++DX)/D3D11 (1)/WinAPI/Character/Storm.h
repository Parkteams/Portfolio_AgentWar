#pragma once
class Player;
class ACS;
class TileMap;
class Tile;

enum StormState
{
    ST_IDLE,
    ST_MOVE,
    ST_SHOT,
    ST_DEAD,
    ST_ALERT,
    ST_BACK

};

struct Storm_Bullet
{
    ObImage* Storm_Bullet;
    ObRect* Hitbox;
    float Speed;
    int Power;
    Vector2 Dir;
};

class Storm : public Character
{
private:
    TileMap* tm;

    ObImage* Storm_Idle;
    ObImage* Storm_Move;
    ObImage* Storm_Die;
    ObImage* Storm_Shot;
    ObImage* Storm_Shot_Effect;
    

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
    int      StormState;
    //bullet
    Storm_Bullet SB[30];
    //Rotate
    float Rotation;

    //Stat
    int Health;

    //time
    float   g_speed;

    bool isAlarm;

    bool isCharge;

    ObRect* HitBox;
    ObRect* Hp_Bar;
    Storm();
    ~Storm();

    void Update();
    void LateUpdate();
    void Render();
    MAKESET(Player*, pl)
    MAKESET(TileMap*, tm)
    MAKESET(ACS*, Acs)
};

