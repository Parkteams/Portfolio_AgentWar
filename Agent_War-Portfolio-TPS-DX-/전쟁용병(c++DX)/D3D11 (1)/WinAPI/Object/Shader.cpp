#include "stdafx.h"
#include "Shader.h"

Shader::Shader(wstring file)
{
    //�����ϰ���� ��Ƴ��� �������̽�
    ID3D10Blob*					VsBlob;
    ID3D10Blob*					PsBlob;

    wstring path = L"Shaders/" + file + L".hlsl";

    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    //���̴��� c++�� �ƴ� �ٸ����⶧���� �������Ͽ� �޸𸮸� �����´�.
    D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "VS", "vs_5_0", flags, 0, &VsBlob, nullptr);

    g_Device->CreateVertexShader(VsBlob->GetBufferPointer(), VsBlob->GetBufferSize(),
        nullptr, &VertexShader);
    if (file == L"1.Basic")
    {
        D3D11_INPUT_ELEMENT_DESC LayoutDesc[] =
        {
            { "POSITION",//�ø�ƽ���� ������ �ڷ���
            0,//�ø�ƽ���� ������ �ε��� 0���� �����߱⿡ 0 ���
            DXGI_FORMAT_R32G32B32_FLOAT,//3���� 32��Ʈ float����
            0,//0~15������ �ε��� ����, ���ÿ� 15������ ���۰� �Է½����� �������ִ�.
            0,//�� ��Ұ� �޸𸮵�� ������������ �󸶳� ������ ��ġ�� �ִ°��� �˷��ش�.ó������0
            D3D11_INPUT_PER_VERTEX_DATA,//�Ѿ��
            0 },//�Ѿ��
            { "COLOR",//�ø�ƽ���� ������ �ڷ���
            0,//�ø�ƽ���� ������ �ε��� 0���� �����߱⿡ 0 ���
            DXGI_FORMAT_R32G32B32_FLOAT,//3���� 32��Ʈ float����
            0,//0~15������ �ε��� ����, ���ÿ� 15������ ���۰� �Է½����� �������ִ�.
            12,//������ R32G32B32 4 ,4,4 ->12
            D3D11_INPUT_PER_VERTEX_DATA,//�Ѿ��
            0 }
        };
        g_Device->CreateInputLayout
        (
            LayoutDesc,//��������ü�迭
            ARRAYSIZE(LayoutDesc),//�迭���Ұ���
            VsBlob->GetBufferPointer(),//�������̴� ������
            VsBlob->GetBufferSize(),//���̴�ũ��
            &VertexLayout//�Է¹�ġ�� �����͸� ���� ������
        );
    }
    if (file == L"2.Image")
    {
        //���� ����
        D3D11_INPUT_ELEMENT_DESC LayoutDesc[] =
        {
            { "POSITION",//�ø�ƽ���� ������ �ڷ���
            0,//�ø�ƽ���� ������ �ε��� 0���� �����߱⿡ 0 ���
            DXGI_FORMAT_R32G32B32_FLOAT,//3���� 32��Ʈ float����
            0,//0~15������ �ε��� ����, ���ÿ� 15������ ���۰� �Է½����� �������ִ�.
            0,//�� ��Ұ� �޸𸮵�� ������������ �󸶳� ������ ��ġ�� �ִ°��� �˷��ش�.ó������0
            D3D11_INPUT_PER_VERTEX_DATA,//�Ѿ��
            0 },//�Ѿ��
            { "UV",//�ø�ƽ���� ������ �ڷ���
            0,//�ø�ƽ���� ������ �ε��� 0���� �����߱⿡ 0 ���
            DXGI_FORMAT_R32G32_FLOAT,//3���� 32��Ʈ float����
            0,//0~15������ �ε��� ����, ���ÿ� 15������ ���۰� �Է½����� �������ִ�.
            12,//������ R32G32B32 4 ,4,4 ->12
            D3D11_INPUT_PER_VERTEX_DATA,//�Ѿ��
            0 }
        };
        g_Device->CreateInputLayout
        (
            LayoutDesc,//��������ü�迭
            ARRAYSIZE(LayoutDesc),//�迭���Ұ���
            VsBlob->GetBufferPointer(),//�������̴� ������
            VsBlob->GetBufferSize(),//���̴�ũ��
            &VertexLayout//�Է¹�ġ�� �����͸� ���� ������
        );
    }
    
    VsBlob->Release();


    
    D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "PS", "ps_5_0", flags, 0, &PsBlob, nullptr);

    g_Device->CreatePixelShader(PsBlob->GetBufferPointer(), PsBlob->GetBufferSize(),
        nullptr, &PixelShader);

    PsBlob->Release();

}

Shader::~Shader()
{
    VertexShader->Release();
    PixelShader->Release();
    VertexLayout->Release();
}

void Shader::SetShader()
{
    //���������ο� ���ε�
    g_DeviceContext->VSSetShader(VertexShader, 0,  0);
    g_DeviceContext->PSSetShader(PixelShader, 0, 0);
    g_DeviceContext->IASetInputLayout(VertexLayout);
}
