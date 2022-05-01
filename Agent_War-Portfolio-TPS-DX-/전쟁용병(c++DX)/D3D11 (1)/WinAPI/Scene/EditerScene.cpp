#include "stdafx.h"
#include "TileMap/Tile.h"
#include "TileMap/TileMap.h"
#include "EditerScene.h"

EditerScene::EditerScene()
{
    tm = new TileMap();
    tm->Images.push_back(TileImg(L"Image/TDS/Tile/Tiles.png", Int2(1, 5)));
}

EditerScene::~EditerScene()
{
    delete tm;
}

void EditerScene::Init()
{
    tm->Init();
    tm->Load("TileMap1.txt");
    tm->isDebug = true;

    Camera_Speed = 300.0f;
}

void EditerScene::Update()
{
    if (INPUT->KeyDown(VK_F7))
    {
        cout << g_WorldMouse.x << 't' << g_WorldMouse.y << endl;
    }
    if (INPUT->KeyDown(VK_F8))
    {
        Int2 idx;
        tm->VectorToIdx(g_WorldMouse, idx);
        cout << idx.x << 't' << idx.y << endl;
    }
    if (INPUT->KeyDown(VK_F1))
    {
        SCENE->ChangeScene("Scene1")->Init();
    }
    if (INPUT->KeyDown(VK_F2))
    {
        Camera_Speed = 100.0f;
    }
    if (INPUT->KeyDown(VK_F3))
    {
        Camera_Speed = 300.0f;
    }
    if (INPUT->KeyDown(VK_F4))
    {
        Camera_Speed = 600.0f;
    }
    if (INPUT->KeyDown(VK_F5))
    {
        Camera_Speed = 2000.0f;
    }
    if (INPUT->KeyDown(VK_F6))
    {
        Camera_Speed = 5000.0f;
    }

    //cam move
    if (INPUT->KeyPress('W'))
    {
        MAINCAM->Pos += UP * Camera_Speed * DeltaTime;
    }
    if (INPUT->KeyPress('S'))
    {
        MAINCAM->Pos += DOWN * Camera_Speed * DeltaTime;
    }
    if (INPUT->KeyPress('A'))
    {
        MAINCAM->Pos += LEFT * Camera_Speed * DeltaTime;
    }
    if (INPUT->KeyPress('D'))
    {
        MAINCAM->Pos += RIGHT * Camera_Speed * DeltaTime;
    }

    ImGui::Begin("TileMapEditer");
    tm->Update();
    ImGui::End();
}

void EditerScene::LateUpdate()
{
}

void EditerScene::Render()
{
    tm->Render();
}

void EditerScene::TextRender()
{
}
