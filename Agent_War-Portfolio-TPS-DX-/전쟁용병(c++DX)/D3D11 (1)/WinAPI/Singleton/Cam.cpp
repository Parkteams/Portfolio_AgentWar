#include "stdafx.h"
#include "Cam.h"

Cam::Cam()
{
    //CreateConstantBuffer
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = sizeof(VPDESC);
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;

        HRESULT hr = g_Device->CreateBuffer(&desc, NULL, &VPBuffer);
        assert(SUCCEEDED(hr));
    }
    
    //첫 카메라 위치
    Pos.x = 0.0f;
    Pos.y = 0.0f;

    up = Vector3(0.0f, 1.0f, 0.0f);
    eye.z = -1.0f;
    look.z = 0.0f;

    viewport.width = WINSIZEX;
    viewport.height = WINSIZEY;
    
    
    //                            연결될레지스터 번호 1
    VP.P = Matrix::CreateOrthographicOffCenter(0.0f, WINSIZEX,
        0.0f, WINSIZEY, 0.0f, 10.0f);
    g_DeviceContext->RSSetViewports(1, viewport.Get11());
    g_DeviceContext->VSSetConstantBuffers(1, 1, &VPBuffer);
}

Cam::~Cam()
{
    VPBuffer->Release();
}

void Cam::SetCam()
{
    eye.x = look.x = Pos.x;
    eye.y = look.y = Pos.y;
    VP.V = Matrix::CreateLookAt(eye, look, up);
    
    
  
    g_DeviceContext->UpdateSubresource(VPBuffer, 0, NULL, &VP, 0, 0);
    
}
