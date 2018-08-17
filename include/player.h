#ifndef PLAYER_H
#define PLAYER_H
// Needs "game.h"
typedef struct Vec Vec_t;
typedef struct Tail Tail_t;

typedef struct Tail
{
    Vec_t pos;
    Tail_t *next;
} Tail_t;

typedef struct Player
{
    Vec_t pos;
    Vec_t facing;
    char ch;
    Tail_t *tail;
} Player_t;

void move_player(Player_t *self, Vec_t dir);
void draw_player(Player_t *self);
void add_tail(Player_t *self);
int tail_len(Player_t *player);
#endif //PLAYER_H