#include "Main.h"

Actionsequence::Actionsequence()
{
}

Actionsequence::Actionsequence(int id)
{
	pointer=0;
	counter=0;

	int inttmp=0;
	std::string temp;

	std::ifstream loader("data/actionsheet.txt");
	while(id!=inttmp)
	{
		while(temp!="clips")					//krachar programmet om namnet inte finns eller är fel
		{
			loader>>temp;
		}
		loader>>inttmp;
		temp="";
	}
	
	getline(loader,temp);						//hoppar över en rad
	loader>>sequencelength;
	getline(loader,temp);						//hoppar över en rad
	int x[4];
	int y[4];
	int w[4];
	int h[4];
	int d;
	for(int i=0;i<sequencelength;i++)
	{
		getline(loader,temp);						//hoppar över en rad
		loader>>d;
		for(int j=0;j<4;j++)
		{
			loader>>x[j];
			loader>>y[j];
			loader>>w[j];
			loader>>h[j];
		}
		clips[i] = Frame(x,y,w,h,d);
		
	}
}

SDL_Rect Actionsequence::get_clip(int direction)
{
	if(pointer==sequencelength && clips[pointer].get_duration()<=counter)
	{
		pointer=0;
	}
		SDL_Rect temp=clips[pointer].get_clips()[direction];
	if(clips[pointer].get_duration()<=counter)
	{
		counter=0;
		pointer++;
	}
	else
	{
		counter++;
	}
		return temp;
}

void Actionsequence::reset()
{
	pointer=0;
	counter=0;
}
