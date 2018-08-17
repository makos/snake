#include "game.h"
#include "player.h"

void move_player(Player_t *self, Vec_t dir)
{
    int temp_y = self->pos.y + dir.y;
    int temp_x = self->pos.x + dir.x;
    self->facing.x = 0;
    self->facing.y = 0;

    if (dir.x == 1)
        self->facing.x = 1;
    else if (dir.y == 1)
        self->facing.y = 1;
    else if (dir.x == -1)
        self->facing.x = -1;
    else if (dir.y == -1)
        self->facing.y = -1;

    if (temp_y >= 0 && temp_y < LINES && temp_x >= 0 && temp_x < COLS)
    {
        Tail_t *tail = self->tail;
        int count = 0;
        while (tail != NULL)
        {
            tail->pos.y = self->pos.y - self->facing.y * count;
            tail->pos.x = self->pos.x - self->facing.x * count;
            tail = tail->next;
            count++;
        }
        self->pos.y += dir.y;
        self->pos.x += dir.x;
    }
}

void draw_player(Player_t *self)
{
    attron(COLOR_PAIR(GREEN));
    mvprintw(self->pos.y, self->pos.x, &self->ch);

    Tail_t *current = self->tail;
    while (current != NULL)
    {
        mvprintw(current->pos.y, current->pos.x, &self->ch);
        current = current->next;
    }

    attroff(COLOR_PAIR(GREEN));
}

void add_tail(Player_t *self)
{
    /*
     *  This function appends the new tail piece to the
     *  end of the linked list Tail struct. 
     */

    // Create space for new tail piece.
    Tail_t *new_piece = (Tail_t *)malloc(sizeof(Tail_t));
    // Used to find the last item.
    Tail_t *last = self->tail;
    if (last != NULL)
    {
        while (last->next != NULL)
            last = last->next;
    }

    // If there are no tail pieces yet, add it behind the head.
    if (self->tail == NULL)
    {
        // Position it behind the snake.
        new_piece->pos.y = self->pos.y - self->facing.y;
        new_piece->pos.x = self->pos.x - self->facing.x;
    }
    // If there are pieces already, we use *last to add
    // the new piece after the last one.
    else
    {
        new_piece->pos.y = last->pos.y - self->facing.y;
        new_piece->pos.x = last->pos.x - self->facing.x;
    }
    // Update the linked-list.
    // We're appending so new piece doesn't have anything after it.
    new_piece->next = NULL;
    // If the list is empty, make the new piece the first item.
    if (self->tail == NULL)
    {
        self->tail = new_piece;
        return;
    }
    // Make the last item point to the new piece.
    last->next = new_piece;
    return;
}

int tail_len(Player_t *player)
{
    int count = 0;
    Tail_t *current = player->tail;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}