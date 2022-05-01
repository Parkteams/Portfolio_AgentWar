#pragma once
class SceneManager :public Singleton<SceneManager>
{
private:
    Scene* pCurrentScene = nullptr;

    //  key(Ž��) , value
    map<string, Scene*> SceneList; //(RB)Ʈ������ �ߺ����x

public:
    ~SceneManager();

    //�� �߰�
    bool AddScene(string key, Scene* value);
    //�� ����
    bool DeleteScene(string key);
    //�� ����
    Scene* ChangeScene(string key);
    //�� ��������
    Scene* GetScene(string key);
    //���� �� ��������
    Scene* GetCurrentScene();

};

