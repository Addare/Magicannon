#ifndef UNIT
#define UNIT

class Unit;

#include <list>

#include "Actionsequence.h"
#include "Interactiveentity.h"
#include "Collisionmanager.h"
#include "Status.h"

#include "Effect.h"

class Unit : public Interactiveentity
{

	friend class AI;

private:

protected:
	int id;
	int xvel;
	int yvel;
	int destx;
	int desty;
	int direction;
	int truedirection;
	int action;
	int walktimer;
	int walkcooldown;
	int shootcooldown;
	int cancelvalue;
	Actionsequence sequence[10];
	Stats stat;
	list<Status> status;
//	Trigger triggers;				//Ska antagligen scrappas
	bool is_active;


	Collisionmanager* collisionman;

	void set_direction(int dir);
	void set_dest();

	Effect testeffect;

public:
	Unit();
	~Unit();
	void create_unit(std::string sheet,std::string name,int ID, int X, int Y,Collisionmanager* col);
	virtual void remove_unit();
	//void move(Unit* units[],World map);
	void move();
	void handle();
	virtual void show(SDL_Surface* scrn);
	void actionhandler();
	//bool check_collision(Unit* units[], int x, int y, int nr,int size,World map);
	bool collides_with(int X,int Y,int size,int nr);
	void trigger();
	bool is_alive();
	void afflict_status(std::string newstatus);
	void take_damage(int amount);
	int get_x();
	int get_y();

	static int grid_corrector(int value)
	{
		if(value%GRID_SIZE>(GRID_SIZE/2))
		{
			return value+(GRID_SIZE-(value%GRID_SIZE));
		}
		else
		{
			return value-(value%GRID_SIZE);
		}
	}

};

#endif