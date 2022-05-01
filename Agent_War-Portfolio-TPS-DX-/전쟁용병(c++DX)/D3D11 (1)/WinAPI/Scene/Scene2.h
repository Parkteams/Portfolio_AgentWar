#pragma once
class Scene2 : public Scene
{
private:
    
public:
    Scene2();
    ~Scene2();
    //순수가상함수는 반드 자식클래스에서 정의해야함
    void Init() override;
    void Update() override;
    void LateUpdate() override;
    void Render() override;
    void TextRender() override;
};

