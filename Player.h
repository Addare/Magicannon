#ifndef PLAYER
#define PLAYER

class Player;
#include "Unit.h"
#include "Spellmanager.h"
#include "Entitymanager.h"
class Player : public Unit
{
private:
		int xSpd;
		int ySpd;
		std::string spell;

		void set_dest();

public:
	Player(Entitymanager* man);
	~Player();
	void handle_input();
	void create_player(string name, int id, int X, int Y,Collisionmanager* col);
	void remove_unit();
};

#endif