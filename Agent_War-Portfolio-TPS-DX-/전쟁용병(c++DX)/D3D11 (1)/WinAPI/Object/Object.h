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
    Matrix              Pi; //중심점값
    Matrix              R; //자전 회전행렬(z축)
    Matrix              R2; //공전 회전행렬(z축)
    
    //static
    static ID3D11Buffer*       WBuffer; //자원
    static ID3D11Buffer*       ColorBuffer;
    static class ObLine*       Axis; //축,원점

protected:
    static Shader* BasicShader; 
    static Shader* ImageShader;
   //알파블렌딩 시작
    static ID3D11BlendState* BlendStateOff;//알파 블렌딩 끝
public:
    static ID3D11BlendState* BlendStateOn;
    //boolean
    bool                isActive; //활성화
    bool                isAxis; //축을 그릴거냐?

    //transform
    Vector2		        Pivot;
    Matrix              S; //크기행렬
    Matrix              T; //이동행렬
    Matrix              W; //월드행렬
    Matrix              RT; //회전이동행렬
    Matrix*             P; // 부모행렬
    Vector2             Position;   //기준 좌표
    Vector2             Scale;      //크기값
    Vector3             Rotation;   //회전값
    Vector3             Rotation2;   //회전값
    Vector2             Up, Right; //방향
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
    //축의 위치
    Vector2 GetWorldPos(){ return Vector2(RT._41, RT._42); }
    //원점의 위치
    Vector2 GetWorldPivot() { return Vector2(W._41, W._42); }
};
