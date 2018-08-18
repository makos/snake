#include "game.h"
#include "utils.h"

/* Tests equality between two Vec_t points. */
int is_eq(Vec_t dir, Vec_t other)
{
    return dir.y == other.y && dir.x == other.x;
}

//TODO: Make this actually RNG
Vec_t random_vec()
{
    time_t tt;
    srand((time(&tt) * 377) % 23);
    int rand_y = rand() % LINES;
    int rand_x = rand() % COLS;
    Vec_t vec = {rand_y, rand_x};
    return vec;
}