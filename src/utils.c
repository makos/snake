#include "game.h"
#include "utils.h"

int is_eq(Vec_t dir, Vec_t other)
{
    return dir.y == other.y && dir.x == other.x;
}

// WINDOW *create_win(int height, int width, int starty, int startx)
// {
//     WINDOW *local;
//     local = newwin(height, width, starty, startx);
//     box(local, 0, 0);
//     // wrefresh(local);
//     return local;
// }