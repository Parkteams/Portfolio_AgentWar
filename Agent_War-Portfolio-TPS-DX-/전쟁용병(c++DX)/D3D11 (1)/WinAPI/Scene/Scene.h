#pragma once
class Scene
{
public:
    float GameTime;
    virtual ~Scene() {};
    //���� �����Լ� virtual = 0; (������ �������������Լ�)
    virtual void Init() = 0; //�ʱ�ȭ
    virtual void Update() = 0;//����
    virtual void LateUpdate() = 0;//��������
    virtual void Render() = 0;//�׸���
    virtual void TextRender() = 0;//�׸���
};