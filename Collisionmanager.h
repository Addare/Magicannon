#ifndef COLLISIONMANAGER
#define COLLISIONMANAGER

class Collisionmanager;

#include "World.h"

class Collisionmanager
{
private:
	World* map;
	int blocked_areas[SCREEN_WIDTH/GRID_SIZE][SCREEN_HEIGHT/GRID_SIZE];

public:

	Collisionmanager(World* map);
	void update_map();
	void add_hitbox(int x, int y);
	void remove_hitbox(int x, int y);
	bool check_collision(int x, int y, int dir);
};
#endif