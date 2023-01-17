// Résolveur/Générateur de grille de Sudoku 9*9
// Par Cheïmâa et Valentin

#include <stdio.h>
#include <unistd.h> //pour usleep()
#include "include/libgestion-de-fichiers.h"
#include <time.h>
#include <stdlib.h> // pour rand()

#define N 9

int GRILLE[N][N];
int grille_temp[N][N];

int NOMBRE_DE_SOLUTIONS = 10;
int TENTATIVES_DE_GENERATION = 0;
int MONTRER_PROCESSUS = 0; //0 = non, 1 = case par case, 2 = uniquement les solutions

int liste_nbe[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};


int generer_grille(void);
void resoudre_grille(int ligne, int colonne);

void initialiser_grille(int soduko[N][N]);
int sans_conflit(int ligne, int colonne, int chiffre);
int grille_complete(void);

void afficher_grille(void);
void afficher_grille2(int soduko[N][N]);

void presentation(void);








int main(void) {
    srand(time(0));




    presentation();

    char input; // 'y' or 'n'

    printf("(r/g) Souhaitez-vous RÉSOUDRE ou GÉNÉRER une grille Sudoku?\n");
    do {
        printf(">");
        scanf("%1s", &input);
    } while (input != 'r' && input != 'g');



    if (input == 'g') {

        int int_input = 5;

        printf("\n(entre 1 et 80 inclus) Combien de cases souhaitez-vous retirer ?\n");
        do {
            printf(">");
            scanf("%d", &int_input);
        } while (int_input < 1 && int_input > 80);

        int nb_a_supprimer = int_input;


        printf("\n(y/n) Afficher le processus de génération ?\n");
        do {
            printf(">");
            scanf("%1s", &input);
        } while (input != 'y' && input != 'n');

        if (input == 'y') {
            MONTRER_PROCESSUS = 1;
        }

        
        
  
        while (NOMBRE_DE_SOLUTIONS != 1) {
            TENTATIVES_DE_GENERATION ++;
            NOMBRE_DE_SOLUTIONS = 0;
            initialiser_grille(GRILLE);
            initialiser_grille(grille_temp);


            if (! MONTRER_PROCESSUS)
                printf("Tentative de génération n°%d en cours...\n", TENTATIVES_DE_GENERATION);



            generer_grille();

            //retrait de certaines cellules
            int ligne = 0;
            int colonne = 0;
            int temp_suppr = nb_a_supprimer;
            while (temp_suppr) {
                ligne = rand()% 9;
                colonne = rand()% 9;
                if (GRILLE[ligne][colonne]) {
                    if (MONTRER_PROCESSUS) {
                        afficher_grille2(GRILLE);
                        usleep(50 * 1000);
                    }
                    GRILLE[ligne][colonne] = 0;
                    temp_suppr --;
                }
            }

            

            //save temp
            for (int ligne = 0; ligne < N; ligne++) {
                for (int colonne = 0; colonne < N; colonne++) {
                    grille_temp[ligne][colonne] = GRILLE[ligne][colonne]; // Copie du tableau 2D sudoku facile dans le tableau 2D global
                }
            }


            //résoudre

            resoudre_grille(0, 0);
            // printf("nb solution = %d\n", NOMBRE_DE_SOLUTIONS); //debug
        }



        for (int ligne = 0; ligne < N; ligne++) {
            for (int colonne = 0; colonne < N; colonne++) {
                GRILLE[ligne][colonne] = grille_temp[ligne][colonne]; // Copie du tableau 2D sudoku facile dans le tableau 2D global
            }
        }



        

        afficher_grille2(GRILLE);
        // attention aux grilles à solutions multiples
        printf("\nSudoku généré en %d tentative(s).\n", TENTATIVES_DE_GENERATION);
        return 0;
    }


    // résoudre

    printf("\n\n(y/n) Charger une grille prédéfinie ?\n");
    do {
        printf(">");
        scanf("%1s", &input);
    } while (input != 'y' && input != 'n');


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
                nom_de_fichier = "fichiers-de-sauvegardes/sudoku_difficile_errone.txt";
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
    NOMBRE_DE_SOLUTIONS = 0;
    resoudre_grille(0, 0);

    if (! NOMBRE_DE_SOLUTIONS) {
        printf("\nLa grille ci-dessus n'a aucune solution.\n");
        return 0;
    }

    printf("\nLa grille ci-dessus à %d solution(s)\n", NOMBRE_DE_SOLUTIONS);





    //montrer le processus ? case par case ou uniquement les solution ?
    for (int i = 0; i < 2; ++i) {
        if (i == 0)
            printf("\n(y/n) Afficher le processus de résolution ? (!!! ça peut être trèèès long)\n>");
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
        resoudre_grille(0, 0);
    else
        return 0;


    printf("\nFin du processus de résolution\n");
    return 0;
}













// résolution du sudoku en utilisant la méthode de backtracking
void resoudre_grille(int ligne, int colonne) {
    // si on atteint la dernière ligne, et la dernière colonne (+1), le sudoku est résolu
    if (ligne == N) {
        NOMBRE_DE_SOLUTIONS++;
        if (MONTRER_PROCESSUS == 2) {
            printf("\n\nSolution n°%d\n", NOMBRE_DE_SOLUTIONS);
            afficher_grille2(GRILLE);
            usleep(1000 * 1000);
        }
        return;
    }

    // on pase à la case suivante si la case est pleine
    if (GRILLE[ligne][colonne] != 0) {
        if (colonne == N - 1)
            return resoudre_grille(ligne + 1, (colonne + 1) % N);
        else
            return resoudre_grille(ligne, (colonne + 1) % N);
    }
    

    if (MONTRER_PROCESSUS == 1) {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\nNombre de solutions trouvées : %d\n", NOMBRE_DE_SOLUTIONS);
        afficher_grille2(GRILLE);
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
                resoudre_grille(ligne + 1, (colonne + 1) % N);
            else
                resoudre_grille(ligne, (colonne + 1) % N);


            // on vide la case s'il y'a eu conflit par le suite
            GRILLE[ligne][colonne] = 0;
        }
    }

    return;
}




