#include "stdafx.h"
#include "Obstacle.h"
#include "Tree2.h"

Tree2::Tree2()
{
    Tree = new ObImage(L"Image/TDS/Object/TDS04_0019_Tree4.png");
    Tree->Scale = Vector2(50.0f, 50.0f);
    Tree->P = &Root->RT;

    HitBox = new ObRect();
    HitBox->isFill = false;
    HitBox->Scale = Vector2(50.0f, 50.0f);
    HitBox->Pivot = Vector2(0.0f, 0.0f);
    HitBox->P = &Root->RT;
}

Tree2::~Tree2()
{
    delete Tree;
    delete HitBox;
}

void Tree2::Update()
{
}

void Tree2::Render()
{
    Obstacle::Render();
    Tree->Render();
    /*HitBox->Render();*/
}