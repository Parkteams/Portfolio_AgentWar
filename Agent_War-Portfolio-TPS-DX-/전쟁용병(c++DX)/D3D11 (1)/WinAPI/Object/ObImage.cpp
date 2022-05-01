#include "stdafx.h"
#include "ObImage.h"



ObImage::ObImage(wstring file)
{
    //�⺻ ���÷� ��
    SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

    SamplerDesc.MipLODBias = 0.0f;
    SamplerDesc.MaxAnisotropy = 1;
    SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    SamplerDesc.MinLOD = -FLT_MAX;
    SamplerDesc.MaxLOD = FLT_MAX;

    //�ϳ� �̻��� ���÷� ����� �α�
    g_Device->CreateSamplerState(&SamplerDesc, &Sampler);

    //�ؽ��� �ε�
    SRV = TEXTURE->LoadTexture(file);

    //           (�ּ���ǥ)   (�ִ���ǥ)
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


    //�ȼ����̴��� ���̴��ڿ��� ����
    g_DeviceContext->PSSetShaderResources(0,// ����ɷ������� ��ȣ 0
        1,//���ҽ�����
        &SRV);

    //����ɷ������� ��ȣ 0
    g_DeviceContext->PSSetSamplers(0,
        1, //���ҽ�����
        &Sampler);//���÷�

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
    //�ð�������� �������
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
        desc.Usage = D3D11_USAGE_DEFAULT;//���۸� �а� ���� ���
        desc.ByteWidth = sizeof(VertexPT) * 4; //���� ũ�� (����Ʈ)�Դϴ�.
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


    //CreateConstantBuffer
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = sizeof(Vector4);
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//�������
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;

        HRESULT hr = g_Device->CreateBuffer(&desc, NULL, &UVBuffer);
        assert(SUCCEEDED(hr));
    }
    //                            ����ɷ������� ��ȣ3
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
        //���� �ٽ� �����
        g_Device->CreateSamplerState(&SamplerDesc, &Sampler);
    }
    else if (sam == _LINEAR)
    {
        SamplerDesc.Filter =
            D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        Sampler->Release();
        //���� �ٽ� �����
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
        //���� �ٽ� �����
        g_Device->CreateSamplerState(&SamplerDesc, &Sampler);
    }
    else if (sam == _WRAP)
    {
        SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

        Sampler->Release();
        //���� �ٽ� �����
        g_Device->CreateSamplerState(&SamplerDesc, &Sampler);
    }
    else if (sam == _MIRROR)
    {
        SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
        SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
        SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
        Sampler->Release();
        //���� �ٽ� �����
        g_Device->CreateSamplerState(&SamplerDesc, &Sampler);
    }
}

void ObImage::PlayAnim()
{
    //���Ұ����� 1�̻��϶�
    if (MaxFrame.x != 1 or MaxFrame.y != 1)
    {
        //������ �ƴѰ�쿡��
        if (AnimState != _STOP)
        {
            //�ð� �����
            AnimTime += DeltaTime;
            //���� ���������� �̵�
            if (AnimTime > AnimInterval)
            {
                AnimTime -= AnimInterval;
                //������ ����ΰ�?
                if (AnimXAxis)
                {
                    //������ ���
                    if (AnimState == _LOOP)
                    {
                        Frame.x++;
                        if (Frame.x == MaxFrame.x)Frame.x = 0;
                    }
                    //������ ���
                    else if (AnimState == _REVERSE_LOOP)
                    {
                        Frame.x--;
                        if (Frame.x == -1)Frame.x = MaxFrame.x - 1;
                    }
                    //������ ���
                    else if (AnimState == _ONCE)
                    {
                        Frame.x++;
                        if (Frame.x == MaxFrame.x)
                        {
                            AnimState = _STOP;
                            Frame.x = MaxFrame.x - 1;
                        }
                    }
                    //������ ���
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
                //������ ����ΰ�?
                else
                {
                    //������ ���
                    if (AnimState == _LOOP)
                    {
                        Frame.y++;
                        if (Frame.y == MaxFrame.y)Frame.y = 0;
                    }
                    //������ ���
                    else if (AnimState == _REVERSE_LOOP)
                    {
                        Frame.y--;
                        if (Frame.y == -1)Frame.y = MaxFrame.y - 1;
                    }
                    //������ ���
                    else if (AnimState == _ONCE)
                    {
                        Frame.y++;
                        if (Frame.y == MaxFrame.y)
                        {
                            AnimState = _STOP;
                            Frame.y = MaxFrame.y - 1;
                        }
                    }
                    //������ ���
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
        //�ٽ� ���Ұ���,������ǥ�� UV�� �����
        UV.x = Frame.x / (float)MaxFrame.x;
        UV.z = (Frame.x + 1.0f) / (float)MaxFrame.x;
        UV.y = Frame.y / (float)MaxFrame.y;
        UV.w = (Frame.y + 1.0f) / (float)MaxFrame.y;
    }
}

void ObImage::ChangeAnim(Animation anim, float interval, bool XAxis)
{
    AnimTime = 0.0f;    //����ð� 0���� �ʱ�ȭ
    AnimState = anim;   //���°� ����
    AnimXAxis = XAxis;  //����� ����
    AnimInterval = interval; //������� ����
    //�ѹ� ����̶��(��Ʈ �� ���̹����� �̵�)
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
