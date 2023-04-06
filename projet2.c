#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

// Define constants for grid size
#define MAX_Y 100
#define MAX_X 100

// Global variables
const int WIDTH = 800;
const int HEIGHT = 800;
const int CELL_W = 800 / MAX_X;
const int CELL_H = 800 / MAX_Y;

// Function prototypes
void InitSetup();
int GrilleDebut(int grille[MAX_Y][MAX_X]);
void AfficherGrille(int grille[MAX_Y][MAX_X]);
void Count(int grille[MAX_Y][MAX_X]);
int Mort(int grille[MAX_Y][MAX_X]);

// SDL variables
SDL_Window* screen = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event event;

void InitSetup() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &screen, &renderer);
    SDL_SetWindowTitle(screen, "Game of Life");
}

int GrilleDebut(int grille[MAX_Y][MAX_X]) {
    int rep11 = 0;
    int rep22 = 0;
    int cases = 0;    
    int ok = 0;
    for (int a = 0; a < MAX_Y; a++) {
        for (int b = 0; b < MAX_X; b++) {
            grille[a][b] = 0;
        }
    }
    while (ok == 0) {
        printf("Combien voulez vous mettre de cases ? : ");
        scanf("%d", &cases);
        fflush(stdin);
        // Loop through each cell and prompt user for which ones should be alive
        for (int e = 0; e < cases; e++) {
            printf("\n  Choissisez une case en Y (%d a %d): ", 1, MAX_Y);
            scanf("%d", &rep11);
            printf("  Choissisez une case en X (%d a %d): ", 1, MAX_X);
            scanf("%d", &rep22);
            // Set the specified cell to be alive
            grille[rep11 - 1][rep22 - 1] = 1;
        }
        ok++;
    }
    return 0;
}

void AfficherGrille(int grille[MAX_Y][MAX_X]) {
    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {
            printf("%d ", grille[i][j]);
        }
        printf("\n");
    }
}

void Count(int grille[MAX_Y][MAX_X]) {
    int temp[MAX_Y][MAX_X] = { 0 };
    for (int l = 0; l < MAX_Y; l++) {
        for (int m = 0; m < MAX_X; m++) {
            int count1 = 0;
            int count2 = 0;

            if (grille[l][m] == 1) {
                if (grille[l + 1][m - 1] == 1) {
                    count1++;
                }
                if (grille[l + 1][m] == 1) {
                    count1++;
                }
                if (grille[l + 1][m + 1] == 1) {
                    count1++;
                }
                if (grille[l][m - 1] == 1) {
                    count1++;
                }
                if (grille[l][m + 1] == 1) {
                    count1++;
                }
                if (grille[l - 1][m + 1] == 1) {
                    count1++;
                }
                if (grille[l - 1][m - 1] == 1) {
                    count1++;
                }
                if (grille[l - 1][m] == 1) {
                    count1++;
                }
                // Update value of cell based on its surroundings
                if (count1 > 1 && count1 < 4) {
                    temp[l][m] = 1;
                }
                if (count1 < 2 || count1 > 3) {
                    temp[l][m] = 0;
                }
            }

            // Count number of alive cells around the current dead cell and update it accordingly
            if (grille[l][m] == 0) {
                if (grille[l + 1][m - 1] == 1) {
                    count2++;
                }
                if (grille[l + 1][m] == 1) {
                    count2++;
                }
                if (grille[l + 1][m + 1] == 1) {
                    count2++;
                }
                if (grille[l][m - 1] == 1) {
                    count2++;
                }
                if (grille[l][m + 1] == 1) {
                    count2++;
                }
                if (grille[l - 1][m + 1] == 1) {
                    count2++;
                }
                if (grille[l - 1][m - 1] == 1) {
                    count2++;
                }
                if (grille[l - 1][m] == 1) {
                    count2++;
                }
                if (count2 > 2 && count2 < 4) {
                    temp[l][m] = 1;
                }
            }
        }
    }
    for (int n = 0; n < MAX_Y; n++) {
        for (int o = 0; o < MAX_X; o++) {
            grille[n][o] = temp[n][o];
        }
    }
}

int Mort(int grille[][MAX_X]) {
    int count_die = 0;
    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {
            if (grille[i][j] == 0) {
                count_die++;
            }
        }
    }
    if (count_die == MAX_X * MAX_Y) {
        printf("C'est finit !");
        return 1;    }
    return 0;
}

int main(int argc, char *argv[]) {
    // Initialize SDL
    InitSetup();
    SDL_Event windowEvent;

    // Create a 2D array to hold the grid
    int grille[MAX_Y][MAX_X] = { 0 };

    // Prompt user to input cell positions
    printf("Choose the initial positions of the cells\n");
    GrilleDebut(grille);

    int mort = 0;
    while (mort == 0) {
        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
        SDL_RenderClear(renderer);

        // Draw the cells
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
        for (int i = 0; i < MAX_Y; i++) {
            for (int j = 0; j < MAX_X; j++) {
                if (grille[i][j] == 1) {
                    SDL_Rect destination = { j * CELL_W, i * CELL_H, CELL_W, CELL_H };
                    SDL_RenderFillRect(renderer, &destination);
                }
            }
        }

        // Update the screen
        SDL_RenderPresent(renderer);

        // Calculate the next generation of cells
        Count(grille);

        // Pause for one second between each generation
        SDL_Delay(100);

        // Check for quit event
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                mort = 1;
            }
        }
    }

    // Quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    SDL_Quit();

    return 0;
}
