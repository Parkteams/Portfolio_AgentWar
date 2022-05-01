#include "stdafx.h"
#include "ObLine.h"


void ObLine::Render()
{
    if (!isActive)return;
    Object::WorldUpdate();
    Object::Render();


    BasicShader->SetShader();

    UINT stride = sizeof(VertexPC);
    UINT offset = 0;
    //������ ��������
    g_DeviceContext->IASetPrimitiveTopology
        //(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        (D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

    g_DeviceContext->IASetVertexBuffers(0,//�Է½���(16~32������ ��������)
        1,//�Է½��Կ� ���̰��� �ϴ� ������ ����
        &VertexBuffer,
        &stride,//���������� �� ������ ����Ʈ���� ũ��
        &offset);

    g_DeviceContext->Draw(2, 0);
}
ID3D11Buffer* ObLine::VertexBuffer = nullptr;

void ObLine::CreateStaticMember()
{
    VertexPC* Vertex = new VertexPC[2];

    Vertex[0].Position.x = 0.0f;
    Vertex[0].Position.y = 0.0f;
    Vertex[0].color = Color(0, 0, 0, 1.0f);

    Vertex[1].Position.x = 1.0f;
    Vertex[1].Position.y = 0.0f;
    Vertex[1].color = Color(0, 0, 0, 1.0f);
    
    //CreateVertexBuffer
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//���۸� �а� ���� ���
        desc.ByteWidth = sizeof(VertexPC) * 2; //���� ũ�� (����Ʈ)�Դϴ�.
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

void ObLine::DeleteStaticMember()
{
    VertexBuffer->Release();
}
