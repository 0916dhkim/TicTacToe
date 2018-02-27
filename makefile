CC=gcc
CFLAGS=-I. -Wall -Werror
DEP=misc.h state.h tournament.h minmax.h
OBJ=misc.o state.o tournament.o minmax.o

tictactoe: tictactoe.c $(OBJ)
	$(CC) $(CFLAGS) tictactoe.c $(OBJ) -o tictactoe

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(OBJ) tictactoe
