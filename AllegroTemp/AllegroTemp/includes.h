#include <iostream>
#include <vector>
#include <functional>
#include <queue>
#include <stack>
#include <string>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#define NONE 0

const int width = 900;
const int height = 600;
const int FPS = 90;

const float gravity = 9.8 / FPS;

extern float mouseX;
extern float mouseY;

extern bool SPACE;
extern bool UP;
extern bool DOWN;
extern bool LEFT;
extern bool RIGHT;

#include "Arbol.h"
#include "Objeto.h"
#include "Beacon.h"
#include "CBalas.h"
#include "Cplayer.h"
#include "CEnemigo.h"
#include "Recurso.h"
#include "CBlock.h"
#include "Scene.h"