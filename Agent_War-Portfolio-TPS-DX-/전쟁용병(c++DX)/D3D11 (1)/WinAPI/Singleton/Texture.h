#pragma once
class Texture :public Singleton<Texture>
{
private:
    map<wstring, ID3D11ShaderResourceView*> TextureList;
public:
    ~Texture();
    ID3D11ShaderResourceView* LoadTexture(wstring file);
    bool DeleteTexture(wstring file);


};

