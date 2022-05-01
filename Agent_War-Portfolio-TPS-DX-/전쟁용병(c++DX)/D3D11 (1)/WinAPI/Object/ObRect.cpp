#include "stdafx.h"
#include "ObRect.h"


void ObRect::Render()
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
        (D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
        g_DeviceContext->OMSetBlendState(BlendStateOn, NULL, 0xFF);
        g_DeviceContext->Draw(4, 0);
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
        g_DeviceContext->Draw(5, 0);
        g_DeviceContext->OMSetBlendState(BlendStateOff, NULL, 0xFF);
    }
   
}
ID3D11Buffer* ObRect::FillVertexBuffer = nullptr;
ID3D11Buffer* ObRect::VertexBuffer = nullptr;

void ObRect::CreateStaticMember()
{
    VertexPC* Vertex;

    Vertex = new VertexPC[4];
    //VertexCount = 4;
    //�ð�������� �������
    Vertex[0].Position.x = -0.5f;
    Vertex[0].Position.y = -0.5f;
    //���
    Vertex[0].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

    Vertex[1].Position.x = -0.5f;
    Vertex[1].Position.y = 0.5f;
    //���
    Vertex[1].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

    Vertex[2].Position.x = 0.5f;
    Vertex[2].Position.y = -0.5f;
    //������
    Vertex[2].color = Color(0.0f, 0.0f, 0.0f, 1.0f);

    Vertex[3].Position.x = 0.5f;
    Vertex[3].Position.y = 0.5f;
    //������
    Vertex[3].color = Color(0.0f, 0.0f, 0.0f, 1.0f);


    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//���۸� �а� ���� ���
        desc.ByteWidth = sizeof(VertexPC) * 4; //���� ũ�� (����Ʈ)�Դϴ�.
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

    Vertex = new VertexPC[5];
    //VertexCount = 5;
    Vertex[0].Position.x = -0.5f;
    Vertex[0].Position.y = -0.5f;
    Vertex[0].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

    Vertex[1].Position.x = -0.5f;
    Vertex[1].Position.y = 0.5f;
    Vertex[1].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

    Vertex[2].Position.x = 0.5f;
    Vertex[2].Position.y = 0.5f;
    Vertex[2].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

    Vertex[3].Position.x = 0.5f;
    Vertex[3].Position.y = -0.5f;
    Vertex[3].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

    Vertex[4].Position.x = -0.5f;
    Vertex[4].Position.y = -0.5f;
    Vertex[4].color = Color(1.0f, 1.0f, 1.0f, 1.0f);

    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//���۸� �а� ���� ���
        desc.ByteWidth = sizeof(VertexPC) * 5; //���� ũ�� (����Ʈ)�Դϴ�.
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

void ObRect::DeleteStaticMember()
{
    VertexBuffer->Release();
    FillVertexBuffer->Release();
}
