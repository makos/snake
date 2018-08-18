CC=gcc

SRCDIR=./src
OUTDIRDBG=./target/debug
OUTDIRREL=./target/release

IDIR=./include
ODIR=./src/obj

CFLAGS=-I$(IDIR) -std=c11 -Wall

_DEPS = game.h player.h apple.h utils.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = game.o player.o apple.o utils.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

ifeq ($(OS),Windows_NT)
	LIBS=-l:pdcurses.a
else
	LIBS=-lncurses
endif
# Binary name
BIN=snake
ifeq ($(OS),Windows_NT)
	EXT=.exe
else
	EXT=
endif
# Default (debug, non-optimized) build
all: $(OBJ)
	mkdir -p $(OUTDIRDBG)
	$(CC) -o $(OUTDIRDBG)/$(BIN) $^ $(CFLAGS) $(LIBS)

$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

# Optimized build
release: $(OBJ)
	mkdir -p $(OUTDIRREL)
	$(CC) -o $(OUTDIRREL)/$(BIN) $^ $(CFLAGS) -O2 $(LIBS)

.PHONY: clean run run_release
clean: 
	rm -rf $(OUTDIRDBG)/* $(OUTDIRREL)/* $(ODIR)/*.o

run:
	$(OUTDIRDBG)/$(BIN)$(EXT)

run_release:
	$(OUTDIRREL)/$(BIN)$(EXT)