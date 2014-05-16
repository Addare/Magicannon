#ifndef GOALHANDLER
#define GOALHANDLER

class Goalhandler;

#include "Structs.h"
#include "Unit.h"

class Goalhandler
{
private:
	Goal currentgoal;
public:
	void modifygoal();
	void newAction();
};

#endif