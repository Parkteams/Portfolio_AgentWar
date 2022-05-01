#pragma once
class Light : public Singleton<Light>
{
private:
    struct PointLight
    {
        Vector2 ScreenPos;      //스크린좌표  //8
        float   Radius;         //반지름크기  //12
        float   select;         //조명선택      //16
        Color   LightColor;     //조명 색     // 16 + 16
        Color   OutColor;       //조명밖 색
    };
    ID3D11Buffer* LightBuffer;
public:
    PointLight light;
    Light();
    ~Light();
    void        SetLight();

};

