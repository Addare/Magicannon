#ifndef WORLD
#define WORLD

class World;

#include "Entitymanager.h"
#include "Mapobject.h"

class World
{
private:
	SDL_Surface *background;
	SDL_Surface *foreground;
	int obstacles[SCREEN_WIDTH/GRID_SIZE][SCREEN_HEIGHT/GRID_SIZE];
	Mapobject *objects;					//Vektorpekare
	int current_map_id;
	int neighbour_map_id[4];
public:
	World();
	void reset_area();
	void load_area(Entitymanager* manager);
	int obstacle_at(int x, int y);
	SDL_Surface* get_background();
	SDL_Surface* get_foreground();
	bool collide(int x,int y,int size, int truedirection);
};
#endif