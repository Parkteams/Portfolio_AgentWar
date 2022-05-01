#pragma once
class House2 : public Obstacle
{
private:
    ObImage* House;


public:
    ObRect* HitBox;
    House2();
    ~House2();

    void Update();
    void Render();
};

