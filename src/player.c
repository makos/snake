#include "game.h"
#include "player.h"

Snake_t *new_snake(Vec_t pos)
{
    SnakePart_t *head = (SnakePart_t *)malloc(sizeof(SnakePart_t));
    head->next = NULL;
    head->prev = NULL;
    head->pos = pos;

    Snake_t *snake = (Snake_t *)malloc(sizeof(Snake_t));
    snake->parts = head;

    return snake;
}

/* Appends new SnakePart at the end. */
void append_part(Snake_t *self, Vec_t pos)
{
    SnakePart_t *current = self->parts;
    while (current->next != NULL)
    {
        current = current->next;
    }
    SnakePart_t *new_part = (SnakePart_t *)malloc(sizeof(SnakePart_t));
    // Vec_t pos = {0, 0};
    new_part->prev = current;
    new_part->next = NULL;
    new_part->pos = pos;
    current->next = new_part;
}

/* Inserts new SnakePart at the beginning of snake. */
void push_part(Snake_t *self, Vec_t pos)
{
    SnakePart_t *new_part = (SnakePart_t *)malloc(sizeof(SnakePart_t));
    // Vec_t pos = {0, 0};
    //TODO: fix this, new_part should be first in the list and now it is not
    new_part->pos = pos;
    new_part->prev = NULL;
    self->parts->prev = new_part;
    new_part->next = self->parts;
    self->parts = new_part;
}

int snake_len(Snake_t *self)
{
    SnakePart_t *current = self->parts;
    int count = 0;
    while (current->next != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}