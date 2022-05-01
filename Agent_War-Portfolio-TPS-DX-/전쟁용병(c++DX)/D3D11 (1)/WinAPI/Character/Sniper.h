#pragma once
class Player;
class ACS;

enum SniperState
{
    SS_IDLE,
    SS_SHOT,
    SS_DEAD,
    SS_ALERT
    
};

struct Sniper_Bullet
{
    ObImage* Sniper_Bullet;
    ObRect* Hitbox;
    float Speed;
    int Power;
    Vector2 Dir;
};

class Sniper : public Character
{
private:
    ObImage* Sniper_Idle;
    ObImage* Sniper_Die;
    ObImage* Sniper_Shot;
    ObImage* Sniper_Shot_Effect;
    

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
    int      SniperState;
    //bullet
    Sniper_Bullet SB[10];

    //Rotate
    float Rotation;

    //Stat
    int Health;
    
    bool isAlarm;

    ObRect* HitBox;
    ObRect* Hp_Bar;
    Sniper();
    ~Sniper();

    void Update();
    void LateUpdate();
    void Render();
    MAKESET(Player*, pl)
    MAKESET(ACS*, Acs)
};

