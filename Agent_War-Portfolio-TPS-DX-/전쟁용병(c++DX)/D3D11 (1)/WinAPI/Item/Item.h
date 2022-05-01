#pragma once
class Item
{
protected:
	ObRect* Root;

public:
	Item();
	~Item();
	void Render();
	Vector2 GetPos();
	void SetPos(Vector2 pos);
};

