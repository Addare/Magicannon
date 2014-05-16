#ifndef ENTITYMANAGER
#define ENTITYMANAGER

class Entitymanager;

#include "Interactiveentity.h"
#include "Player.h"
#include "Enemy.h"
#include "Npc.h"

class Entitymanager
{
private:

	SDL_Surface* screen;
	Interactiveentity** entities;
	Collisionmanager* collisionman;
	int containersize;
	int size;
	Player* players[5];
	int playercounter;

	void double_size();
	void half_size();

public:


	Entitymanager(SDL_Surface* scrn, World* map);

	void move_entities();
	void handle_entities();
	void show_entities();
	void handle_input();

	void create_entity(string createtype, int x, int y, string name, int identifier, int arg1, int arg2);

};
#endif