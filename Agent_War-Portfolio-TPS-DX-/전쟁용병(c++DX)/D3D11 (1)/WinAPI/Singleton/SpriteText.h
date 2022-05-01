#pragma once
class SpriteText : public Singleton<SpriteText>
{
    
    map<string, SpriteFont*>  FontList;

public:
    SpriteText();
    ~SpriteText();
    SpriteBatch* spriteBatch;
    bool AddFont(wstring File, string Key);
    bool DeleteFont( string Key);
    void RenderText(string Key, wstring Text, Vector2 ScreenPos,
        Color TextColor = Color(1,1,1,1),float Rotation = 0.0f , 
        Vector2 Origin = Vector2(0.0f,0.0f), float scale = 1.0f,
        SpriteEffects effects = SpriteEffects_None, float layerDepth = 0);
};

