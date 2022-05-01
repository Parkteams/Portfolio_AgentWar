#pragma once
class Timer : public Singleton<Timer>
{

private:
    //���� �����ð�
    chrono::steady_clock::time_point CurrentTime;
    //������ �����ð�
    chrono::steady_clock::time_point LastTime;
    //�����Ӵ� ����ð�
    float deltaTime;

    //������ Ȯ�ο� ����
    UINT  FPS;
    float WorldTime;

    //FPS������ ����
    UINT  FPSCount;
    float FPSTimeElapsed;
public:
    Timer();
    //                  �⺻�Ű������� 60
    void SetFrameRate(UINT lock = 60);
    float GetDeltaTime() { return deltaTime; }

    MAKEGET(UINT, FPS)
    MAKEGET(float, WorldTime)
    //MAKEGET(float, deltaTime)
};