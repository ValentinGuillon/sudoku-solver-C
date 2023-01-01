/* Projet de Fatimzahra et Cheïmâa */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define N 9

void afficher_grille(int sudoku[N][N]);
int lire_grille(FILE *fp, int sudoku[N][N]);
void ecrire_grille(int sudoku[N][N], FILE *fp);
int sans_conflit(int sudoku[N][N]);
int sans_conflit_voisines(int sudoku[N][N]);
int conversion(char c);
int Jeu(int sudoku[N][N]);
int sudoku_o[N][N]; // Sudoku original passé en variable globale afin d'y stocker la grille initiale accessible à toutes les fonctions



int main(){

    char yn; // variable yes/no
    
    /////// Initialisation grille facile 
    
    int sudoku_f[N][N] ;
    char *fichier_f = "sudoku_facile.txt";
    FILE *fp = fopen(fichier_f, "r");
    lire_grille(fp, sudoku_f);
    fclose(fp); 
    
    // Sauvegarde notre partie, à inclure dans la boucle principale
    
    FILE *fp2 = fopen("sudoku_facile_sauvegarde.txt", "w+");
    ecrire_grille(sudoku_f, fp2);
    
    
    for (int k = 0; k < N; k++) 
        for (int l = 0; l < N; l++) {     
        sudoku_o[k][l] = sudoku_f[k][l]; // Copie du tableau 2D sudoku facile dans le tableau 2D global
    }
    
    /*
    
    Il y a un problème de mémoire qui empêche la création de différents niveau
    
    //////// moyen
    
    int sudoku_m[N][N] ;
    char *fichier_m = "sudoku_moyen.txt";
    FILE *mp = fopen(fichier_m, "r");
    lire_grille(mp, sudoku_m);
    fclose(mp); 
    //FILE *mp2 = fopen("sudoku_moyen_sauvegarde.txt", "w+");
    //ecrire_grille(sudoku_m, mp2);
    
    
    ////////// difficile
    
    int sudoku_d[N][N] ;
    char *fichier_d = "sudoku_difficile.txt";
    FILE *dp = fopen(fichier_d, "r");
    lire_grille(dp, sudoku_d, fichier_d);
    fclose(dp); 
    FILE *dp2 = fopen("sudoku_difficile_sauvegarde.txt", "w+");
    ecrire_grille(sudoku_d, dp2);*/
    
     
    
    // Visuel du jeu
    
    printf("\n********************* SUDOKU *********************\n\n");
	printf("Bienvenue au jeu du SUDOKU !\n\n\n");
	printf("Règles du jeu :\n");
	printf("Le but est de remplir le tableau de sorte que dans chaque ligne, chaque colonne, chaque région de 3x3, les chiffres (1 à 9) apparaissent une et une seule fois.\n\n\n");
	
	printf("Voulez-vous commencer une nouvelle partie ? (Y/N)\n");
	scanf("%c", &yn);	
	if (tolower(yn) == 'y'){
	    printf("\n\n\nVoici la grille :\n\n");
	    afficher_grille(sudoku_f);
	    // S'il existe une valeur dans le tableau qui soit égale à 0, alors notre fonction Jeu() est lancée
	    for (int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(sudoku_f[i][j] == 0){ 	    	      
                    Jeu(sudoku_f);}}}} 
    else exit(0);
    
    printf("\n\n\nVous avez complété la grille. Bravo !"); // Message de fin
                
        
	
    
    
    return EXIT_SUCCESS;
}


