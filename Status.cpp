#include "Main.h"


Status::Status(std::string name, Unit* affectedunit)
{
	duration_timer=0;

	affected_unit=affectedunit;
	std::ifstream loader("data/statussheet.txt");

	std::string temp;
	while(temp!=name)					//krachar programmet om npcnamnet inte finns eller är fel
	{
		getline(loader,temp);
	}
	std::string effectname;
	int tempduration;
	getline(loader,effectname);
	loader>>max_duration;
	effect.create_effect(effectname,max_duration,affected_unit->get_x(), affected_unit->get_y());

	int tempint; 
	loader>>tempint;
	getline(loader,temp);
	for(int i=0;i<tempint;i++)
	{
		action[i].name=temp;
		getline(loader,temp);
		int counter=0;
		while(temp.at(0)>=0 && temp.at(0)<=9)
		{
			action[i].arg[counter]=atoi(temp.c_str());
			counter++;
		}
	}
}


int Status::handle()
{
	duration_timer++;
	for(int i=0;i<10;i++)
	{
		if(action[i].name=="DAMAGE")		//Ersättas med funktionspekare?
		{
			damage(action[i].arg);
		}

		if(action[i].name=="SLOW")
		{
			slow(action[i].arg);
		}
		effect.move(affected_unit->get_x(), affected_unit->get_y());

	}
	if(duration_timer >=max_duration*FRAMES_PER_SECOND)
	{
		return 1;
	}
	return 0;
}

void Status::damage(int arg[])
{
	if(duration_timer%arg[1]==0)
	{
		affected_unit->take_damage(arg[0]);
	}
}

void Status::show(SDL_Surface* screen)
{
	effect.show(screen);
}

void Status::slow(int arg[])
{
	return;
}