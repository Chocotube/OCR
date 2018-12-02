CC=gcc
CFLAGS=`sdl2-config --libs` -ISDL/SDL2.h -Wall -Wextra -std=c99
EXEC=main

all: $(EXEC)

main: main.c surface.o color.o cut.o text.o
	$(CC) -o $@ $^ $(CFLAGS)

color.o: color.c color.h surface.h
	$(CC) -o $@ -c $< $(CFLAGS)

cut.o: cut.c cut.h surface.h
	$(CC) -o $@ -c $< $(CFLAGS)

surface.o: surface.c surface.h
	$(CC) -o $@ -c $< $(CFLAGS)

neuralNet.o: neuraNet.c neuralNet.h
	$(CC) -o $@ -c $< $(CFLAGS)

text.o: text.c text.h surface.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o main ./Letters/*.bmp
