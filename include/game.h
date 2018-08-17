#ifndef GAME_H
#define GAME_H

#include <curses.h>
#include <stdlib.h>
#include <time.h>

// Colors
const short RED, GREEN, YELLOW;
bool RUN;

typedef struct Vec
{
    int y, x;
} Vec_t;

// Directions
const Vec_t DIR_LEFT;
const Vec_t DIR_UP;
const Vec_t DIR_RIGHT;
const Vec_t DIR_DOWN;

// void setup_colors();
// void game_setup();
// void show_debug_info();
// int main(int argc, char *argv[]);

#endif //GAME_H