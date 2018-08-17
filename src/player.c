#include "game.h"
#include "player.h"

void move_player(Player_t *self, Vec_t dir)
{
    int temp_y = self->pos.y + dir.y;
    int temp_x = self->pos.x + dir.x;
    self->facing.x = 0;
    self->facing.y = 0;

    if (dir.x == 1)
        self->facing.x = 1;
    else if (dir.y == 1)
        self->facing.y = 1;
    else if (dir.x == -1)
        self->facing.x = -1;
    else if (dir.y == -1)
        self->facing.y = -1;

    if (temp_y >= 0 && temp_y < LINES && temp_x >= 0 && temp_x < COLS)
    {
        self->pos.x += dir.x;
        self->pos.y += dir.y;
    }
}

void draw_player(Player_t *self)
{
    attron(COLOR_PAIR(GREEN));
    mvprintw(self->pos.y, self->pos.x, &self->ch);
    attroff(COLOR_PAIR(GREEN));
}