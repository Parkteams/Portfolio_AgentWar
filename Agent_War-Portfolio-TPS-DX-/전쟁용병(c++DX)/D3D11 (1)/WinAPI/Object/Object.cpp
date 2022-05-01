#include "stdafx.h"
#include "Object.h"

Object::Object()
{
    P = nullptr;
    isActive = true;
    Scale = Vector2(1.0f, 1.0f);
    color = Color(0.5f, 0.5f, 0.5f, 0.5f);
    isAxis = false;
    Up = Vector2(0.0f, 1.0f);
    Right = Vector2(1.0f, 0.0f);
    Pivot = Vector2(0.0f, 0.0f);
    CollisionType = COL_NONE;
}


void Object::WorldUpdate()
{
    if (!isActive)return;


    Pi = Matrix::CreateTranslation(Pivot.x, Pivot.y, 0.0f);
    S = Matrix::CreateScale(Scale.x, Scale.y, 1.0f);
    T = Matrix::CreateTranslation(Position.x, Position.y, 0.0f);
    R = Matrix::CreateFromYawPitchRoll(Rotation.y, Rotation.x, Rotation.z);
    R2 = Matrix::CreateFromYawPitchRoll(Rotation2.y, Rotation2.x, Rotation2.z);
    //      이동
    RT = R * T * R2;
    if (P) //부모행렬이 있다면
    {
        RT *= *P;
    }
    W = Pi * S * RT;

    Right = Vector2(RT._11, RT._12);
    Up = Vector2(RT._21, RT._22);
}

void Object::Render()
{
    if (!isActive)return;
    if (isAxis)
    {
        //right
        Axis->Position = GetWorldPos();
        Axis->Rotation.z = DirToRadian(Right);
        Axis->Scale.x = Scale.x;
        Axis->Render();
        //up
        Axis->Position = GetWorldPos();
        Axis->Rotation.z = DirToRadian(Up);
        Axis->Scale.x = Scale.y;
        Axis->Render();
    }
    g_DeviceContext->VSSetConstantBuffers(0, 1, &WBuffer);
    g_DeviceContext->UpdateSubresource(WBuffer, 0, NULL, &W, 0, 0);
    g_DeviceContext->UpdateSubresource(ColorBuffer, 0, NULL, &color, 0, 0);
   
}

ObLine* Object::Axis = nullptr;
ID3D11Buffer* Object::WBuffer = nullptr;
ID3D11Buffer* Object::ColorBuffer = nullptr;
Shader* Object::BasicShader = nullptr;
Shader* Object::ImageShader = nullptr;
ID3D11BlendState* Object::BlendStateOn = nullptr;
ID3D11BlendState* Object::BlendStateOff = nullptr;

void Object::CreateStaticMember()
{
    //CreateConstantBuffer
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = sizeof(Matrix);
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;

        HRESULT hr = g_Device->CreateBuffer(&desc, NULL, &WBuffer);
        assert(SUCCEEDED(hr));
    }
    //CreateConstantBuffer
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = sizeof(Color);
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;

        HRESULT hr = g_Device->CreateBuffer(&desc, NULL, &ColorBuffer);
        assert(SUCCEEDED(hr));
    }
    g_DeviceContext->VSSetConstantBuffers(2, 1, &ColorBuffer);
    BasicShader = new Shader(L"1.Basic");
    ImageShader = new Shader(L"2.Image");
   
    
   

    Axis = new ObLine();

    //알파값 처리
    {
        D3D11_BLEND_DESC desc;
        ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));
        //섞지 않을 BlendStateOff
        desc.RenderTarget[0].BlendEnable = false;
        desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        g_Device->CreateBlendState(&desc, &BlendStateOff);

        //섞어줄 BlendStateOn
        //Dest밑에깔린 Src그려줄
        //dest a= 0.7
        desc.RenderTarget[0].BlendEnable = true;
        //rgb
        desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; //1-0.7 -> 0.3
        desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // 0.7
        desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;// 0.3 * dest + 0.7 *src
        //a
        desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE; // 1
        desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO; // 0
        desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD; // 0 + 1
        g_Device->CreateBlendState(&desc, &BlendStateOn);


    }
   
}
void Object::DeleteStaticMember()
{
    delete Axis;
    delete BasicShader;
    delete ImageShader;
    WBuffer->Release();
    ColorBuffer->Release();
    BlendStateOff->Release();
    BlendStateOn->Release();
}