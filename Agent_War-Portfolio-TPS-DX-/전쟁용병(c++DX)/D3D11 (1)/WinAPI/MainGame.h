#pragma once
class MainGame
{
private:
    ID3D11DepthStencilState*    depthStencilState;
    ID3D11RasterizerState*      rasterizerState;
    bool                        isVsync; //��������ȭ �Ұ���
    
public:
    MainGame();//����
    ~MainGame();//�Ҹ�

    void Init();//�ʱ�ȭ

    //����
    void Update();//����
    void LateUpdate();//��������
    void Render();//�׸���
    void TextRender();//�׸���
};

