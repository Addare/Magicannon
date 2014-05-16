#include "Main.h"

bool init()			//startar programmets applikationer
{
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1)
	{
		return false;
	}
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
	if(screen==NULL)
	{
		return false;
	}
	if(TTF_Init()==-1)
	{
		return false;
	}
	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT,2,4096)==-1)
	{
		return false;
	}
	
	srand(0);							//gör rand() beroende av tiden
	//SDL_WM_SetCaption("fail", NULL);						// kopieras i felsökning
	return true;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip) //sätter bild pEskärm
{
	SDL_Rect offset;
	offset.x=x;
	offset.y=y;
	SDL_BlitSurface(source,clip,destination,&offset);
}

void clean_up()				//rensar variablar efter användning
{
	
	/*SDL_FreeSurface(message);
	SDL_FreeSurface(world.background);
	SDL_FreeSurface(world.foreground);
	SDL_FreeSurface(tempsprites);
	TTF_CloseFont(font);
	Mix_FreeMusic(music);

	SDL_FreeSurface(background);
	SDL_FreeSurface(startbutton);
	SDL_FreeSurface(musicbutton);
	SDL_FreeSurface(quitbutton);
	SDL_FreeSurface(mutebutton);
	SDL_FreeSurface(backtext);
	SDL_FreeSurface(mutetext);
	SDL_FreeSurface(tooltip);
	SDL_FreeSurface(song1);
	SDL_FreeSurface(song2);
	SDL_FreeSurface(song3);

	*/
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}

SDL_Surface *load_image(std::string filename)			//laddar och optimerar bileden, credits till Lazyfootutorials
{
	SDL_Surface* loadedimage=NULL;
	SDL_Surface* optimizedimage=NULL;

	loadedimage=IMG_Load(filename.c_str());

	if(loadedimage != NULL)
	{
		optimizedimage=SDL_DisplayFormat(loadedimage);
		SDL_FreeSurface(loadedimage);

		if(optimizedimage!=NULL)
		{
			Uint32 colorkey=SDL_MapRGB(optimizedimage->format,0,0xFE,0xFE);		//bakgrundsfärg som ignoreras!
			SDL_SetColorKey(optimizedimage,SDL_SRCCOLORKEY,colorkey);
		}
	}
	return optimizedimage;
}