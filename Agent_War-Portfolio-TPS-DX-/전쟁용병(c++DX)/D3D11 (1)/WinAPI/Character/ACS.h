#pragma once
#define ACS_Health 20
class Sniper;
class Soldier;
class Storm;
class Bazooka;
class Player;

enum ACSState
{
    ACS_EMPTY,
    ACS_IDLE,
    ACS_SHOT,
    ACS_DEAD

};

enum ACSMoveState
{
    ACS_MOVE,
    ACS_STAND
};

struct ACS_Bullet
{
    ObImage* ACS_Bullet;
    ObRect* Hitbox;
    ObRect* Hitbox2;
    float Speed;
    float Explode_Time;
    bool Explode;
    int Power;
    Vector2 Dir;
};

class ACS : public Character
{
private:

    ObImage* ACS_Idle_T;
    ObImage* ACS_Idle_B;
    ObImage* ACS_Move_B;
    ObImage* ACS_Die_T;
    ObImage* ACS_Die_B;
    ObImage* ACS_Shot_Effect;
    ObCircle* ACS_Ride;
    int      ACSState;
    int      ACSMoveState;
    Vector2  PrevPos;

    //Player
    Player* pl;

    //Enemy
    Sniper** Sp;
    Soldier** Sd;
    Storm** St;
    Bazooka** Bz;

    //time
    float    Shooting_Time;
    float    Reloading_Time;

    //function
    void Input();
    void StateIdle();
    void StateFire();
    void StateDead();
    void StateEmpty();

    //leg
    void ACSStand();
    void ACSMove();

public:
    //bullet
    ACS_Bullet SB[30];

    //Rotate
    float Rotation;

    //time
    float   g_speed;

    //Stat
    int Health;

    //ride
    bool isRide;

    //aspeed
    float   Input_Power;

    ObRect* HitBox;
    ObRect* Hp_Bar;
    float ACSSpeed;
    float Tile_Speed;
    float ACSRotateSpeed;
    float ACS_TRotateSpeed;
    ACS();
    ~ACS();

    void Update();
    void LateUpdate();
    void Render();
    void Turnback();

    MAKESET(Player*, pl)

   //enemy
   MAKESET(Sniper**, Sp)
   MAKESET(Soldier**, Sd)
   MAKESET(Storm**, St)
   MAKESET(Bazooka**, Bz)
};

