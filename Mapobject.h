#ifndef MAPOBJECT
#define MAPOBJECT

class Mapobject;

//#include "Interactiveentity.h"
//#include "Player.h"


class Mapobject  : public Graphicentity
{
private:

	int size;
	int ** hitbox;
	int arg1, arg2;
	Trigger ** triggers;		//Subklass?

public:
	Mapobject();
	~Mapobject();
	void create(string name, int posx, int posy);
	void remove();
	bool check_collision(int X, int Y, int dir);

};
#endif