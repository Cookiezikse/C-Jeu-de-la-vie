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
SDL_bool mouse_active = SDL_FALSE;
SDL_bool mouse_hover = SDL_FALSE;
SDL_bool quit = SDL_FALSE;
SDL_Color grid_cell_empty = {0, 0, 0, 255};
// SDL_Color grid_line_color = {44, 44, 44, 255};
SDL_Color grid_cursor_ghost_color = {44, 44, 44, 255};
SDL_Color grid_cell_alive = {255, 255, 255, 255};

void InitSetup() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &screen, &renderer);
    SDL_SetWindowTitle(screen, "Game of Life");
}

int GrilleDebut(int grille[MAX_Y][MAX_X]) {   
    for (int a = 0; a < MAX_Y; a++) {
        for (int b = 0; b < MAX_X; b++) {
            grille[a][b] = 0;
        }
    }
    
    SDL_Rect grid_cursor = {
    .x = MAX_X  * 800 / MAX_X, 
    .y = MAX_Y * 800 / MAX_Y,
    .w = 800 / MAX_X,
    .h = 800 / MAX_Y,
    };
    SDL_Rect grid_cursor_ghost = {grid_cursor.x, grid_cursor.y, 800 / MAX_X, 800 / MAX_Y};
    while (!quit) {
            SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            // Utiliser le clavier pour placer
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_w:
                case SDLK_z:
                case SDLK_UP:
                    grid_cursor_ghost.y -= CELL_H;
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    grid_cursor_ghost.y += CELL_H;
                    break;
                case SDLK_a:
                case SDLK_q:
                case SDLK_LEFT:
                    grid_cursor_ghost.x -= CELL_W;
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    grid_cursor_ghost.x += CELL_W;
                    break;
                case SDLK_e:
                    grid_cursor.x = grid_cursor_ghost.x;
                    grid_cursor.y = grid_cursor_ghost.y;
                    grille[grid_cursor.y / CELL_H][grid_cursor.x / CELL_W] = 1;
                    break;
                case SDLK_ESCAPE:
                    quit = SDL_TRUE;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                grid_cursor.x = (event.motion.x / CELL_H) * CELL_H;
                grid_cursor.y = (event.motion.y / CELL_W) * CELL_W;
                grille[grid_cursor.y / CELL_H][grid_cursor.x / CELL_W] = 1;
                break;
            case SDL_MOUSEMOTION:
                grid_cursor_ghost.x = (event.motion.x / CELL_H) * CELL_H;
                grid_cursor_ghost.y = (event.motion.y / CELL_W) * CELL_W;
                if (!mouse_active)
                    mouse_active = SDL_TRUE;
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_ENTER && !mouse_hover)
                    mouse_hover = SDL_TRUE;
                else if (event.window.event == SDL_WINDOWEVENT_LEAVE && mouse_hover)
                    mouse_hover = SDL_FALSE;
                break;
            case SDL_QUIT:
                quit = SDL_TRUE;
                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, grid_cell_empty.r, grid_cell_empty.g, grid_cell_empty.b, grid_cell_empty.a);
        SDL_RenderClear(renderer);

        if (mouse_active && mouse_hover) {
            SDL_SetRenderDrawColor(renderer, grid_cursor_ghost_color.r, grid_cursor_ghost_color.g, grid_cursor_ghost_color.b, grid_cursor_ghost_color.a);
            SDL_RenderFillRect(renderer, &grid_cursor_ghost);
        }
        // SDL_SetRenderDrawColor(renderer, grid_cell_empty.r, grid_cell_empty.g, grid_cell_empty.b, grid_cell_empty.a);
        // SDL_RenderPresent(renderer);

        // SDL_SetRenderDrawColor(renderer, grid_line_color.r, grid_line_color.g,grid_line_color.b, grid_line_color.a);

        // for (int x = 0; x < 1 + CELL_H * CELL_W;
        //      x += CELL_W) {
        //     SDL_RenderDrawLine(renderer, x, 0, x, HEIGHT);
        // }
        // for (int y = 0; y < 1 + CELL_H * CELL_H;
        //      y += CELL_H) {
        //     SDL_RenderDrawLine(renderer, 0, y, WIDTH, y);
        // }
        
        SDL_SetRenderDrawColor(renderer, grid_cell_alive.r, grid_cell_alive.g, grid_cell_alive.b, grid_cell_alive.a);
        for (int i = 0; i < MAX_X; i++){
            for (int j = 0; j < MAX_Y; j++) {
                if (grille[i][j]  ==  1) {
                grid_cursor.x = j*CELL_H;
                grid_cursor.y = i*CELL_W;
                SDL_RenderFillRect(renderer, &grid_cursor);
                }
            }
        }
        // SDL_RenderFillRect(renderer, &grid_cursor);
        SDL_RenderPresent(renderer);

    }
    return 0;
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
