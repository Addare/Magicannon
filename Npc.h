#ifndef NPC
#define NPC

class Npc;
#include "Unit.h"
#include "Entitymanager.h"
class Npc : public Unit
{
private:
//	AI ai;

public:
	Npc(Entitymanager* man);
	~Npc();
	void create_npc(std::string name,int ID, int X, int Y, Collisionmanager* col);
	void remove_npc();
};
#endif
