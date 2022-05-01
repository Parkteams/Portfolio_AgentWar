#pragma once

class Bush : public Obstacle
{
private:
    ObImage* Bu_sh;


public:
    ObRect* HitBox;
    Bush();
    ~Bush();

    void Update();
    void Render();
};

