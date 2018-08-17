#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player
{
    int y, x;
    char ch;
} Player;

void move_player(Player *self, int y, int x);
#endif //PLAYER_H