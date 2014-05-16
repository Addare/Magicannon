#include "Main.h"

int grid_corrector(int value)
{
	if(value%GRID_SIZE>(GRID_SIZE/2))
	{
		return value+(GRID_SIZE-(value%GRID_SIZE));
	}
	else
	{
		return value-(value%GRID_SIZE);
	}
}