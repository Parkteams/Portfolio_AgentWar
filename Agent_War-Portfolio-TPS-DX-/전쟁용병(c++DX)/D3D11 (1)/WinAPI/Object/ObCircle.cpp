#include "stdafx.h"
#include "ObCircle.h"

void ObCircle::Render()
{
    if (!isActive)return;
    Object::WorldUpdate();
    Object::Render();

    BasicShader->SetShader();

    UINT stride = sizeof(VertexPC);
    UINT offset = 0;


    if (isFill)
    {
        g_DeviceContext->IASetVertexBuffers(0,
            1,
            &FillVertexBuffer,
            &stride,
            &offset);
        g_DeviceContext->IASetPrimitiveTopology
        (D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        g_DeviceContext->OMSetBlendState(BlendStateOn, NULL, 0xFF);
        g_DeviceContext->Draw(360*3, 0);
        g_DeviceContext->OMSetBlendState(BlendStateOff, NULL, 0xFF);
    }
    else
    {
        g_DeviceContext->IASetVertexBuffers(0,//입력슬롯(16~32개까지 설정가능)
            1,//입력슬롯에 붙이고자 하는 버퍼의 갯수
            &VertexBuffer,
            &stride,//정점버퍼의 한 원소의 바이트단위 크기
            &offset);
        g_DeviceContext->IASetPrimitiveTopology
        (D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
        g_DeviceContext->OMSetBlendState(BlendStateOn, NULL, 0xFF);
        g_DeviceContext->Draw(360, 0);
        g_DeviceContext->OMSetBlendState(BlendStateOff, NULL, 0xFF);
    }
}
ID3D11Buffer* ObCircle::FillVertexBuffer = nullptr;
ID3D11Buffer* ObCircle::VertexBuffer = nullptr;

void ObCircle::CreateStaticMember()
{
    VertexPC* Vertex;
    Vertex = new VertexPC[360 * 3];

    Color col1 = Color(1.0f, 0.0f, 0.0f, 1.0f);
    Color col2 = Color(0.0f, 1.0f, 0.0f, 1.0f);
    Color col3 = Color(0.0f, 0.0f, 1.0f, 1.0f);

    for (UINT i = 0; i < 360; i++)
    {
        Vertex[i * 3].Position.x = 0.0f;
        Vertex[i * 3].Position.y = 0.0f;

        Vertex[i * 3 + 1].Position.x = cosf(i * TORADIAN) * 0.5f;
        Vertex[i * 3 + 1].Position.y = sinf(i * TORADIAN) * 0.5f;

        Vertex[i * 3 + 2].Position.x = cosf((i + 1) * TORADIAN) * 0.5f;
        Vertex[i * 3 + 2].Position.y = sinf((i + 1) * TORADIAN) * 0.5f;

        Vertex[i * 3].color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        Vertex[i * 3+1].color = Color(0.0f, 0.0f, 0.0f, 1.0f);
        Vertex[i * 3+2].color = Color(0.0f, 0.0f, 0.0f, 1.0f);
        //Vertex[i * 3].color = Color(0.333333f, 0.333333f, 0.333333f, 1.0f);

        //if (i < 120)
        //{
        //    //0~1
        //    float k = ((float)i + 0.0f) / 120.0f;
        //    Vertex[i * 3 + 1].color = col2 * k + col1 * (1.0f - k);
        //    k = ((float)i + 1.0f) / 120.0f;
        //    Vertex[i * 3 + 2].color = col2 * k + col1 * (1.0f - k);
        //}
        //else if (i < 240)
        //{
        //    //0~1
        //    float k = ((float)i - 120.0f) / 120.0f;
        //    Vertex[i * 3 + 1].color = col3 * k + col2 * (1.0f - k);
        //    k = ((float)i - 120.0f + 1.0f) / 120.0f;
        //    Vertex[i * 3 + 2].color = col3 * k + col2 * (1.0f - k);
        //}
        //else
        //{
        //    //0~1
        //    float k = ((float)i - 240.0f) / 120.0f;
        //    Vertex[i * 3 + 1].color = col1 * k + col3 * (1.0f - k);
        //    k = ((float)i - 240.0f + 1.0f) / 120.0f;
        //    Vertex[i * 3 + 2].color = col1 * k + col3 * (1.0f - k);
        //}
    }
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//버퍼를 읽고 쓰는 방법
        desc.ByteWidth = sizeof(VertexPC) * 360 * 3; //버퍼 크기 (바이트)입니다.
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//버퍼가 파이프 라인에 바인딩되는 방법을 식별하십시오

        D3D11_SUBRESOURCE_DATA data = { 0 };
        //하위 리소스를 초기화하기위한 데이터를 지정합니다.
        data.pSysMem = Vertex;
        //초기화 데이터의 포인터.

        //버퍼 만들기
        HRESULT hr = g_Device->CreateBuffer(&desc, &data, &FillVertexBuffer);
        assert(SUCCEEDED(hr));

    }
    
    delete[] Vertex;

    Vertex = new VertexPC[360];

    //두가지 랜덤한 색 만들기
    for (UINT i = 0; i < 360; i++)
    {
        Vertex[i].color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        Vertex[i].Position.x = cosf(i * TORADIAN) * 0.5f;
        Vertex[i].Position.y = sinf(i * TORADIAN) * 0.5f;
    }
    

    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//버퍼를 읽고 쓰는 방법
        desc.ByteWidth = sizeof(VertexPC) *360; //버퍼 크기 (바이트)입니다.
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
}

void ObCircle::DeleteStaticMember()
{
    VertexBuffer->Release();
    FillVertexBuffer->Release();
}
