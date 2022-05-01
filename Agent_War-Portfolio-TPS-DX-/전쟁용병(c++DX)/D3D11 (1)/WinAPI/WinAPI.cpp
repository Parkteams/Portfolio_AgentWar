#include "stdafx.h"
#include "MainGame.h"


HINSTANCE                   g_hInst; 
HWND                        g_hwnd;  
ID3D11Device*				g_Device;
ID3D11DeviceContext*		g_DeviceContext;
IDXGISwapChain*				g_SwapChain;
ID3D11RenderTargetView*		g_RTV;

POINT                       g_ScreenMouse;
Vector2                     g_WorldMouse;
Color                       g_BackGround;


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void SetWindowSize(int x, int y, int width, int height);


int APIENTRY wWinMain( HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPWSTR    lpCmdLine,
                      int       nCmdShow)
{
    
    WNDCLASS                    wc;
    MainGame*                   Mg;
    ZeroMemory(&wc, sizeof(WNDCLASS));
    UNREFERENCED_PARAMETER(lpCmdLine);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wc.lpfnWndProc = static_cast<WNDPROC>(WndProc);
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH));
    wc.lpszClassName = L"DX11";
    wc.lpszMenuName = nullptr;

    if (!RegisterClass(&wc))
        return FALSE; 

    g_hInst = hInstance;
    g_hwnd = CreateWindowW(
        L"DX11",
        L"DX11",
        WS_OVERLAPPEDWINDOW,
        WINSTARTX,			
        WINSTARTY,			
        WINSIZEX,			
        WINSIZEY,         
        nullptr,
        nullptr,
        hInstance,	
        nullptr
    );
   
    if (!g_hwnd)
        return FALSE;

    SetWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
    ShowWindow(g_hwnd, nCmdShow);


    //Create Device and DeviceContext, SwapChain
    {
        DXGI_MODE_DESC bufferDesc;
        ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

        bufferDesc.Width = WINSIZEX;
        bufferDesc.Height = WINSIZEY;
        bufferDesc.RefreshRate.Numerator = FIXFRAME; 
        bufferDesc.RefreshRate.Denominator = 1; 
        bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;


        DXGI_SWAP_CHAIN_DESC desc;
        ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

        
        desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        desc.BufferDesc = bufferDesc;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        desc.BufferCount = 1;
        desc.OutputWindow = g_hwnd;
        desc.Windowed = TRUE;
        desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        UINT creationFlags = D3D11_CREATE_DEVICE_DEBUG;
        HRESULT hr = D3D11CreateDeviceAndSwapChain
        (
            NULL,
            D3D_DRIVER_TYPE_HARDWARE,
            NULL,
            creationFlags, 
            NULL, 
            0, 
            D3D11_SDK_VERSION,
            &desc,
            &g_SwapChain, 
            &g_Device,	
            NULL, 
            &g_DeviceContext
        );
        assert(SUCCEEDED(hr) && "Device");

    }
    //Create BackBuffer
    {
        HRESULT hr;

        ID3D11Texture2D* BackBuffer;
        hr = g_SwapChain->GetBuffer(0,  __uuidof(ID3D11Texture2D),(void**)&BackBuffer);
        assert(SUCCEEDED(hr));
        hr = g_Device->CreateRenderTargetView(BackBuffer, NULL,&g_RTV);
        assert(SUCCEEDED(hr));
        BackBuffer->Release();
        g_DeviceContext->OMSetRenderTargets(1, &g_RTV, NULL);
    }

    Mg = new MainGame();//할당
    Mg->Init();//초기화



    //**메시지 루프**
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            TIMER->SetFrameRate(FIXFRAME);
            Mg->Update();
            Mg->LateUpdate();
            Mg->Render();
            Mg->TextRender();

        }
    }
    delete Mg; //소멸
     //생성된 윈도우 삭제
    DestroyWindow(g_hwnd);
    //등록된 프로그램 해제
    UnregisterClass(L"DX11", hInstance);

    return (int)msg.wParam;
}


// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//os가 호출해주는 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //어떤 메세지가 발생되었는가를 통해 처리할 조건문
    switch (message)
    {
        //화면창 건들때 나오는 윈메세지
    case WM_MOUSEMOVE:
    {
        g_ScreenMouse.x = LOWORD(lParam);
        g_ScreenMouse.y = HIWORD(lParam);

        break;
    }
    //파괴하거나 닫으라는 메세지가 들어온경우
    case WM_DESTROY: case WM_CLOSE:
    {
        //프로그램 종료 호출 함수
        PostQuitMessage(0);
        break;
    }
    //아무키나 눌렀을때
    case WM_KEYDOWN:
    {
        // VK 버츄얼키 가상키
        if (wParam == VK_ESCAPE)
        {
            //프로그램 종료 호출 함수
            PostQuitMessage(0);
        }
        break;
    }
    
    }
    ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam);
    return (DefWindowProc(hWnd, message, wParam, lParam));
}

void SetWindowSize(int x, int y, int width, int height)
{
    //화면크기에 맞는 렉트
    RECT rc;
    rc.left = 0;
    rc.top = 0;
    rc.right = width;
    rc.bottom = height;

    //실제 윈도우 크기 조정
    AdjustWindowRect(&rc, WS_CAPTION | WS_SYSMENU, false);
    //위 RECT 정보로 윈도우 사이즈 세팅
    SetWindowPos(g_hwnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);
}