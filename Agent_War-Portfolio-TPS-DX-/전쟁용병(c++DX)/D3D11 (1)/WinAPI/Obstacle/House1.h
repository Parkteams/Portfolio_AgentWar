#pragma once

class House1 : public Obstacle
{
private:
    ObImage* House;
    

public:
    ObRect* HitBox;
    House1();
    ~House1();

    void Update();
    void Render();
};

