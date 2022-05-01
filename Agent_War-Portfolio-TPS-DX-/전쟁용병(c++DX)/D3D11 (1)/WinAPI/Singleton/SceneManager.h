#pragma once
class SceneManager :public Singleton<SceneManager>
{
private:
    Scene* pCurrentScene = nullptr;

    //  key(탐색) , value
    map<string, Scene*> SceneList; //(RB)트리구조 중복허용x

public:
    ~SceneManager();

    //씬 추가
    bool AddScene(string key, Scene* value);
    //씬 삭제
    bool DeleteScene(string key);
    //씬 변경
    Scene* ChangeScene(string key);
    //씬 가져오기
    Scene* GetScene(string key);
    //현재 씬 가져오기
    Scene* GetCurrentScene();

};

