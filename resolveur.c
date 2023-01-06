// Résolveur de grille de Sudoku 9*9
// Par Cheïmâa et Valentin

#include <stdio.h>
#include <unistd.h> //pour usleep()
#include "include/libgestion-de-fichiers.h"

#define N 9

int GRILLE[N][N];
int NOMBRE_DE_SOLUTIONS = 0;
int MONTRER_PROCESSUS = 0; //0 = non, 1 = case par case, 2 = uniquement les solutions


int sans_conflit(int ligne, int colonne, int numero);
// int sans_conflit(int sudoku[N][N]); //de Cheïmâa
// int sans_conflit_voisines(int sudoku[N][N]); //de Cheïmâa
void resoudre_sudoku(int ligne, int colonne);

void presentation(void);
void afficher_grille(void);
void afficher_grille2(int soduko[N][N]);







int main(void) {
    presentation();

    char input; // 'y' or 'n'

    printf("(y/n) Charger une grille prédéfinie ?\n");
    do {
        printf(">");
        scanf("%1s", &input);
    } while (input != 'y' && input > 'n');


    if (input == 'y') {
        // choix de la difficulté
        int difficulte;

        printf("\n(1 à 3) Difficulté ? (0 pour test)\n");

        do {
            printf(">");
            scanf("%d", &difficulte);
        } while (difficulte < 0 || difficulte > 3);


        // chargement du fichier en fonction de la difficulté
        char *nom_de_fichier = NULL;

        switch (difficulte) {
            case 0:
                nom_de_fichier = "fichiers-de-sauvegardes/test2.txt";
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
    }

    if (input == 'n') {
        // ...donnée ligne par ligne par l'utilisateur

        printf("\nRemplissez la grille, ligne par ligne (0 pour une case vide)\n\n");
        printf("    1 2 3 4 5 6 7 8 9\n");
        printf("    | | | | | | | | |\n");
        for (int i = 0; i < N; i++) {
            printf("%d - ", i+1);
            scanf("%d %d %d %d %d %d %d %d %d", &GRILLE[i][0], &GRILLE[i][1], &GRILLE[i][2], &GRILLE[i][3], &GRILLE[i][4], &GRILLE[i][5], &GRILLE[i][6], &GRILLE[i][7], &GRILLE[i][8]);
        }
    }



    // RÉSOLUTION DU SUDOKU

    //on lance la fonction juste pour connaître le nombre de solutions
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    afficher_grille2(GRILLE);
    resoudre_sudoku(0, 0);
    printf("\nLa grille ci-dessus à %d solution(s)\n", NOMBRE_DE_SOLUTIONS);



    //montrer le processus ? case par case ou uniquement les solution ?
    for (int i = 0; i < 2; ++i) {
        if (i == 0)
            printf("\n(y/n) Afficher le processus de résolution ? (!!! ça peut être tèèès long)\n>");
        else
            if (i == 1 && MONTRER_PROCESSUS == 0)
                break;
            else
                printf("(y/n) Afficher uniquement les solutions ?\n>");

        scanf("%1s", &input);

        if (input == 'y')
            MONTRER_PROCESSUS++;
    }


    //on relance la fonction s'il faut montrer le processus de résolution
    NOMBRE_DE_SOLUTIONS = 0;
    if (MONTRER_PROCESSUS)
        resoudre_sudoku(0, 0);
    else
        return 0;


    printf("\nFin du processus de résolution\n");
    return 0;
}


/*
 * This code first reads the Sudoku puzzle from the input and then tries to solve it using the backtracking algorithm.
 * The resoudre_sudoku function is a recursive function that tries to place all numbers from 1 to 9 in each empty cell,
 * and then recursively tries to solve the rest of the puzzle.
 * If it reaches a point where it is not possible to place a number in any cell, it backtracks
 */














// résolution du sudoku en utilisant la méthode de backtracking
// on parcours la grille, case par case, dans le sens de lecture
void resoudre_sudoku(int ligne, int colonne) {
    // si on atteint la dernière ligne, et la dernière colonne (+1), le sudoku est résolu
    if (ligne == N) {
        NOMBRE_DE_SOLUTIONS++;
        if (MONTRER_PROCESSUS == 2) {
            printf("\n\nSolution n°%d\n", NOMBRE_DE_SOLUTIONS);
            afficher_grille();
            usleep(1000 * 1000);
        }
        return;
    }

    // on pase à la case suivante si la case est pleine
    if (GRILLE[ligne][colonne] != 0) {
        if (colonne == N - 1)
            return resoudre_sudoku(ligne + 1, (colonne + 1) % N);
        else
            return resoudre_sudoku(ligne, (colonne + 1) % N);
    }
    

    if (MONTRER_PROCESSUS == 1) {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\nNombre de solutions trouvées : %d\n", NOMBRE_DE_SOLUTIONS);
        afficher_grille();
        usleep(50 * 1000);
    }

    // on essaye tous les nombres de 1 à 9
    for (int numero = 1; numero <= N; numero++) {
        // on vérifie qu'il n'y a pas de conflit

        // GRILLE[ligne][colonne] = numero;
        // if (sans_conflit(GRILLE) && sans_conflit_voisines(GRILLE)) {
        if (sans_conflit(ligne, colonne, numero)) {
            GRILLE[ligne][colonne] = numero;
            

            // on passe à la case suivante
            // int resolu = 0;

            if (colonne == N - 1)
                resoudre_sudoku(ligne + 1, (colonne + 1) % N);
            else
                resoudre_sudoku(ligne, (colonne + 1) % N);


            // on vide la case s'il y'a eu conflit par le suite
            GRILLE[ligne][colonne] = 0;
        }
    }

    return;
}





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



/* 
* Nous construisons un tableau d'occurrences pour chaque numéro.
*  Ce tableau d'occurences est remis à 0 à chaque fois qu'on lit une nouvelle ligne.
*  A la fin de la ligne et donc après avoir renseigné les 9 cases du tableau d'occurrences, on regarde s'il y a des doublons dans la ligne (nombre d'occurrences > 1)
*  S'il y a des doublons, alors il y a conflit. 
*  Ensuite nous faisons exactement la même chose pour les colonnes.
*/


// int sans_conflit(int sudoku[N][N]){
//     int occurrence[N] = {0};
//     int i, j, o;


//     //LIGNES
//     for (i = 0; i < N; i++) {
//         for(j = 0; j < N; j++) {
//             switch(sudoku[i][j]) {
//                 case 1:
//                     occurrence[0]++;
//                     break;
//                 case 2:
//                     occurrence[1]++;
//                     break;
//                 case 3:
//                     occurrence[2]++;
//                     break;
//                 case 4:
//                     occurrence[3]++;
//                     break;
//                 case 5:
//                     occurrence[4]++;
//                     break;
//                 case 6:
//                     occurrence[5]++;
//                     break;
//                 case 7:
//                     occurrence[6]++;
//                     break;
//                 case 8:
//                     occurrence[7]++;
//                     break;
//                 case 9:
//                     occurrence[8]++;
//                     break;
//                 default:
//                     break;
//             }
//         }

//         for (o = 0; o < N; o++) {
//                 if (occurrence[o] > 1) {
//                     // printf("Les règles ne sont pas respectées.\n");
//                     return 0;
//                 }

//                 else occurrence[o] = 0;
//             }
//         }


//     //COLONNES
//     for (i = 0; i < N; i++) {
//         for(j = 0; j < N; j++){
//             switch(sudoku[j][i]){
//                 case 1:
//                     occurrence[0]++;
//                     break;
//                 case 2:
//                     occurrence[1]++;
//                     break;
//                 case 3:
//                     occurrence[2]++;
//                     break;
//                 case 4:
//                     occurrence[3]++;
//                     break;
//                 case 5:
//                     occurrence[4]++;
//                     break;
//                 case 6:
//                     occurrence[5]++;
//                     break;
//                 case 7:
//                     occurrence[6]++;
//                     break;
//                 case 8:
//                     occurrence[7]++;
//                     break;
//                 case 9:
//                     occurrence[8]++;
//                     break;
//                 default:
//                     break;
//             }
//         }

//         for (o = 0; o < N; o++){
//                 if (occurrence[o] > 1) {
//                     // printf("Les règles ne sont pas respectées.\n");
//                     return 0;
//                 }

//                 else occurrence[o] = 0;
//             }
//         }

//     return 1;
// }


// /* 
// * Même logique que la précédente fonction
// * Cette fois-ci k et l sont ajoutés pour faire jump les indices de 3 à chaque itération et ainsi étudier chaque région de 3x3 
// */
// int sans_conflit_voisines(int sudoku[N][N]){
//     int i, j, k, l, o;
//     int occurrence[N] = {0};

//     for (l = 0; l < 3;l++) {
//         for(k = 0; k < 3; k++) {
//             for (i = 3*k; i < 3*(k+1); i++) {
//                 for(j = 3*l; j < 3*(l+1); j++) {
//                     switch(sudoku[i][j]) {
//                         case 1:
//                             occurrence[0]++;
//                             break;
//                         case 2:
//                             occurrence[1]++;
//                             break;
//                         case 3:
//                             occurrence[2]++;
//                             break;
//                         case 4:
//                             occurrence[3]++;
//                             break;
//                         case 5:
//                             occurrence[4]++;
//                             break;
//                         case 6:
//                             occurrence[5]++;
//                             break;
//                         case 7:
//                             occurrence[6]++;
//                             break;
//                         case 8:
//                             occurrence[7]++;
//                             break;
//                         case 9:
//                             occurrence[8]++;
//                             break;
//                         default:
//                             break;
//                     }
//                 }
//             }

//         /* Après avoir itéré sur une région, il faut maintenant vérifier si une valeur du tableau occurence (de longueur 9) est supérieure à 1, ce qui supposerait qu'une valeur sur la grille apparaît plus d'une fois --> il y a conflit. */

//             for (o = 0;  o < N; o++) {
//                 if (occurrence[o] > 1) {
//                     // printf("Les règles ne sont pas respectées.\n");
//                     return 0;
//                 }

//                 else occurrence[o] = 0;
//             }
//         }
//     }

//     return 1;
// }








void presentation(void) {
    printf("====================================================\n");
    printf("=== Résolveur de Sudoku, par Cheïmâa et Valentin ===\n");
    printf("====================================================\n\n");
    printf("Soit vous donnez une grille à la main, soit vous chargez une grille prédéfinie.\n");
    printf("Le nombre de solutions sera indiqué,\nvous aurez ensuite le choix de voir l'ordinateur faire défiler le processus de résolution,\nou bien uniquement toutes les solutions possibles.\n\n");
}




void afficher_grille(void){
    printf("\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) {
            if (GRILLE[i][j] == 0)
                printf("- ");
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
            if (sudoku[i][j] == 0)
                printf(((j+1)%3) ? "- " : "-  |  "); // Si J+1 / 3 == 0, alors mettre un espace après la valeur sinon, un espace + |
            else
                printf(((j+1)%3) ? "%d " : "%d  |  ", sudoku[i][j]); // Si J+1 / 3 == 0, alors mettre un espace après la valeur sinon, un espace + |

            if (j == 8){ printf("%d", k++);} // Séparation visuelle en 3
            if ((i == 2 || i == 5) && (j == 8)  ){ printf("\n____________________________\n");}
            
        }
        printf("\n");
    }
}

