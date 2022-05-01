#pragma once

//�������� ����
static void LoadingThread();
static mutex m1;
static thread t1;
static int loadingCount = 0;


class LoadingScene : public Scene
{
private:
    ObImage* Bg;
    ObImage* Icon;
    ObImage* Bar;

public:
    LoadingScene();
    ~LoadingScene();
    //���������Լ��� �ݵ� �ڽ�Ŭ�������� �����ؾ���
    void Init() override;
    void Update() override;
    void LateUpdate() override;
    void Render() override;
    void TextRender() override;
};


