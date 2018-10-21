all: ocr

loadfile.o: loadfile.c loadfile.h
	gcc -o loadfile.o -c loadfile.c sdl2-config --libs -ISDL/SDL2.h -Wall -Wextra -std=c99

grey.o: grey.c grey.h loadfile.h
	gcc -o grey.o -c grey.c sdl2-config --libs -ISDL/SDL2.h -Wall -Wextra -std=c99

Cutimage.o: Cutimage.c Cutimage.h grey.h loadfile.h
	gcc -o Cutimage.o -c Cutimage.c sdl2-config --libs -ISDL/SDL2.h -Wall -Wextra -std=c99

Cutletter.o: Cutletter.c Cutletter.h Cutimage.h grey.h loadfile.h
	gcc -o Cutletter.o -c Cutletter.c sdl2-config --libs -ISDL/SDL2.h -Wall -Wextra -std=c99

main.o: main.c loadfile.h grey.h cutimage.h
	gcc -o main.o -c main.c sdl2-config --libs -ISDL/SDL2.h -Wall -Wextra -std=c99

ocr: blocs.o Cutimage.o Cutletter.o grey.o lines.o loadfile.o main.o pixel.o surf.o
	gcc -o ocr *.o sdl2-config --libs -ISDL/SDL2.h -Wall -Wextra -std=c99

clean:
	rm -rf *.o
