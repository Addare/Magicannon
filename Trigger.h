#ifndef TRIGGER
#define TRIGGER

class Trigger;

class Trigger
{
private:
	int type;
	int argument1;
	int argument2;

public:
	Trigger();
	Trigger(int triggertype, int arg1, int arg2);
	void set(int triggertype, int arg1, int arg2);
	bool get_hitbox();
};

#endif