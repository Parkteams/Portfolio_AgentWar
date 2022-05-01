#pragma once
class HUD
{
private:
	ObImage* Bar;
	ObImage* Hp;
	ObImage* Armor;
	ObImage* Pistol;
	ObImage* Mg;
	ObImage* Rifle;
	ObImage* Gl;
	ObImage* Ft;
	ObImage* Bullet;
	ObImage* Menu;
	ObImage* Money;
	ObImage* Play;
	ObImage* Play2;
	ObImage* Stop;

public:
	ObRect* Play_Box;
	ObRect* Play2_Box;
	ObRect* Stop_Box;
	ObRect* Hp_Bar;
	ObRect* Armor_Bar;

	int Gun_Kind;
	HUD();
	~HUD();
	void Init();
	void Update();
	void Render();
};

