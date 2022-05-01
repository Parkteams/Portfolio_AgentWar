#include "stdafx.h"
#include "Tile.h"

void Tile::ClearCost()
{
    //비용을 무한값으로 초기화
    F = G = H = INT_MAX;
    P = nullptr;
    isFind = false;
}

void Tile::ClacH(Int2 DestIdx)
{
    //너의 목적지까지의 예상비용을 계산해라
    int tempX = abs(idx.x - DestIdx.x) * 10;
    int tempY = abs(idx.y - DestIdx.y) * 10;

    H = tempX + tempY;
}

void Tile::ClacF()
{
    F = G + H;
}
