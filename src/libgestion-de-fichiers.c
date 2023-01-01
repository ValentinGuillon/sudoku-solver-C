#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 9

void ecrire_grille(int sudoku[9][9], FILE *fp);
int lire_grille(FILE *fp, int sudoku[9][9]);
int conversion(char c);


void ecrire_grille(int sudoku[9][9], FILE *fp){
    
    for (int i = 0 ; i<9; i++){
        for (int j = 0 ; j < 9; j++){
            if(sudoku[i][j] == 0) fprintf(fp, "_");
            else fprintf(fp, "%d", sudoku[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp); 
}


int lire_grille(FILE *fp, int sudoku[9][9]){

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
    
    for (int i = 0 ; i<9; i++){
        for (int j = 0 ; j < 9; j++){

            c = chaine[i*9 +j];

            if (c == '_'){
                sudoku[i][j] = 0;
            }
            else sudoku[i][j] = conversion(c) ; // Appel d'une fonction de conversion des numéros CHAR en INT car les cast n'étaient pas fiables

        }
    }
    
    return 1;     
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