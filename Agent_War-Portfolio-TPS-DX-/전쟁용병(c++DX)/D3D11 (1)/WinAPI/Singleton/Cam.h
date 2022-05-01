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
    VPDESC              VP;          //�� ���        
    ID3D11Buffer*		VPBuffer;    //�� ����
    Viewport            viewport;
public:
    Cam();
    ~Cam();
    void                SetCam();
    //ī�޶���ġ
    Vector2             Pos;
};