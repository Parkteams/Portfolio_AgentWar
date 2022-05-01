#include "stdafx.h"
#include "ObStar.h"

void ObStar::Render()
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
        g_DeviceContext->Draw(5 * 3, 0);
        g_DeviceContext->OMSetBlendState(BlendStateOff, NULL, 0xFF);
    }
    else
    {
        g_DeviceContext->IASetVertexBuffers(0,//�Է½���(16~32������ ��������)
            1,//�Է½��Կ� ���̰��� �ϴ� ������ ����
            &VertexBuffer,
            &stride,//���������� �� ������ ����Ʈ���� ũ��
            &offset);
        g_DeviceContext->IASetPrimitiveTopology
        (D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
        g_DeviceContext->OMSetBlendState(BlendStateOn, NULL, 0xFF);
        g_DeviceContext->Draw(6, 0);
        g_DeviceContext->OMSetBlendState(BlendStateOff, NULL, 0xFF);
    }
}
ID3D11Buffer* ObStar::FillVertexBuffer = nullptr;
ID3D11Buffer* ObStar::VertexBuffer = nullptr;
void ObStar::CreateStaticMember()
{
    VertexPC* Vertex;
    //ä��� �� ��ŵ

    Vertex = new VertexPC[5 * 3];

    for (UINT i = 0; i < 5; i++)
    {
        Vertex[i * 3].Position.x = 0.0f;
        Vertex[i * 3].Position.y = 0.0f;

        Vertex[i * 3 + 1].Position.x = cosf(i * 144.0f * TORADIAN) * 0.5f;
        Vertex[i * 3 + 1].Position.y = sinf(i * 144.0f * TORADIAN) * 0.5f;

        Vertex[i * 3 + 2].Position.x = cosf((i + 1) * 144.0f * TORADIAN) * 0.5f;
        Vertex[i * 3 + 2].Position.y = sinf((i + 1) * 144.0f * TORADIAN) * 0.5f;

        Vertex[i * 3].color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        Vertex[i * 3 + 1].color = Color(0.0f, 0.0f, 0.0f, 1.0f);
        Vertex[i * 3 + 2].color = Color(0.0f, 0.0f, 0.0f, 1.0f);
        
    }
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//���۸� �а� ���� ���
        desc.ByteWidth = sizeof(VertexPC) * 5 * 3; //���� ũ�� (����Ʈ)�Դϴ�.
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//���۰� ������ ���ο� ���ε��Ǵ� ����� �ĺ��Ͻʽÿ�

        D3D11_SUBRESOURCE_DATA data = { 0 };
        //���� ���ҽ��� �ʱ�ȭ�ϱ����� �����͸� �����մϴ�.
        data.pSysMem = Vertex;
        //�ʱ�ȭ �������� ������.

        //���� �����
        HRESULT hr = g_Device->CreateBuffer(&desc, &data, &FillVertexBuffer);
        assert(SUCCEEDED(hr));

    }

    delete[] Vertex;

    //���� �׸��� ��

    Vertex = new VertexPC[6];

    //�ΰ��� ������ �� �����
    for (UINT i = 0; i < 6; i++)
    {
        Vertex[i].color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        Vertex[i].Position.x = cosf(i * 144.0f * TORADIAN) * 0.5f;
        Vertex[i].Position.y = sinf(i * 144.0f * TORADIAN) * 0.5f;
    }


    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//���۸� �а� ���� ���
        desc.ByteWidth = sizeof(VertexPC) * 6; //���� ũ�� (����Ʈ)�Դϴ�.
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//���۰� ������ ���ο� ���ε��Ǵ� ����� �ĺ��Ͻʽÿ�

        D3D11_SUBRESOURCE_DATA data = { 0 };
        //���� ���ҽ��� �ʱ�ȭ�ϱ����� �����͸� �����մϴ�.
        data.pSysMem = Vertex;
        //�ʱ�ȭ �������� ������.

        //���� �����
        HRESULT hr = g_Device->CreateBuffer(&desc, &data, &VertexBuffer);
        assert(SUCCEEDED(hr));

    }
    delete[] Vertex;
}

void ObStar::DeleteStaticMember()
{
    VertexBuffer->Release();
    FillVertexBuffer->Release();
}
