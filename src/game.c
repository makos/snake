#include "game.h"
#include "player.h"
#include "apple.h"
#include "utils.h"

const short GREEN = 1;
const short RED = 2;
const short YELLOW = 3;

const Vec_t DIR_LEFT = {0, -1};
const Vec_t DIR_UP = {-1, 0};
const Vec_t DIR_RIGHT = {0, 1};
const Vec_t DIR_DOWN = {1, 0};

bool RUN = TRUE;

WINDOW *create_win(int height, int width, int starty, int startx)
{
    WINDOW *local;
    local = newwin(height, width, starty, startx);
    box(local, 0, 0);
    wrefresh(local);
    return local;
}

void setup_colors()
{
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(RED, COLOR_RED, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
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

void show_debug_info(Snake_t *player, WINDOW *win)
{
    // mvwprintw(win, 1, 1, "Len: %i", snake_len(player));
    // mvwprintw(win, 2, 1, "Pos: %i %i", player->head->pos.y, player->head->pos.x);
    // mvwaddstr(win, 1, 1, "test");
    // mvwaddstr(win, 2, 1, "another");
}

int main(int argc, char *argv[])
{
    int ch; // For input.
    //DEBUG STUFF
    // WINDOW *debug_win = create_win(4, 4, 10, 10);
    // WINDOW *debug_win = newwin(4, 4, 10, 10);
    game_setup();

    Vec_t pos = {LINES / 2, COLS / 2};
    Snake_t *player = new_snake(pos, '#');

    draw_snake(player);

    Apple_t *apple = new_random_apple();
    draw_apple(apple);

    // wrefresh(debug_win);
    refresh();

    while (RUN)
    {
        clear();
        ch = wgetch(stdscr);
        move_snake(player, player->facing);

        switch (ch)
        {
        case KEY_LEFT:
            if (snake_len(player) == 0)
            {
                move_snake(player, DIR_LEFT);
                break;
            }
            if (!is_eq(player->facing, DIR_RIGHT))
                move_snake(player, DIR_LEFT);
            break;
        case KEY_RIGHT:
            if (snake_len(player) == 0)
            {
                move_snake(player, DIR_RIGHT);
                break;
            }
            if (!is_eq(player->facing, DIR_LEFT))
                move_snake(player, DIR_RIGHT);
            break;
        case KEY_UP:
            if (snake_len(player) == 0)
            {
                move_snake(player, DIR_UP);
                break;
            }
            if (!is_eq(player->facing, DIR_DOWN))
                move_snake(player, DIR_UP);
            break;
        case KEY_DOWN:
            if (snake_len(player) == 0)
            {
                move_snake(player, DIR_DOWN);
                break;
            }
            if (!is_eq(player->facing, DIR_UP))
                move_snake(player, DIR_DOWN);
            break;
        case 'a':
            add_score(player);
            break;
        case 'q':
            RUN = FALSE;
            break;
        }

        draw_snake(player);

        if (player->head->pos.y == apple->pos.y &&
            player->head->pos.x == apple->pos.x)
        {
            eat_apple(apple);
            apple = new_random_apple();
            add_score(player);
        }

        draw_apple(apple);

        box(stdscr, 0, 0);

        // show_debug_info(player, debug_win);
        // wprintw(debug_win, "test");

        // wrefresh(debug_win);
        refresh();
        napms(50);
    }

    // curs_set(1);
    endwin();
    return 0;
}
