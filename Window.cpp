#include "Main.h"
Window::Window()		//initierar klassen window
{
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
	if(screen==NULL)
	{
		windowOK=false;
		return;
	}
	else
	{
		windowOK=true;
	}
	SDL_WM_SetCaption("Magicannon",NULL);
	windowed=true;
	close=false;
}

void Window::toggle_fullscreen()		//sätter spelet i fullscreen
{
	if(windowed==true)
	{
		screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE|SDL_RESIZABLE|SDL_FULLSCREEN);
		if(screen==NULL)
		{
			windowOK=false;
			return;
		}
		windowed = false;
	}
	else if(windowed==false)
	{
		screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE|SDL_RESIZABLE);
		if(screen==NULL)
		{
			windowOK=false;
			return;
		}
		windowed = true;
	}
}

void Window::handle_events(bool* shutdown)			//hanterar events för rutan, används för tillfället ej, förutom till fullscreen
{
	Uint8 *keystates=SDL_GetKeyState(NULL);
	if(windowOK==false)
	{
		return;
	}
	if(event.type==SDL_VIDEORESIZE)
	{
		screen=SDL_SetVideoMode(event.resize.w,event.resize.h,SCREEN_BPP,SDL_SWSURFACE|SDL_RESIZABLE);
		if(screen==NULL)
		{
			windowOK=false;
			return;
		}
	}
	else if(event.type==SDL_QUIT)		//avslutar spelet om rutan kryssas
		{								//Ska kanske ändras i framtiden
			*shutdown=true;
		}


	else if(keystates[SDLK_LALT])		
			{		
				if(keystates[SDLK_F4])	//alt + F4
				{
					*shutdown=true;
				}
			}
	else if(event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_RETURN)
	{
		toggle_fullscreen();
	}

	else if(event.type==SDL_ACTIVEEVENT)
	{
		if(event.active.state & SDL_APPACTIVE)
		{
			if(event.active.gain==0)
			{
				//SDL_WM_SetCaption("Window event test:iconified",NULL);
			}
			else
			{
				//SDL_WM_SetCaption("Window",NULL);
			}
		}
		else if(event.active.state & SDL_APPINPUTFOCUS)
		{
			if(event.active.gain==0)
			{
			//	SDL_WM_SetCaption("Window event test:keyboard focus lost",NULL);
			}
			else
			{
			//	SDL_WM_SetCaption("Window",NULL);
			}
		}
		if(event.active.state & SDL_APPMOUSEFOCUS)
		{
			if(event.active.gain==0)
			{
			//	SDL_WM_SetCaption("Window event test:Mouse focus lost",NULL);
			}
			else
			{
			//	SDL_WM_SetCaption("Window",NULL);
			}
		}
	}
	else if(event.type==SDL_VIDEOEXPOSE)
	{
		if(SDL_Flip(screen)==-1)
		{
			windowOK=false;
			return;
		}
	}
}
bool Window::error()		//returnerar om Windowklassen failar
{
	return !windowOK;
}
bool Window::exit()		//returnerar om Windowklassen failar
{
	return close;
}