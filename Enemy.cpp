#include "Main.h"
Enemy::Enemy(Entitymanager* man)
{
	manager = man;
}
Enemy::~Enemy()
{
}
void Enemy::create_enemy(std::string name,int ID, int X, int Y,Collisionmanager* col)
{
	create_unit("enemychart.txt",name,ID,X,Y,col);
}
void Enemy::remove_enemy()
{
	remove_unit();
}