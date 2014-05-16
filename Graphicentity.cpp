#include "Main.h"

Graphicentity::Graphicentity()
{
	x=0;
	y=0;
	spritesheet=NULL;
}
Graphicentity::Graphicentity(int X, int Y)
{
	x=X;
	y=Y;
	spritesheet=NULL;
}
Graphicentity::Graphicentity(SDL_Surface* source)
{
	x=0;
	y=0;
	spritesheet=source;
}
Graphicentity::Graphicentity(int X, int Y, SDL_Surface* source)
{
	x=X;
	y=Y;
	spritesheet=source;
}

void Graphicentity::show(SDL_Surface* screen)
{//cout<<x<<" "<<y<<endl;
	apply_surface(x,y,spritesheet,screen,NULL);
}