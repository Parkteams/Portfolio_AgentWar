#pragma once
class ObStar : public Object
{
private:

    static ID3D11Buffer* FillVertexBuffer;
    static ID3D11Buffer* VertexBuffer;

public:
    bool                isFill = true;
    void Render()override;
    static void CreateStaticMember();
    static void DeleteStaticMember();

};

