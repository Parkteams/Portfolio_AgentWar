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
    //�ߺ��Ȱ� ����.
    if (iter == TextureList.end())
    {
        ID3D11ShaderResourceView* temp;
        ID3D11Resource* resource;
        HRESULT hr =  CreateWICTextureFromFile(g_Device, file.c_str(), &resource, &temp);

        assert(SUCCEEDED(hr) && "�ؽ��ķε� ����");

        TextureList[file] = temp;
        return temp;
    }
    //������ �Ҵ���ִ� �ؽ��ĸ� ��ȯ
    return iter->second;
}

bool Texture::DeleteTexture(wstring file)
{
    auto iter = TextureList.find(file);

    //�ߺ��Ȱ� ����.
    if (iter == TextureList.end())
    {
        return false;
    }
    //first�� Ű, second ���
    iter->second->Release();

    //�ʿ����� ����
    TextureList.erase(iter);

    return true;
}
