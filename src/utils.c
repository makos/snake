/* 
 * utils.c - utility functions used in various places.
 */
#include "game.h"
#include "utils.h"

/* Tests equality between two Vec_t points. */
int is_eq(Vec_t dir, Vec_t other)
{
    return dir.y == other.y && dir.x == other.x;
}

//TODO: Make this actually RNG
Vec_t random_vec(int maxy, int maxx)
{
    // time_t tt;
    int rand_y = rand() % maxy;
    int rand_x = rand() % maxx;
    if (rand_y == 0)
        rand_y++;
    if (rand_x == 0)
        rand_x++;
    Vec_t vec = {rand_y, rand_x};
    return vec;
}

// Reverses the given direction.
Vec_t reverse_dir(Vec_t dir)
{
    Vec_t temp = {-dir.y, -dir.x};
    return temp;
}