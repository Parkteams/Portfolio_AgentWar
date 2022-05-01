#pragma once
class Obstacle
{
protected:
	ObRect* Root;

public:
	//Speed
	float Game_Speed;

	Obstacle();
	~Obstacle();
	void Render();
	Vector2 GetPos();
	void SetPos(Vector2 pos);
};

