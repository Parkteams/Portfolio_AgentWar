#pragma once
class Tree2 : public Obstacle
{
private:
    ObImage* Tree;


public:
    ObRect* HitBox;
    Tree2();
    ~Tree2();

    void Update();
    void Render();
};

