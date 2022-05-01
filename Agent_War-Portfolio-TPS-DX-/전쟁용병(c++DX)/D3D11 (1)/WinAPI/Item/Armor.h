#pragma once
class Armor : public Item
{
private:
    ObImage* Ar_mor;

    int Amount;

public:
    ObRect* HitBox;
    Armor();
    ~Armor();

    void Update();
    void Render();
};

