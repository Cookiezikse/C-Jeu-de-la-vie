all:
	gcc -I src/include -L src/lib -o Projet Projet.c -lmingw32 -lSDL2main -lSDL2