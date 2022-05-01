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
    UINT        ImgIdx; //몇번째 이미지를 사용중인가
    int         state;  //타일 상태값
    int         F, G, H;//타일 비용
    Int2        idx;    //타일 인덱스
    Tile*       P;      //나를 갱신시킨 타일
    bool        isFind; //검사한적이 있는가?

    void ClearCost();         //비용 초기화
    void ClacH(Int2 DestIdx); //H계산해라
    void ClacF(); //F계산해라
};
//               타일주소,비교값
using PTile = pair<Tile*, int>;

struct compare
{
    //연산자 오버로딩
    bool operator()(PTile& a, PTile& b)
    {
        return a.second > b.second;
    }
};