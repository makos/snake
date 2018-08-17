#include "game.h"
#include "apple.h"

Apple_t *new_random_apple()
{
    srand((unsigned int)clock());
    int rand_y = rand() % LINES;
    int rand_x = rand() % COLS;
    Apple_t *apple = malloc(sizeof(Apple_t));
    apple->pos.y = rand_y;
    apple->pos.x = rand_x;
    apple->ch = '@';
    return apple;
}

void draw_apple(Apple_t *self)
{
    attron(COLOR_PAIR(RED));
    mvprintw(self->pos.y, self->pos.x, &self->ch);
    attroff(COLOR_PAIR(RED));
}

void eat_apple(Apple_t *self)
{
    free(self);
}