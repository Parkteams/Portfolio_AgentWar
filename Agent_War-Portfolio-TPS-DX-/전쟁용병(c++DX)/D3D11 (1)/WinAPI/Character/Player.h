#pragma once
class Sniper;
class Soldier;
class Storm;
class Bazooka;

enum PlayerState
{
    PL_PISTOL,
    PL_PISTOLFIRE,
    PL_MG,
    PL_MGFIRE,
    PL_GL,
    PL_GLFIRE,
    PL_FT,
    PL_FTFIRE,
    PL_RIFLE,
    PL_RIFLEFIRE,
    PL_DEAD,
    PL_RIDE
};

enum PlayerMoveState
{
    PL_MOVE,
    PL_STAND
};

struct Pistol_Bullet
{
    ObImage* Pistol_Bullet;
    ObRect* Hitbox;
    float Speed;
    int Power;
    Vector2 Dir;
};

struct Mg_Bullet
{
    ObImage* MG_Bullet;
    ObRect* Hitbox;
    float Speed;
    int Power;
    Vector2 Dir;
};

struct Rifle_Bullet
{
    ObImage* RIFLE_Bullet;
    ObRect* Hitbox;
    float Speed;
    int Power;
    Vector2 Dir;
};

struct GL_Bullet
{
    ObImage* GL_Shot1;
    ObImage* GL_Shot2;
    ObRect* GL_HitBox;
    ObRect* GL_HitBox2;
    float Speed;
    float Explode_Time;
    bool Explode;
    int Power;
    Vector2 Dir;
};

class Player : public Character
{
private:
    ObImage* Move;
    ObImage* Pistol;
    ObImage* Pistol_Fire;
    ObImage* Pistol_Effect;
    ObImage* RIFLE;
    ObImage* RIFLE_Fire;
    ObImage* RIFLE_Effect;
    ObImage* MG;
    ObImage* MG_Fire;
    ObImage* MG_Effect;
    ObImage* GL;
    ObImage* GL_Fire;
    ObImage* Dead;

    
    

    Vector2  PrevPos; //전에 위치값

    //time
    float    Shooting_Time;
    float    Reloading_Time;
    float    Hit_Time;

    //Enemy
    Sniper** Sp;
    Soldier** Sd;
    Storm** St;
    Bazooka** Bz;

    //function
    void Input();
    void StatePistol();
    void StatePistolFire();
    void StateMg();
    void StateMgFire();
    void StateGl();
    void StateGlFire();
    void StateFt();
    void StateFtFire();
    void StateRifle();
    void StateRifleFire();
    void StateDead();
    void StateRide();

    //leg
    void PlayerStand();
    void PlayerMove();

public:
    int      PlayerState;
    int      PlayerMoveState;
    //Stat
    int Health;
    int Armor;
    int Money;
    int Gun_Kind;

    //about gun
    int MG_Bullet_Num;
    int R_Bullet_Num;
    int GL_Bullet_Num;
    int FT_Bullet_Num;

    float P_Range;
    float MG_Range;
    float R_Range;

    bool Hide;

    //hit circle
    ObCircle* Shot_Circle;
    ObCircle* Hit_Circle;

    //bullet
    Pistol_Bullet PB[10];
    Mg_Bullet MB[50];
    Rifle_Bullet RB[30];
    GL_Bullet GB[3];
    ObRect* Fire_HitBox;

    //fire
    ObImage* FT;
    ObImage* FT_Effect;
    ObImage* FT_Fire;

    ObRect* HitBox;
    float PlayerSpeed;
    float Player_Speed;
    Player();
    ~Player();

    void Update();
    void LateUpdate();
    void Render();
    void Turnback();
    //enemy
    MAKESET(Sniper**, Sp)
    MAKESET(Soldier**, Sd)
    MAKESET(Storm**, St)
    MAKESET(Bazooka**, Bz)

};

