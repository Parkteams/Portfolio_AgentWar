#include "stdafx.h"
#include "Tile.h"
#include "TileMap.h"

TileMap::TileMap()
{
    TileSize = Int2(30, 20);
    TileScale = Vector2(50.0f, 50.0f);
    LB = Vector2(50.0f, 50.0f);
    isDebug = false;
    Tiles.resize(TileSize.x);
    for (int i = 0; i < TileSize.x; i++)
    {
        Tiles[i].resize(TileSize.y);
    }

    EditTileSize = TileSize;
}

TileMap::~TileMap()
{
    DeleteTiles(Int2(0, 0), TileSize);
}

void TileMap::Init()
{
    ResetTiles(Int2(0, 0), TileSize);
    ResetPosition(Int2(0, 0), TileSize);
}

void TileMap::Update()
{
    TileButton();
    if (ImGui::InputInt("State", &State))
    {
        if (State < TILE_NONE)
        {
            State = TILE_NONE;
        }
        if (State > TILE_BUSH)
        {
            State = TILE_BUSH;
        }
    }
    TileBrush();
    
    if (ImGui::SliderFloat2("LB", (float*)&LB, -1000.f, 1000.f))
    {
        ResetPosition(Int2(0, 0), TileSize);
    }
    if (ImGui::SliderFloat2("Scale", (float*)&TileScale, 1.0f, 1000.f))
    {
        ResetPosition(Int2(0, 0), TileSize);
    }
    if (ImGui::InputInt("Size.X", &EditTileSize.x))
    {
        //   21                  20
        if (EditTileSize.x > TileSize.x)
        {
            //끝에 하나 추가
            Tiles.emplace_back();
            //마지막 배열원소에 마찬가지로 사이즈를 y만큼 늘려놓기
            Tiles[TileSize.x].resize(TileSize.y);

            ResetTiles(Int2(TileSize.x, 0), Int2(TileSize.x + 1, TileSize.y));
            ResetPosition(Int2(TileSize.x, 0), Int2(TileSize.x + 1, TileSize.y));
            TileSize.x = EditTileSize.x;
        }
        //줄여야함
        else
        {
            DeleteTiles(Int2(TileSize.x - 1, 0), TileSize);
            Tiles[TileSize.x - 1].clear();
            Tiles.pop_back();
            TileSize.x = EditTileSize.x;
        }
    }
    if (ImGui::InputInt("Size.Y", &EditTileSize.y))
    {
        if (EditTileSize.y > TileSize.y)
        {
            for (int i = 0; i < TileSize.x; i++)
            {
                Tiles[i].emplace_back();
            }

            ResetTiles(Int2(0, TileSize.y), Int2(TileSize.x, TileSize.y + 1));
            ResetPosition(Int2(0, TileSize.y), Int2(TileSize.x, TileSize.y + 1));
            TileSize.y = EditTileSize.y;
        }
        else
        {
            DeleteTiles(Int2(0, TileSize.y - 1),
                Int2(TileSize.x, TileSize.y));

            for (int i = 0; i < TileSize.x; i++)
            {
                Tiles[i].pop_back();
            }
            TileSize.y = EditTileSize.y;
        }
    }
    //char file[128] = "";
    ImGui::InputText("SaveFile", Savefile, 128);
    if (ImGui::Button("SAVE"))
    {
        Save(Savefile);
    }
    ImGui::InputText("LoadFile", Loadfile, 128);
    if (ImGui::Button("Load"))
    {
        Load(Loadfile);
    }
    if (ImGui::Checkbox("isDebug", &isDebug))
    {
        if (!isDebug)
        {
            for (int i = 0; i < TileSize.x; i++)
            {
                for (int j = 0; j < TileSize.y; j++)
                {
                    Tiles[i][j].img->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
                }
            }
        }
    }
}

