# Makefile for lab10

fractals: fractals1.c
	gcc fractals1.c gfx.o -lX11 -lm -o fractals

clean:
	rm fractals 

