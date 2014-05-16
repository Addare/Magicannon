#ifndef STRUCTS
#define STRUCTS


struct Map				//struct for keeping track of the current map
{
	SDL_Surface *background;
	SDL_Surface *foreground;
	int obstacles[200];
	char globaltrigger[20];
	char triggers[200];
	int current_map_id;
	int neighbour_map_id[4];

};

struct Stats			//Bundles stats for units
{
	int hp;
	int pow;
	int def;
	int spd;
	int size;
};

struct Clips			//Bundles the clip variables
{
	SDL_Rect clip[10][5][20];
	int cliptime[10][20];
	int clipcounter;
	int current_clip;

};
struct Activate					//används till triggers
{
	std::string name;
	char type;
	char activation;
	int timer;
	int direction;
	int modifier;
};


struct Status_effect			//används i status
{
	std::string name;
	int arg[5];
};

struct Goal
{
	int mainaction;
	int arg[5];
	Goal* preaction;
};
#endif