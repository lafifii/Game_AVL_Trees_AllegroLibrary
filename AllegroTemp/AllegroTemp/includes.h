#include <iostream>
#include <vector>
#include <functional>
#include <queue>
#include <stack>
#include <string>
#include <windows.h>
using namespace std;


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#define NONE 0

const int width = 1600 / 1.5;
const int height = 900 / 1.5;
const int FPS = 60;

const float gravity = 9.8 / FPS;

extern float mouseX;
extern float mouseY;

extern bool CLICK;

extern bool SPACE;
extern bool UP;
extern bool DOWN;
extern bool LEFT;
extern bool RIGHT;
extern bool ELEX;
extern bool DEL;


extern bool key[26];
extern bool num[10];

#include "Arbol.h"
#include "Objeto.h"
#include "CBalas.h"
#include "Cplayer.h"
#include "CEnemigo.h"
#include "Recurso.h"
#include "CBlock.h"
#include "Beacon.h"
#include "Scene.h"
#include "Juego.h"
#include "Input.h"
#include "Menu.h"