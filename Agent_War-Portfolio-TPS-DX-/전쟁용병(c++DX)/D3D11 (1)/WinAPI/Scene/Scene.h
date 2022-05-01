#pragma once
class Scene
{
public:
    float GameTime;
    virtual ~Scene() {};
    //순수 가상함수 virtual = 0; (선언후 정의하지않은함수)
    virtual void Init() = 0; //초기화
    virtual void Update() = 0;//갱신
    virtual void LateUpdate() = 0;//늦은갱신
    virtual void Render() = 0;//그리기
    virtual void TextRender() = 0;//그리기
};