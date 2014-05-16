#include "Main.h"
Unit::Unit()			//initierar variablerna, fˆr att fˆrhidra mˆjlig crash
{
	id=0;
	x=0;
	y=0;
	xvel=0;
	yvel=0;
	destx=0;
	desty=0;
	direction=DIR_DOWN;
	is_active=false;
	stat.hp=0;
	stat.pow=0;
	stat.def=0;
	stat.spd=0;
	stat.size=0;
	action=0;
	walktimer=0;
	walkcooldown=0;
	shootcooldown=0;
	cancelvalue=0;
}

Unit::~Unit()		//frigˆr minnet n‰r programmet avslutas
{
		SDL_FreeSurface(spritesheet);
}

bool Unit::is_alive()
{
	if(stat.hp<=0)
	{
		return false;
	}
	return true;
}

void Unit::create_unit(std::string file,std::string name,int ID, int X, int Y, Collisionmanager* col)
{
	id=ID;
	x=X;

	y=Y;
	destx=x;
	desty=y;
	is_active=true;
	collisionman=col;
	col->add_hitbox(x,y);
	file.insert(0,"data/");					//l‰gger till "data/"
	std::ifstream loader(file.c_str());

	std::string temp;
	while(temp!=name)					//krachar programmet om npcnamnet inte finns eller ‰r fel
	{
		getline(loader,temp);
	}
	getline(loader,temp);					//ignorerar ett mellanrum
	loader>>stat.hp;						//laddar in variablerna frÂn filen
	loader>>stat.pow;
	loader>>stat.def;
	loader>>stat.spd;
	loader>>stat.size;
	std::string sheet;
	getline(loader,temp);
	getline(loader,sheet);
	int tempint=0;
	loader>>tempint;
	int tempint2;
	for(int i=0;i<tempint;i++)
	{
		loader>>tempint2;
		sequence[i] = Actionsequence(tempint2);
}
	sheet.insert(0,"images/sprites/");					//l‰gger till "images/sprites" i filnamnet
	spritesheet=load_image(sheet.c_str());
	loader.close();			//st‰nger textfilen 
	
}

void Unit::remove_unit()					//nollst‰ller en npc n‰r den dˆr, eller fˆrsvinner frÂn banan
{
	id=0;
	x=0;
	y=0;
	destx=0;
	desty=0;
	stat.hp=0;
	stat.pow=0;
	stat.def=0;
	stat.spd=0;
	stat.size=1;

	direction=DIR_DOWN;

	is_active=false;
}


void Unit::move()
{
	
	if(is_alive()==false || is_active==false)
	{
		return;
	}
	if(destx>x)
	{
		x+=stat.spd;
	}
	if(destx<x)
	{
		x-=stat.spd;
	}
	if(desty>y)
	{
		y+=stat.spd;
	}
	if(desty<y)
	{
		y-=stat.spd;
	}
}

/*void Unit::move(Unit* units[],World map)
{
	if(is_alive()==false || is_active==false)
	{
		return;
	}

	set_dest(units,map);

	if(destx!=x)
	{
		if(x>destx)
		{
			x-=stat.spd;
		}
		else if(x<destx)
		{
			x+=stat.spd;
		}
	}
	if(destx%GRID_SIZE!=0)
	{
//	destx=grid_corrector(destx,GRID_SIZE);			//Bugfixare; Ser till sÅEatt enheten inte fastnar mitt mellan rutsystemet, d‰r den inte kan rˆra sig
	}
	if(desty!=y)
	{
		if(y>desty)
		{
			y-=stat.spd;
		}
		else if(y<desty)
		{
			y+=stat.spd;
		}
	}
	if(desty%GRID_SIZE!=0)
	{
//	desty=grid_corrector(desty,GRID_SIZE);			//Bugfixare; Ser till sÅEatt enheten inte fastnar mitt mellan rutsystemet, d‰r den inte kan rˆra sig
	}
}
*/
/*bool Unit::check_collision(Unit* units[], int X, int Y,int nr, int size, World map)			//compares collision between a position and an npc
{
	bool collideflag=false;
	int truedir=direction;
	if(x>X)
	{
		truedir=DIR_LEFT;
	}
	else if(x<X)
	{
		truedir=DIR_RIGHT;
	}
	if(y>Y)
	{
		truedir=DIR_UP;
	}
	else if(y<Y)
	{
		truedir=DIR_DOWN;
	}
	if(map.collide(X,Y,size,truedir)==false)
	{
		for(int i=0;i<UNIT_AMOUNT*2+1;i++)								
		{
			if(units[i]->collides_with(X,Y,size,nr)==true)
			{
				collideflag=true;
			}
		}
	}
	else
	{
		collideflag=true;
	}
	return collideflag;
}*/

