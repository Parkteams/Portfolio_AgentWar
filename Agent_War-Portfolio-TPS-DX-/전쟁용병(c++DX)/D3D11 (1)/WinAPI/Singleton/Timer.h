#pragma once
class Timer : public Singleton<Timer>
{

private:
    //현재 측정시간
    chrono::steady_clock::time_point CurrentTime;
    //지난번 측정시간
    chrono::steady_clock::time_point LastTime;
    //프레임당 경과시간
    float deltaTime;

    //측정값 확인용 변수
    UINT  FPS;
    float WorldTime;

    //FPS측정용 변수
    UINT  FPSCount;
    float FPSTimeElapsed;
public:
    Timer();
    //                  기본매개변수값 60
    void SetFrameRate(UINT lock = 60);
    float GetDeltaTime() { return deltaTime; }

    MAKEGET(UINT, FPS)
    MAKEGET(float, WorldTime)
    //MAKEGET(float, deltaTime)
};