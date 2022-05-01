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
            //���� �ϳ� �߰�
            Tiles.emplace_back();
            //������ �迭���ҿ� ���������� ����� y��ŭ �÷�����
            Tiles[TileSize.x].resize(TileSize.y);

            ResetTiles(Int2(TileSize.x, 0), Int2(TileSize.x + 1, TileSize.y));
            ResetPosition(Int2(TileSize.x, 0), Int2(TileSize.x + 1, TileSize.y));
            TileSize.x = EditTileSize.x;
        }
        //�ٿ�����
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
    //â ��ǥ�� Ÿ�ϸ� i,j�� ��ȯ
    VectorToIdx(WindowLB, Min);
    VectorToIdx(WindowRT, Max);
    //�ε����� ����°� �����ֱ�
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
    //�̹��� �ѱ��
    if (ImGui::InputInt("ImgIdx", &tempIdx))
    {
        if (tempIdx > (int)Images.size() - 1)
        {
            ImgIdx = 0; //ù��°�̹����� ������
        }
        else if (tempIdx < 0)
        {
            //������ �̹����� ������
            ImgIdx = Images.size() - 1;
        }
        else
        {
            ImgIdx = tempIdx;
        }
    }

    Int2 MF = Images[ImgIdx].MaxFrame;
    ImVec2 size;
    // 300 x 300�ȿ� �̹���������ŭ ������
    size.x = 300.0f / (float)MF.x;
    size.y = 300.0f / (float)MF.y;

    //�ؽ��� ��ǥ
    ImVec2 LT, RB;
    int index = 0;
    for (UINT i = 0; i < MF.y; i++)
    {
        for (UINT j = 0; j < MF.x; j++)
        {
            if (j != 0)
            {
                //�����ٿ� ��ġ
                ImGui::SameLine();
            }
            //�ؽ��� ��ǥ
            LT.x = 1.0f / MF.x * j;
            LT.y = 1.0f / MF.y * i;
            RB.x = 1.0f / MF.x * (j + 1);
            RB.y = 1.0f / MF.y * (i + 1);

            ID3D11ShaderResourceView* srv =
                TEXTURE->LoadTexture(Images[ImgIdx].File);
            //�̰��־�� ��ư�� ���� ����
            ImGui::PushID(index);
            //������ �̹�����ư
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
    //���콺�� ImGui â ���� ������
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
        //��������ִ� ���� ����
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
                //����ִ� �̹��� �ε����� �ٸ����
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

    //��� ��ǥ����?
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
    //���߿� �ϳ��� ���̸� �� �� �ִ±��� ����.
    if (Tiles[dest.x][dest.y].state == TILE_WALL ||
        Tiles[sour.x][sour.y].state == TILE_WALL)
    {
        return false;
    }
    //������ �ִ� ���� ���� ����.
    way.clear();
    //����� ������ ������
    if (sour == dest)
    {
        return false;//���ڸ� ���߱�
    }
    //Ÿ�� ��� �ʱ�ȭ
    for (int i = 0; i < TileSize.x; i++)
    {
        for (int j = 0; j < TileSize.y; j++)
        {
            Tiles[i][j].ClearCost();
        }
    }
    //�켱���� ť
    /*Tile* a, b;
    if (a > b)
    {

    }
    priority_queue<char> List2;*/

    //F���� ������ �������ִ� ����Ʈ
    priority_queue<PTile, vector<PTile>, compare> List;

    //����Ʈ�� ������� �߰�
    Tile* pTemp = &Tiles[sour.x][sour.y];
    pTemp->G = 0;//����� �������� 0
    pTemp->ClacH(dest);//���������� ������ �����
    pTemp->ClacF(); //�ѿ����� �����
    List.push({ pTemp ,pTemp->F });

    //���������� ����� ���涧 ���� �ݺ�
    while (1)
    {
        //�����ߵ� F���� ���̻� ������
        if (List.empty())
        {
            return false;
        }

        //Ž����� �޾ƿ���
        PTile Temp = List.top();
        //Ž����Ͽ��� ����
        Temp.first->isFind = true;
        //������ ��������
        List.pop();

        //�������� �������̸� ����(��ã�� ��������)
        if (Temp.first->idx == dest)
        {
            break;
        }

        //���� Ÿ�� ���˻�
        vector<Int2> LoopIdx;

        //����Ÿ���� �����Ҷ�
        if (Temp.first->idx.x > 0)
        {
            LoopIdx.push_back(Int2(Temp.first->idx.x - 1,
                Temp.first->idx.y));
        }
        //����Ÿ���� �����Ҷ�
        if (Temp.first->idx.y > 0)
        {
            LoopIdx.push_back(Int2(Temp.first->idx.x,
                Temp.first->idx.y - 1));
        }
        //������Ÿ���� �����Ҷ�
        if (Temp.first->idx.x < TileSize.x - 1)
        {
            LoopIdx.push_back(Int2(Temp.first->idx.x + 1,
                Temp.first->idx.y));
        }
        //�Ʒ���Ÿ���� �����Ҷ�
        if (Temp.first->idx.y < TileSize.y - 1)
        {
            LoopIdx.push_back(Int2(Temp.first->idx.x,
                Temp.first->idx.y + 1));
        }
        //�����¿�Ÿ�� ���˻�
        for (int i = 0; i < LoopIdx.size(); i++)
        {
            Tile* loop =
                &Tiles[LoopIdx[i].x][LoopIdx[i].y];
            //���� �ƴҶ�
            if (loop->state != TILE_WALL)
            {
                //������ �����
                loop->ClacH(dest);
                //���� �������ִ� ����� Ŭ��
                if (loop->G > Temp.first->G + 10)
                {
                    //��밻��
                    loop->G = Temp.first->G + 10;
                    loop->ClacF();
                    //�����κ��� �������� ǥ��
                    loop->P = Temp.first;
                    //�� Ÿ���� ã���� ���� Ÿ���̸� ����Ʈ�� �߰�
                    if (!loop->isFind)
                    {
                        List.push({ loop,loop->F });
                    }
                }
            }
        }
        LoopIdx.clear();

        //�밢��4�� 




    }
    //�������� ������ �Ǿ�����

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