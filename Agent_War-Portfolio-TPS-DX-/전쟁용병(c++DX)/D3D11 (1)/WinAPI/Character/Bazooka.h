#pragma once
class Player;
class ACS;

enum BazookaState
{
    Bz_IDLE,
    Bz_SHOT,
    Bz_DEAD,
    Bz_ALERT

};

struct Bazooka_Bullet
{
    ObImage* Bazooka_Bullet;
    ObRect* Hitbox;
    float Speed;
    int Power;
    Vector2 Dir;
};

class Bazooka : public Character
{
private:
    ObImage* Bazooka_Idle;
    ObImage* Bazooka_Die;
    ObImage* Bazooka_Shot;
    ObImage* Bazooka_Shot_Effect;
    

    ObCircle* Shot_Circle;
    ObLine* Shot_Line1;
    ObLine* Shot_Line2;

    //Player
    Player* pl;

    //Ride
    ACS* Acs;

    //time
    float    Shooting_Time;
    float    Reloading_Time;

    //function
    void StateIdle();
    void StateShot();
    void StateDead();
    void StateAlert();

public:
    int      BazookaState;
    //bullet
    Bazooka_Bullet SB[10];

    //Rotate
    float Rotation;

    bool isAlarm;

    //Stat
    int Health;

    ObRect* HitBox;
    ObRect* Hp_Bar;
    Bazooka();
    ~Bazooka();

    void Update();
    void LateUpdate();
    void Render();
    MAKESET(Player*, pl)
    MAKESET(ACS*, Acs)
};

