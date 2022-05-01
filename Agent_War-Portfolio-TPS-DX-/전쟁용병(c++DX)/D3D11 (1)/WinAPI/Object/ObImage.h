#pragma once

enum Sampling
{
    //filter
    _POINT,         //���ػ�(�ȼ��̹���)�� ��︮�� ����
    _LINEAR,        //���ػ󵵿� ��︮�� ����
    //address mode
    _CLAMP,
    _WRAP,
    _MIRROR
};

enum Animation
{
    _STOP,      //����
    _LOOP,      //�ݺ����
    _ONCE,      //�ѹ����
    _REVERSE_LOOP,//���ݺ����
    _REVERSE_ONCE,//
};

class ObImage : public Object
{
private:
    static ID3D11Buffer* VertexBuffer;
    static ID3D11Buffer* UVBuffer;
    ID3D11ShaderResourceView*   SRV;
    ID3D11SamplerState*         Sampler;//s0
    D3D11_SAMPLER_DESC	        SamplerDesc;
    float                       AnimTime = 0.0f;
    Animation                   AnimState = _STOP;
    float                       AnimInterval = 0.0f; //�������
    bool                        AnimXAxis = true;   //�������?
    //                          ���ο��� �����ų �Լ�
    void                        PlayAnim();
public:
    Vector4         UV;
    Int2            MaxFrame{ 1,1 };   //���� ����
    Int2            Frame{ 0,0 };      //���� ����� ��ǥ
   
    ObImage(wstring file);
    ~ObImage();

    void Render();
    static void CreateStaticMember();
    static void DeleteStaticMember();
    //���ø� ü����
    void ChangeFilter(Sampling sam);
    void ChangeAddress(Sampling sam);
    //�ִϸ��̼� �Լ�              �󸶰���
    void ChangeAnim(Animation anim, float interval, bool XAxis = true);
    //�̹��� �ٲٱ� �Լ�
    void ChangeImage(wstring file, Int2 maxFrame = Int2(1, 1));
};

