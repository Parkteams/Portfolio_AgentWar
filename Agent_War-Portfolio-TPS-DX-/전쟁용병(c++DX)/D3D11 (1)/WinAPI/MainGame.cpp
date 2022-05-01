#include "stdafx.h"
#include "MainGame.h"
#include "Scene/LoadingScene.h"

MainGame::MainGame()
{
    //Disable DepthStencil
    {
        //�ش� �������ٽ� ��ɰ��úκ��� ���δ� �ɼ����� ����
        D3D11_DEPTH_STENCIL_DESC desc = { 0 };
        desc.DepthEnable = false;
        desc.StencilEnable = false;
        g_Device->CreateDepthStencilState(&desc, &depthStencilState);
        g_DeviceContext->OMSetDepthStencilState(depthStencilState, 0xFF);
    }
    //�����Ͷ����� �ɼ�
    {
        D3D11_RASTERIZER_DESC desc;
        ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
        desc.FillMode = D3D11_FILL_SOLID; // D3D11_FILL_WIREFRAME�� �׵θ�������
        desc.CullMode = D3D11_CULL_NONE; //�ø��Ҷ� �ո�,�޸� �߷����� �Ұ���
        desc.DepthBias = 0;
        desc.FrontCounterClockwise = false; //cw ccw �� ���ϱ�
        desc.DepthBiasClamp = 0;
        desc.SlopeScaledDepthBias = 0;
        desc.DepthClipEnable = false; //����Ŭ���� ����
        desc.ScissorEnable = false; //�����׽�Ʈ ���� ����
        desc.MultisampleEnable = false; //��Ƽ ���ø� ��������
        desc.AntialiasedLineEnable = false; //���ξ�Ƽ�ٸ���� ����
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
    //�� �߰�
    SCENE->AddScene("Loading", new LoadingScene());
    SCENE->ChangeScene("Loading")->Init();


}

void MainGame::Update()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    //���ϴ� ���ڿ� ���
    ImGui::Text("FPS: %d", TIMER->GetFPS());
    ImGui::Text("WorldTime: %f", TIMER->GetWorldTime());
    ImGui::Text("Delata: %f", DeltaTime);
    //üũ�ڽ������� 0,1�� �����
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
