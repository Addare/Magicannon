#ifndef ENEMY
#define ENEMY

class Enemy;
#include "Unit.h"
class Enemy : public Unit
{
private:
//	AI ai;

public:
	Enemy(Entitymanager* man);
	~Enemy();
	void create_enemy(std::string name,int ID, int X, int Y,Collisionmanager* col);
	void remove_enemy();
};

#endif