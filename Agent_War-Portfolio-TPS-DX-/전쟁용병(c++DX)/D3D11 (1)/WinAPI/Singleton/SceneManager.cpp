#include "stdafx.h"
#include "SceneManager.h"

SceneManager::~SceneManager()
{
    for (auto i = SceneList.begin();
        i != SceneList.end(); i++)
    {
        //i->first; // key
        //i->second;// value
        if (i->second)
        {
            delete i->second;
        }
    }
    SceneList.clear();
}

bool SceneManager::AddScene(string key, Scene* value)
{
    //key 중복 허용x
    auto iter = SceneList.find(key);

    //중복된게 있다.
    if (iter != SceneList.end())
    {
        return false;
    }
    //중복된게 없다.
    SceneList[key] = value;
    //SceneList.insert(make_pair(key, value));

    return true;
}

bool SceneManager::DeleteScene(string key)
{
    auto iter = SceneList.find(key);

    //중복된게 없다.
    if (iter == SceneList.end())
    {
        return false;
    }
    //first가 키, second 밸류
    delete iter->second;

    //맵에서도 삭제
    SceneList.erase(iter);

    return true;

}

Scene* SceneManager::ChangeScene(string key)
{
    Scene* temp = GetScene(key);
    if (temp)pCurrentScene = temp;
    return temp;
}

Scene* SceneManager::GetScene(string key)
{
    //검색한씬 반환
    auto iter = SceneList.find(key);
    //중복된게 없다.
    if (iter == SceneList.end())
    {
        return nullptr;
    }
    return iter->second;
}

Scene* SceneManager::GetCurrentScene()
{
    return pCurrentScene;
}