bool Unit::collides_with(int X,int Y,int size,int nr)
{
	if(is_active==true && id!=nr)
	{
		if((X+GRID_SIZE*size<=x || X>=x+GRID_SIZE*stat.size ||
			Y+GRID_SIZE*size<=y || Y>=y+GRID_SIZE*stat.size))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}
void Unit::show(SDL_Surface* screen)
{
	if(is_active==false)
	{
		return;
	}
	apply_surface(x,y,spritesheet,screen,&sequence[action].get_clip(direction));
	for(list<Status>::iterator it=status.begin(); it!=status.end() ;it++)	//statuses.show()		
	{
		it->show(screen);
	}

}

void Unit::set_dest()
{
	if(x%GRID_SIZE==GRID_SIZE/2 || y%GRID_SIZE==GRID_SIZE/2)
	{
		if(destx>x)
		{
			collisionman->remove_hitbox(destx-GRID_SIZE,desty);
		}
		else if(destx<x)
		{
			collisionman->remove_hitbox(destx+GRID_SIZE,desty);
		}
		if(desty>y)
		{
			collisionman->remove_hitbox(destx,desty-GRID_SIZE);
		}
		else if(desty<y)
		{
			collisionman->remove_hitbox(destx,desty+GRID_SIZE);
		}
	}
	if(x%GRID_SIZE!=0 || y%GRID_SIZE!=0 || (xvel==0 && yvel==0) || walkcooldown>0)
	{
		return;
	}
	if(walktimer>0)			//tiden som behˆvs fˆr att bˆrja gÅEfˆr att kunna v‰nda sig utan att gÅE
	{
		walktimer--;
		return;
	}

	if(xvel>1)	{		//ser till sÅEatt hasigheten aldrig blir fˆr stor/liten
		xvel=1;
	}
	if(xvel<-1){
		xvel=-1;
	}
	if(yvel>1){
		yvel=1;
	}
	if(yvel<-1){
		yvel=-1;
	}
	
	bool xblock = collisionman->check_collision(x+xvel*GRID_SIZE, y, truedirection);
	bool yblock = collisionman->check_collision(x, y+yvel*GRID_SIZE, truedirection);
	if(xvel!=0 && yvel!=0 && xblock==false && yblock==false)
	{
		switch (direction)
		{
		case DIR_UP:	destx+=xvel*GRID_SIZE;	
						break;
		case DIR_DOWN:	destx+=xvel*GRID_SIZE;
						break;
		case DIR_LEFT:	desty+=yvel*GRID_SIZE;
						break;
		case DIR_RIGHT:	desty+=yvel*GRID_SIZE;
						break;
		}
		set_direction(direction);
		collisionman->add_hitbox(destx,desty);
		walkcooldown=GRID_SIZE/stat.spd;
	}
	else if(xvel!=0 || yvel!=0)
	{
		if(xvel!=0 && xblock==false)
		{
			destx+=xvel*GRID_SIZE;
			direction = DIR_DOWN+xvel*-1;
			collisionman->add_hitbox(destx,desty);
			walkcooldown=GRID_SIZE/stat.spd;						//godtycklig tillf‰llig cooldown
		}
		else if (yvel!=0 && yblock==false)
		{
			desty+=yvel*GRID_SIZE;
			direction = DIR_RIGHT+yvel;
			collisionman->add_hitbox(destx,desty);
			walkcooldown=GRID_SIZE/stat.spd;
		}
	}
}

void Unit::set_direction(int dir)
{
	if(xvel==0 && yvel==0)
	{
		direction=dir;
	}
	if(xvel!=0 && yvel!=0 && (destx!=x || desty!=y))
	{
		if(dir==DIR_UP || dir==DIR_DOWN)
		{
			if(xvel>0)
			{
				direction=DIR_RIGHT;
			}
			else
			{
				direction=DIR_LEFT;
			}
		}
		else if(dir==DIR_LEFT || dir==DIR_RIGHT)
		{
			if(yvel>0)
			{
				direction=DIR_DOWN;
			}
			else
			{
				direction=DIR_UP;
			}
		}
	}
	else
	{
		direction=dir;
	}
	if(destx>x)
	{
		truedirection=DIR_LEFT;
	}
	else if(destx<x)
	{
		truedirection=DIR_RIGHT;
	}
	if(desty>y)
	{
		truedirection=DIR_UP;
	}
	else if(desty<y)
	{
		truedirection=DIR_DOWN;
	}
}

void Unit::actionhandler()
{
	if(walkcooldown>0)
	{
		action=1;
		walkcooldown--;
		cancelvalue=2;
	}
	else if(shootcooldown>0)
	{
		action=2;
		if(shootcooldown>10)
		{				
			cancelvalue=4;
		}
		else
		{
			cancelvalue=3;
		}
		shootcooldown--;
		
	}
	else
	{
		action=0;
		cancelvalue=0;
		sequence[2].reset();
	}

}

void Unit::handle()								//Dubbelkolla ordningen saker utfˆrs (status kan sabotera saker kanske)
{
	for(list<Status>::iterator it=status.begin(); it!=status.end() ;)	//statuses.handle()		
	{
		int removestatus = it->handle();
		if(removestatus)
		{
			it = status.erase(it);				
		}
		else
		{
			it++;				//Ser till sÂ att iteratorn inte hoppar ˆver n‰sta element
		}
		removestatus=false;
	}
	set_dest();
	actionhandler();
}

void Unit::take_damage(int dmg)
{
	stat.hp-=dmg;
}

void Unit::afflict_status(std::string newstatus)
{
	Status temp(newstatus,this);
	status.push_back(temp);
}

int Unit::get_x()
{
	return x;
}

int Unit::get_y()
{
	return y;
}
