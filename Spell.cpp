#include "Main.h"

Spell::Spell()
{
	x=0;
	y=0;
	size=0;
	hits=0;
	dmg=0;
	duration=0;
	singleblit=false;
	is_active=false;
	end_after_hits=false;
	delaypointer=0;
	hitbox = NULL;
	hitdelayed = new Unit[UNIT_AMOUNT];
	hitbox = NULL;
}

Spell::~Spell()
{
	x=0;
	y=0;
	size=0;
	hits=0;
	dmg=0;
	duration=0;
	singleblit=false;
	is_active=false;
	end_after_hits=false;
	delaypointer=0;
	for(int i=0;i<size;i++)
	{
		delete [] hitbox[i];
	}
	delete [] hitbox;
	delete [] hitdelayed;
}

void Spell::create_spell(int pwr, int X, int Y, int own, int dir, std::string name)
{																//Skapar en spell från parametrar och fil
	std::ifstream loader("data/spellsheet.txt");
	std::string temp;
	while(temp!=name)											//krachar om projectilen inte finns
	{
		getline(loader,temp);
	}
	getline(loader,temp);
	temp.insert(0,"images/sprites/");					//lägger till "images/sprites"
	spritesheet=load_image(temp.c_str());

	int tempint=0;
	loader>>tempint;
	sequence=Actionsequence(tempint);
	loader>>hits;
	loader>>dmg;
	loader>>duration;
	loader>>hitdelay;
	loader>>singleblit;									
	loader>>end_after_hits;

	loader>>tempint;
	getline(loader,temp);
	for(int i=0;i<tempint;i++)
	{
		getline(loader,activates[i].name);
		loader>>activates[i].type;
		loader>>activates[i].activation;
		loader>>activates[i].timer;
		loader>>activates[i].direction;
		loader>>activates[i].modifier;
		getline(loader,temp);
	}
	getline(loader,temp);
	for(int i = tempint;i<10;i++)
	{
		activates[i].name=" ";
		activates[i].type=' ';
		activates[i].activation=' ';
		activates[i].timer=0;
		activates[i].direction=0;
		activates[i].modifier=0;
	}

	for(int i=0;i<size;i++)
	{
		delete [] hitbox[i];
	}
	delete [] hitbox;
	loader>>size;
	hitbox=new bool*[size];
	for(int i=0;i<size;i++)
	{
		hitbox[i] = new bool[size];
	}
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			loader>>hitbox[j][i];
		}
	}

	loader.close();
	x=X-((size+1)/2-1)*GRID_SIZE;
	y=Y-((size+1)/2-1)*GRID_SIZE;
	owner=own;
	direction=dir;
	dmg+=pwr;
	this->pwr=pwr;
	is_active=true;
	turn_spell();
}

void Spell::handle_collision(Spellmanager* sm, World map, Unit* units[])
{										//Hanterar allt som spellen behöver kolla
	if(is_active==false)
	{
		return;
	}
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			if(hitbox[j][i]==true)
			{
				Unit * u=check_collision(x+i%size,y+i/size, map, units);
				if(u!=NULL)
				{
					if(!is_delayed(u))
					{
						hits--;
						u->take_damage(dmg+pwr);
						for(int n=0;n<10;n++)
						{
							if(activates[n].activation=='h')
							{
								if(activates[n].type=='s')
								{
									//u.afflict_status(activates[n].name);
								}
								else if(activates[n].type=='m')			//skapa spell (s upptagen till Status)
								{									//SKA FIXA FLER ALTERNATIV TILL ATT SKAPA NYA SPELLS(kanske också projektiler)
									sm->create_spell(pwr+activates[n].modifier,x,y,direction,owner,activates[n].name);
								}
								else if(activates[n].type=='p')
								{
									sm->create_projectile(pwr+activates[n].modifier,x,y,activates[n].direction,owner,activates[n].name);
								}
							}
						}
					}
				}
			}
		}
	}
}

void Spell::handle_timer(Spellmanager* sm, World map, Unit* units[])
{
	if(is_active==false)
	{
		return;
	}
	if(duration>0)
	{
		duration--;
	}
	for(int i = 0; i<UNIT_AMOUNT;i++)
	{
		if(hitdelaytimer[i]>0)
		{
			hitdelaytimer[i]--;
		}
	}
	if(duration==0)
	{
		for(int n=0;n<10;n++)
		{
			if(activates[n].activation=='t')
			{
				if(activates[n].type=='m')					//skapa spell (s upptagen till Status)
				{
					sm->create_spell(pwr+activates[n].modifier,x,y,direction,owner,activates[n].name);			
				}
				else if(activates[n].type=='p')
				{
					sm->create_projectile(pwr+activates[n].modifier,x,y,direction,owner,activates[n].name);				//Skapa projektil
				}
			}
		}
		is_active=false;	//remove
	}
}

void Spell::show_spell()
{
	if(is_active==false)
	{
		return;
	}
	if(singleblit==false)
	{
		SDL_Rect clip = sequence.get_clip(direction);
		for(int i=0;i<size;i++)
		{
			for(int j=0;j<size;j++)
			{
				if(hitbox[i][j]==true)
				{
					apply_surface(x+(i*GRID_SIZE),y+(j*GRID_SIZE),spritesheet,screen,&clip);
				}
			}
		}
	}
	else
	{
		apply_surface(x,y,spritesheet,screen,&sequence.get_clip(direction));
	}

	
}

bool Spell::get_active()
{
	return is_active;
}

Unit* Spell::check_collision(int X, int Y, World map, Unit* units[])
{
	for(int i=0;i<UNIT_AMOUNT*2+1;i++)								
	{
		if(units[i]->collides_with(X,Y,1,-100000)==true)		//Tillfälligt nr för att kunna krocka med allt
		{
			return units[i];
		}
	}
	return NULL;
}

bool Spell::is_delayed(Unit* unit)
{
	for(int i = 0; i<UNIT_AMOUNT;i++)
	{
		if(&hitdelayed[i]==unit)
		{
			if(hitdelaytimer[i]>0)
			{
				return true;
			}
			else
			{
				hitdelaytimer[i]=hitdelay;
				return false;
			}
		}
	}
	hitdelayed[delaypointer]=*unit;
	hitdelaytimer[delaypointer]=hitdelay;
	delaypointer++;
	return false;
}

void Spell::turn_spell()
{
	bool ** newhitbox = new bool*[size];
	for(int i=0;i<size;i++)
	{
		newhitbox[i] = new bool[size];
	}
	if(direction==DIR_DOWN)
	{
		for(int y=0;y<size;y++)
		{
			for(int x=0;x<size;x++)
			{
				newhitbox[x][y]=hitbox[y][size-x-1];
			}
		}
	}
	else if(direction==DIR_LEFT)
	{
		for(int y=0;y<size;y++)
		{
			for(int x=0;x<size;x++)
			{
				newhitbox[x][y]=hitbox[size-x-1][size-y-1];
			}
		}
	}
	else if(direction==DIR_UP)
	{
		for(int y=0;y<size;y++)
		{
			for(int x=0;x<size;x++)
			{
				newhitbox[x][y]=hitbox[size-y-1][x];
			}
		}
	}
	if(direction!=DIR_RIGHT)
	{
		hitbox=newhitbox;
	}

}