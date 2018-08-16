CC=gcc
CFLAGS=-I.
DEPS = game.h player.h
OBJ = game.o player.o
LIBS=-l:pdcurses.a

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

curses: game.c game.h player.h player.c
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)