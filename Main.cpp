#include "Main.h"


SDL_Surface* screen=NULL;
SDL_Event event;

int main(int argc, char* args[])
{
	

	Window win;
	Timer fps;
	bool* shutdown= new bool;
	*shutdown=false;
	
	if(init()==false)		//startar SDL
	{
		return 1;
	}
	if(win.error()==true)		//startar SDL
	{
		return 1;
	}

	
	World map;							
	Entitymanager* manager = new Entitymanager(screen,&map);		//Startar enhetshanteraren
	map.load_area(manager);

	manager->create_entity("player", 320,200, "Rachel", 0, 0, 0);
	//manager->create_entity("enemy", 120, 120, "normal_slime", 0, 0 , 0);

	while(*shutdown==false)
	{
		fps.start();				//en fps-timer som håller reda pEtiden det tar att gEett varv
			while(SDL_PollEvent(&event))	//koller efter events, dvs knapptryck mm
			{
				manager->handle_input();
				win.handle_events(shutdown);
			}//cout<<"fail";
			//SDL_Surface* test = load_image("images/sprites/slimeshot.bmp");
			apply_surface(0,0,map.get_background(),screen);		//lägger till bakgrunden
			
			//apply_surface(0,0,test,screen);
			manager->move_entities();
			manager->handle_entities();
			manager->show_entities();

			//apply_surface(0,0,map.get_foreground(),screen); //lägger till förgrunden
			if(SDL_Flip(screen)==-1)			//uppdaterar skärmen
			{
				return 1;
			}

			if(fps.get_ticks()<1000/FRAMES_PER_SECOND)		//begränsar fps:en genom att vänta den tiden som "blir över"
			{
				SDL_Delay(1000/FRAMES_PER_SECOND-fps.get_ticks());
			}
	}
	return 0;
}
		

