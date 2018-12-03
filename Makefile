
PKGS=gtk+-3.0 glib-2.0 gmodule-2.0
CC=gcc
CFLAGS= `pkg-config --libs gtk+-3.0` `pkg-config --cflags gtk+-3.0` `sdl2-config --libs` -lm -rdynamic -ISDL/SDL2.h -Wall -Wextra -std=c99
EXEC=main

all: $(EXEC)

main: main.c surface.o test.o color.o NeuralNet.o cut.o text.o app.o resize.o Training.o Save.o
	$(CC) -o $@ $^ $(CFLAGS)

color.o: color.c color.h surface.h
	$(CC) -o $@ -c $< $(CFLAGS)

cut.o: cut.c cut.h surface.h
	$(CC) -o $@ -c $< $(CFLAGS)

surface.o: surface.c surface.h
	$(CC) -o $@ -c $< $(CFLAGS)

text.o: text.c text.h surface.h
	$(CC) -o $@ -c $< $(CFLAGS)

app.o: app.c app.h
	$(CC) -o $@ -c $< $(CFLAGS)

resize.o: resize.c resize.h
	$(CC) -o $@ -c $< $(CFLAGS)

test.o: test.c test.h
	$(CC) -o $@ -c $< $(CFLAGS)

NeuralNet.o: NeuralNet.c NeuralNet.h
	$(CC) -o $@ -c $< $(CFLAGS)

Training.o: Training.c Training.h
	$(CC) -o $@ -c $< $(CFLAGS)

Save.o: Save.c Save.h
	$(CC) -o $@ -c $< $(CFLAGS)
clean:
	rm -rf *.o main ./Letters/*.bmp
