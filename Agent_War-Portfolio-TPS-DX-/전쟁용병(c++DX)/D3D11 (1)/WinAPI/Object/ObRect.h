#pragma once
class ObRect: public Object
{
private:

    static ID3D11Buffer*       FillVertexBuffer;
    static ID3D11Buffer*       VertexBuffer;
   
public:
    ObRect() { CollisionType = COL_RECT; };
    bool                isFill = true;
    void Render()override;
    static void CreateStaticMember();
    static void DeleteStaticMember();
    
};

