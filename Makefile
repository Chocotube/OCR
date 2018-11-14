CC=gcc
CFLAGS=`sdl2-config --libs` -ISDL/SDL2.h -Wall -Wextra -std=c99
EXEC=ocr

all: $(EXEC)

ocr: 
	$(CC) -o $@ $^ $(CFLAGS)

color.o: color.c color.h surface.h
	$(CC) -o $@ -c $< $(CFLAGS)

cut.o: cut.c cut.h surface.h
	$(CC) -o $@ -c $< $(CFLAGS)

surface.o: surface.c surface.h
	$(CC) -o $@ -c $< $(CFLAGS)

neuralNet.o : neuraNet.c neuralNet.h
	$(CC) -o $@ -c $< $(CFLAGS)

main.o: main.c surface.h color.h surface.h neuralNet.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
