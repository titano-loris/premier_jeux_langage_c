#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include"main.h"

int main(int argc, char* argv[])
{
    char lettre = 0;
    char motSecret[]="CODING";
    int coupsRestants = 10;
    int nombreLettres = tailleMot(motSecret);
    int *lettreTrouvee = NULL;// Tableau de booléens 0 = lettre non trouvée, 1 = lettre trouvée
    lettreTrouvee = malloc(nombreLettres * sizeof(int));
    initTableau(lettreTrouvee, nombreLettres);

    printf(" jeux du Pendu !\n\n");

    while (coupsRestants > 0 && !gagne(lettreTrouvee, nombreLettres))
    {
        printf("\n\nIl vous reste %d coups a jouer", coupsRestants);
        printf("\nQuel est le mot secret ? ");

        // on masquent les lettres non trouvées (*)

        for (int i = 0 ; i < nombreLettres ; i++)
        {
            if (lettreTrouvee[i])
                printf("%c", motSecret[i]);
            else
                printf("*");
        }

        printf("\nProposez une lettre : ");
        lettre = lireCaractere();


        if (!rechercheLettre(lettre, motSecret, lettreTrouvee))
        {
            coupsRestants--;
        }
    }

    if (gagne(lettreTrouvee, nombreLettres))
        printf("\n\nGagne ! Le mot secret etait bien : %s\n", motSecret);
    else
        printf("\n\nPerdu ! Le mot secret etait : %s \n", motSecret);

    return 0;
}

int tailleMot(char motSecret[])
{
    int nombreLettre = 0;
    for(int i = 0; motSecret[i] != '\0'; i++)
    {
        nombreLettre++;
    }
    return nombreLettre;
}

char lireCaractere()
{
    char caractere = 0;

    caractere = getchar(); // lecture du premier caractère
    caractere = toupper(caractere); // lettre en majuscule si elle ne l'est pas

    // lecture des autres caractères mémorisés un à un jusqu'au \n
    while (getchar() != '\n') ;

    return caractere; // On retourne le premier caractère qu'on a lu
}

void initTableau(int* lettreTrouvee, int taille)
{
    for(int i = 0; i < taille; i++)
    {
        lettreTrouvee[i] = 0;
    }
}

int gagne(int *lettreTrouvee, int nombreLettres)
{
    int i = 0;
    int joueurGagne = 1;

    for (i = 0 ; i < nombreLettres ; i++)
    {
        if (lettreTrouvee[i] == 0)
            joueurGagne = 0;
    }

    return joueurGagne;
}


int rechercheLettre(char lettre, char motSecret[], int* lettreTrouvee)
{
    int i = 0;
    int bonneLettre = 0;

    // balayage motSecret pour vérifier la lettre proposée
    for (i = 0 ; motSecret[i] != '\0' ; i++)
    {
        if (lettre == motSecret[i]) // Si la lettre y est
        {
            bonneLettre = 1; // On mémorise que c'était une bonne lettre
            lettreTrouvee[i] = 1; // On met à 1 la case du tableau de booléens correspondant à la lettre actuelle
        }
    }

    return bonneLettre;
}
