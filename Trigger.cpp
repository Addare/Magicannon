#include "Main.h"

Trigger::Trigger()
{
}

Trigger::Trigger(int triggertype, int arg1, int arg2)
{
	type=triggertype;
	argument1=arg1;
	argument2=arg2;
}

void Trigger::set(int triggertype, int arg1, int arg2)
{
	Trigger(triggertype, arg1, arg2);
}

bool Trigger::get_hitbox()
{
	return false;
}