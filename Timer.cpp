#include "Main.h"
Timer::Timer()				//intitierar timerklassen
{
	startticks=0;
	pausedticks=0;
	paused=false;
	started=false;
}

void Timer::start()			//startar timern
{
	started=true;
	paused=false;
	startticks=SDL_GetTicks();
}

void Timer::stop()			//stannar timern
{
	started=false;
	paused=false;
}

int Timer::get_ticks()		//hämtar tiden som gått, i millisekunder
{
	if(started==true)
	{
		if(paused==true)
		{
			return pausedticks;
		}
		else
		{
			return SDL_GetTicks()-startticks;
		}
	}
	return 0;
}

void Timer::pause()			//pausar timern
{
	if(started==true && paused==false)
	{
		paused=true;
		pausedticks=SDL_GetTicks()-startticks;
	}
}

void Timer::unpause()		//avpausar timern
{
	if(paused==true)
	{
		paused=false;
		startticks=SDL_GetTicks()-pausedticks;
		pausedticks=0;
	}
}

bool Timer::is_started()	//returnerar om timern är igång
{
	return started;
}
bool Timer::is_paused()		//returnerar om timern är pausad
{
	return paused;
}