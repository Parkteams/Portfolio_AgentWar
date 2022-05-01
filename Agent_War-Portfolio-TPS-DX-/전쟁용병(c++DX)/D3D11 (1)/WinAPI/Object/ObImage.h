#pragma once

enum Sampling
{
    //filter
    _POINT,         //저해상도(픽셀이미지)에 어울리는 필터
    _LINEAR,        //고해상도에 어울리는 필터
    //address mode
    _CLAMP,
    _WRAP,
    _MIRROR
};

enum Animation
{
    _STOP,      //정지
    _LOOP,      //반복재생
    _ONCE,      //한번재생
    _REVERSE_LOOP,//역반복재생
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
    float                       AnimInterval = 0.0f; //재생간격
    bool                        AnimXAxis = true;   //가로재생?
    //                          내부에서 재생시킬 함수
    void                        PlayAnim();
public:
    Vector4         UV;
    Int2            MaxFrame{ 1,1 };   //분할 갯수
    Int2            Frame{ 0,0 };      //현재 출력할 좌표
   
    ObImage(wstring file);
    ~ObImage();

    void Render();
    static void CreateStaticMember();
    static void DeleteStaticMember();
    //샘플링 체인지
    void ChangeFilter(Sampling sam);
    void ChangeAddress(Sampling sam);
    //애니메이션 함수              얼마간격
    void ChangeAnim(Animation anim, float interval, bool XAxis = true);
    //이미지 바꾸기 함수
    void ChangeImage(wstring file, Int2 maxFrame = Int2(1, 1));
};

