#include "stdafx.h"
#include "SpriteText.h"

SpriteText::SpriteText()
{
    spriteBatch = new SpriteBatch(g_DeviceContext);
    //spriteBatch->
    //spriteFont = std::make_unique<SpriteFont>(g_Device, L"myfile.spritefont");
    //spriteFont = new SpriteFont(g_Device, L"Font/rosewood32.spritefont");
}

SpriteText::~SpriteText()
{
    delete spriteBatch;
    for (auto iter = FontList.begin(); iter != FontList.end(); iter++)
    {
        delete iter->second;
    }
    FontList.clear();
}

bool SpriteText::AddFont(wstring File, string Key)
{
    auto iter = FontList.find(Key);

    //�ߺ��Ȱ� �ִ�.
    if (iter != FontList.end())
    {
        return false;
    }
    //�ߺ��Ȱ� ����.
    SpriteFont* temp = new SpriteFont(g_Device, File.c_str());
    FontList[Key] = temp;
    return true;
}

bool SpriteText::DeleteFont(string Key)
{
    auto iter = FontList.find(Key);

    //�ߺ��Ȱ� ����.
    if (iter == FontList.end())
    {
        return false;
    }
    //first�� Ű, second ���
    delete iter->second;

    //�ʿ����� ����
    FontList.erase(iter);

    return true;
}

void SpriteText::RenderText(string Key, wstring Text, Vector2 ScreenPos, Color TextColor, float Rotation, Vector2 Origin, float scale, SpriteEffects effects, float layerDepth)
{

    //key �ߺ� ���x
    auto iter = FontList.find(Key);

    //�ߺ��Ȱ� �ִ�.
    if (iter != FontList.end())
    {
        iter->second->DrawString(spriteBatch, Text.c_str(), ScreenPos, TextColor, Rotation, Origin, scale, effects, layerDepth);
    }
}
