#ifndef EFFECT
#define EFFECT

class Effect;

#include "Graphicentity.h"
#include "Actionsequence.h"

class Effect : public Graphicentity
{
private:
	Actionsequence action;

public:

	Effect();
	void create_effect(string type, int duration, int X, int Y);
	void show(SDL_Surface* screen);
	void move(int newx, int newy);

};
#endif