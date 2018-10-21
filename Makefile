all: ocr

loadfile.o: loadfile.c loadfile.h
	gcc -o loadfile.o -c loadfile.c `sdl2-config --libs` -ISDL/SDL2.h -Wall -Wextra -std=c99

grey.o: grey.c grey.h loadfile.h
	gcc -o grey.o -c grey.c `sdl2-config --libs` -ISDL/SDL2.h -Wall -Wextra -std=c99

Cutimage.o: Cutimage.c Cutimage.h grey.h loadfile.h
	gcc -o Cutimage.o -c Cutimage.c `sdl2-config --libs` -ISDL/SDL2.h -Wall -Wextra -std=c99

CutLetter.o: CutLetter.c CutLetter.h Cutimage.h grey.h loadfile.h
	gcc -o CutLetter.o -c CutLetter.c `sdl2-config --libs` -ISDL/SDL2.h -Wall -Wextra -std=c99

main.o: main.c loadfile.h grey.h Cutimage.h NeuralNet.h
	gcc -o main.o -c main.c `sdl2-config --libs` -ISDL/SDL2.h -Wall -Wextra -std=c99

ocr: blocs.o Cutimage.o CutLetter.o grey.o lines.o loadfile.o main.o pixel.o surf.o
	gcc -o ocr *.o `sdl2-config --libs` -ISDL/SDL2.h -Wall -Wextra -std=c99
	
NeuralNet.o : NeuraNet.c NeuralNet.h
	gcc -o NeuralNet.o -c NeuralNet.c `sdl2-config --libs` -ISDL/SDL2.h -Wall -Wextra -std=c99


clean:
	rm -rf *.o
