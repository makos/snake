#ifndef GAME_H
#define GAME_H

#include <curses.h>
#include <stdlib.h>
#include <time.h>

// Colors
const short RED, GREEN;
bool RUN;

typedef struct Vec
{
    int y, x;
} Vec_t;

// void setup_colors();
// void game_setup();
// void show_debug_info();
// int main(int argc, char *argv[]);

#endif //GAME_H