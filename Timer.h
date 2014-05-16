#ifndef TIMER
#define TIMER

class Timer;

class Timer			//timer-class
{
private:
	int startticks;
	int pausedticks;

	bool paused;
	bool started;

public:
	Timer();

	void start();
	void stop();
	void pause();
	void unpause();
	int get_ticks();
	bool is_started();
	bool is_paused();
};

#endif