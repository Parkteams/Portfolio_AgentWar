#pragma once
class Tree1 : public Obstacle
{
private:
    ObImage* Tree;


public:
    ObRect* HitBox;
    Tree1();
    ~Tree1();

    void Update();
    void Render();
};


