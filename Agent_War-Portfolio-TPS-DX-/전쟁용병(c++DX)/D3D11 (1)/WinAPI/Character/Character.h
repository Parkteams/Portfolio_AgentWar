#pragma once
class Character
{
protected:
    ObRect* Root;   //�����̵� ������Ʈ

public:
    //Speed
    float Game_Speed;

    //isdead
    bool isDead;

    //Pos
    Vector2 Selected_Pos;

    //Hit
    bool isHit;
    float DamagedTime;

    Vector2 MoveDir;//�����̰� ���� ����
    Character();
    ~Character();
    void Render();
    Vector2 GetPos();
    float GetRotate();
    void SetPos(Vector2 pos);
    void SetPosX(Vector2 pos);
    void SetPosY(Vector2 pos);

    void Rotate_Root(float Rotation);

    void LookTarget(Vector2 target, ObImage* img, float Rotation);
    void LookTarget2(Vector2 target, ObImage* img, float Rotation);

    //range in
    bool Range(Vector2 target, ObLine* line1, ObLine* line2, float Rotation, float Rotation2);

};

