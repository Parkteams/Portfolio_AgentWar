#pragma once
class Cam : public Singleton<Cam>
{
private:
    struct VPDESC
    {
        Matrix              V;
        Matrix              P;
    };
    Vector3 eye;
    Vector3 look;
    Vector3 up;
    VPDESC              VP;          //뷰 행렬        
    ID3D11Buffer*		VPBuffer;    //뷰 버퍼
    Viewport            viewport;
public:
    Cam();
    ~Cam();
    void                SetCam();
    //카메라위치
    Vector2             Pos;
};