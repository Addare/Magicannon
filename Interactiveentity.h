#ifndef INTERACTIVEENTITY
#define INTERACTIVEENTITY

class Interactiveentity;

#include "Graphicentity.h"
#include "Entitymanager.h"

class Interactiveentity : public Graphicentity
{
private:

	bool is_active;

protected:
	Entitymanager* manager;

public:

	virtual void move();
	virtual void handle();
	bool active();

};

#endif