#pragma once
class Tile;
class TileImg;
class TileMap
{
private:
    //�����Ϳ� ����
    Int2                    EditTileSize;
    char                    Savefile[128] = "TileMap1.txt";
    char                    Loadfile[128] = "TileMap1.txt";
    UINT                    ImgIdx;     //���° �̹���?
    Int2                    Frame;      //�ٲٷ��� ������ǥ
    int                     State;      //�ٲٷ��� ���°�
    


    void ResetPosition(Int2 from , Int2 to );
    void ResetTiles(Int2 from , Int2 to );
    void DeleteTiles(Int2 from , Int2 to );

    void TileButton();
    void TileBrush();

public:
    vector<TileImg>         Images;
    vector<vector<Tile>>    Tiles;
    Int2                    TileSize;   //����
    Vector2                 TileScale;  //Ÿ���Ѱ�ũ��
    Vector2                 LB;         //���ʾƷ��𼭸���
    bool                    isDebug;    //����׻���?
    TileMap();
    ~TileMap();
    void Init();
    void Update(); //�����Ϳ� �� gui �����
    void Render();

    void Save(string file);
    void Load(string file);
    //Vector2 -> TileIdx
    bool VectorToIdx(IN Vector2 pt, OUT Int2& Idx);
    Vector2 IdxToVector(Int2 idx);
    //��ã�� �Լ�                                       ���
    bool PathFinding(Int2 sour, Int2 dest, OUT vector<Tile*>& way);
};

