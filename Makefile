CC = gcc
CFLAGS = -I/opt/X11/include
LDFLAGS = -L/opt/X11/lib -lX11 -lm

OBJ = gfx3.o

all: fractals

gfx3.o: gfx3.c
	$(CC) $(CFLAGS) -c gfx3.c -o gfx3.o

fractals: fractals.c $(OBJ)
	$(CC) $(CFLAGS) fractals.c $(OBJ) $(LDFLAGS) -o fractals

clean:
	rm -f fractals gfx3.o