

#include <stdio.h>
#include <unistd.h>
#include "include/libgestion-de-fichiers.h"

#define N 9

int GRILLE[N][N];
int MONTRER_PROCESSUS; //bool

int sans_conflit(int ligne, int colonne, int numero);
int resoudre_sudoku(int ligne, int colonne);
void afficher_grille(void);
void afficher_grille2(int soduko[N][N]);







int main(void) {

    // choix de la difficulté
    int difficulte;

    printf("Difficulté ? (1 à 3) (0 pour test)\n");

    do {
        printf(">");
        scanf("%d", &difficulte);
    } while (difficulte < 0 || difficulte > 3);


    // chargement du fichier en fonction de la difficulté
    char *nom_de_fichier = NULL;

    switch (difficulte) {
        case 0:
            nom_de_fichier = "fichiers-de-sauvegardes/test.txt";
            break;
        case 1:
            nom_de_fichier = "fichiers-de-sauvegardes/sudoku_facile.txt";
            break;
        case 2:
            nom_de_fichier = "fichiers-de-sauvegardes/sudoku_moyen.txt";
            break;
        case 3:
            nom_de_fichier = "fichiers-de-sauvegardes/sudoku_difficile.txt";
            break;
        default:
            return 1;
            break;
    }

    // CHARGEMENT DE LA GRILLE

    // ...contenu dans le fichier .txt

    int grille_chargee[N][N];
    FILE *fichier_du_sudoku = fopen(nom_de_fichier, "r");
    lire_grille(fichier_du_sudoku, grille_chargee);
    fclose(fichier_du_sudoku);


    for (int ligne = 0; ligne < N; ligne++) 
        for (int colonne = 0; colonne < N; colonne++) {     
        GRILLE[ligne][colonne] = grille_chargee[ligne][colonne]; // Copie du tableau 2D sudoku facile dans le tableau 2D global
    }


    // // ...donnée ligne par ligne par l'utilisateur

    // printf("Remplissez la grille, ligne par ligne :\n\n");
    // printf("    1 2 3 4 5 6 7 8 9\n");
    // printf("    | | | | | | | | |\n");
    // for (int i = 0; i < N; i++) {
    //     printf("%d - ", i+1);
    //     scanf("%d %d %d %d %d %d %d %d %d", &grid[i][0], &grid[i][1], &grid[i][2], &grid[i][3], &grid[i][4], &grid[i][5], &grid[i][6], &grid[i][7], &grid[i][8]);
    // }


    //montrer le processus ?
    char input;
    printf("Afficher le processus de résolution ? (y/n) (!!! ça peut être tèèès long)\n>");
    scanf("%1s", &input);
    if (input == 'y')
        MONTRER_PROCESSUS = 1;
    else
        MONTRER_PROCESSUS = 0;



    // RÉSOLUTION DU SUDOKU
    if (resoudre_sudoku(0, 0))
        printf("Solution trouvée\n");
    else
        printf("Aucune solution trouvée\n");

    // afficher_grille();
    afficher_grille2(GRILLE);

    return 0;
}


/*
 * This code first reads the Sudoku puzzle from the input and then tries to solve it using the backtracking algorithm.
 * The resoudre_sudoku function is a recursive function that tries to place all numbers from 1 to 9 in each empty cell,
 * and then recursively tries to solve the rest of the puzzle.
 * If it reaches a point where it is not possible to place a number in any cell, it backtracks
 */











// Check if the current position is safe
int sans_conflit(int ligne, int colonne, int numero) {
    // Check if 'numero' is not already placed in current ligne, current column and current 3x3 subgrid
    for (int i = 0; i < N; i++)
        if (GRILLE[ligne][i] == numero || GRILLE[i][colonne] == numero)
            return 0;

    int startRow = ligne - ligne % 3;
    int startCol = colonne - colonne % 3;
    for (int i = startRow; i < startRow + 3; i++)
        for (int j = startCol; j < startCol + 3; j++)
            if (GRILLE[i][j] == numero)
                return 0;

    return 1;
}



// résolution du sudoku en utilisant la méthode de backtracking
// on parcours la grille, case par case, dans le sens de lecture
int resoudre_sudoku(int ligne, int colonne) {
    // si on atteint la dernière ligne, et la dernière colonne (+1), le sudoku est résolu
    if (ligne == N)
        return 1;

    // on pase à la case suivante si la case est pleine
    if (GRILLE[ligne][colonne] != 0) {
        // return resoudre_sudoku(colonne == N - 1 ? ligne + 1 : ligne, (colonne + 1) % N);
        if (colonne == N - 1)
            return resoudre_sudoku(ligne + 1, (colonne + 1) % N);
        else
            return resoudre_sudoku(ligne, (colonne + 1) % N);
    }
    

    if (MONTRER_PROCESSUS) {
        usleep(50 * 1000);
        afficher_grille();
    }

    // on essaye tous les nombres de 1 à 9
    for (int numero = 1; numero <= N; numero++) {
        // on vérifie qu'il n'y a pas de conflit
        if (sans_conflit(ligne, colonne, numero)) {
            GRILLE[ligne][colonne] = numero;

            // on passe à la case suivante
            int resolu = 0;

            if (colonne == N - 1)
                resolu = resoudre_sudoku(ligne + 1, (colonne + 1) % N);
            else
                resolu = resoudre_sudoku(ligne, (colonne + 1) % N);

            if (resolu)
                return 1;



            // if (resoudre_sudoku(colonne == N - 1 ? ligne + 1 : ligne, (colonne + 1) % N))
            //     return 1;



            // on vide la case s'il y'a eu conflit par le suite
            GRILLE[ligne][colonne] = 0;
        }
    }

    return 0;
}




void afficher_grille(void){
    printf("\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) {
            if (GRILLE[i][j] == 0)
                printf("_ ");
            else
                printf("%d ", GRILLE[i][j]);
        }
        printf("\n");
    }
}

void afficher_grille2(int sudoku[N][N]) {
    printf("\n1 2 3     4 5 6     7 8 9\n\n"); // Affichage numéro de colonne
    int k = 1; // Compteur pour le numéro de ligne
    
    for (int i = 0 ; i<N; i++){
        for (int j = 0 ; j < N; j++){
            printf(((j+1)%3) ? "%d " : "%d  |  ", sudoku[i][j]); // Si J+1 / 3 == 0, alors mettre un espace après la valeur sinon, un espace + |
            if (j == 8){ printf("%d", k++);} // Séparation visuelle en 3
            if ((i == 2 || i == 5) && (j == 8)  ){ printf("\n____________________________\n");}
            
        }
        printf("\n");
    }
}

