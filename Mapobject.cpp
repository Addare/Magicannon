#include "Main.h"

#include "Main.h"

Mapobject::Mapobject()
{
	x=0;
	y=0;
	spritesheet=NULL;
	size=0;
	hitbox=NULL;
}

Mapobject::~Mapobject()
{
	delete spritesheet;
	
	for(int i=0;i<size;i++)
	{
		delete [] hitbox[i];
	}
	delete [] hitbox;
}

void Mapobject::create(string name, int posx, int posy)
{
	x=posx;
	y=posy;
	string file = "objectchart";
	file.insert(0,"data/");					//lägger till "data/"
	std::ifstream loader(file.c_str());

	std::string temp;
	while(temp!=name)					//krachar programmet om npcnamnet inte finns eller är fel
	{
		getline(loader,temp);
	}
	getline(loader, temp);
	temp.insert(0,"images/maps/");
	spritesheet=load_image(temp);
	loader>>arg1;
	loader>>arg2;
	loader>>size;
	int tempint;
	triggers = new Trigger*[size];
	for(int i = 0;i<size;i++)
	{
		triggers[i] = new Trigger[size];
		for(int j=0;j<=size;j++)
		{
			loader>>tempint;
		//	triggers[i][j] = 
				//LADDA IN TILL "TRIGGER"!! som inte finns än, eller nåt;
		}
	}
	
}