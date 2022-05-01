#pragma once
class ObCircle : public Object
{
private:

    static ID3D11Buffer* FillVertexBuffer;
    static ID3D11Buffer* VertexBuffer;

public:
    ObCircle() { CollisionType = COL_CIRCLE; };
    bool                isFill = true;
    void Render()override;
    static void CreateStaticMember();
    static void DeleteStaticMember();

};

