#include "stdafx.h"
#include "Texture.h"

Texture::~Texture()
{
    for (auto i = TextureList.begin();
        i != TextureList.end(); i++)
    {
        //i->first; // key
        //i->second;// value
        if (i->second)
        {
            i->second->Release();
        }
    }
    TextureList.clear();
}

ID3D11ShaderResourceView* Texture::LoadTexture(wstring file)
{
    auto iter = TextureList.find(file);
    //중복된게 없다.
    if (iter == TextureList.end())
    {
        ID3D11ShaderResourceView* temp;
        ID3D11Resource* resource;
        HRESULT hr =  CreateWICTextureFromFile(g_Device, file.c_str(), &resource, &temp);

        assert(SUCCEEDED(hr) && "텍스쳐로드 실패");

        TextureList[file] = temp;
        return temp;
    }
    //기존에 할당되있던 텍스쳐를 반환
    return iter->second;
}

bool Texture::DeleteTexture(wstring file)
{
    auto iter = TextureList.find(file);

    //중복된게 없다.
    if (iter == TextureList.end())
    {
        return false;
    }
    //first가 키, second 밸류
    iter->second->Release();

    //맵에서도 삭제
    TextureList.erase(iter);

    return true;
}
