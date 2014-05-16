#include "Main.h"
Npc::Npc(Entitymanager* man)
{
	manager = man;
	//Unit();
}
Npc::~Npc()
{
	//~Unit();
}
void Npc::create_npc(std::string name,int ID, int X, int Y, Collisionmanager* col)
{
	create_unit("npcchart",name,ID,X,Y,col);
}
void Npc::remove_npc()
{
	remove_unit();
}