void TileMap::Render()
{
    Vector2 WindowLB = MAINCAM->Pos;
    Vector2 WindowRT = MAINCAM->Pos + Vector2(WINSIZEX,WINSIZEY);
    Int2 Min,Max;
    //창 좌표를 타일맵 i,j로 변환
    VectorToIdx(WindowLB, Min);
    VectorToIdx(WindowRT, Max);
    //인덱스를 벗어나는값 막아주기
    Saturate(Min.x, 0, TileSize.x - 1);
    Saturate(Min.y, 0, TileSize.y - 1);
    Saturate(Max.x, 0, TileSize.x - 1);
    Saturate(Max.y, 0, TileSize.y - 1);


    if (!isDebug)
    {
        for (int i = Min.x; i <= Max.x; i++)
        {
            for (int j = Min.y; j <= Max.y; j++)
            {
                Tiles[i][j].img->Render();
            }
        }
    }
    else
    {
        for (int i = Min.x; i <= Max.x; i++)
        {
            for (int j = Min.y; j <= Max.y; j++)
            {
                if (Tiles[i][j].state == TILE_NONE)
                {
                    Tiles[i][j].img->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
                    Tiles[i][j].img->Render();
                }
                if (Tiles[i][j].state == TILE_WALL)
                {
                    Tiles[i][j].img->color = Color(1.0f, 0.5f, 0.5f, 0.5f);
                    Tiles[i][j].img->Render();
                }
                if (Tiles[i][j].state == TILE_ASPHALT)
                {
                    Tiles[i][j].img->color = Color(1.0f, 0.5f, 1.0f, 0.5f);
                    Tiles[i][j].img->Render();
                }
                if (Tiles[i][j].state == TILE_SAND)
                {
                    Tiles[i][j].img->color = Color(1.0f, 1.0f, 0.5f, 0.5f);
                    Tiles[i][j].img->Render();
                }
                if (Tiles[i][j].state == TILE_BUSH)
                {
                    Tiles[i][j].img->color = Color(0.5f, 0.5f, 1.0f, 0.5f);
                    Tiles[i][j].img->Render();
                }
            }
        }
    }
}

void TileMap::ResetPosition(Int2 from, Int2 to)
{
    for (int i = from.x; i < to.x; i++)
    {
        for (int j = from.y; j < to.y; j++)
        {
            Tiles[i][j].img->Scale = TileScale;
            Tiles[i][j].img->Position
                = LB + Vector2(i * TileScale.x, j * TileScale.y);
        }
    }
}

void TileMap::ResetTiles(Int2 from, Int2 to)
{
    for (int i = from.x; i < to.x; i++)
    {
        for (int j = from.y; j < to.y; j++)
        {
            Tiles[i][j].img = new ObImage(Images[0].File);
            Tiles[i][j].img->MaxFrame = Images[0].MaxFrame;
            Tiles[i][j].img->Pivot = OFFSET_LB;
            Tiles[i][j].ImgIdx = 0;
            Tiles[i][j].state = TILE_NONE;
            Tiles[i][j].idx = Int2(i, j);
        }
    }
}

void TileMap::DeleteTiles(Int2 from, Int2 to)
{
    for (int i = from.x; i < to.x; i++)
    {
        for (int j = from.y; j < to.y; j++)
        {
            delete Tiles[i][j].img;
        }
    }
}

void TileMap::TileButton()
{
    int tempIdx = ImgIdx;
    //이미지 넘기기
    if (ImGui::InputInt("ImgIdx", &tempIdx))
    {
        if (tempIdx > (int)Images.size() - 1)
        {
            ImgIdx = 0; //첫번째이미지로 돌리기
        }
        else if (tempIdx < 0)
        {
            //마지막 이미지로 돌리기
            ImgIdx = Images.size() - 1;
        }
        else
        {
            ImgIdx = tempIdx;
        }
    }

    Int2 MF = Images[ImgIdx].MaxFrame;
    ImVec2 size;
    // 300 x 300안에 이미지갯수만큼 나누기
    size.x = 300.0f / (float)MF.x;
    size.y = 300.0f / (float)MF.y;

    //텍스쳐 좌표
    ImVec2 LT, RB;
    int index = 0;
    for (UINT i = 0; i < MF.y; i++)
    {
        for (UINT j = 0; j < MF.x; j++)
        {
            if (j != 0)
            {
                //같은줄에 배치
                ImGui::SameLine();
            }
            //텍스쳐 좌표
            LT.x = 1.0f / MF.x * j;
            LT.y = 1.0f / MF.y * i;
            RB.x = 1.0f / MF.x * (j + 1);
            RB.y = 1.0f / MF.y * (i + 1);

            ID3D11ShaderResourceView* srv =
                TEXTURE->LoadTexture(Images[ImgIdx].File);
            //이게있어야 버튼이 각자 눌림
            ImGui::PushID(index);
            //눌리는 이미지버튼
            if (ImGui::ImageButton((void*)srv, size, LT, RB))
            {
                Frame.x = j;
                Frame.y = i;
            }
            index++;
            ImGui::PopID();
        }
    }
}

