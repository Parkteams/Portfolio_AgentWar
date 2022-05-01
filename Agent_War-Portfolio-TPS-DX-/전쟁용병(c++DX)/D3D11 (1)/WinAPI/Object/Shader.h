#pragma once
class Shader
{
    ID3D11VertexShader*			VertexShader;
    ID3D11PixelShader*			PixelShader;
    
    ID3D11InputLayout*			VertexLayout;
public:
    Shader(wstring file);
    ~Shader();
    void SetShader();
};

