#pragma once
class Scene2 : public Scene
{
private:
    
public:
    Scene2();
    ~Scene2();
    //���������Լ��� �ݵ� �ڽ�Ŭ�������� �����ؾ���
    void Init() override;
    void Update() override;
    void LateUpdate() override;
    void Render() override;
    void TextRender() override;
};

