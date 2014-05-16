#include "Main.h"
World::World()			//funkar kanske inte, kopiera isåfall reset_area
{
	//reset_area();
}

void World::reset_area()
{
	background = NULL;
	foreground = NULL;
	current_map_id=0;
	for(int n=0;n<4;n++)
	{
		neighbour_map_id[n]=0;
	}
	for(int n=0;n<SCREEN_HEIGHT/GRID_SIZE;n++)
	{
		for(int m=0;m<SCREEN_WIDTH/GRID_SIZE;m++)
		{
			obstacles[m][n]=0;
		}
	}
//	for(int n=0;n<20;n++)
	{
	//	globaltrigger[n]=' ';		//Ska inte användas längre?
	}
}

void World::load_area(Entitymanager* manager)
{
	SDL_Surface* ground = load_image("images/maps/b.bmp");// = new SDL_Surface();
	SDL_Surface* foreground = NULL;// = new SDL_Surface();
	int map_nr = 2;
	int map_nr_compare=0;
	current_map_id=map_nr;

	std::ifstream mapload("data/mapsheet.txt");		//laddar in information till kartan från en fil
	std::string temp;
	while(map_nr!=map_nr_compare)		//krachar programmet om bannummret inte finns eller är fel
	{
		while(temp!="Map")		
		{
			mapload>>temp;
		}
		mapload>>map_nr_compare;
		temp=' ';								//kollar om det räcker, använd nedanstående annars
		//getline(mapload,temp);				//ignorerar ett mellanrum, ser till sEatt temp inte är kvar som "Map" nästa varv
	}
	getline(mapload,temp);						//ignorerar ett mellanrum

	int tempint;
	SDL_Surface* groundsheets[10];
	mapload>>tempint;
	getline(mapload,temp);						//ignorerar ett mellanrum
	for(int a=0;a<tempint;a++)
	{
		getline(mapload,temp);
		temp.insert(0,"images/maps/");
		groundsheets[a] = load_image(temp);
	}
	getline(mapload,temp);

	char square[3] = {0, 0, 0};
	int posx = 0;
	int	posy = 0;
	while(posy<12)
	{
		int sheetnumber=0;
		int squarenumber=0;
		square[0] = 0;
		square[1] = 0;
		mapload>>square;
		switch (square[0])
		{
		case '0': sheetnumber=0;break;
		case '1': sheetnumber=1;break;
		case '2': sheetnumber=2;break;
		case '3': sheetnumber=3;break;
		case '4': sheetnumber=4;break;
		case '5': sheetnumber=5;break;
		case '6': sheetnumber=6;break;
		case '7': sheetnumber=7;break;
		case '8': sheetnumber=8;break;
		case '9': sheetnumber=9;break;
		}
	
		if((int)square[1] >= 65 && (int)square[1] <=90)
		{
			squarenumber = (int)square[1] - 65;
		}
		else if((int)square[1] >= 97 && (int)square[1] <=122)
		{
			squarenumber = (int)square[1] - 97 + 26;
		}
		SDL_Rect tempclip;
		tempclip.x = (squarenumber / 3) * GRID_SIZE;
		tempclip.y = (squarenumber % 3) * GRID_SIZE;
		tempclip.w = 40;
		tempclip.h = 40;
		

		apply_surface(posx*GRID_SIZE,posy*GRID_SIZE,groundsheets[sheetnumber],ground,&tempclip);
		SDL_Flip(ground);

		posx++;
		if(posx>=16)
		{
			posx=0;
			posy++;
		}
	}
	background=ground;


	getline(mapload,temp);
//	obstacles[5][8] = true;

/*	mapload>>tempint;
	for(int i=0;i<tempint;i++)
	{
		string name;
		int x=0;
		int y=0;
		int var1=0;
		int var2=0;

		mapload>>name;
		mapload>>x;
		mapload>>y;
		mapload>>var1;
		mapload>>var2;

		getline(mapload,temp);

		//SKAPA OBJEKT
	}

	mapload>>tempint;
	for(int n=0;n<tempint;n++)
	{
		std::string name;
		int nr;
		int X,Y;
		mapload>>name;
		mapload>>nr;
		mapload>>X;
		mapload>>Y;
		manager->create_entity("enemy", X, Y, name, nr, 0, 0);		//skapar fienderna
		getline(mapload,temp);
	}
	mapload>>tempint;
	for(int n=0;n<tempint;n++)
	{
		std::string name;
		int nr;
		int X,Y;
		mapload>>name;
		mapload>>nr;
		mapload>>X;
		mapload>>Y;
		manager->create_entity("npc", X, Y, name, nr, 0, 0);		//skapar npcs
		getline(mapload,temp);
	}




//	mapload>>back;
	//mapload>>fore;
//	back.insert(0,"images/maps/");
//	fore.insert(0,"images/maps/");
//	background=load_image(back);		//laddar in bilderna till banan
	//foreground=load_image(fore);
	for(int n=0;n<4;n++)
	{
		mapload>>neighbour_map_id[n];
	}
	for(int n=0;n<30;n++)
	{
	//	enm[n]->remove_enemy();
	//	npc[n]->remove_npc();
	}

	char pos;
	for(int n=0;(SCREEN_HEIGHT/GRID_SIZE)>n;n++)		//laddar in banans hitbox
	{	
																	//Använder sig av chars
		for(int m=0;(SCREEN_WIDTH/GRID_SIZE)>m;m++)
		{
			mapload>>pos;
			if(pos>=48 && pos<=57)
			{
				obstacles[m][n]=pos-48;
			}
			else if(pos>=65 && pos<=70)
			{
				obstacles[m][n]=pos-55;
			}
			else
			{
				obstacles[m][n]=0;
			}
		}
	}

	getline(mapload,temp);

	
	mapload>>tempint;
	for(int n=0;n<tempint;n++)
	{
		globaltrigger[n];
	}
	getline(mapload,temp);				//ignorerar ett mellanrum
	for(int n=0;(SCREEN_HEIGHT/GRID_SIZE)>n;n++)		//laddar in banans triggers
	{
																		//Använder sig av chars
		for(int m=0;(SCREEN_WIDTH/GRID_SIZE)>m;m++)
		{
			mapload>>pos;
			triggers[m][n]=pos;
		}
	}*/
	mapload.close();
}

SDL_Surface* World::get_background()
{
	return background;
}
SDL_Surface* World::get_foreground()
{
	return foreground;
}

bool World::collide(int x,int y,int size,int truedirection)
{
	for(int n=0;(SCREEN_HEIGHT/GRID_SIZE)>n;n++)
	{
		for(int m=0;(SCREEN_WIDTH/GRID_SIZE)>m;m++)
		{
			if((x+GRID_SIZE*size<=m*GRID_SIZE || x>=m*GRID_SIZE+GRID_SIZE ||
				y+GRID_SIZE*size<=n*GRID_SIZE || y>=n*GRID_SIZE+GRID_SIZE))
			{
			}
			else
			{
				if(obstacles[m][n]==15)
				{
					return true;
				}
				if(obstacles[m][n]%8>=4)
				{
					if(truedirection==DIR_UP)
					{
						return true;
					}
				}
				if(obstacles[m][n]%2==1)
				{
					if(truedirection==DIR_DOWN)
					{
						return true;
					}
				}
				if(obstacles[m][n]%4>=2)
				{
					if(truedirection==DIR_LEFT)
					{
						return true;
					}
				}
				if(obstacles[m][n]>=8)
				{
					if(truedirection==DIR_RIGHT)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

int World::obstacle_at(int x, int y)
{
	return obstacles[x][y];
}
