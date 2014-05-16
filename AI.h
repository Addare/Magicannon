#ifndef AI
#define AI

class AI;

#include "Unit.h"

class AI
{
private:
	Unit* unit;
	Unit* target;
	Goalhandler goal;

public:

	AI(Unit* unit);
	void newAction();
};

#endif