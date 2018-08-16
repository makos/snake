#include "game.h"
#include "player.h"

int main(int argc, char *argv[])
{
    int ch;
    bool run = TRUE;

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    Player snake;
    snake.x = 5;
    snake.y = 10;
    snake.ch = '#';
    mvprintw(snake.y, snake.x, &snake.ch);
    mvprintw(1, COLS - 5, "%d %d", snake.y, snake.x);
    refresh();
    nodelay(stdscr, TRUE);

    while (run)
    {
        ch = getch();
        move_player(&snake, snake.y, snake.x + 1);
        clear();
        switch (ch)
        {
        case KEY_LEFT:
            move_player(&snake, snake.y, snake.x - 1);
            break;
        case KEY_RIGHT:
            move_player(&snake, snake.y, snake.x + 1);
            break;
        case KEY_UP:
            move_player(&snake, snake.y - 1, snake.x);
            break;
        case KEY_DOWN:
            move_player(&snake, snake.y + 1, snake.x);
            break;
        case 'q':
            run = FALSE;
            break;
        }
        mvprintw(snake.y, snake.x, &snake.ch);
        mvprintw(1, COLS - 5, "%d %d", snake.y, snake.x);
        refresh();
        napms(50);
    }

    curs_set(1);
    endwin();
    return 0;
}
