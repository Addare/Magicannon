#include "Main.h"



Entitymanager::Entitymanager(SDL_Surface* scrn, World* map)
{
	screen=scrn;
	containersize=40;
	size=0;
	playercounter=0;

	entities=new Interactiveentity*[containersize];
	collisionman = new Collisionmanager(map);
}


void Entitymanager::double_size() //dubblar vektorstorleken på entities. Crashar om entities inte är "Full"
{
	Interactiveentity** temp = new Interactiveentity*[containersize];
	temp = entities;
	entities = new Interactiveentity*[containersize*2];
	for(int i=0;i<containersize;i++)
	{
		entities[i] = temp[i];
	}

	containersize=containersize*2;
}

void Entitymanager::half_size()	//halverar vektorstorleken på entities. Crashar om entities inte är "Full"
{
	Interactiveentity** temp = new Interactiveentity*[containersize];
	temp = entities;
	entities = new Interactiveentity*[containersize*2];
	int newsize=0;
	for(int i=0;i<containersize;i++)
	{
		if(temp[i]->active()==true)
		{
			entities[newsize] = temp[i];
			newsize++;
		}
	}
	size=newsize;
	containersize=containersize*2;
}

void Entitymanager::show_entities()
{
	for(int i=0;i<size;i++)
	{
		entities[i]->show(screen);
	}
}

void Entitymanager::move_entities()
{
	for(int i=0;i<size;i++)
	{
		entities[i]->move();
	}
}

void Entitymanager::handle_entities()
{
	for(int i=0;i<size;i++)
	{
		entities[i]->handle();
		//collisionman->check_collision(0,0);
	}
}

void Entitymanager::handle_input()
{
	for(int i=0;i<playercounter;i++)
	{
		players[i]->handle_input();
	}
}


void Entitymanager::create_entity(string createtype, int x, int y, string name, int identifier, int arg1, int arg2)
{
	if(createtype == "player")
	{	
		Unit* u = new Unit();								//Vad fan gör dena!?
		Player* p = new Player(this);
		players[playercounter] = p;
		playercounter++;
		p->create_player(name, identifier, x, y,collisionman);
		entities[size] = p;
		p->afflict_status("poison1");

	}
	
	else if(createtype == "enemy")
	{
		Enemy* e = new Enemy(this);
		e->create_enemy(name, identifier, x, y,collisionman);
		entities[size] = e;
		
	}

	else if(createtype == "npc")
	{
		Npc* n = new Npc(this);
		n->create_npc(name, identifier, x, y,collisionman);
		entities[size] = n;
	}

	else if(createtype == "projectile")
	{
		Projectile* p = new Projectile();
		p->create_projectile(arg1, x, y, identifier, arg2, name);
		entities[size] = p;
	}

	else if(createtype == "spell")
	{
		Spell* s = new Spell();
		s->create_spell(arg1, x, y, identifier, arg2, name);
		entities[size] = s;
	}
	
	else
	{
		return;											//möjligtvis ge ett riktigt error senare
	}
	size++;
	if(size == containersize-1)
	{
		double_size();
	}
	if(size <= containersize*0.25 && containersize > 40)
	{
		half_size();
	}

}