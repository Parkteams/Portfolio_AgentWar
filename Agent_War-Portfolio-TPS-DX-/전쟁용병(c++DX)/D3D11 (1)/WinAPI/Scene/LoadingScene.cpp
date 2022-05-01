#include "stdafx.h"
#include "LoadingScene.h"
#include "Scene/Scene1.h"
#include "Scene/Scene2.h"
#include "Scene/EditerScene.h"


LoadingScene::LoadingScene()
{
    Bg = new ObImage(L"Image/TDS/UI/Loading/Background.png");
    Icon = new ObImage(L"Image/TDS/UI/Loading/Loading icon.png");
    Bar = new ObImage(L"Image/TDS/UI/Loading/Loading Bar.png");
    t1 = thread(LoadingThread);
}

LoadingScene::~LoadingScene()
{
    delete Bg;
    delete Icon;
    delete Bar;
    t1.join();
}

void LoadingScene::Init()
{
    Bg->Pivot = OFFSET_LB;
    Bg->Scale = Vector2(WINSIZEX, WINSIZEY);
    Icon->Pivot = OFFSET_LB;
    Icon->Scale = Vector2(WINSIZEX, WINSIZEX/200.0f * 48.0f);
    Icon->Position.y = 300.0f;
    Bar->Pivot = OFFSET_LB;
    Bar->Scale.y = 100.0f;
    Bar->Position.y = 100.0f;
    
}

void LoadingScene::Update()
{
    Bar->Scale.x = loadingCount * WINSIZEX / 3.0f;
}

void LoadingScene::LateUpdate()
{
}

void LoadingScene::Render()
{
    Bg->Render();
    Icon->Render();
    Bar->Render();
}

void LoadingScene::TextRender()
{
    if (loadingCount == 3)
    {
        SPRITETEXT->RenderText("HAND", L"PRESS SPACEBAR",
           Vector2(WINSIZEX/2.0f, WINSIZEY/2.0f));
        if (INPUT->KeyDown(VK_SPACE))
        {
            SCENE->ChangeScene("Scene1")->Init();
        }
    }
}

void LoadingThread()
{
   
    SCENE->AddScene("Scene1", new Scene1());
    m1.lock();
    loadingCount++;
    m1.unlock();
    Sleep(1000);
    

   
    SCENE->AddScene("Scene2", new Scene2());
    m1.lock();
    loadingCount++;
    m1.unlock();
    Sleep(1000);

    SCENE->AddScene("Edit", new EditerScene());
    m1.lock();
    loadingCount++;
    m1.unlock();
    Sleep(1000);
   
}
