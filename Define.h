#pragma once
#pragma comment(lib, "winmm.lib")

#include <iostream>
#include <ctime>
#include "Console.h"

using namespace std;
using namespace System;

#define GAMENAME "Kokorinzo"

#define WINDOW_WIDTH (Console::WindowWidth())
#define WINDOW_HEIGHT (Console::WindowHeight())

#define PLAYER_COLOR Yellow
#define PLAYER_XMAX (10*WINDOW_WIDTH-1)
#define PLAYER_YMAX (20*WINDOW_HEIGHT-1)
#define GRAVITY (5)
#define JUMP_HEIGHT (PLAYER_YMAX*2/3)
#define JUMP_VELOCITY (sqrt(2*GRAVITY*JUMP_HEIGHT))
#define FRICTION (0.1)
#define BOUNCE (0.95)
#define GROUND (40)

#define ENEMY_COLOR Red
#define E1_U (5)
#define E2_U (4)
#define ENEMY_1_Y (WINDOW_HEIGHT*E1_U/9)
#define ENEMY_2_Y (WINDOW_HEIGHT*E2_U/9)
#define ENEMY_1_X (0)
#define ENEMY_2_X (WINDOW_WIDTH-1)
#define ENEMY_1_X_VEL (3)
#define ENEMY_2_X_VEL (-2)

#define RADIUS (2)

#define DIAMOND_X_MAX (WINDOW_WIDTH-3)
#define DIAMOND_X_MIN (2)
#define DIAMOND_Y_MAX (WINDOW_HEIGHT*2/3-2)
#define DIAMOND_Y_MIN (WINDOW_HEIGHT/3+2)
#define DIAMOND_COLOR DarkBlue

#define FPS (60)
#define DEFAULT_WIDTH (181)
#define DEFAULT_HEIGHT (41)
#define BACKGROUND (DarkGreen)

static int width = WINDOW_WIDTH;
static int height = WINDOW_HEIGHT;

// ☻☺ トニー ☺☻ //