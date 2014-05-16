#ifndef SPELL
#define SPELL

class Spell;

#include "Unit.h"
#include "Spellmanager.h"

class Spell : public Interactiveentity
{
private:
	int x;
	int y;
	int size;
	int owner;
	bool ** hitbox;
	int hits;
	int pwr;				//behˆvde hÂlla reda pÅEbasskadan fˆr att kunna skapa fler spells med samma power
	int dmg;
	int duration;
	int direction;
	int hitdelay;
	Activate activates[10];
	bool singleblit;
	bool is_active;
	bool end_after_hits;
	Unit * hitdelayed;
	int hitdelaytimer[UNIT_AMOUNT];
	int delaypointer;
	Actionsequence sequence;
	SDL_Surface* spritesheet;

public:
	Spell();
	~Spell();
	void create_spell(int pwr, int X, int Y, int dir,int own, std::string name);
	void end_spell();
	void handle_collision(Spellmanager* sm, World map, Unit* units[]);
	Unit* check_collision(int X, int Y, World map, Unit* units[]);
	bool is_delayed(Unit* unit);
	void handle_timer(Spellmanager* sm, World map, Unit* units[]);
	void show_spell();
	bool get_active();
	void turn_spell();
};

#endif