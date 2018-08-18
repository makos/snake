/*
 * apple.c - Apple data structure and related functions.
 * 
 * Apple is as simple as it gets. It holds position data and the character it
 * should be printed as. It has basic drawing, creating and freeing functions.
 */
#include "utils.h"
#include "game.h"
#include "apple.h"

// Spawn a new apple at a random position.
Apple_t *new_random_apple()
{
    Apple_t *apple = (Apple_t *)malloc(sizeof(Apple_t));
    apple->pos = random_vec(MAXY - 1, MAXX - 1);
    apple->ch = '@';
    return apple;
}

// Draw the apple.
void draw_apple(Apple_t *self)
{
    wattron(MAIN_WIN, COLOR_PAIR(RED));
    mvwprintw(MAIN_WIN, self->pos.y, self->pos.x, (char *)&self->ch);
    wattroff(MAIN_WIN, COLOR_PAIR(RED));
}

// "Eat" the apple, freeing memory.
void eat_apple(Apple_t *self)
{
    free(self);
}