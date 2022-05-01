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

    //중복된게 있다.
    if (iter != FontList.end())
    {
        return false;
    }
    //중복된게 없다.
    SpriteFont* temp = new SpriteFont(g_Device, File.c_str());
    FontList[Key] = temp;
    return true;
}

bool SpriteText::DeleteFont(string Key)
{
    auto iter = FontList.find(Key);

    //중복된게 없다.
    if (iter == FontList.end())
    {
        return false;
    }
    //first가 키, second 밸류
    delete iter->second;

    //맵에서도 삭제
    FontList.erase(iter);

    return true;
}

void SpriteText::RenderText(string Key, wstring Text, Vector2 ScreenPos, Color TextColor, float Rotation, Vector2 Origin, float scale, SpriteEffects effects, float layerDepth)
{

    //key 중복 허용x
    auto iter = FontList.find(Key);

    //중복된게 있다.
    if (iter != FontList.end())
    {
        iter->second->DrawString(spriteBatch, Text.c_str(), ScreenPos, TextColor, Rotation, Origin, scale, effects, layerDepth);
    }
}
