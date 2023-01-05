

#include <stdio.h>
#include "include/libgestion-de-fichiers.h"

#define N 9

int GRILLE[N][N];

int sans_conflit(int ligne, int colonne, int numero);
int resoudre_sudoku(int ligne, int colonne);







int main(void) {

    // choix de la difficulté
    int difficulte;

    printf("Difficulté ? (1 à 3)\n");

    do {
        printf(">");
        scanf("%d", &difficulte);
    } while (difficulte < 1 || difficulte > 3);


    // chargement du fichier en fonction de la difficulté
    char *nom_de_fichier = NULL;

    switch (difficulte) {
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



    // RÉSOLUTION DU SUDOKU
    if (resoudre_sudoku(0, 0))
    {
        // Print the solution
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                printf("%d ", GRILLE[i][j]);
            printf("\n");
        }
    }
    else
    {
        printf("Aucune solution trouvée\n");
        // Print the grid
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

    return 0;
}


/*
 * This code first reads the Sudoku puzzle from the input and then tries to solve it using the backtracking algorithm.
 * The resoudre_sudoku function is a recursive function that tries to place all numbers from 1 to 9 in each empty cell,
 * and then recursively tries to solve the rest of the puzzle.
 * If it reaches a point where it is not possible to place a number in any cell, it backtracks
 */











// Check if the current position is safe
int sans_conflit(int ligne, int colonne, int numero)
{
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

// Solve the Sudoku puzzle using backtracking
int resoudre_sudoku(int ligne, int colonne)
{
    // If all cells are filled, the puzzle is solved
    if (ligne == N - 1 && colonne == N)
        return 1;

    // Move to the next cell if the current cell is already filled
    if (GRILLE[ligne][colonne] != 0)
        return resoudre_sudoku(colonne == N - 1 ? ligne + 1 : ligne, (colonne + 1) % N);

    // Try placing all numbers from 1 to 9 in the current cell
    for (int numero = 1; numero <= N; numero++)
    {
        // Check if it is safe to place 'numero' in the current cell
        if (sans_conflit(ligne, colonne, numero))
        {
            GRILLE[ligne][colonne] = numero;

            // Solve the rest of the puzzle
            if (resoudre_sudoku(colonne == N - 1 ? ligne + 1 : ligne, (colonne + 1) % N))
                return 1;

            // Backtrack if the puzzle cannot be solved
            GRILLE[ligne][colonne] = 0;
        }
    }

    return 0;
}






