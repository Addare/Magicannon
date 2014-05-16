#ifndef HEADDUR1
#define HEADDUR1

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int GRID_SIZE = 40;
const int FRAMES_PER_SECOND = 60;
const int DIR_UP = 0;
const int DIR_RIGHT = 1;
const int DIR_DOWN = 2;
const int DIR_LEFT = 3;
const int UNIT_AMOUNT = 30;
const int PROJECTILE_AMOUNT = 30;

#include "SDL.h"
#include "SDL_Image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include <iostream>
using namespace std;

#include "Structs.h"
#include "Trigger.h"
#include "World.h"
#include "Graphicentity.h"
#include "Interactiveentity.h"
#include "Entitymanager.h"
#include "Collisionmanager.h"
#include "Mapobject.h"
#include "Unit.h"
#include "Player.h"
#include "Enemy.h"
#include "Effect.h"
#include "Npc.h"
#include "Timer.h"
#include "Window.h"
#include "Spellmanager.h"
#include "Spell.h"
#include "Projectile.h"
#include "Actionsequence.h"
#include "Frame.h"



extern SDL_Surface* screen;
extern SDL_Event event;



bool init();
void load_area(int map_nr);
void load_files();
void clean_up();
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination,SDL_Rect* clip=NULL);
SDL_Surface *load_image(std::string filename);
int grid_corrector(int x);


#endif


/*
TODO!!!

Kommentarer
Mallar till filer
G�ra unitsen till pekare
St�d f�r st�rre proektiler
F�r�lderklass till spell och projectile?
spells: Fler alternativ p�E"chainspelling"
Spellsens hitboxes, de ska g�Ein i rutan de tr�ffar-------Ser konstigt ut, komma p�El�sning. Borde fungera funktionellt
hitta l�sning till prestandaproblem med hitboxes
Status
effekter
Hitta l�sning till v�ggar
Spellsystemet, se till s�Eatt spells som spawnar spells v�ljer var den ska spawnas
AI
Fiender
Units, se till s�Eatt spelaren inte f�rsvinner n�r banan byter, p�Eett b�ttre s�tt
Konstrukt�rer till units
B�ttre felhantering, f�nga fel mm.








*/