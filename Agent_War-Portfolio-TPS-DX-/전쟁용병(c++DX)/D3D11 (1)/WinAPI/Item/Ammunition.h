#pragma once
enum
{
    MG,
    RIFLE,
    GL,
    FT
};

class Ammunition : public Item
{
private:
    ObImage* Ammu_nition;

public:
    int Kind;

    ObRect* HitBox;
    Ammunition();
    ~Ammunition();

    void Update();
    void Render();
};

