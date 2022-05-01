#include "stdafx.h"
#include "Light.h"

Light::Light()
{
    light.ScreenPos =
        Vector2(WINSIZEX / 2.0f, WINSIZEY / 2.0f);
    //���� ������
    light.Radius = WINSIZEX * 1.5f;
    //�����
    light.LightColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
    //���� ��
    light.OutColor = Color(0.2f, 0.2f, 0.2f, 0.5f);
    //���� 0��
    light.select = 0;

    //CreateConstantBuffer
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = sizeof(PointLight); //16����Ʈ ���
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//�������
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;

        HRESULT hr = g_Device->CreateBuffer(&desc, NULL, &LightBuffer);
        assert(SUCCEEDED(hr));
    }
    //                            ����ɷ������� ��ȣ 0
    g_DeviceContext->PSSetConstantBuffers(0, 1, &LightBuffer);
}

Light::~Light()
{
    LightBuffer->Release();
}

void Light::SetLight()
{
    //�ӽ� ���� �����
    /*ImGui::SliderFloat2("LIGHTPOS",
        (float*)&light.ScreenPos, -800.0f, 800.0f);
    ImGui::SliderFloat("LIGHTRADIUS",
        (float*)&light.Radius, 0.0f, 1200.0f);
    ImGui::ColorEdit4("LIGHTCOLOR",
        (float*)&light.LightColor);
    ImGui::ColorEdit4("OUTCOLOR",
        (float*)&light.OutColor);
    if (ImGui::Button("1.light"))
    {
        light.select = 0.0f;
    }
    if (ImGui::Button("2.light"))
    {
        light.select = 1.0f;
    }*/

    g_DeviceContext->UpdateSubresource(LightBuffer, 0, NULL, &light, 0, 0);
   
}
