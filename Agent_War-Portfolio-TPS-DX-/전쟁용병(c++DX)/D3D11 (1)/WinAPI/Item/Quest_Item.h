#pragma once
class Quest_Item : public Item
{
private:
    ObImage* QuestItem;

public:
    bool isEat;

    ObRect* HitBox;
    Quest_Item();
    ~Quest_Item();

    void Update();
    void Render();
};

