#pragma once
//                  ��ӹ����鼭<T>�� ����
class Input : public Singleton<Input>
{
private:
    //�迭ũ�⸦ Ű����ŭ ���´�
    byte keyState[256];//�������
    byte keyOldState[256];//����������Ʈ����
    byte keyMap[256];

    //Ű�Է¿����� ���ٰ�����  �͸� enum
    enum
    {
        KEY_INPUT_STATUS_DOWN,
        KEY_INPUT_STATUS_PRESS,
        KEY_INPUT_STATUS_NONE,
        KEY_INPUT_STATUS_UP,
    };
public:
    Input();
    ~Input();

    bool KeyDown(int KeyCode); //�������� ����1ȸ
    bool KeyPress(int KeyCode);//������������
    bool KeyUp(int KeyCode); //�����ٰ� �������� ����1ȸ
    void Update();

};

