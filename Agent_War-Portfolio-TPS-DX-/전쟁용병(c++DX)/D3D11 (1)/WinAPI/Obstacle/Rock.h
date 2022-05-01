#pragma once

class Rock : public Obstacle
{
private:
    ObImage* Ro_ck;


public:
    ObRect* HitBox;
    Rock();
    ~Rock();

    void Update();
    void Render();
};

