CC=gcc

SRCDIR=./src
OUTDIRDBG=./target/debug
OUTDIRREL=./target/release

IDIR=./include
ODIR=./src/obj

CFLAGS=-I$(IDIR) -std=c11 -Wall

_DEPS = game.h player.h apple.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = game.o player.o apple.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

LIBS=-l:pdcurses.a

# Binary name
BIN=snake

# Default (debug, non-optimized) build
snake: $(OBJ)
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
	rm -rf $(OUTDIRDBG)/*.exe $(OUTDIRREL)/*.exe $(ODIR)/*.o

run:
	$(OUTDIRDBG)/$(BIN).exe

run_release:
	$(OUTDIRREL)/$(BIN).exe