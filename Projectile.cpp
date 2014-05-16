#include "Main.h"

Projectile::Projectile()
{
	name=" ";
	pwr=0;
	spd=0;
	owner=0;
	x=0;
	y=0;
	direction=0;
	distance=0;
	max_distance=0;
	piercing=false;
	hit_on_contact=false;
	friendly_fire=false;
	is_active=false;
	spritesheet=NULL;
}

Projectile::~Projectile()
{
	name=" ";
	pwr=0;
	spd=0;
	owner=0;
	x=0;
	y=0;
	direction=0;
	distance=0;
	max_distance=0;
	piercing=false;
	hit_on_contact=false;
	friendly_fire=false;
	is_active=false;
	spritesheet=NULL;
}

void Projectile::handle_projectile(Spellmanager* sm, World map, Unit* units[])
{
	if(is_active==false)
	{
		return;
	}
	Unit* u = check_collision(Unit::grid_corrector(x),Unit::grid_corrector(y),map,units);
	if(distance>=max_distance)
	{
		sm->create_spell(pwr, Unit::grid_corrector(x),Unit::grid_corrector(y), owner, direction, spell);
		remove_projectile();
	}
	else if(u!=NULL || map_collision(map))
	{
		sm->create_spell(pwr, Unit::grid_corrector(x),Unit::grid_corrector(y), owner, direction, spell);
		if(piercing==false || u==NULL)
		{
			remove_projectile();
		}
	}
	else
	{
		switch (direction)
		{
		case DIR_UP:		y-=spd; break;
		case DIR_RIGHT:		x+=spd; break;
		case DIR_DOWN:		y+=spd; break;
		case DIR_LEFT:		x-=spd; break;
		}
		distance+=spd;
	}
}


void Projectile::create_projectile(int pw, int X, int Y, int dir, int own, std::string projectilename)
{
	pwr=pw;
	x=X;
	y=Y;
	direction=dir;
	owner=own;
	name=projectilename;

	std::ifstream projload("data/projectilesheet.txt");		//laddar in information om projectilen från en fil
	std::string temp;
	while(temp!=name)											//krachar om projectilen inte finns
	{
		getline(projload,temp);
	}
	projload>>spd;
	projload>>max_distance;
	int temp2;
	projload>>temp2;
	if(temp2==1)
	{
		piercing=true;
	}
	else
	{
		piercing=false;
	}
	projload>>temp2;
	if(temp2==1)
	{
		hit_on_contact=true;
	}
	else
	{
		hit_on_contact=false;
	}
	getline(projload,temp);
	getline(projload,temp);
	spell = temp;
	getline(projload,temp);
	temp.insert(0,"images/sprites/");					//lägger till "images/sprites"
	spritesheet=load_image(temp.c_str());
	projload>>temp2;
	sequence=Actionsequence(temp2);
	projload.close();
	is_active=true;
}


bool Projectile::get_active()
{
	return is_active;
}

void Projectile::remove_projectile()
{
	name=" ";
	pwr=0;
	spd=0;
	owner=0;
	x=0;
	y=0;
	direction=0;
	distance=0;
	max_distance=0;
	piercing=false;
	hit_on_contact=false;
	friendly_fire=false;
	is_active=false;
	spritesheet=NULL;
}

Unit* Projectile::check_collision(int X, int Y, World map, Unit* units[])
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

void Projectile::show_projectile()
{
	if(is_active==false)
	{
		return;
	}
	apply_surface(x,y,spritesheet,screen,&sequence.get_clip(direction));
	
}

bool Projectile::map_collision(World map)
{
	return map.collide(Unit::grid_corrector(x),Unit::grid_corrector(y),1,direction);		//SKa lägga till så att sizen funkar
}