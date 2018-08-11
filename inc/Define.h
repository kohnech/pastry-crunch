#pragma once

/*
 * Default defines if none specified in json
 */
#include <SDL2/SDL.h>

#define MAP_WIDTH 40
#define MAP_HEIGHT 40

const int GRID_WIDTH = 4;
const int GRID_HEIGHT = 4;

const int ICON_WIDTH = 64;
const int ICON_HEIGHT = 72;

#define TILE_SIZE 16

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


// Colors
const SDL_Color WHITE = { 255, 255, 255 };
const SDL_Color RED = { 255, 0, 0 };
const SDL_Color GREEN = { 0, 255, 0 };
const SDL_Color BLUE = { 0, 0, 255 };