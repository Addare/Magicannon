#ifndef SPELLMANAGER
#define SPELLMANAGER

class Spellmanager;

#include "Projectile.h"
#include "Spell.h"

class Spellmanager
{
private:
	Projectile projectiles[PROJECTILE_AMOUNT];
	Spell spells[PROJECTILE_AMOUNT];

	int get_free_projectile();
	int get_free_spell();

public:
	Spellmanager();
	~Spellmanager();
	void create_projectile(int pwr, int x, int y, int direction, int owner, std::string name);
	void create_spell(int pwr, int x, int y, int owner, int direction, std::string name);
	void show();
	void handle(Unit* units[], World map);


};

#endif