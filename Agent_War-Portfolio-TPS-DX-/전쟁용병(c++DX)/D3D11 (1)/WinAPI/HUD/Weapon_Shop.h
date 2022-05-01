#pragma once
class Player;

class Weapon_Shop
{
private:
	ObImage* HUD;
	ObRect* HitBox_P;
	ObRect* HitBox_R;
	ObRect* HitBox_MG;
	ObRect* HitBox_GT;
	ObRect* HitBox_FT;
	ObRect* HitBox_R_B;
	ObRect* HitBox_MG_B;
	ObRect* HitBox_GT_B;
	ObRect* HitBox_FT_B;
	ObRect* HitBox_HEALTH;
	ObRect* HitBox_ARMOR;

	//Player
	Player* pl;

	//Mouse
	int Click_Num;
	

public:
	int Upgrade_P;
	int Upgrade_R;
	int Upgrade_MG;
	int Upgrade_GT;
	int Upgrade_FT;

	ObRect* HitBox_OK;

	Weapon_Shop();
	~Weapon_Shop();
	void Init();
	void Update();
	void Render();

	MAKESET(Player*, pl)
};

