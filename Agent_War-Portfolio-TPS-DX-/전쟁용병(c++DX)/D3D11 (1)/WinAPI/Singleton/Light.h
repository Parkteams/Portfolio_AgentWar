#pragma once
class Light : public Singleton<Light>
{
private:
    struct PointLight
    {
        Vector2 ScreenPos;      //��ũ����ǥ  //8
        float   Radius;         //������ũ��  //12
        float   select;         //������      //16
        Color   LightColor;     //���� ��     // 16 + 16
        Color   OutColor;       //����� ��
    };
    ID3D11Buffer* LightBuffer;
public:
    PointLight light;
    Light();
    ~Light();
    void        SetLight();

};

