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
    //key �ߺ� ���x
    auto iter = SceneList.find(key);

    //�ߺ��Ȱ� �ִ�.
    if (iter != SceneList.end())
    {
        return false;
    }
    //�ߺ��Ȱ� ����.
    SceneList[key] = value;
    //SceneList.insert(make_pair(key, value));

    return true;
}

bool SceneManager::DeleteScene(string key)
{
    auto iter = SceneList.find(key);

    //�ߺ��Ȱ� ����.
    if (iter == SceneList.end())
    {
        return false;
    }
    //first�� Ű, second ���
    delete iter->second;

    //�ʿ����� ����
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
    //�˻��Ѿ� ��ȯ
    auto iter = SceneList.find(key);
    //�ߺ��Ȱ� ����.
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
