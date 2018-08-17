#include "game.h"
#include "player.h"
#include "apple.h"

const short GREEN = 1;
const short RED = 2;

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

// void show_debug_info(Player_t *player, Vec_t dir)
void show_debug_info(Snake_t *player)
{
    int n = snake_len(player);
    int i = 2;
    mvprintw(1, COLS - 20, "Snake len: %i", n);
    SnakePart_t *cur = player->parts;
    if (cur->next != NULL)
    {
        while (cur->next != NULL)
        {
            mvprintw(i, COLS - 20, "%i %i", cur->pos.y, cur->pos.x);
            cur = cur->next;
            i++;
        }
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

    Snake_t *player = new_snake();
    Vec_t pos = {2, 0};
    append_part(player, pos);

    // Apple_t *apple = new_random_apple();
    // draw_apple(apple);

    refresh();

    while (RUN)
    {
        ch = getch();
        clear();

        // Vec_t dir = {0, 0};
        Vec_t pos = {0, 0};
        switch (ch)
        {
        // case KEY_LEFT:
        //     break;
        // case KEY_RIGHT:
        //     break;
        // case KEY_UP:
        //     break;
        // case KEY_DOWN:
        //     break;
        case 'a':
            pos.y = 1;
            append_part(player, pos);
            break;
        case 'p':
            pos.x = 1;
            push_part(player, pos);
            break;
        case 'q':
            RUN = FALSE;
            break;
        }

        // draw_apple(apple);

        show_debug_info(player);

        refresh();
        napms(50);
    }

    curs_set(1);
    endwin();
    return 0;
}
