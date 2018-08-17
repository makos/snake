#ifndef PLAYER_H
#define PLAYER_H

typedef struct Vec
{
    int y, x;
} Vec;

typedef struct Player
{
    Vec pos;
    Vec facing;
    char ch;
} Player;

void move_player(Player *self, Vec dir);
void draw_player(Player *self);
#endif //PLAYER_H