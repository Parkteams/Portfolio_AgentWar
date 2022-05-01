#pragma once

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 


//��ũ�� �Լ�
#define MAKEGET(Type, Value)	\
	Type Get##Value(){return Value;} 
#define MAKESET(Type, Value)	\
	void Set##Value(Type val){Value = val;}
#define MAKEGETSET(Type, Value) \
	MAKEGET(Type, Value) MAKESET(Type, Value)



//offset
#define OFFSET_N Vector2(0.0f, 0.0f)
#define OFFSET_L Vector2(0.5f, 0.0f)
#define OFFSET_R Vector2(-0.5f, 0.0f)
#define OFFSET_B Vector2(0.0f, 0.5f)
#define OFFSET_T Vector2(0.0f, -0.5f)

#define OFFSET_LB Vector2(0.5f, 0.5f)
#define OFFSET_RB Vector2(-0.5f, 0.5f)
#define OFFSET_LT Vector2(0.5f, -0.5f)
#define OFFSET_RT Vector2(-0.5f, -0.5f)



#define     WINSTARTX			0
#define     WINSTARTY			0
#define     WINSIZEX			1280
#define     WINSIZEY			720 
#define     FIXFRAME			180

#define     PI          3.141592f //������
#define     TORADIAN	0.017453f //pi/180 �ǰ�
#define		TODEGREE	57.29577f		//180/pi �ǰ�
#define     PI_8        0.392699f

#define     UP Vector2(0.0f,1.0f)
#define     DOWN Vector2(0.0f,-1.0f)
#define     LEFT Vector2(-1.0f, 0.0f)
#define     RIGHT Vector2(1.0f, 0.0f)

//�ٸ����Ͽ��� ������ �������� ��������
extern		HINSTANCE                    g_hInst;    //���α׷� ��ü�� ������                               // �⺻ â Ŭ���� �̸��Դϴ�.
extern		HWND                         g_hwnd;     //â ������        
extern		ID3D11Device*				 g_Device;
extern		ID3D11DeviceContext*		 g_DeviceContext;
extern		IDXGISwapChain*				 g_SwapChain;
extern		ID3D11RenderTargetView*		 g_RTV;
extern		POINT                        g_ScreenMouse;
extern      Vector2                      g_WorldMouse;
extern		Color                        g_BackGround;