#include "Main.h"

Player::Player(Entitymanager* man)
{
	xSpd=0;
	ySpd=0;
	manager = man;
}
Player::~Player()
{
}
void Player::create_player(string name, int id, int X, int Y,Collisionmanager* col)
{
	create_unit("playerchart.txt",name,id,X,Y, col);
	spell="Magic burst";
}

void Player::remove_unit()			//väldigt makeshift, ska kanske ändras
{
	return;
}

void Player::handle_input()		//hanterar knappintryckningar från spelaren
{
	Uint8 *keystates=SDL_GetKeyState(NULL);

	if(event.type==SDL_KEYDOWN)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_UP:		if(y%GRID_SIZE==0 && x%GRID_SIZE==0){set_direction(DIR_UP);}
								yvel-=1;
								walktimer=3;
								break;
			case SDLK_DOWN:		if(y%GRID_SIZE==0 && x%GRID_SIZE==0){set_direction(DIR_DOWN);}
								yvel+=1;
								walktimer=3;
								break;
			case SDLK_LEFT:		if(y%GRID_SIZE==0 && x%GRID_SIZE==0){set_direction(DIR_LEFT);}
								xvel-=1;
								walktimer=3;
								break;
			case SDLK_RIGHT:	if(y%GRID_SIZE==0 && x%GRID_SIZE==0){set_direction(DIR_RIGHT);}
								xvel+=1;
								walktimer=3;
								break;
			case SDLK_x:			
				{			if(cancelvalue<1){	int posx=x,posy=y;
									switch (direction)
									{
									case DIR_UP:	posy=y-GRID_SIZE;
													break;

									case DIR_RIGHT:	posx=x+GRID_SIZE;
													break;

									case DIR_DOWN:	posy=y+GRID_SIZE;
													break;

									case DIR_LEFT:	posx=x-GRID_SIZE;
									}		//skapar en projektil
									shootcooldown=40;
								//	manager->create_projectile(stat.pow, posx, posy, id, direction, "Testchain2");
				}
									
						}
									break;

			case SDLK_1:			spell="Magic burst";				//byter attakc för spelaren
									break;
			case SDLK_2:			spell="Magic missile";
									break;
			default:				break;
		}
	}
	else if(event.type==SDL_KEYUP)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_UP:		yvel+=1; break;
			case SDLK_DOWN:		yvel-=1; break;
			case SDLK_LEFT:		xvel+=1; break;
			case SDLK_RIGHT:	xvel-=1; break;
		}
	}


		
}

