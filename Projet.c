#include <stdio.h>
#include <Windows.h>

int main() {
    int cases,rep11,rep22;
    int zero = 0;
    int ok = 0;
    char cellule_vivante = '0';
    char cellule_mort = '.';
    int max_x = 60;
    int max_y = 20;
    char grille[50][100]= {0};
    for (int a = 0; a < max_y; a++) {
        for (int b = 0; b < max_x; b++) {
            grille[a] [b] = cellule_mort;
        }
    }
    // printf("Entrez le nombre de round à faire : ");
    // scanf("%d", &round);
    printf("\n");
    // printf("Entrez le nombre de cases : ");
    // scanf("%d", &cases);
    for (int c = 0; c < max_y; c++) {
        for (int d = 0; d <max_x; d++) {
            printf("%c",grille[c][d]);
        }
        printf("\n");
    }
    while (ok == 0) {
    printf("Combien voulez vous mettre de cases ? : ");
    scanf("%d", &cases);
    for (int e = 0; e < cases; e++) {
        fflush(stdin);
        printf("\n  Choissisez une case en Y (%d a %d): ",1,max_y);
       scanf("%d",&rep11);
        printf("  Choissisez une case en X (%d a %d): ",1,max_x);
        scanf("%d",&rep22);
        if (rep11 == 1505 || rep22 == 1505) {
            ok = 1;
            break;
        }
        for (int f = 0; f < max_y; f++) {
            for (int g = 0; g <max_x; g++) {
                if (f == rep11-1 && g == rep22-1) {
                    grille[f][g] = cellule_vivante;
            }
        }
        }
    }
    ok++;
    }
    int mort = 0;
    int fige = 0;
    while (mort == 0) {

        for (int h = 0; h < max_y; h++) {
            for (int i = 0; i <max_x; i++) {
                printf("%c",grille[h][i]);
            }
            printf("\n");
        }
        printf("\n");
        char temp[100][100] = {'.'};
        for (int j = 0; j < max_y; j++) {
            for (int k = 0; k <max_x; k++) {
                temp[j][k] = grille[j][k];
            }
        }
        for (int l = 0; l < max_y; l++) {
            for (int m = 0; m <max_x; m++) {
                int count1 = 0;
                int count2 = 0;
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
                    if (count1 > 1 && count1 < 4 ) {
                        temp[l][m] = cellule_vivante;
                    }
                    if (count1 < 2 || count1 > 3) {
                        temp[l][m] = cellule_mort;
                    }
                }
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
                    // TESTER PARCE QUE CA MARCHAIT PAS
                    // if (count2 > 1 && count2 < 4 ) {
                    //     printf("\nCount2 : %d",count2);
                    //     temp[l][m] = cellule_vivante;    
                    // }
                    if (count2 > 2 && count2 < 4) {
                        temp[l][m] = cellule_vivante;
                        // printf("\n COUNT2 MARCHE");
                    }
                }
                // TESTER POUR VOIR LES VALEURS
                // if (count1 != 0 || count2 != 0) {
                //     printf("count 1 : %d ||| count2 : %d le l : %d le m : %d\n",count1,count2,l,m);
                // }
            }
        }
        for (int n = 0; n < max_y; n++) {
            for (int o = 0; o <max_x; o++) {
                grille[n][o] = temp[n][o];
            }
        }
        int count_die=0;
        for (int i = 0; i < max_y; i++) {
            for (int j = 0; j < max_x; j++) {
                if (grille [i][j] == cellule_mort) {
                    count_die++;
                }
            }
        }
        // printf("count_die : %d\n",count_die);
        if (count_die == max_x*max_y) {
            printf("C'est finit !");
            mort = 1;
            break;
        } 
        printf("\n");
        // int pk;
        // printf("Entrez quelque chose pour continuer : ");
        // scanf("%d", &pk);
        Sleep(1000);
        zero++;

    }
    return 0;
} 