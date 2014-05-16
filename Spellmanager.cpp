#include "main.h"

Spellmanager::Spellmanager()
{
}

Spellmanager::~Spellmanager()
{
}

int Spellmanager::get_free_projectile()
{
	for(int i=0;i<PROJECTILE_AMOUNT;i++)
	{
		if(projectiles[i].get_active()==false)
		{
			return i;
		}
	}
	return 0;
}

int Spellmanager::get_free_spell()
{
	for(int i=0;i<PROJECTILE_AMOUNT;i++)
	{
		if(spells[i].get_active()==false)
		{
			return i;
		}
	}
	return 0;
}
void Spellmanager::create_projectile(int pwr, int x, int y, int direction, int owner, std::string name)
{
	projectiles[get_free_projectile()].create_projectile(pwr, x, y, direction, owner, name);
}

void Spellmanager::create_spell(int pwr, int x, int y, int direction, int owner, std::string name)
{
	spells[get_free_spell()].create_spell(pwr, x, y, direction, owner, name);
}

void Spellmanager::show()
{
	for(int i=0;i<PROJECTILE_AMOUNT;i++)
	{
		spells[i].show_spell();
	}
	for(int i=0;i<PROJECTILE_AMOUNT;i++)
	{
		projectiles[i].show_projectile();
	}
}
void Spellmanager::handle(Unit* units[], World map)
{
	for(int i=0;i<PROJECTILE_AMOUNT;i++)
	{
		spells[i].handle_timer(this, map, units);
		spells[i].handle_collision(this, map, units);
	}
	for(int i=0;i<PROJECTILE_AMOUNT;i++)
	{
		projectiles[i].handle_projectile(this, map, units);
	}
}

