#include "player.h"
#include "game.h"

void move_player(Player *self, int y, int x)
{
    if (y >= 0 && y < LINES && x >= 0 && x < COLS)
    {
        self->x = x;
        self->y = y;
    }
}