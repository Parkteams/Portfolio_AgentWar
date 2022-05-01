#pragma once
class Tile;
class TileImg;
class TileMap
{
private:
    //에디터용 변수
    Int2                    EditTileSize;
    char                    Savefile[128] = "TileMap1.txt";
    char                    Loadfile[128] = "TileMap1.txt";
    UINT                    ImgIdx;     //몇번째 이미지?
    Int2                    Frame;      //바꾸려는 분할좌표
    int                     State;      //바꾸려는 상태값
    


    void ResetPosition(Int2 from , Int2 to );
    void ResetTiles(Int2 from , Int2 to );
    void DeleteTiles(Int2 from , Int2 to );

    void TileButton();
    void TileBrush();

public:
    vector<TileImg>         Images;
    vector<vector<Tile>>    Tiles;
    Int2                    TileSize;   //갯수
    Vector2                 TileScale;  //타일한개크기
    Vector2                 LB;         //왼쪽아래모서리점
    bool                    isDebug;    //디버그상태?
    TileMap();
    ~TileMap();
    void Init();
    void Update(); //에디터에 쓸 gui 만들기
    void Render();

    void Save(string file);
    void Load(string file);
    //Vector2 -> TileIdx
    bool VectorToIdx(IN Vector2 pt, OUT Int2& Idx);
    Vector2 IdxToVector(Int2 idx);
    //길찾기 함수                                       경로
    bool PathFinding(Int2 sour, Int2 dest, OUT vector<Tile*>& way);
};

