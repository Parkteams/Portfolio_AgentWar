#pragma once
class Player;

class NPC2 : public Character
{
private:

    //Player
    Player* pl;

    

public:
	ObRect* HitBox;
    ObCircle* Range;
    ObImage* NPC2_Idle;
    bool isClick;

    float Rotation;

    NPC2();
    ~NPC2();

    void Update();
    void LateUpdate();
    void Render();

    MAKESET(Player*, pl)
};

