#pragma once

//전역으로 선언
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
    //순수가상함수는 반드 자식클래스에서 정의해야함
    void Init() override;
    void Update() override;
    void LateUpdate() override;
    void Render() override;
    void TextRender() override;
};


