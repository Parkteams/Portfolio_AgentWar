#pragma once
class Sound : public Singleton<Sound>
{
    struct SoundNode
    {
        FMOD::Sound* sound;
        FMOD::Channel* channel;
    };
    map<string, SoundNode*> SoundList;
    FMOD::System* system;
public:
    Sound();
    ~Sound();
    bool AddSound(string File, string Key,
        bool loop = false);
    bool DeleteSound(string Key);
    void Play(string Key);
    void Stop(string Key);
    //�Ͻ�����
    void Pause(string Key);
    //�Ͻ����� ����
    void Resume(string Key);
    void SetVolume(string Key, float scale);

    void Update();
};

