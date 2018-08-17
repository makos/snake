#ifndef APPLE_H
#define APPLE_H
// Needs "game.h"
typedef struct Vec Vec_t;

typedef struct Apple
{
    Vec_t pos;
    char ch;
} Apple_t;

Apple_t *new_random_apple();
void draw_apple(Apple_t *self);
void eat_apple(Apple_t *self);

#endif //APPLE_H