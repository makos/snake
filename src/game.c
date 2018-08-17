#include "game.h"
#include "player.h"
#include "apple.h"

const short GREEN = 1;
const short RED = 2;

const Vec_t DIR_LEFT = {0, -1};
const Vec_t DIR_UP = {-1, 0};
const Vec_t DIR_RIGHT = {0, 1};
const Vec_t DIR_DOWN = {1, 0};

bool RUN = TRUE;

void setup_colors()
{
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(RED, COLOR_RED, COLOR_BLACK);
}

void game_setup()
{
    // Curses initializaiton & setup.
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    if (has_colors())
    {
        start_color();
    }
    nodelay(stdscr, TRUE);
    curs_set(0);
    setup_colors();
}

void show_debug_info(Snake_t *player)
{
    int i = 2;
    SnakePart_t *cur = player->head;
    while (cur != NULL)
    {
        mvprintw(i, COLS - 20, "%i %i", cur->pos.y, cur->pos.x);
        cur = cur->next;
        i++;
    }
    //     mvprintw(1, COLS - 20, "Max: %i %i", LINES, COLS);
    //     mvprintw(2, COLS - 20, "Player.pos: %i %i", player->pos.y, player->pos.x);
    //     mvprintw(3, COLS - 20, "Player.facing: %i %i", player->facing.y, player->facing.x);
    //     mvprintw(4, COLS - 20, "Move dir: %i %i", dir.y, dir.x);
    //     // mvprintw(5, COLS - 20, "Clock: %i", (unsigned int)clock());
    //     mvprintw(5, COLS - 20, "Tail length: %i", tail_len(player));
}

int main(int argc, char *argv[])
{
    int ch; // For input.
    game_setup();

    Vec_t pos = {2, 5};
    Snake_t *player = new_snake(pos, '#');

    draw_snake(player);

    Apple_t *apple = new_random_apple();
    draw_apple(apple);

    refresh();

    while (RUN)
    {
        clear();
        ch = getch();
        move_snake(player, player->facing);

        switch (ch)
        {
        case KEY_LEFT:
            move_snake(player, DIR_LEFT);
            break;
        case KEY_RIGHT:
            move_snake(player, DIR_RIGHT);
            break;
        case KEY_UP:
            move_snake(player, DIR_UP);
            break;
        case KEY_DOWN:
            move_snake(player, DIR_DOWN);
            break;
        case 'q':
            RUN = FALSE;
            break;
        }

        draw_snake(player);

        if (player->head->pos.y == apple->pos.y && player->head->pos.x == apple->pos.x)
        {
            eat_apple(apple);
            apple = new_random_apple();
            add_score(player);
        }

        draw_apple(apple);

        // show_debug_info(player);

        refresh();
        napms(50);
    }

    curs_set(1);
    endwin();
    return 0;
}
