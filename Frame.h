#ifndef FRAME
#define FRAME

class Frame;

class Frame
{
private:
	SDL_Rect clip[4];
	int duration;

public:
	Frame();
	Frame(int x[], int y[], int w[], int h[], int dur);
	SDL_Rect* get_clips();
	int get_duration();
};

#endif