#include "game.h"
#include "player.h"
#include "apple.h"

const short GREEN = 1;
const short RED = 2;

bool RUN = TRUE;

void setup_colors()
{
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(RED, COLOR_RED, COLOR_RED);
}

void game_setup()
{
    // Curses initializaiton & setup.
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    if (has_colors())
    {
        start_color();
    }
    nodelay(stdscr, TRUE);
    curs_set(0);
    setup_colors();
}

void show_debug_info(Player_t *player, Vec_t dir)
{
    mvprintw(1, COLS - 20, "Max: %i %i", LINES, COLS);
    mvprintw(2, COLS - 20, "Player.pos: %i %i", player->pos.y, player->pos.x);
    mvprintw(3, COLS - 20, "Player.facing: %i %i", player->facing.y, player->facing.x);
    mvprintw(4, COLS - 20, "Move dir: %i %i", dir.y, dir.x);
}

int main(int argc, char *argv[])
{
    int ch; // For input.
    game_setup();

    // Set up player and the first apple.
    Player_t snake = {
        {5, 10}, // Vec(y,x) position
        {0, -1}, // Vec(y,x) facing direction (looking up by default)
        '#'};    // char to print
    draw_player(&snake);

    Apple_t *apple = new_random_apple();
    draw_apple(apple);

    refresh();

    while (RUN)
    {
        ch = getch();
        clear();
        move_player(&snake, snake.facing);

        Vec_t dir = {0, 0};
        switch (ch)
        {
        case KEY_LEFT:
            mvprintw(5, COLS - 20, "moved left");
            dir.x = -1;
            move_player(&snake, dir);
            break;
        case KEY_RIGHT:
            dir.x = 1;
            move_player(&snake, dir);
            break;
        case KEY_UP:
            dir.y = -1;
            move_player(&snake, dir);
            break;
        case KEY_DOWN:
            dir.y = 1;
            move_player(&snake, dir);
            break;
        case 'q':
            RUN = FALSE;
            break;
        }
        napms(250);

        draw_player(&snake);
        draw_apple(apple);
        show_debug_info(&snake, dir);
        refresh();
    }

    curs_set(1);
    endwin();
    return 0;
}
