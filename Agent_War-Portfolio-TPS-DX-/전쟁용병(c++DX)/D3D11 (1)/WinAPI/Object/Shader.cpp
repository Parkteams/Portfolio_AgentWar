#include "stdafx.h"
#include "Shader.h"

Shader::Shader(wstring file)
{
    //컴파일결과를 담아놓는 인터페이스
    ID3D10Blob*					VsBlob;
    ID3D10Blob*					PsBlob;

    wstring path = L"Shaders/" + file + L".hlsl";

    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    //쉐이더는 c++이 아닌 다른언어기때문에 컴파일하여 메모리를 가져온다.
    D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "VS", "vs_5_0", flags, 0, &VsBlob, nullptr);

    g_Device->CreateVertexShader(VsBlob->GetBufferPointer(), VsBlob->GetBufferSize(),
        nullptr, &VertexShader);
    if (file == L"1.Basic")
    {
        D3D11_INPUT_ELEMENT_DESC LayoutDesc[] =
        {
            { "POSITION",//시멘틱에서 정의한 자료형
            0,//시멘틱에서 정의한 인덱스 0으로 지정했기에 0 사용
            DXGI_FORMAT_R32G32B32_FLOAT,//3개의 32비트 float설정
            0,//0~15사이의 인덱스 지정, 동시에 15개까지 버퍼가 입력슬롯을 가질수있다.
            0,//이 요소가 메모리덩어리 시작지점부터 얼마나 떨어진 위치에 있는가를 알려준다.처음시작0
            D3D11_INPUT_PER_VERTEX_DATA,//넘어가기
            0 },//넘어가기
            { "COLOR",//시멘틱에서 정의한 자료형
            0,//시멘틱에서 정의한 인덱스 0으로 지정했기에 0 사용
            DXGI_FORMAT_R32G32B32_FLOAT,//3개의 32비트 float설정
            0,//0~15사이의 인덱스 지정, 동시에 15개까지 버퍼가 입력슬롯을 가질수있다.
            12,//포지션 R32G32B32 4 ,4,4 ->12
            D3D11_INPUT_PER_VERTEX_DATA,//넘어가기
            0 }
        };
        g_Device->CreateInputLayout
        (
            LayoutDesc,//정점구조체배열
            ARRAYSIZE(LayoutDesc),//배열원소갯수
            VsBlob->GetBufferPointer(),//정점셰이더 포인터
            VsBlob->GetBufferSize(),//셰이더크기
            &VertexLayout//입력배치를 포인터를 통해 돌려줌
        );
    }
    if (file == L"2.Image")
    {
        //정점 서술
        D3D11_INPUT_ELEMENT_DESC LayoutDesc[] =
        {
            { "POSITION",//시멘틱에서 정의한 자료형
            0,//시멘틱에서 정의한 인덱스 0으로 지정했기에 0 사용
            DXGI_FORMAT_R32G32B32_FLOAT,//3개의 32비트 float설정
            0,//0~15사이의 인덱스 지정, 동시에 15개까지 버퍼가 입력슬롯을 가질수있다.
            0,//이 요소가 메모리덩어리 시작지점부터 얼마나 떨어진 위치에 있는가를 알려준다.처음시작0
            D3D11_INPUT_PER_VERTEX_DATA,//넘어가기
            0 },//넘어가기
            { "UV",//시멘틱에서 정의한 자료형
            0,//시멘틱에서 정의한 인덱스 0으로 지정했기에 0 사용
            DXGI_FORMAT_R32G32_FLOAT,//3개의 32비트 float설정
            0,//0~15사이의 인덱스 지정, 동시에 15개까지 버퍼가 입력슬롯을 가질수있다.
            12,//포지션 R32G32B32 4 ,4,4 ->12
            D3D11_INPUT_PER_VERTEX_DATA,//넘어가기
            0 }
        };
        g_Device->CreateInputLayout
        (
            LayoutDesc,//정점구조체배열
            ARRAYSIZE(LayoutDesc),//배열원소갯수
            VsBlob->GetBufferPointer(),//정점셰이더 포인터
            VsBlob->GetBufferSize(),//셰이더크기
            &VertexLayout//입력배치를 포인터를 통해 돌려줌
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
    //파이프라인에 바인딩
    g_DeviceContext->VSSetShader(VertexShader, 0,  0);
    g_DeviceContext->PSSetShader(PixelShader, 0, 0);
    g_DeviceContext->IASetInputLayout(VertexLayout);
}
