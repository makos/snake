#ifndef GAME_H
#define GAME_H

#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Needs "utils.h" "apple.h" "player.h"
typedef struct Vec Vec_t;
typedef struct Snake Snake_t;
typedef struct Apple Apple_t;

// The current apple being drawn.
Apple_t *APPLE;
// The main window pointer.
WINDOW *MAIN_WIN;
// Main window's position and size.
int POSY, POSX, MAXY, MAXX;

// Directions.
const Vec_t DIR_LEFT;
const Vec_t DIR_UP;
const Vec_t DIR_RIGHT;
const Vec_t DIR_DOWN;

// Colors.
const short RED, GREEN, YELLOW;
// Global is the game running? boolean.
bool RUN;
// Game speed.
int SPEED;

void reset_game(Snake_t *player);
void game_over(Snake_t *player);
void new_game_prompt();
void setup_colors();
void game_setup();
//DEBUG:
void debug_info(WINDOW *win, Snake_t *player);
void check_valid_move(Snake_t *player, Vec_t dir);
void handle_input(Snake_t *player, int ch);
void set_defaults();
void parse_args(int argc, char *argv[]);

#endif //GAME_H