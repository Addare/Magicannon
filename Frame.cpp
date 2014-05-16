#include "Main.h"

Frame::Frame(int x[], int y[], int w[], int h[], int dur)
{
	duration=dur;
	for(int i=0;i<4;i++)
	{
		clip[i].x=x[i];
		clip[i].y=y[i];
		clip[i].w=w[i];
		clip[i].h=h[i];
	}
}

Frame::Frame()
{}
SDL_Rect* Frame::get_clips()
{
	return clip;
}

int Frame::get_duration()
{
	return duration;
}

