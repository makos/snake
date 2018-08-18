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

void reset_game(Snake_t *player)
{
    player->head->next = NULL;
    player->head->pos = random_vec(MAXY - 1, MAXX - 1);
    eat_apple(APPLE);
    APPLE = new_random_apple();
}

void game_over(Snake_t *player)
{
    int mid_y = MAXY / 2;
    char ch;
    int loop = TRUE;
    mvwprintw(MAIN_WIN, mid_y, 1, "Game Over");
    mvwprintw(MAIN_WIN, mid_y + 1, 1, "Press Q to quit and R to restart");
    nodelay(MAIN_WIN, FALSE);

    while (loop)
    {
        ch = wgetch(MAIN_WIN);
        switch (ch)
        {
        case 'Q':
            loop = FALSE;
            RUN = FALSE;
            break;
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
    refresh();

    MAIN_WIN = newwin(10, 20, 5, 5);
    // Get position and size of the window.
    getbegyx(MAIN_WIN, POSY, POSX);
    getmaxyx(MAIN_WIN, MAXY, MAXX);
    // Create a border.
    box(MAIN_WIN, 0, 0);

    cbreak();
    noecho();
    keypad(MAIN_WIN, TRUE);
    if (has_colors())
    {
        start_color();
    }
    nodelay(MAIN_WIN, TRUE);
    curs_set(0);
    setup_colors();
}

void debug_info(WINDOW *win, Snake_t *player)
{
    mvwprintw(win, 0, 0, "Pos:%i %i", player->head->pos.y, player->head->pos.x);
    // mvwprintw(win, 1, 0, "Pos:%i %i", player->head->pos.y, player->head->pos.x);
}

void check_valid_move(Snake_t *player, Vec_t dir)
{
    // If the snake doesn't have a tail, allow movement in any direction.
    // The second check is to disallow players from adding velocity by holding
    // an arrow button while moving in the same direction.
    if (snake_len(player) == 0 && !is_eq(player->facing, dir))
    {
        move_snake(player, dir);
    }
    else
    {
        // Second check prevents the player from turning inside themselves,
        // first is like the second one above.
        if (!is_eq(player->facing, dir) &&
            !is_eq(player->facing, reverse_dir(dir)))
            move_snake(player, dir);
    }
}

void handle_input(Snake_t *player, int ch)
{
    switch (ch)
    {
    case KEY_LEFT:
        check_valid_move(player, DIR_LEFT);
        break;
    case KEY_RIGHT:
        check_valid_move(player, DIR_RIGHT);
        break;
    case KEY_UP:
        check_valid_move(player, DIR_UP);
        break;
    case KEY_DOWN:
        check_valid_move(player, DIR_DOWN);
        break;
    case 'Q':
        RUN = FALSE;
        break;
    case 'R':
        reset_game(player);
        break;
    default:
        move_snake(player, player->facing);
    }
}

int main(int argc, char *argv[])
{
    int ch; // For input.
    game_setup();
    WINDOW *dbg_win = newwin(5, 20, 5, 30);

    Snake_t *player = new_snake(random_vec(MAXY - 1, MAXX - 1), '#');
    draw_snake(player);

    APPLE = new_random_apple();
    draw_apple(APPLE);

    wrefresh(MAIN_WIN);
    wrefresh(dbg_win);

    while (RUN)
    {
        ch = wgetch(MAIN_WIN);

        werase(MAIN_WIN);
        werase(dbg_win);

        handle_input(player, ch);

        if (is_eq(player->head->pos, APPLE->pos))
        {
            eat_apple(APPLE);
            APPLE = new_random_apple();
            add_score(player);
        }

        box(MAIN_WIN, 0, 0);

        draw_snake(player);

        draw_apple(APPLE);

        debug_info(dbg_win, player);

        wrefresh(MAIN_WIN);
        wrefresh(dbg_win);

        napms(100);
    }

    endwin();
    return 0;
}
