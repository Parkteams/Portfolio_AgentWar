#pragma once

enum TileState
{
    TILE_NONE,
    TILE_WALL,
    TILE_ASPHALT,
    TILE_SAND,
    TILE_BUSH

};

class TileImg
{
public:
    TileImg(wstring file, Int2 maxframe)
    {
        File = file; MaxFrame = maxframe;
    }
    wstring  File;
    Int2     MaxFrame;
};

class Tile
{
public:
    ObImage*    img;
    UINT        ImgIdx; //���° �̹����� ������ΰ�
    int         state;  //Ÿ�� ���°�
    int         F, G, H;//Ÿ�� ���
    Int2        idx;    //Ÿ�� �ε���
    Tile*       P;      //���� ���Ž�Ų Ÿ��
    bool        isFind; //�˻������� �ִ°�?

    void ClearCost();         //��� �ʱ�ȭ
    void ClacH(Int2 DestIdx); //H����ض�
    void ClacF(); //F����ض�
};
//               Ÿ���ּ�,�񱳰�
using PTile = pair<Tile*, int>;

struct compare
{
    //������ �����ε�
    bool operator()(PTile& a, PTile& b)
    {
        return a.second > b.second;
    }
};