
PKGS=gtk+-3.0 glib-2.0 gmodule-2.0
CC=gcc
CFLAGS= `pkg-config --libs gtk+-3.0` `pkg-config --cflags gtk+-3.0` `sdl2-config --libs` -rdynamic -ISDL/SDL2.h -Wall -Wextra -std=c99
EXEC=main

all: $(EXEC)

main: main.c surface.o color.o cut.o app.o
	$(CC) -o $@ $^ $(CFLAGS)

color.o: color.c color.h surface.h
	$(CC) -o $@ -c $< $(CFLAGS)

cut.o: cut.c cut.h surface.h
	$(CC) -o $@ -c $< $(CFLAGS)

surface.o: surface.c surface.h
	$(CC) -o $@ -c $< $(CFLAGS)

neuralNet.o: neuraNet.c neuralNet.h
	$(CC) -o $@ -c $< $(CFLAGS)

app.o: app.c app.h
	$(CC) -o $@ -c $< $(CFLAGS)


clean:
	rm -rf *.o