int Jeu(int sudoku[N][N]){

    // Intitialisation de notre grille temporaire utile à nos tests

    int sudoku_temp[N][N];
    for (int k = 0; k < N; k++) 
        for (int l = 0; l < N; l++) {     
        sudoku_temp[k][l] = sudoku[k][l];     
    }
    
    
    int i, j; // Indices entrés par l'utilisateur
    int val; // Valeur entrée par l'utilisateur
    
    printf("\nVeuillez saisir le numéro de la ligne que vous souhaitez modifier : ");
	scanf("%d", &i);
	
	// Série de boucles tant que des valeurs correctes ne sont pas entrées
	
	while(i < 1 || i > 9){
	    printf("Ce chiffre est incorrect. Veuillez réessayer.\n");
	    printf("Saisissez le numéro de la ligne que vous souhaitez modifier : ");
	    scanf("%d", &i);}
	
	
	printf("\nVeuillez saisir le numéro de la colonne que vous souhaitez modifier : ");
	scanf("%d", &j);
	
	while(j < 1 || j > 9){
	    printf("Ce chiffre est incorrect. Veuillez réessayer.\n");
	    printf("Saisissez le numéro de la ligne que vous souhaitez modifier : ");
	    scanf("%d", &j);}
	
	printf("\nVeuillez saisir la valeur que vous souhaitez y inscrire : ");
	scanf("%d", &val);
	
	while(val < 1 || val > 9){
	    printf("Ce chiffre est incorrect. Veuillez réessayer.\n");
	    printf("Saisissez le numéro de la ligne que vous souhaitez modifier : ");
	    scanf("%d", &val);}
	
    // Test l'inscription sur une case initiale

	if(sudoku_o[i-1][j-1] != 0){
	    printf("Cette action n'est pas possible. Veuillez choisir une case vide.\n");
	    Jeu(sudoku);}
	else sudoku_temp[i-1][j-1] = val;
	  
	// Test de conflits sur notre grille temporaire, s'il n'y en a aucun --> modification de la grille prise en argument  
	   
	if (sans_conflit(sudoku_temp) == 1 || sans_conflit_voisines(sudoku_temp) == 1){
	    printf("\n");}
	else sudoku[i-1][j-1] = val;
	
	// Affichage de notre grille à chaque itération
	
	printf("\n\n\nVoici la grille :\n\n");
	    afficher_grille(sudoku);
	

	
	return 0;
	}




/* Parcours les lignes et les colonnes pour écrire chaque case une par une dans le fichier passé en argument */

