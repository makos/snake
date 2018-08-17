#ifndef GAME_H
#define GAME_H

#include <curses.h>
#include <stdlib.h>
// #include <time.h>

const short RED, GREEN;
bool RUN;

void setup_colors();
void game_setup();
void show_debug_info();
int main(int argc, char *argv[]);

#endif //GAME_H