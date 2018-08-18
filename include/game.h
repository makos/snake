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

typedef struct Snake Snake_t;
typedef struct Apple Apple_t;

// The current apple being drawn.
Apple_t *APPLE;

// Directions
const Vec_t DIR_LEFT;
const Vec_t DIR_UP;
const Vec_t DIR_RIGHT;
const Vec_t DIR_DOWN;

void reset_game(Snake_t *player);
void game_over(Snake_t *player);

#endif //GAME_H