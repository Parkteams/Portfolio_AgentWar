#include "stdafx.h"
#include "Obstacle.h"

Obstacle::Obstacle()
{
	Root = new ObRect();
	Root->isFill = false;
}

Obstacle::~Obstacle()
{
	delete Root;
}

void Obstacle::Render()
{
	Root->Render();
}

Vector2 Obstacle::GetPos()
{
	return Root->GetWorldPos();
}

void Obstacle::SetPos(Vector2 pos)
{
	Root->Position = pos;
}