void ecrire_grille(int sudoku[N][N], FILE *fp){
    
    for (int i = 0 ; i<N; i++){
        for (int j = 0 ; j < N; j++){
            if(sudoku[i][j] == 0) fprintf(fp, "_");
            else fprintf(fp, "%d", sudoku[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp); 
}


/* Parcours les lignes et les colonnes pour les afficher dans la console */

void afficher_grille(int sudoku[N][N]){
    printf("1 2 3     4 5 6     7 8 9\n\n"); // Affichage numéro de colonne
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
 



int lire_grille(FILE *fp, int sudoku[N][N]){

    /*Nous savons que la grille doit comporter 81 caractères. Ainsi, pour s'assurer du bon formatage, nous allons lire les caractères un à un depuis le fichier soumis.
      A chaque fois qu'un caractère correspondant à un chiffre ou à un "_" est lu, nous pouvons le copier. Nous le copions dans la variable "chaine", et ensuite nous réallouons
      de l'espace en mémoire à "chaine". Si un caractère n'est pas lisible, alors c'est la fin de la lecture de la grille car la chaine arrête de grandir.

      A la fin de la lecture de la grille, nous testons la taille de la chaîne. Si sa longueur est de 81, alors nous estimons que tous les caractères ont bien été lus.
    */
    
    
    char c; //caractère variant
    int nb_c = 1; //compteur de caractère dans notre chaîne de caractère dynamique
    
    char *chaine = malloc(sizeof(char));

    while (c != EOF) {
        c = (char)fgetc(fp);
        
        if(isdigit(c) || c=='_') // Si caractère est un chiffre ou un _
        {
            strncat(chaine, &c, 1); //Nous ajoutons le caractère variant c à la chaine de caractère CHAINE
            nb_c++;                 // Incrémentation de la taille de la chaîne de caractère
            chaine= realloc(chaine, (nb_c+1)*sizeof(char)); //Allocation de la nouvelle place en mémoire
        }
        else if(c!=-1 && c!=13 && c !=10){ //Si le caractère n'est pas un null byte ni un saut de ligne, alors le caractère est illisible et c'est la fin de la lecture
                
                printf("Caractère inconnu, lecture de la grille impossible. Fin du jeu.\n");
                exit(0);
        }       
    }


    // Nous testons la taille de la chaîne. Si sa longueur est de 81, alors nous estimons que tous les caractères ont bien été lus
    
    int len = strlen(chaine);
    if(len != 81){
        printf("La grille de Sudoku soumise n'est pas correctement formatée ! Il y a des caractères manquants ou en trop."); // DEBUG : ajouter "%d", len
        exit(0);
    }


    // Copie des caractères un à un dans le tableau d'entiers à deux dimensions SUDOKU
    
    for (int i = 0 ; i<N; i++){
        for (int j = 0 ; j < N; j++){

            c = chaine[i*N +j];

            if (c == '_'){
                sudoku[i][j] = 0;
            }
            else sudoku[i][j] = conversion(c) ; // Appel d'une fonction de conversion des numéros CHAR en INT car les cast n'étaient pas fiables

        }
    }
    
    return 1;     
}


/* 
* Nous construisons un tableau d'occurrences pour chaque numéro.
*  Ce tableau d'occurences est remis à 0 à chaque fois qu'on lit une nouvelle ligne.
*  A la fin de la ligne et donc après avoir renseigné les 9 cases du tableau d'occurrences, on regarde s'il y a des doublons dans la ligne (nombre d'occurrences > 1)
*  S'il y a des doublons, alors il y a conflit. 
*  Ensuite nous faisons exactement la même chose pour les colonnes.
*/
int sans_conflit(int sudoku[N][N]){
    int occurrence[N] = {0}; 
                              
                             

    //LIGNES
    for (int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            switch(sudoku[i][j]){
                case 1:
                    occurrence[0]++;
                    break;
                case 2:
                    occurrence[1]++;
                    break;
                case 3:
                    occurrence[2]++;
                    break;
                case 4:
                    occurrence[3]++;
                    break;
                case 5:
                    occurrence[4]++;
                    break;
                case 6:
                    occurrence[5]++;
                    break;
                case 7:
                    occurrence[6]++;
                    break;
                case 8:
                    occurrence[7]++;
                    break;
                case 9:
                    occurrence[8]++;
                    break;
                default:
                    break;
            }      
            
        }

        for (int o = 0; o<N; o++){
                //printf("o = %d : occurence=%d | ", o+1, occurrence[o]); //DEBUG
                if (occurrence[o]>1){
                    printf("Les règles ne sont pas respectées.\n");
                    return 1;}
                else occurrence[o] = 0;
            }
            //printf("\n");
            
        }


        //printf("\n");

    //COLONNES
    for (int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            switch(sudoku[j][i]){
                case 1:
                    occurrence[0]++;
                    break;
                case 2:
                    occurrence[1]++;
                    break;
                case 3:
                    occurrence[2]++;
                    break;
                case 4:
                    occurrence[3]++;
                    break;
                case 5:
                    occurrence[4]++;
                    break;
                case 6:
                    occurrence[5]++;
                    break;
                case 7:
                    occurrence[6]++;
                    break;
                case 8:
                    occurrence[7]++;
                    break;
                case 9:
                    occurrence[8]++;
                    break;
                default:
                    break;
            }      
            
        }
        for (int o = 0; o<N; o++){
                //printf("o = %d : occurence=%d | ", o+1, occurrence[o]);
                if (occurrence[o]>1){
                    printf("Les règles ne sont pas respectées.\n");
                    return 1;}
                else occurrence[o] = 0;
            }
            //printf("\n");
            
        }


    return 0;
}

int sans_conflit_voisines(int sudoku[N][N]){

/* 
* Même logique que la précédente fonction
* Cette fois-ci k et l sont ajoutés pour faire jump les indices de 3 à chaque itération et ainsi étudier chaque région de 3x3 
*/
    int occurrence[N] = {0};
        for (int l=0; l<3;l++){
            for(int k = 0; k<3; k++){
                for (int i=3*k; i<3*(k+1); i++){
                    for(int j=3*l; j<3*(l+1); j++){
                        switch(sudoku[i][j]){
                case 1:
                    occurrence[0]++;
                    break;
                case 2:
                    occurrence[1]++;
                    break;
                case 3:
                    occurrence[2]++;
                    break;
                case 4:
                    occurrence[3]++;
                    break;
                case 5:
                    occurrence[4]++;
                    break;
                case 6:
                    occurrence[5]++;
                    break;
                case 7:
                    occurrence[6]++;
                    break;
                case 8:
                    occurrence[7]++;
                    break;
                case 9:
                    occurrence[8]++;
                    break;
                default:
                    break;
                }
                //printf("%d", sudoku[i][j]);
            }
            
        }
        /* Après avoir itéré sur une région, il faut maintenant vérifier si une valeur du tableau occurence (de longueur 9) est supérieure à 1, ce qui supposerait qu'une valeur sur la grille apparaît plus d'une fois --> il y a conflit. */
        
        for (int o = 0; o<N; o++){
                //printf("o = %d : occurence=%d | ", o+1, occurrence[o]); //DEBUG
            if (occurrence[o]>1){
                printf("Les règles ne sont pas respectées.\n");
                return 1;}
            else occurrence[o] = 0;
            }
            //printf("\n");
            
         
     }
     }
        
        return 0;
}



int conversion(char c){
    switch(c){
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;      
        default:
            return 0;  
    }
}