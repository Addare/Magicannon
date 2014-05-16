#ifndef GRAPHICENTITY
#define GRAPHICENTITY

class Graphicentity;


class Graphicentity
{
protected:
	int x;
	int y;
	SDL_Surface* spritesheet;


public:
	Graphicentity();
	Graphicentity(int X, int Y);
	Graphicentity(SDL_Surface* source);
	Graphicentity(int X, int Y, SDL_Surface* source);
	virtual void show(SDL_Surface* screen);

};
#endif