#include "stdafx.h"
#include "Obstacle.h"
#include "Tree1.h"

Tree1::Tree1()
{
    Tree = new ObImage(L"Image/TDS/Object/TDS04_0022_Tree1.png");
    Tree->Scale = Vector2(50.0f, 50.0f);
    Tree->P = &Root->RT;

    HitBox = new ObRect();
    HitBox->isFill = false;
    HitBox->Scale = Vector2(50.0f, 50.0f);
    HitBox->Pivot = Vector2(0.0f, 0.0f);
    HitBox->P = &Root->RT;
}

Tree1::~Tree1()
{
    delete Tree;
    delete HitBox;
}

void Tree1::Update()
{
}

void Tree1::Render()
{
    Obstacle::Render();
    Tree->Render();
    /*HitBox->Render();*/
}