#pragma once
//¼±
class ObLine : public Object
{
private:
    static ID3D11Buffer* VertexBuffer;
public:
    void Render();
    static void CreateStaticMember();
    static void DeleteStaticMember();
};


