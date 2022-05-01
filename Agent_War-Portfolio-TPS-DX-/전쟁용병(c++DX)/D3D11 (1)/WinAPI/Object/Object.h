#pragma once

enum CollisionType
{
    COL_NONE,
    COL_RECT,
    COL_CIRCLE,

};


class Object
{
private:
    //transform
    Matrix              Pi; //�߽�����
    Matrix              R; //���� ȸ�����(z��)
    Matrix              R2; //���� ȸ�����(z��)
    
    //static
    static ID3D11Buffer*       WBuffer; //�ڿ�
    static ID3D11Buffer*       ColorBuffer;
    static class ObLine*       Axis; //��,����

protected:
    static Shader* BasicShader; 
    static Shader* ImageShader;
   //���ĺ��� ����
    static ID3D11BlendState* BlendStateOff;//���� ���� ��
public:
    static ID3D11BlendState* BlendStateOn;
    //boolean
    bool                isActive; //Ȱ��ȭ
    bool                isAxis; //���� �׸��ų�?

    //transform
    Vector2		        Pivot;
    Matrix              S; //ũ�����
    Matrix              T; //�̵����
    Matrix              W; //�������
    Matrix              RT; //ȸ���̵����
    Matrix*             P; // �θ����
    Vector2             Position;   //���� ��ǥ
    Vector2             Scale;      //ũ�Ⱚ
    Vector3             Rotation;   //ȸ����
    Vector3             Rotation2;   //ȸ����
    Vector2             Up, Right; //����
    //Blend Color
    Color               color;
    //Collision type
    int                 CollisionType;

public:
    Object();
    virtual ~Object() {};

    void WorldUpdate();
    virtual void Render();
    static void CreateStaticMember();
    static void DeleteStaticMember();
    //���� ��ġ
    Vector2 GetWorldPos(){ return Vector2(RT._41, RT._42); }
    //������ ��ġ
    Vector2 GetWorldPivot() { return Vector2(W._41, W._42); }
};
