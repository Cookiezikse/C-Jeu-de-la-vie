all:
	gcc -I src/include -L src/lib -o JeuDeLaVie GameOfLife.c -lmingw32 -lSDL2main -lSDL2