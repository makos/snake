#ifndef PLAYER_H
#define PLAYER_H
// Needs "game.h" "curses.h"
typedef struct Vec Vec_t;
typedef struct SnakePart SnakePart_t;

#ifdef _WIN32
typedef struct _win WINDOW;
#endif

#ifdef _gnu_linux_
typedef struct _win_st WINDOW;
#endif

typedef struct SnakePart
{
    SnakePart_t *prev;
    Vec_t pos;
    SnakePart_t *next;
} SnakePart_t;

typedef struct Snake
{
    SnakePart_t *head;
    Vec_t facing;
    int ch;
    int score;
} Snake_t;

Snake_t *new_snake(Vec_t pos, int ch);
int snake_len(Snake_t *self);
void move_snake(Snake_t *self, Vec_t dir);
void draw_snake(Snake_t *self);
void add_score(Snake_t *self);
void delete_part(SnakePart_t *part);
void append_part(Snake_t *self);
void push_part(Snake_t *self);
SnakePart_t *get_last(Snake_t *snake);
void clear_snake(Snake_t *self);

#endif //PLAYER_H