void TileMap::TileBrush()
{
    //마우스가 ImGui 창 위에 없을때
    ImVec2 min = ImGui::GetWindowPos();
    ImVec2 max;
    max.x = min.x + ImGui::GetWindowSize().x;
    max.y = min.y + ImGui::GetWindowSize().y;

    if (!ImGui::IsMouseHoveringRect(min, max))
    {
        if (INPUT->KeyPress(VK_LBUTTON))
        {
            //cout << TIMER->GetWorldTime() << endl;
            //Tiles[3][2].img->Frame = Frame;
            Int2 idx;
            if (VectorToIdx(g_WorldMouse, idx))
            {
                ObImage* Target
                    = Tiles[idx.x][idx.y].img;
                Target->Frame = Frame;
                Tiles[idx.x][idx.y].state = State;
                if (ImgIdx != Tiles[idx.x][idx.y].ImgIdx)
                {
                    Tiles[idx.x][idx.y].ImgIdx = ImgIdx;
                    Target->ChangeImage(Images[ImgIdx].File,
                        Images[ImgIdx].MaxFrame);
                }
            }
        }
    }


}

void TileMap::Save(string file)
{
    ofstream fout;
    fout.open(file.c_str(), ios::out);

    if (fout.is_open())
    {
        fout << EditTileSize.x << ' ' << EditTileSize.y << endl;
        fout <<TileSize.x << ' ' << TileSize.y << endl;
        fout << TileScale.x << ' ' << TileScale.y << endl;
        fout << LB.x << ' ' << LB.y << endl;

        for (int i = 0; i < TileSize.x; i++)
        {
            for (int j = 0; j < TileSize.y; j++)
            {
                fout << Tiles[i][j].ImgIdx << endl;
                fout << Tiles[i][j].state << endl;
                fout << Tiles[i][j].img->Frame.x <<
                    ' ' << Tiles[i][j].img->Frame.y << endl;
            }
        }
        fout.close();
    }
}

void TileMap::Load(string file)
{
    ifstream fin;
    fin.open(file.c_str(), ios::in);

    if (fin.is_open())
    {
        //원래들고있던 벡터 해제
        DeleteTiles(Int2(0, 0), TileSize);
        for (int i = 0; i < TileSize.x; i++)
        {
            Tiles[i].clear();
        }
        Tiles.clear();

        fin >> EditTileSize.x >> EditTileSize.y;
        fin >> TileSize.x >> TileSize.y;
        fin >> TileScale.x >> TileScale.y;
        fin >> LB.x >> LB.y;


        Tiles.resize(TileSize.x);
        for (int i = 0; i < TileSize.x; i++)
        {
            Tiles[i].resize(TileSize.y);
        }
        ResetTiles(Int2(0, 0), TileSize);
        ResetPosition(Int2(0, 0), TileSize);
       
        for (int i = 0; i < TileSize.x; i++)
        {
            for (int j = 0; j < TileSize.y; j++)
            {
                int ImgIdx;
                fin >> ImgIdx;
                //들고있는 이미지 인덱스랑 다른경우
                if (Tiles[i][j].ImgIdx != ImgIdx)
                {
                    Tiles[i][j].img->ChangeImage(Images[ImgIdx].File,
                        Images[ImgIdx].MaxFrame);
                    Tiles[i][j].ImgIdx = ImgIdx;
                }

                fin >> Tiles[i][j].state;
                fin >> Tiles[i][j].img->Frame.x 
                    >> Tiles[i][j].img->Frame.y;
            }
        }
        fin.close();
    }
}

bool TileMap::VectorToIdx(IN Vector2 pt, OUT Int2& Idx)
{
    pt -= LB;

    Idx.x = (int)(pt.x / TileScale.x);
    Idx.y = (int)(pt.y / TileScale.y);

    //벗어난 좌표인지?
    if (Idx.x < 0 || Idx.y < 0 ||
        Idx.x > TileSize.x - 1 || Idx.y > TileSize.y - 1)
        return false;

    return true;
}

