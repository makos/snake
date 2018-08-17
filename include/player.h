#ifndef PLAYER_H
#define PLAYER_H
// Needs "game.h"
typedef struct Vec Vec_t;
typedef struct SnakePart SnakePart_t;

typedef struct SnakePart
{
    SnakePart_t *prev;
    Vec_t pos;
    SnakePart_t *next;
} SnakePart_t;

typedef struct Snake
{
    SnakePart_t *parts;
} Snake_t;

Snake_t *new_snake();
void append_part(Snake_t *self, Vec_t pos);
void push_part(Snake_t *self, Vec_t pos);
int snake_len(Snake_t *self);

#endif //PLAYER_H