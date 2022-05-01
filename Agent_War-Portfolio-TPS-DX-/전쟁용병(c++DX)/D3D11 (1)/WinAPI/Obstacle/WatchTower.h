#pragma once

class WatchTower : public Obstacle
{
private:
    ObImage* Watch_Tower;

    float Alarm_Time;

public:
    bool isHit;
    bool isCharge;
    ObRect* HitBox;
    ObCircle* Sight;
    ObCircle* Alarm;

    WatchTower();
    ~WatchTower();

    void Update();
    void Render();
};

