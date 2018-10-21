 all: ocr

loadfile.o: loadfile.c loadfile.h
	gcc -o loadfile.o -c loadfile.c sdl2-config --libs -ISDL/SDL2.h -Wall -Wextra -std=c99

grey.o: grey.c grey.h loadfile.o
	gcc -o grey.o loadfile.o -c grey.c sdl2-config --libs -ISDL/SDL2.h -Wall -Wextra -std=c99

Cutimage.o: Cutimage.c Cutimage.h grey.o loadfile.o
	gcc -o Cutimage.o grey.o loadfile.o -c Cutimage.c sdl2-config --libs -ISDL/SDL2.h -Wall -Wextra -std=c99

Cutletter.o: Cutletter.c Cutletter.h Cutimage.o grey.o loadfile.o
	gcc -o Cutletter.o Cutimage.o grey.o loadfile.o -c Cutletter.c sdl2-config --libs -ISDL/SDL2.h -Wall -Wextra -std=c99

main.o: main.c loadfile.o grey.o cutimage.o
	gcc -o main.o loadfile.o grey.o cutimage.o -c main.c sdl2-config --libs -ISDL/SDL2.h -Wall -Wextra -std=c99

ocr: blocs.o cutimage.o cutletter.o grey.o lines.o loadfile.o main.o pixel.o surf.o
	gcc -o ocr *.o sdl2-config --libs -ISDL/SDL2.h -Wall -Wextra -std=c99

clean:
	rm -rf *.o