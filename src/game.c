#include "utils.h"
#include "game.h"
#include "player.h"
#include "apple.h"

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
    APPLE = new_random_apple(player);
    wclear(MAIN_WIN);
    draw_snake(player);
    draw_apple(APPLE);
    wrefresh(MAIN_WIN);
    new_game_prompt();
}

void game_over(Snake_t *player)
{
    nodelay(MAIN_WIN, FALSE);
    // Fixes memory leak? Not actually profiled yet.
    clear_snake(player);
    char ch;
    int loop = TRUE;
    mvwprintw(MAIN_WIN, 1, 1, "Game Over");
    mvwprintw(MAIN_WIN, 2, 1, "Press Q to quit and R to restart");

    while (loop)
    {
        ch = wgetch(MAIN_WIN);
        switch (ch)
        {
        case 'Q':
            endwin();
            exit(0);
            break;
        case 'r':
        case 'R':
            loop = FALSE;
            // nodelay(MAIN_WIN, TRUE);
            reset_game(player);
            break;
        }
    }
}

void new_game_prompt()
{
    int ch;
    nodelay(MAIN_WIN, FALSE);
    mvwprintw(MAIN_WIN, 1, 1, "Press any key to start...");
    wrefresh(MAIN_WIN);
    // The following calls to wgetch() and ungetch() grab a key the user presses,
    // and if it's an arrow key it gets processed in the main loop, so the
    // snake immediately starts moving in the selected direction.
    ch = wgetch(MAIN_WIN);
    nodelay(MAIN_WIN, TRUE);
    ungetch(ch);
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

    MAIN_WIN = newwin(10, 20, 1, 1);
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
    curs_set(0);
    setup_colors();

    // Random seed.
    time_t tt;
    srand((time(&tt)));
}

//DEBUG:
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
    if (snake_len(player) == 0 && !dir_is_eq(player->facing, dir))
    {
        move_snake(player, dir);
    }
    else
    {
        // Second check prevents the player from turning inside themselves,
        // first is like the second one above.
        if (!dir_is_eq(player->facing, dir) &&
            !dir_is_eq(player->facing, reverse_dir(dir)))
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
        // When no input is given, move the snake one cell per frame in
        // the direction it's facing.
        move_snake(player, player->facing);
    }
}

int main(int argc, char *argv[])
{
    int ch; // For input.
    game_setup();
    //DEBUG: remove later
    // WINDOW *dbg_win = newwin(5, 20, 5, 30);

    // Initialize the player.
    Snake_t *player = new_snake(random_vec(MAXY - 1, MAXX - 1), '#');
    draw_snake(player);

    // Initialize the first apple.
    APPLE = new_random_apple(player);
    draw_apple(APPLE);

    new_game_prompt();
    //DEBUG:
    // wrefresh(dbg_win);

    // Main loop.
    while (RUN)
    {
        ch = wgetch(MAIN_WIN);

        werase(MAIN_WIN);
        //DEBUG:
        // werase(dbg_win);

        handle_input(player, ch);

        // Check if player has collided with the apple.
        if (dir_is_eq(player->head->pos, APPLE->pos))
        {
            eat_apple(APPLE);
            APPLE = new_random_apple(player);
            add_score(player);
        }

        box(MAIN_WIN, 0, 0);

        draw_snake(player);

        draw_apple(APPLE);

        //DEBUG:
        // debug_info(dbg_win, player);

        wrefresh(MAIN_WIN);
        //DEBUG:
        // wrefresh(dbg_win);

        napms(100);
    }

    endwin();
    return 0;
}
