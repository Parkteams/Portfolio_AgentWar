#pragma once
class TileMap;
class EditerScene : public Scene
{
private:
    TileMap* tm;
    float Camera_Speed;

public:
    EditerScene();
    ~EditerScene();
    //���������Լ��� �ݵ� �ڽ�Ŭ�������� �����ؾ���
    void Init() override;
    void Update() override;
    void LateUpdate() override;
    void Render() override;
    void TextRender() override;
};
