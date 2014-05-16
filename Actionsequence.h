#ifndef ACTIONSEQUENCE
#define ACTIONSEQUENCE

class Actionsequence;

#include "Frame.h"

class Actionsequence
{
private:
	Frame clips[20];
	int sequencelength;
	int pointer;
	int counter;

public:
	Actionsequence();
	Actionsequence(int id);
	SDL_Rect get_clip(int direction);
	void reset();

};



#endif