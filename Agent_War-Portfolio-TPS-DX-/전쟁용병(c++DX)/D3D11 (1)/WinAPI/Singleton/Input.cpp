#include "stdafx.h"
#include "Input.h"

Input::Input()
{
    ZeroMemory(keyState, sizeof(keyState));
    ZeroMemory(keyOldState, sizeof(keyOldState));
    ZeroMemory(keyMap, sizeof(keyMap));
}

Input::~Input()
{
}

bool Input::KeyDown(int KeyCode)
{
    return keyMap[KeyCode] == KEY_INPUT_STATUS_DOWN;
}

bool Input::KeyPress(int KeyCode)
{
    return keyMap[KeyCode] <= KEY_INPUT_STATUS_PRESS;
}

bool Input::KeyUp(int KeyCode)
{
    return keyMap[KeyCode] == KEY_INPUT_STATUS_UP;
}

void Input::Update()
{
    //메모리복사 keyOldState = keyState 
    memcpy(keyOldState, keyState, sizeof(keyOldState));

    //기존의 배열값 초기화
    ZeroMemory(keyState, sizeof(keyState));
    ZeroMemory(keyMap, sizeof(keyMap));


    //현재 호출상태에서의 키입력값을 가져오는 함수
    if (GetKeyboardState(keyState))
    {
        for (UINT i = 0; i < 256; i++)
        {
            byte key = keyState[i] & 0x80;
            //삼항연산자   (bool)? 1{} 0{}
            keyState[i] = key ? 1 : 0;

            int oldState = keyOldState[i];
            int state = keyState[i];

            if (oldState == 0 && state == 1)
                keyMap[i] = KEY_INPUT_STATUS_DOWN; //이전 0, 현재 1 - KeyDown
            else if (oldState == 1 && state == 0)
                keyMap[i] = KEY_INPUT_STATUS_UP; //이전 1, 현재 0 - KeyUp
            else if (oldState == 1 && state == 1)
                keyMap[i] = KEY_INPUT_STATUS_PRESS; //이전 1, 현재 1 - KeyPress
            else
                keyMap[i] = KEY_INPUT_STATUS_NONE;
        }
    }
    // 0x80
    // 0x81
    // 0x00
    // 0x01

   

}
