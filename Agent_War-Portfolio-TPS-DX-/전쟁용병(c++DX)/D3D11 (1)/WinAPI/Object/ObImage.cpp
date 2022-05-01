#include "stdafx.h"
#include "ObImage.h"



ObImage::ObImage(wstring file)
{
    //기본 샘플러 값
    SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

    SamplerDesc.MipLODBias = 0.0f;
    SamplerDesc.MaxAnisotropy = 1;
    SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    SamplerDesc.MinLOD = -FLT_MAX;
    SamplerDesc.MaxLOD = FLT_MAX;

    //하나 이상의 샘플러 만들어 두기
    g_Device->CreateSamplerState(&SamplerDesc, &Sampler);

    //텍스쳐 로드
    SRV = TEXTURE->LoadTexture(file);

    //           (최소좌표)   (최대좌표)
    UV = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
}

ObImage::~ObImage()
{
    Sampler->Release();
    //SRV->Release();
}

void ObImage::Render()
{
    if (!isActive)return;
    Object::WorldUpdate();
    Object::Render();

    ImageShader->SetShader();

    UINT stride = sizeof(VertexPT);
    UINT offset = 0;

    PlayAnim();

    g_DeviceContext->UpdateSubresource(UVBuffer, 0, NULL, &UV, 0, 0);


    //픽셀쉐이더에 쉐이더자원값 세팅
    g_DeviceContext->PSSetShaderResources(0,// 연결될레지스터 번호 0
        1,//리소스갯수
        &SRV);

    //연결될레지스터 번호 0
    g_DeviceContext->PSSetSamplers(0,
        1, //리소스갯수
        &Sampler);//샘플러

    g_DeviceContext->IASetVertexBuffers(0,
        1,
        &VertexBuffer,
        &stride,
        &offset);
    g_DeviceContext->IASetPrimitiveTopology
    (D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    g_DeviceContext->OMSetBlendState(BlendStateOn, NULL, 0xFF);
    g_DeviceContext->Draw(4, 0);
    g_DeviceContext->OMSetBlendState(BlendStateOff, NULL, 0xFF);
}
ID3D11Buffer* ObImage::VertexBuffer = nullptr;
ID3D11Buffer* ObImage::UVBuffer = nullptr;
void ObImage::CreateStaticMember()
{
    VertexPT* Vertex;

    Vertex = new VertexPT[4];
    //VertexCount = 4;
    //시계방향으로 정점찍기
    Vertex[0].Position.x = -0.5f;
    Vertex[0].Position.y = -0.5f;
    Vertex[0].Uv = Vector2(0.0f, 1.0f);

    Vertex[1].Position.x = -0.5f;
    Vertex[1].Position.y = 0.5f;
    Vertex[1].Uv = Vector2(0.0f, 0.0f);

    Vertex[2].Position.x = 0.5f;
    Vertex[2].Position.y = -0.5f;
    Vertex[2].Uv = Vector2(1.0f, 1.0f);

    Vertex[3].Position.x = 0.5f;
    Vertex[3].Position.y = 0.5f;
    Vertex[3].Uv = Vector2(1.0f, 0.0f);


    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//버퍼를 읽고 쓰는 방법
        desc.ByteWidth = sizeof(VertexPT) * 4; //버퍼 크기 (바이트)입니다.
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//버퍼가 파이프 라인에 바인딩되는 방법을 식별하십시오

        D3D11_SUBRESOURCE_DATA data = { 0 };
        //하위 리소스를 초기화하기위한 데이터를 지정합니다.
        data.pSysMem = Vertex;
        //초기화 데이터의 포인터.

        //버퍼 만들기
        HRESULT hr = g_Device->CreateBuffer(&desc, &data, &VertexBuffer);
        assert(SUCCEEDED(hr));
    }

    delete[] Vertex;


    //CreateConstantBuffer
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = sizeof(Vector4);
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;

        HRESULT hr = g_Device->CreateBuffer(&desc, NULL, &UVBuffer);
        assert(SUCCEEDED(hr));
    }
    //                            연결될레지스터 번호3
    g_DeviceContext->VSSetConstantBuffers(3, 1, &UVBuffer);
}

void ObImage::DeleteStaticMember()
{
    VertexBuffer->Release();
    UVBuffer->Release();
}

void ObImage::ChangeFilter(Sampling sam)
{
    if (sam == _POINT)
    {
        SamplerDesc.Filter =
            D3D11_FILTER_MIN_MAG_MIP_POINT;
        Sampler->Release();
        //새로 다시 만들기
        g_Device->CreateSamplerState(&SamplerDesc, &Sampler);
    }
    else if (sam == _LINEAR)
    {
        SamplerDesc.Filter =
            D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        Sampler->Release();
        //새로 다시 만들기
        g_Device->CreateSamplerState(&SamplerDesc, &Sampler);
    }
}

