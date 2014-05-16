#ifndef PROJECTILE
#define PROJECTILE

class Projectile;

#include "Spellmanager.h"
#include "Unit.h"

class Projectile : public Interactiveentity
{
private:
	std::string name;
	int pwr;
	int spd;
	int x, y;
	int direction;
	int distance;
	int max_distance;
	bool piercing;
	bool hit_on_contact;
	bool friendly_fire;
	bool is_active;
	int owner;
	Actionsequence sequence;
	SDL_Surface* spritesheet;
	std::string spell;

	void set_clips();
public:
	Projectile();
	~Projectile();
	void show_projectile();
	void handle_projectile(Spellmanager* sm, World map, Unit* units[]);
	Unit * check_collision(int x, int y, World map, Unit* units[]);
	bool Projectile::map_collision(World map);
	void create_projectile(int pw, int X, int Y, int dir, int own, std::string projectilename);
	void remove_projectile();
	bool get_active();
};

#endif