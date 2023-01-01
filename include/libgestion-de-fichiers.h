#include <stdio.h>
#define N 9


void ecrire_grille(int sudoku[N][N], FILE *fp);

int lire_grille(FILE *fp, int sudoku[N][N]);