void ObImage::ChangeAddress(Sampling sam)
{
    if (sam == _CLAMP)
    {
        SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
        SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
        SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

        Sampler->Release();
        //새로 다시 만들기
        g_Device->CreateSamplerState(&SamplerDesc, &Sampler);
    }
    else if (sam == _WRAP)
    {
        SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

        Sampler->Release();
        //새로 다시 만들기
        g_Device->CreateSamplerState(&SamplerDesc, &Sampler);
    }
    else if (sam == _MIRROR)
    {
        SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
        SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
        SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
        Sampler->Release();
        //새로 다시 만들기
        g_Device->CreateSamplerState(&SamplerDesc, &Sampler);
    }
}

void ObImage::PlayAnim()
{
    //분할갯수가 1이상일때
    if (MaxFrame.x != 1 or MaxFrame.y != 1)
    {
        //정지가 아닌경우에만
        if (AnimState != _STOP)
        {
            //시간 경과량
            AnimTime += DeltaTime;
            //다음 프레임으로 이동
            if (AnimTime > AnimInterval)
            {
                AnimTime -= AnimInterval;
                //가로축 재생인가?
                if (AnimXAxis)
                {
                    //정방향 재생
                    if (AnimState == _LOOP)
                    {
                        Frame.x++;
                        if (Frame.x == MaxFrame.x)Frame.x = 0;
                    }
                    //역방향 재생
                    else if (AnimState == _REVERSE_LOOP)
                    {
                        Frame.x--;
                        if (Frame.x == -1)Frame.x = MaxFrame.x - 1;
                    }
                    //정방향 재생
                    else if (AnimState == _ONCE)
                    {
                        Frame.x++;
                        if (Frame.x == MaxFrame.x)
                        {
                            AnimState = _STOP;
                            Frame.x = MaxFrame.x - 1;
                        }
                    }
                    //역방향 재생
                    else if (AnimState == _REVERSE_ONCE)
                    {
                        Frame.x--;
                        if (Frame.x == -1)
                        {
                            AnimState = _STOP;
                            Frame.x = 0;
                        }
                    }
                }
                //세로축 재생인가?
                else
                {
                    //정방향 재생
                    if (AnimState == _LOOP)
                    {
                        Frame.y++;
                        if (Frame.y == MaxFrame.y)Frame.y = 0;
                    }
                    //역방향 재생
                    else if (AnimState == _REVERSE_LOOP)
                    {
                        Frame.y--;
                        if (Frame.y == -1)Frame.y = MaxFrame.y - 1;
                    }
                    //정방향 재생
                    else if (AnimState == _ONCE)
                    {
                        Frame.y++;
                        if (Frame.y == MaxFrame.y)
                        {
                            AnimState = _STOP;
                            Frame.y = MaxFrame.y - 1;
                        }
                    }
                    //역방향 재생
                    else if (AnimState == _REVERSE_ONCE)
                    {
                        Frame.y--;
                        if (Frame.y == -1)
                        {
                            AnimState = _STOP;
                            Frame.y = 0;
                        }
                    }
                }
            }

        }
        //핵심 분할갯수,현재좌표로 UV를 만든다
        UV.x = Frame.x / (float)MaxFrame.x;
        UV.z = (Frame.x + 1.0f) / (float)MaxFrame.x;
        UV.y = Frame.y / (float)MaxFrame.y;
        UV.w = (Frame.y + 1.0f) / (float)MaxFrame.y;
    }
}

void ObImage::ChangeAnim(Animation anim, float interval, bool XAxis)
{
    AnimTime = 0.0f;    //재생시간 0으로 초기화
    AnimState = anim;   //상태값 대입
    AnimXAxis = XAxis;  //재생축 대입
    AnimInterval = interval; //재생간격 대입
    //한번 재생이라면(시트 맨 앞이미지로 이동)
    if (AnimState == _ONCE)
    {
        if (XAxis)
        {
            Frame.x = 0;
        }
        else
        {
            Frame.y = 0;
        }
    }
    if (AnimState == _REVERSE_ONCE)
    {
        if (XAxis)
        {
            Frame.x = MaxFrame.x - 1;
        }
        else
        {
            Frame.y = MaxFrame.y - 1;
        }
    }
}

void ObImage::ChangeImage(wstring file, Int2 maxFrame)
{
    SRV = TEXTURE->LoadTexture(file);
    MaxFrame = maxFrame;
}