Vector2 TileMap::IdxToVector(Int2 idx)
{
    Vector2 temp;
    temp.x = LB.x + (idx.x + 0.5f) * TileScale.x;
    //temp.x = LB.x + idx.x  * TileScale.x + 0.5f * TileScale.x;
    temp.y = LB.y + (idx.y + 0.5f) * TileScale.y;
    return temp;
}

bool TileMap::PathFinding(Int2 sour, Int2 dest, OUT vector<Tile*>& way)
{
    //둘중에 하나가 벽이면 갈 수 있는길이 없다.
    if (Tiles[dest.x][dest.y].state == TILE_WALL ||
        Tiles[sour.x][sour.y].state == TILE_WALL)
    {
        return false;
    }
    //기존에 있던 길은 전부 비운다.
    way.clear();
    //출발지 목적지 같으면
    if (sour == dest)
    {
        return false;//제자리 멈추기
    }
    //타일 비용 초기화
    for (int i = 0; i < TileSize.x; i++)
    {
        for (int j = 0; j < TileSize.y; j++)
        {
            Tiles[i][j].ClearCost();
        }
    }
    //우선순위 큐
    /*Tile* a, b;
    if (a > b)
    {

    }
    priority_queue<char> List2;*/

    //F값을 가지고 정렬해주는 리스트
    priority_queue<PTile, vector<PTile>, compare> List;

    //리스트에 출발지를 추가
    Tile* pTemp = &Tiles[sour.x][sour.y];
    pTemp->G = 0;//출발지 현재비용은 0
    pTemp->ClacH(dest);//목적지까지 예상비용 만들기
    pTemp->ClacF(); //총예상비용 만들기
    List.push({ pTemp ,pTemp->F });

    //도착점까지 비용이 생길때 까지 반복
    while (1)
    {
        //꺼내야될 F값이 더이상 없을때
        if (List.empty())
        {
            return false;
        }

        //탐색노드 받아오기
        PTile Temp = List.top();
        //탐색목록에서 제외
        Temp.first->isFind = true;
        //맨윗값 빼버리기
        List.pop();

        //맨윗값이 도착점이면 종료(길찾기 종료조건)
        if (Temp.first->idx == dest)
        {
            break;
        }

        //인접 타일 비용검사
        vector<Int2> LoopIdx;

        //왼쪽타일이 존재할때
        if (Temp.first->idx.x > 0)
        {
            LoopIdx.push_back(Int2(Temp.first->idx.x - 1,
                Temp.first->idx.y));
        }
        //위쪽타일이 존재할때
        if (Temp.first->idx.y > 0)
        {
            LoopIdx.push_back(Int2(Temp.first->idx.x,
                Temp.first->idx.y - 1));
        }
        //오른쪽타일이 존재할때
        if (Temp.first->idx.x < TileSize.x - 1)
        {
            LoopIdx.push_back(Int2(Temp.first->idx.x + 1,
                Temp.first->idx.y));
        }
        //아래쪽타일이 존재할때
        if (Temp.first->idx.y < TileSize.y - 1)
        {
            LoopIdx.push_back(Int2(Temp.first->idx.x,
                Temp.first->idx.y + 1));
        }
        //상하좌우타일 비용검사
        for (int i = 0; i < LoopIdx.size(); i++)
        {
            Tile* loop =
                &Tiles[LoopIdx[i].x][LoopIdx[i].y];
            //벽이 아닐때
            if (loop->state != TILE_WALL)
            {
                //예상비용 만들기
                loop->ClacH(dest);
                //현재 가지고있는 비용이 클때
                if (loop->G > Temp.first->G + 10)
                {
                    //비용갱신
                    loop->G = Temp.first->G + 10;
                    loop->ClacF();
                    //누구로부터 갱신인지 표시
                    loop->P = Temp.first;
                    //이 타일이 찾은적 없던 타일이면 리스트에 추가
                    if (!loop->isFind)
                    {
                        List.push({ loop,loop->F });
                    }
                }
            }
        }
        LoopIdx.clear();

        //대각선4개 




    }
    //도착지가 설정이 되었을때

    Tile* p = &Tiles[dest.x][dest.y];
    //dest 4,1 -> 4,2 -> 4,3 -> 3,3 ->2,3-> 1,3 ->
    while (1)
    {
        way.push_back(p);
        p = p->P;
        if (p == nullptr)
        {
            break;
        }
    }
    return true;
}