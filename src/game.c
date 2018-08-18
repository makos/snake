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
Apple_t *APPLE;
WINDOW *MAIN_WIN;

// Creating a new window segfaults, WHY??
WINDOW *create_win(int height, int width, int starty, int startx)
{
    WINDOW *local;
    local = newwin(height, width, starty, startx);
    // local = subwin(stdscr, height, width, starty, startx);
    box(local, 0, 0);
    // wnoutrefresh(local);
    wrefresh(local);
    return local;
}

void reset_game(Snake_t *player)
{
    player->head->next = NULL;
    // Vec_t pos = {10, 10};
    player->head->pos = random_vec();
    eat_apple(APPLE);
    APPLE = new_random_apple();
}

void game_over(Snake_t *player)
{
    int mid_y = LINES / 2;
    char ch;
    int loop = TRUE;
    mvwprintw(MAIN_WIN, mid_y, COLS / 2, "Game Over");
    mvwprintw(MAIN_WIN, mid_y + 1, COLS / 2, "Press Q to quit and R to restart");
    nodelay(MAIN_WIN, FALSE);

    while (loop)
    {
        ch = wgetch(MAIN_WIN);
        switch (ch)
        {
        // case 'q':
        case 'Q':
            loop = FALSE;
            RUN = FALSE;
            break;
        // case 'r':
        case 'R':
            loop = FALSE;
            nodelay(MAIN_WIN, TRUE);
            reset_game(player);
            break;
        }
    }
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
    MAIN_WIN = newwin(5, 100, 0, 0);
    cbreak();
    noecho();
    keypad(MAIN_WIN, TRUE);
    if (has_colors())
    {
        start_color();
    }
    nodelay(MAIN_WIN, TRUE);
    curs_set(0);
    box(MAIN_WIN, 0, 0);
    setup_colors();
}

void debug_info(WINDOW *win, Snake_t *player)
{
    mvwprintw(win, 1, 1, "test");
}

int main(int argc, char *argv[])
{
    int ch; // For input.
    game_setup();
    WINDOW *dbg_win = create_win(5, 20, 5, 5);

    // Vec_t pos = {LINES / 2, COLS / 2};
    Snake_t *player = new_snake(random_vec(), '#');
    draw_snake(player);

    APPLE = new_random_apple();
    draw_apple(APPLE);

    wrefresh(MAIN_WIN);
    wrefresh(dbg_win);

    while (RUN)
    {
        // erase() seems to be faster?
        // wclear(main_win);
        werase(MAIN_WIN);
        // werase(dbg_win);
        // clear();
        // erase();
        ch = wgetch(MAIN_WIN);
        // ch = getch();
        move_snake(player, player->facing);

        switch (ch)
        {
        case KEY_LEFT:
            if (snake_len(player) == 0 && !is_eq(player->facing, DIR_LEFT))
            {
                move_snake(player, DIR_LEFT);
                break;
            }
            if (!is_eq(player->facing, DIR_RIGHT) &&
                !is_eq(player->facing, DIR_LEFT))
                move_snake(player, DIR_LEFT);
            break;
        case KEY_RIGHT:
            if (snake_len(player) == 0 && !is_eq(player->facing, DIR_RIGHT))
            {
                move_snake(player, DIR_RIGHT);
                break;
            }
            if (!is_eq(player->facing, DIR_LEFT) &&
                !is_eq(player->facing, DIR_RIGHT))
                move_snake(player, DIR_RIGHT);
            break;
        case KEY_UP:
            if (snake_len(player) == 0 && !is_eq(player->facing, DIR_UP))
            {
                move_snake(player, DIR_UP);
                break;
            }
            if (!is_eq(player->facing, DIR_DOWN) &&
                !is_eq(player->facing, DIR_UP))
                move_snake(player, DIR_UP);
            break;
        case KEY_DOWN:
            if (snake_len(player) == 0 && !is_eq(player->facing, DIR_DOWN))
            {
                move_snake(player, DIR_DOWN);
                break;
            }
            if (!is_eq(player->facing, DIR_UP) &&
                !is_eq(player->facing, DIR_DOWN))
                move_snake(player, DIR_DOWN);
            break;
        case 'Q':
            // case 'q':
            RUN = FALSE;
            break;
        case 'R':
            reset_game(player);
            break;
        }

        draw_snake(player);

        if (is_eq(player->head->pos, APPLE->pos))
        {
            eat_apple(APPLE);
            APPLE = new_random_apple();
            add_score(player);
        }

        draw_apple(APPLE);

        wrefresh(dbg_win);
        wrefresh(MAIN_WIN);
        napms(50);
    }

    // clear();
    endwin();
    return 0;
}
