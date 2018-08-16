CC=gcc
CFLAGS=-I.
LIBS=-l:pdcurses.a

curses: game.c game.h player.h player.c
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)