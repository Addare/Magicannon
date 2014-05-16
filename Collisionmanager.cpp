#include "Main.h"


Collisionmanager::Collisionmanager(World* Map)
{
	map=Map;
	for(int i = 0;i<SCREEN_WIDTH/GRID_SIZE;i++)
	{
		for(int j=0;j<SCREEN_HEIGHT/GRID_SIZE;j++)
		{
			blocked_areas[i][j]=false;
		}
	}
}

void Collisionmanager::update_map()
{
	for(int i = 0;i<SCREEN_WIDTH/GRID_SIZE;i++)
	{
		for(int j=0;j<SCREEN_HEIGHT/GRID_SIZE;j++)
		{
			blocked_areas[i][j]=map->obstacle_at(i, j);
		}
	}
}

void Collisionmanager::add_hitbox(int x, int y)
{	//cout<<"added hitbox at "<<x<< " "<<y<<endl;
	blocked_areas[grid_corrector(x)/GRID_SIZE][grid_corrector(y)/GRID_SIZE]=15;
}

void Collisionmanager::remove_hitbox(int x, int y)
{	//cout<<"removed hitbox at "<<x<< " "<<y<<endl;
	blocked_areas[grid_corrector(x)/GRID_SIZE][grid_corrector(y)/GRID_SIZE]=0;
}

bool Collisionmanager::check_collision(int x, int y, int dir)
{
	//cout<<blocked_areas[grid_corrector(x)/GRID_SIZE][grid_corrector(y)/GRID_SIZE]<<endl;
		if(blocked_areas[grid_corrector(x)/GRID_SIZE][grid_corrector(y)/GRID_SIZE]==15)
		{
			return true;
		}
		if(blocked_areas[grid_corrector(x)/GRID_SIZE][grid_corrector(y)/GRID_SIZE]%8>=4)
		{
			if(dir==DIR_UP)
			{
				return true;
			}
		}
		if(blocked_areas[grid_corrector(x)/GRID_SIZE][grid_corrector(y)/GRID_SIZE]%2==1)
		{
			if(dir==DIR_DOWN)
			{
				return true;
			}
		}
		if(blocked_areas[grid_corrector(x)/GRID_SIZE][grid_corrector(y)/GRID_SIZE]%4>=2)
		{
			if(dir==DIR_LEFT)
			{
				return true;
			}
		}
		if(blocked_areas[grid_corrector(x)/GRID_SIZE][grid_corrector(y)/GRID_SIZE]>=8)
		{
			if(dir==DIR_RIGHT)
			{
				return true;
			}
		}
	return false;
}