#include "Main.h"

Effect::Effect()
{
	
}

void Effect::create_effect(string name, int duration, int X, int Y)
{
	x=X;
	y=Y;

	std::ifstream loader("data/effectsheet.txt");

	std::string temp;
	while(temp!=name)					//krachar programmet om namnet inte finns eller är fel
	{
		getline(loader,temp);
	}
	//getline(loader,temp);					//ignorerar ett mellanrum

	std::string sheet;
	getline(loader,sheet);
	int tempint=0;
	loader>>tempint;
	action = Actionsequence(tempint);
	sheet.insert(0,"images/sprites/");					//lägger till "images/sprites" i filnamnet
	spritesheet=load_image(sheet.c_str());
	loader.close();			//stänger textfilen 
}

void Effect::show(SDL_Surface* screen)
{
	apply_surface(x,y,spritesheet,screen,&action.get_clip(0));
}

void Effect::move(int newx, int newy)
{
	x=newx;
	y=newy;
}