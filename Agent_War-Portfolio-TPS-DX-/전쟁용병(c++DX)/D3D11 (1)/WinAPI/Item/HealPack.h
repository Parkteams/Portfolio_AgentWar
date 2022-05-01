#pragma once
class HealPack : public Item
{
private:
	ObImage* Heal_Pack;

	int Heal;

public:
    ObRect* HitBox;
    HealPack();
    ~HealPack();

    void Update();
    void Render();
};

