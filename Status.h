#ifndef STATUS
#define STATUS

class Status;

#include "Structs.h"
#include "Unit.h"
#include "Effect.h"

class Status
{
private:
	int max_duration;
	int duration_timer;
	Unit* affected_unit;
	Status_effect action[10];
	Effect effect;

	void damage(int arg[]);
	void slow(int arg[]);
	void createstatus(int arg[]);

public:
	Status(std::string name, Unit* affectedunit);
	int handle();
	void show(SDL_Surface* screen);
};
#endif
