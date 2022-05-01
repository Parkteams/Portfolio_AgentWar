#pragma once
class Player;

class NPC1 : public Character
{
private:
	ObImage* NPC1_Idle;

	//Player
	Player* pl;

	
	
public:
	ObRect* HitBox;
	ObCircle* Range;

	float Rotation;

	NPC1();
	~NPC1();

	void Update();
	void LateUpdate();
	void Render();

	MAKESET(Player*, pl)
};

