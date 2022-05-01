#include "stdafx.h"
#include "Item.h"

Item::Item()
{
	Root = new ObRect();
	Root->isFill = false;
}

Item::~Item()
{
	delete Root;
}

void Item::Render()
{
	Root->Render();
}

Vector2 Item::GetPos()
{
	return Root->GetWorldPos();
}

void Item::SetPos(Vector2 pos)
{
	Root->Position = pos;
}