// génération du sudoku en utilisant la méthode de backtracking
int generer_grille(void) {
    
    if (MONTRER_PROCESSUS == 1) {
        printf("\n\nTentative n°%d\n", TENTATIVES_DE_GENERATION);
        afficher_grille2(GRILLE);
        usleep(50 * 1000);
    }

    for (int cellule = 0; cellule < 81; cellule++) {
        int ligne = cellule / 9;
        int colonne = cellule % 9;

        if (GRILLE[ligne][colonne] == 0) {
            // mélange de la liste des chiffres
            for (int i = 0; i < N; i++) {
                int randomIndex = rand() % 9;
                int temp = liste_nbe[i];
                liste_nbe[i] = liste_nbe[randomIndex];
                liste_nbe[randomIndex] = temp;
            }

            // parcours de la liste des chiffres
            for (int i = 0; i < N; i++) {
                int valeur = liste_nbe[i];

                // s'il n'y a aucun conflit
                if (sans_conflit(ligne, colonne, valeur)){
                    GRILLE[ligne][colonne] = valeur;

                    // si la grille est complète, arrêt de la fonction
                    if (grille_complete())
                        return 1;
                    // sinon, rappel de la fonction
                    else {
                        if (generer_grille())
                            return 1;
                    }
                }
            }

            GRILLE[ligne][colonne] = 0;
            return 0;

        }
    }
    
    return 1;
}








void initialiser_grille(int soduko[N][N]) {
    for (int ligne = 0; ligne < N; ligne++) {
        for (int colonne = 0; colonne < N; colonne++)
            soduko[ligne][colonne] = 0;
    }
}



// Vérifie si la position est corrrecte
int sans_conflit(int ligne, int colonne, int chiffre) {
    // Vérifie si 'numero' n'est pas déja sur la ligne, colonne et sous-grille (3x3)
    for (int i = 0; i < N; i++)
        if (GRILLE[ligne][i] == chiffre || GRILLE[i][colonne] == chiffre)
            return 0;

    int startRow = ligne - ligne % 3;
    int startCol = colonne - colonne % 3;
    for (int i = startRow; i < startRow + 3; i++)
        for (int j = startCol; j < startCol + 3; j++)
            if (GRILLE[i][j] == chiffre)
                return 0;

    return 1;
}





int grille_complete(void) {
    for (int ligne = 0; ligne < 9; ligne++) {
        for (int colonne = 0; colonne < 9; colonne++) {
            if (GRILLE[ligne][colonne] == 0) {
                return 0;
            }
        }
    }
    //la grille est complete
    return 1;
}







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

