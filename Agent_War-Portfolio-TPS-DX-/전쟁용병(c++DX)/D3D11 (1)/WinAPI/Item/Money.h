#pragma once
class Money : public Item
{
private:
    ObImage* Mo_ney;

    int Amount;

public:
    ObRect* HitBox;
    Money();
    ~Money();

    void Update();
    void Render();
};

