#include "stdafx.h"
#include "Tile.h"

void Tile::ClearCost()
{
    //����� ���Ѱ����� �ʱ�ȭ
    F = G = H = INT_MAX;
    P = nullptr;
    isFind = false;
}

void Tile::ClacH(Int2 DestIdx)
{
    //���� ������������ �������� ����ض�
    int tempX = abs(idx.x - DestIdx.x) * 10;
    int tempY = abs(idx.y - DestIdx.y) * 10;

    H = tempX + tempY;
}

void Tile::ClacF()
{
    F = G + H;
}
