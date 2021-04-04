CC=cc
CFLAGS=-std=c99 -pedantic -Wall -Os
LDLIBS=-lm

SRC=maaya.c calc.c
OBJ=$(SRC:.c=.o)
OUT=maaya

all: maaya

.c.o:
	$(CC) -c $(CFLAGS) $<

$(OBJ): config.h calc.h

maaya: maaya.o calc.o

clean:
	rm -f $(OBJ) $(OUT)

install: all
	cp -f maaya /usr/bin

uninstall:
	rm -f /bin/usr/maaya

.PHONY: all clean
