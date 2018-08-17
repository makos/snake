#ifndef PLAYER_H
#define PLAYER_H
// Needs "game.h"
typedef struct Vec Vec_t;

typedef struct Player
{
    Vec_t pos;
    Vec_t facing;
    char ch;
} Player_t;

void move_player(Player_t *self, Vec_t dir);
void draw_player(Player_t *self);
#endif //PLAYER_H