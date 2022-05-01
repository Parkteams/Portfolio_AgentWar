#include "stdafx.h"
#include "Obstacle.h"
#include "WatchTower.h"

WatchTower::WatchTower()
{
    isHit = false;
    isCharge = true;
    Watch_Tower = new ObImage(L"Image/TDS/Object/WatchTower.png");
    Watch_Tower->Scale = Vector2(150.0f, 150.0f);
    Watch_Tower->P = &Root->RT;

    HitBox = new ObRect();
    HitBox->isFill = false;
    HitBox->Scale = Vector2(150.0f, 150.0f);
    HitBox->Pivot = Vector2(0.0f, 0.0f);
    HitBox->P = &Root->RT;

    //WatchTower Range
    Sight = new ObCircle();
    Sight->isFill = false;
    Sight->Scale = Vector2(300.0f, 300.0f);
    Sight->P = &Root->RT;

    Alarm = new ObCircle();
    Alarm->isFill = false;
    Alarm->Scale = Vector2(1000.0f, 1000.0f);
    Alarm->P = &Root->RT;
    Alarm->isActive = false;

    Alarm_Time = 0.0f;

    //Alert
    SOUND->AddSound("Sound/ENEMY/ALERT.wav", "ALERT", false);
}

WatchTower::~WatchTower()
{
    delete Watch_Tower;
    delete HitBox;
    delete Sight;
    delete Alarm;
}

void WatchTower::Update()
{
    if (isHit)
    {
        Watch_Tower->color = Color(0.7f, 0.5f, 0.5f, 0.5f);
        Alarm->isActive = true;
        if (Alarm_Time < 0.1f)
        {
            Alarm_Time += DeltaTime;
        }
        else
        {
            //SOUND->Stop("ALERT");
            //SOUND->Play("ALERT");
            //SOUND->SetVolume("ALERT", 1.0f);
            Alarm->isActive = false;
        }
    }
    

}

void WatchTower::Render()
{
    Obstacle::Render();
    Watch_Tower->Render();
    /*HitBox->Render();
    Sight->Render();
    Alarm->Render();*/
}
