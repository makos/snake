/*
 * apple.c - Apple data structure and related functions.
 * 
 * Apple is as simple as it gets. It holds position data and the character it
 * should be printed as. It has basic drawing, creating and freeing functions.
 */
#include "utils.h"
#include "game.h"
#include "player.h"
#include "apple.h"

// Spawn a new apple at a random position.
Apple_t *new_random_apple(Snake_t *player)
{
    Apple_t *apple = (Apple_t *)malloc(sizeof(Apple_t));
    Vec_t pos = random_vec(MAXY - 1, MAXX - 1);

    // If we tried to spawn an apple on the snake, try again.
    if (dir_is_eq(player->head->pos, pos))
        pos = random_vec(MAXY - 1, MAXX - 1);
    else
    {
        SnakePart_t *current = player->head;
        while (current->next != NULL)
        {
            if (dir_is_eq(current->pos, pos))
                pos = random_vec(MAXY - 1, MAXX - 1);
            current = current->next;
        }
    }
    apple->pos = pos;
    apple->ch = '@';
    return apple;
}

// Draw the apple.
void draw_apple(Apple_t *self)
{
    wattron(MAIN_WIN, COLOR_PAIR(RED));
    mvwprintw(MAIN_WIN, self->pos.y, self->pos.x, (char *)&self->ch);
    wattroff(MAIN_WIN, COLOR_PAIR(RED));
}

// "Eat" the apple, freeing memory.
void eat_apple(Apple_t *self)
{
    free(self);
}