CC=cc
CFLAGS=-pedantic -Wall -I/usr/include/ImageMagick-7 -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16
LDLIBS=-lMagickWand-7.Q16HDRI -lMagickCore-7.Q16HDRI

SRC=drw.c maaya.c
OBJ=$(SRC:.c=.o)
OUT=maaya

all: maaya

.c.o:
	$(CC) -c $(CFLAGS) $<

$(OBJ): config.h drw.h

maaya: maaya.o drw.o

clean:
	rm -f $(OBJ) $(OUT)

.PHONY: all clean
