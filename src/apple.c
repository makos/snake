#include "game.h"
#include "apple.h"

Apple_t *new_random_apple()
{
    // Initialize the RNG with current CPU clock time
    time_t tt;
    srand(time(&tt));
    int rand_y = rand() % LINES;
    int rand_x = rand() % COLS;
    Apple_t *apple = (Apple_t *)malloc(sizeof(Apple_t));
    apple->pos.y = rand_y;
    apple->pos.x = rand_x;
    apple->ch = '@';
    return apple;
}

void draw_apple(Apple_t *self)
{
    attron(COLOR_PAIR(RED));
    mvprintw(self->pos.y, self->pos.x, (char *)&self->ch);
    attroff(COLOR_PAIR(RED));
}

void eat_apple(Apple_t *self)
{
    free(self);
}