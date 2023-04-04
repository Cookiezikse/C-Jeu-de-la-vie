// Include necessary libraries
#include <stdio.h>
#include <Windows.h>
#include <SLD2/SDL.h>


// Define constants for grid size
#define max_y 10
#define max_x 100

int main() {
    // Declare necessary variables and arrays
    int cases, rep11, rep22;
    int zero = 0;
    int ok = 0;
    char cellule_vivante = '0';
    char cellule_mort = '.';

    // Create a 2D array to hold the grid
    char grille[50][100] = {0};

    // Populate the grid with dead cells (represented by ".")
    for (int a = 0; a < max_y; a++) {
        for (int b = 0; b < max_x; b++) {
            grille[a] [b] = cellule_mort;
        }
    }

    // Display the initial grid
    printf("\n");
    for (int c = 0; c < max_y; c++) {
        for (int d = 0; d < max_x; d++) {
            printf("%c",grille[c][d]);
        }
        printf("\n");
    }

    // Prompt user for number of cells to simulate
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

            // Break out of loop if user inputs 1505 for either coordinate
            if (rep11 == 1505 || rep22 == 1505) {
                ok = 1;
                break;
            }

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

    // Loop through each generation and simulate the game of life
    int mort = 0;
    int fige = 0;
    while (mort == 0) {
        // Display the current grid
        for (int h = 0; h < max_y; h++) {
            for (int i = 0; i <max_x; i++) {
                printf("%c",grille[h][i]);
            }
            printf("\n");
        }
        printf("\n");

        // Create a temporary grid to hold updated cell values
        char temp[100][100] = {'.'};

        // Copy over all existing cell values to temporary grid
        for (int j = 0; j < max_y; j++) {
            for (int k = 0; k < max_x; k++) {
                temp[j][k] = grille[j][k];
            }
        }

        // Loop through each cell and update its value based on surrounding cells
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

                    // Update value of cell based on its surroundings
                    if (count2 > 2 && count2 < 4) {
                        temp[l][m] = cellule_vivante;
                    }
                }
            }
        }

        // Copy updated cell values from temporary grid back into main grid
        for (int n = 0; n < max_y; n++) {
            for (int o = 0; o < max_x; o++) {
                grille[n][o] = temp[n][o];
            }
        }

        // Check if all cells are dead and end simulation if they are
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
            break;
        } 
        
        // Pause for one second between each generation
        Sleep(500);
        zero++;
    }
    return 0;
} 