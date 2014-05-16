#ifndef WINDOW
#define WINDOW

class Window;

class Window		//class for controlling the window
{
	private:
		bool windowed;
		bool windowOK;
		bool close;					//kanske flyttas till en generell klass
	public:
		Window();
		void handle_events(bool* shutdown);
		void toggle_fullscreen();
		bool error();
		bool exit();
};

#endif