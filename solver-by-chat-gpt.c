
/*
 * Request :
 * write a sudoku solver by using backtracking algorithm in C
 */


#include <stdio.h>

#include "include/libgestion-de-fichiers.h"

#define N 9

int grid[N][N];

// Check if the current position is safe
int isSafe(int row, int col, int num)
{
    // Check if 'num' is not already placed in current row, current column and current 3x3 subgrid
    for (int i = 0; i < N; i++)
        if (grid[row][i] == num || grid[i][col] == num)
            return 0;

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = startRow; i < startRow + 3; i++)
        for (int j = startCol; j < startCol + 3; j++)
            if (grid[i][j] == num)
                return 0;

    return 1;
}

// Solve the Sudoku puzzle using backtracking
int solveSudoku(int row, int col)
{
    // If all cells are filled, the puzzle is solved
    if (row == N - 1 && col == N)
        return 1;

    // Move to the next cell if the current cell is already filled
    if (grid[row][col] != 0)
        return solveSudoku(col == N - 1 ? row + 1 : row, (col + 1) % N);

    // Try placing all numbers from 1 to 9 in the current cell
    for (int num = 1; num <= N; num++)
    {
        // Check if it is safe to place 'num' in the current cell
        if (isSafe(row, col, num))
        {
            grid[row][col] = num;

            // Solve the rest of the puzzle
            if (solveSudoku(col == N - 1 ? row + 1 : row, (col + 1) % N))
                return 1;

            // Backtrack if the puzzle cannot be solved
            grid[row][col] = 0;
        }
    }

    return 0;
}





int main()
{

    // choix de la difficulté
    int difficulte;

    printf("Difficulté ? (1 à 3)\n");

    do {
        printf(">");
        scanf("%d", &difficulte);
    } while (difficulte < 1 || difficulte > 3);


    // chargement du fichier en fonction de la difficulté
    char *fichier_f = NULL;

    switch (difficulte) {
        case 1:
            fichier_f = "fichiers-de-sauvegardes/sudoku_facile.txt";
            break;
        case 2:
            fichier_f = "fichiers-de-sauvegardes/sudoku_moyen.txt";
            break;
        case 3:
            fichier_f = "fichiers-de-sauvegardes/sudoku_difficile.txt";
            break;
        
        default:
            return 1;
            break;
    }

    // Read the Sudoku puzzle

    //chargement de la grille contenu dans le fichier

    int sudoku_f[N][N] ;
    FILE *fp = fopen(fichier_f, "r");
    lire_grille(fp, sudoku_f);
    fclose(fp);


    for (int k = 0; k < N; k++) 
        for (int l = 0; l < N; l++) {     
        grid[k][l] = sudoku_f[k][l]; // Copie du tableau 2D sudoku facile dans le tableau 2D global
    }


    // User gives each grid's cases

    // //by Valentin
    // printf("Fill the grid, line by line :\n\n");
    // printf("    1 2 3 4 5 6 7 8 9\n");
    // printf("    | | | | | | | | |\n");
    // for (int i = 0; i < N; i++) {
    //     printf("%d - ", i+1);
    //     scanf("%d %d %d %d %d %d %d %d %d", &grid[i][0], &grid[i][1], &grid[i][2], &grid[i][3], &grid[i][4], &grid[i][5], &grid[i][6], &grid[i][7], &grid[i][8]);
    // }

    // //by Chat GPT
    // for (int i = 0; i < N; i++)
    //     for (int j = 0; j < N; j++)
    //         scanf("%d", &grid[i][j]);

    // Solve the puzzle
    if (solveSudoku(0, 0))
    {
        // Print the solution
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                printf("%d ", grid[i][j]);
            printf("\n");
        }
    }
    else
    {
        printf("No solution exists\n");
        // Print the grid
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 0)
                    printf("_ ");
                else
                    printf("%d ", grid[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}


/*
 * This code first reads the Sudoku puzzle from the input and then tries to solve it using the backtracking algorithm.
 * The solveSudoku function is a recursive function that tries to place all numbers from 1 to 9 in each empty cell,
 * and then recursively tries to solve the rest of the puzzle.
 * If it reaches a point where it is not possible to place a number in any cell, it backtracks
 */


