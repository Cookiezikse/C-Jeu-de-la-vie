// Include necessary libraries
#include <stdio.h>
#include <Windows.h>
// #include <SDL2/SDL.h>

// Define constants for grid size
#define max_y 10
#define max_x 50
#define true 1
const int WIDTH = 800, HEIGHT = 600;

// int main(int argc, char *argv[]) {
//     // Initialize SDL
//     SDL_Init( SDL_INIT_EVERYTHING);
//     SDL_Window *window = SDL_CreateWindow( "Jeu de la vie", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI); 
//     if (window == NULL) {
//         // std::cout << "Window could not be created! SDL Error: " << SDL_GetError();
//         return 1;
//     }
//     SDL_Event windowEvent;

//     while (true) {
//         if (SDL_PollEvent(&windowEvent)) {
//             if (windowEvent.type == SDL_QUIT)
//             {break;}
//         }
//     }

//     SDL_DestroyWindow(window);
//     SDL_Quit();

//     return EXIT_SUCCESS;
// }

int GrilleDebut(int grille[100][100],int cellule_vivante,int cellule_mort) {
    int rep11 = 0;
    int rep22 = 0;
    int cases = 0;
    int ok = 0;
    for (int a = 0; a < max_y; a++) {
        for (int b = 0; b < max_x; b++) {
            grille[a] [b] = cellule_mort;
        }
    }
    while (ok == 0) {
    printf("Combien voulez vous mettre de cases ? : ");
    scanf("%d", &cases);
    // Loop through each cell and prompt user for which ones should be alive
    for (int e = 0; e < cases; e++) {
        fflush(stdin);
        printf("\n  Choissisez une case en Y (%d a %d): ",1,max_y);
        scanf("%d",&rep11);
        printf("  Choissisez une case en X (%d a %d): ",1,max_x);
        scanf("%d",&rep22);
        // Set the specified cell to be alive
        for (int f = 0; f < max_y; f++) {
            for (int g = 0; g < max_x; g++) {
                if (f == rep11-1 && g == rep22-1) {
                    grille[f][g] = cellule_vivante;
                }
            }
        }
    }
    ok++;
    }
    return grille;
}

int AfficherGrille (int x[100][100]) {
    int i, j;
    for (i = 0; i < max_y; i++) {
        for (j = 0; j < max_x; j++) {
            printf("%d ", x[i][j]);
        }
        printf("\n");
    }
    return 0;
}
int Count(int grille[100][100],int cellule_vivante,int cellule_mort) {
    int temp[100][100] = {0};
    for (int j = 0; j < max_y; j++) {
        for (int k = 0; k < max_x; k++) {
            temp[j][k] = grille[j][k];
        }
    }
    for (int l = 0; l < max_y; l++) {
        for (int m = 0; m < max_x; m++) {
            int count1 = 0;
            int count2 = 0;
            // Count number of alive cells around the current cell
            if (grille[l][m] == cellule_vivante) {
                if (grille[l+1][m-1] == cellule_vivante) {
                    count1++;    
                }
                if (grille[l+1][m] == cellule_vivante) {
                    count1++;
                }
                if (grille[l+1][m+1] == cellule_vivante) {
                    count1++;
                }
                if (grille[l][m-1] == cellule_vivante) {
                    count1++;
                }
                if (grille[l][m+1] == cellule_vivante) {
                    count1++;
                }
                if (grille[l-1][m+1] == cellule_vivante) {
                    count1++;
                }
                if (grille[l-1][m-1] == cellule_vivante) {
                    count1++;
                }
                if (grille[l-1][m] == cellule_vivante) {
                    count1++;
                }
                // Update value of cell based on its surroundings
                if (count1 > 1 && count1 < 4 ) {
                    temp[l][m] = cellule_vivante;
                }
                if (count1 < 2 || count1 > 3) {
                    temp[l][m] = cellule_mort;
                }
            }

            // Count number of alive cells around the current dead cell and update it accordingly
            if (grille[l][m] == cellule_mort) {
                if (grille[l+1][m-1] == cellule_vivante) {
                    count2++;    
                }
                if (grille[l+1][m] == cellule_vivante) {
                    count2++;
                }
                if (grille[l+1][m+1] == cellule_vivante) {
                    count2++;
                }
                if (grille[l][m-1] == cellule_vivante) {
                    count2++;
                }
                if (grille[l][m+1] == cellule_vivante) {
                    count2++;
                }
                if (grille[l-1][m+1] == cellule_vivante) {
                    count2++;
                }
                if (grille[l-1][m-1] == cellule_vivante) {
                    count2++;
                }
                if (grille[l-1][m] == cellule_vivante) {
                    count2++;
                }
                if (count2 > 2 && count2 < 4) {
                    temp[l][m] = cellule_vivante;
                }
            }
        }
    }
    for (int n = 0; n < max_y; n++) {
        for (int o = 0; o < max_x; o++) {
            grille[n][o] = temp[n][o];
        }
    }
    return grille;
}

int Mort(int grille[100][100],int cellule_mort,int mort) {
    int count_die=0;
    for (int i = 0; i < max_y; i++) {
        for (int j = 0; j < max_x; j++) {
            if (grille [i][j] == cellule_mort) {
                count_die++;
            }
        }
    }
    if (count_die == max_x*max_y) {
        printf("C'est finit !");
        mort = 1;
    } 
    return mort;
}

int main() {

    int cellule_vivante = 1;
    int cellule_mort = 0;

    // Create a 2D array to hold the grid
    int grille[100][100] = {0};

    printf("\n");
    AfficherGrille(grille);
    GrilleDebut(grille, cellule_vivante, cellule_mort);

    int mort = 0;
    while (mort == 0) {
        AfficherGrille(grille);
        printf("\n");
        Count(grille,cellule_vivante,cellule_mort);
        mort = Mort(grille,cellule_mort,mort);
        
        // Pause for one second between each generation
        Sleep(500);
    }
    return 0;
} 