#pragma once
//c++
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <list>
#include <map>
#include <queue>
#include <thread>
#include <mutex>
using namespace std;

//c
#include <time.h>
#include <assert.h>
#include <Windows.h> //winapi

//DirectX d3d 11
#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

//DirectXTk 
#include "DirectXTK/DDSTextureLoader.h"
#include "DirectXTK/ScreenGrab.h"
#include "DirectXTK/SimpleMath.h"
#include "DirectXTK/SpriteBatch.h"
#include "DirectXTK/SpriteFont.h"
#include "DirectXTK/WICTextureLoader.h"
using namespace DirectX;
using namespace SimpleMath;

#pragma comment (lib,"DirectXTK/DirectXTK.lib")

//Imgui
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"
#pragma comment(lib, "ImGui/ImGuiL.lib")

//Fmod
#include "Fmod/fmod.hpp"
#pragma comment (lib,"Fmod/fmodL_vc.lib")



#include "UserDef.h"
#include "Util/Math.h"
#include "Object/VertexType.h"
#include "Object/Shader.h"
#include "Object/Object.h"
#include "Object/ObRect.h"
#include "Object/ObCircle.h"
#include "Object/ObLine.h"
#include "Object/ObStar.h"
#include "Object/ObImage.h"

#include "Util/Collision.h"

#include "Scene/Scene.h"

#include "Singleton/Singleton.h"
#include "Singleton/Input.h"
#include "Singleton/Timer.h"
#include "Singleton/Cam.h"
#include "Singleton/SceneManager.h"
#include "Singleton/Texture.h"
#include "Singleton/Sound.h"
#include "Singleton/Light.h"
#include "Singleton/SpriteText.h"


#define  INPUT          Input::GetInstance()
#define  TIMER          Timer::GetInstance()
#define  DeltaTime      Timer::GetInstance()->GetDeltaTime()
#define  MAINCAM        Cam::GetInstance()
#define  SCENE          SceneManager::GetInstance()
#define  TEXTURE        Texture::GetInstance()
#define  SOUND          Sound::GetInstance()
#define  LIGHT          Light::GetInstance()
#define  SPRITETEXT     SpriteText::GetInstance()
