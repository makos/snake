/* 
 * player.c - player (snake) structure and related functions.
 * 
 * The Snake is represented as a structure that is made out of SnakeParts.
 * This is essentialy a doubly linked list. It supports rudimentary operations
 * such as pushing, appending and deleting.
 * 
 * The Snake also has a Vec_t facing field which tells us which way the player
 * is facing, so we can move the snake one cell every frame.
 */
#include "game.h"
#include "player.h"
#include "utils.h"

/* Allocate memory for a new snake.
   Snakes always have a head that connects to the tail */
Snake_t *new_snake(Vec_t pos, int ch)
{
    SnakePart_t *head = (SnakePart_t *)malloc(sizeof(SnakePart_t));
    head->next = NULL;
    head->prev = NULL;
    head->pos = pos;

    Snake_t *snake = (Snake_t *)malloc(sizeof(Snake_t));
    snake->head = head;
    snake->facing = DIR_UP;
    snake->ch = ch;

    return snake;
}

void move_snake(Snake_t *self, Vec_t dir)
{
    // Change facing direction accordingly.
    if (is_eq(dir, DIR_UP))
        self->facing = DIR_UP;
    else if (is_eq(dir, DIR_RIGHT))
        self->facing = DIR_RIGHT;
    else if (is_eq(dir, DIR_DOWN))
        self->facing = DIR_DOWN;
    else if (is_eq(dir, DIR_LEFT))
        self->facing = DIR_LEFT;

    Vec_t new_pos = {
        self->head->pos.y + dir.y,
        self->head->pos.x + dir.x};

    // Check for collisions with the tail.
    if (self->head->next != NULL)
    {
        SnakePart_t *current = self->head->next;
        while (current->next != NULL)
        {
            if (is_eq(self->head->pos, current->pos))
                game_over(self);
            current = current->next;
        }
    }

    // Stop at the edges. 1 and -1 because of borders.
    if (new_pos.y < 1 || new_pos.y >= MAXY - 1 ||
        new_pos.x < 1 || new_pos.x >= MAXX - 1)
    {
        game_over(self);
    }

    // "Caterpillar-like" movement behavior (peristaltic).
    SnakePart_t *last = get_last(self);
    push_part(self);
    delete_part(last);
    self->head->pos = new_pos;
}

void draw_snake(Snake_t *self)
{
    SnakePart_t *current = self->head;
    while (current != NULL)
    {
        // Draw the head in different color.
        if (current->prev == NULL)
        {
            wattron(MAIN_WIN, COLOR_PAIR(YELLOW));
            mvwprintw(MAIN_WIN, current->pos.y, current->pos.x, (char *)&self->ch);
            wattroff(MAIN_WIN, COLOR_PAIR(YELLOW));
        }
        else
        {
            wattron(MAIN_WIN, COLOR_PAIR(GREEN));
            mvwprintw(MAIN_WIN, current->pos.y, current->pos.x, (char *)&self->ch);
            wattroff(MAIN_WIN, COLOR_PAIR(GREEN));
        }
        current = current->next;
    }
}

// Add tail segment when apple is eaten.
void add_score(Snake_t *self)
{
    append_part(self);
}

// Find the last part of snake's tail.
SnakePart_t *get_last(Snake_t *snake)
{
    SnakePart_t *last = snake->head;
    while (last->next != NULL)
        last = last->next;
    return last;
}

// Delete snake's part. (ouch!)
void delete_part(SnakePart_t *part)
{
    if (part->prev == NULL)
        return;
    part->prev->next = NULL;
    part->prev = NULL;
    free(part);
}

// Appends new SnakePart at the end.
void append_part(Snake_t *self)
{
    SnakePart_t *last = get_last(self);
    SnakePart_t *new_part = (SnakePart_t *)malloc(sizeof(SnakePart_t));

    new_part->prev = last;
    new_part->next = NULL;
    new_part->pos = last->pos;

    last->next = new_part;
}

// Inserts new SnakePart at the beginning of snake.
void push_part(Snake_t *self)
{
    SnakePart_t *new_part = (SnakePart_t *)malloc(sizeof(SnakePart_t));
    new_part->pos = self->head->pos;
    // New part should point to the current head.
    new_part->next = self->head;
    // new_part is first so no previous part exists.
    new_part->prev = NULL;
    // "Move" current head.
    if (self->head != NULL)
        self->head->prev = new_part;
    // Make the new part actually the first part.
    self->head = new_part;
}

// Returns the length of snake.
int snake_len(Snake_t *self)
{
    SnakePart_t *current = self->head;
    int count = 0;
    while (current->next != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}