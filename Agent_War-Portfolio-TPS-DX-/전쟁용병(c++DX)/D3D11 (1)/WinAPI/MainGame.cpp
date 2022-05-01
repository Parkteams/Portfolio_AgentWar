#include "stdafx.h"
#include "MainGame.h"
#include "Scene/LoadingScene.h"

MainGame::MainGame()
{
    //Disable DepthStencil
    {
        //해당 뎁스스텐실 기능관련부분은 꺼두는 옵션으로 설정
        D3D11_DEPTH_STENCIL_DESC desc = { 0 };
        desc.DepthEnable = false;
        desc.StencilEnable = false;
        g_Device->CreateDepthStencilState(&desc, &depthStencilState);
        g_DeviceContext->OMSetDepthStencilState(depthStencilState, 0xFF);
    }
    //레스터라이저 옵션
    {
        D3D11_RASTERIZER_DESC desc;
        ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
        desc.FillMode = D3D11_FILL_SOLID; // D3D11_FILL_WIREFRAME은 테두리만나옴
        desc.CullMode = D3D11_CULL_NONE; //컬링할때 앞면,뒷면 추려내기 할건지
        desc.DepthBias = 0;
        desc.FrontCounterClockwise = false; //cw ccw 값 정하기
        desc.DepthBiasClamp = 0;
        desc.SlopeScaledDepthBias = 0;
        desc.DepthClipEnable = false; //깊이클리핑 끄기
        desc.ScissorEnable = false; //시저테스트 하지 않음
        desc.MultisampleEnable = false; //멀티 샘플링 하지않음
        desc.AntialiasedLineEnable = false; //라인안티앨리어싱 없음
        g_Device->CreateRasterizerState(&desc, &rasterizerState);
        g_DeviceContext->RSSetState(rasterizerState);
    }
    srand((UINT)time(NULL));
    g_BackGround = Color(0.6f, 0.6f, 0.6f, 1.0f);
    isVsync = false;
    Object::CreateStaticMember();
    ObRect::CreateStaticMember();
    ObLine::CreateStaticMember();
    ObCircle::CreateStaticMember();
    ObStar::CreateStaticMember();
    ObImage::CreateStaticMember();
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(g_hwnd);
    ImGui_ImplDX11_Init(g_Device, g_DeviceContext);

}

MainGame::~MainGame()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    g_SwapChain->Release();
    g_Device->Release();
    g_DeviceContext->Release();
    g_RTV->Release();
    rasterizerState->Release();
    depthStencilState->Release();
    Object::DeleteStaticMember();
    ObRect::DeleteStaticMember();
    ObLine::DeleteStaticMember();
    ObCircle::DeleteStaticMember();
    ObStar::DeleteStaticMember();
    ObImage::DeleteStaticMember();
    INPUT->DeleteSingleton();
    TIMER->DeleteSingleton();
    MAINCAM->DeleteSingleton();
    SCENE->DeleteSingleton();
    TEXTURE->DeleteSingleton();
    SOUND->DeleteSingleton();
    LIGHT->DeleteSingleton();
    SPRITETEXT->DeleteSingleton();
}

void MainGame::Init()
{
    //씬 추가
    SCENE->AddScene("Loading", new LoadingScene());
    SCENE->ChangeScene("Loading")->Init();


}

void MainGame::Update()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    //원하는 문자열 출력
    ImGui::Text("FPS: %d", TIMER->GetFPS());
    ImGui::Text("WorldTime: %f", TIMER->GetWorldTime());
    ImGui::Text("Delata: %f", DeltaTime);
    //체크박스를통해 0,1값 만들기
    ImGui::Checkbox("Vsync", &isVsync);

    g_WorldMouse.x = (float)g_ScreenMouse.x + MAINCAM->Pos.x;
    g_WorldMouse.y = (float)WINSIZEY - (float)g_ScreenMouse.y + MAINCAM->Pos.y;


    INPUT->Update();

    

    SCENE->GetCurrentScene()->Update();
}

void MainGame::LateUpdate()
{


    SCENE->GetCurrentScene()->LateUpdate();
    SOUND->Update();
}

void MainGame::Render()
{
    g_DeviceContext->ClearRenderTargetView(g_RTV, g_BackGround);

    MAINCAM->SetCam();
    LIGHT->SetLight();

    SCENE->GetCurrentScene()->Render();
}

void MainGame::TextRender()
{
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    SPRITETEXT->spriteBatch->Begin(DirectX::SpriteSortMode_Deferred,
        Object::BlendStateOn,nullptr, depthStencilState, rasterizerState);
    SCENE->GetCurrentScene()->TextRender();
    SPRITETEXT->spriteBatch->End();

  
    g_SwapChain->Present(isVsync, 0);
}
