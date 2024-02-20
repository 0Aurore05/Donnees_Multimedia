#include <bits/types/FILE.h>
#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char nomImgLue[250]; char nomProfilOut[250];
    int nH, nW, indice;
    int n=0;
    char mode;

    if (argc != 5) 
    {
        printf("Usage: ImageIn.pgm profilOut.txt l/c indice \n"); 
        exit (1) ;
    }
    sscanf(argv[1], "%s", nomImgLue);
    sscanf(argv[2], "%s", nomProfilOut);
    sscanf(argv[3], "%c", &mode);
    sscanf(argv[4], "%d", &indice);

    OCTET *ImgIn;
    lire_nb_lignes_colonnes_image_pgm(nomImgLue, &nH, &nW);
    allocation_tableau(ImgIn, OCTET, nW*nH);
    lire_image_pgm(nomImgLue, ImgIn, nH*nW);    

    if(mode == 'l') //on considère une ligne
    {
        n = nW;
    }
    else if(mode == 'c') //on considère une colonne
    {
        n = nH;
    }
    else //on considère rien du tout on s'est trompé
    {
        perror("mode non valide, l ou c");
        exit(1);
    }
    
    int histo[n];
    for(int k=0; k<n; k++)
    {
        int p = indice*n+k;
        histo[k] = ImgIn[p];
    }

    FILE* f;
    if( (f = fopen(nomProfilOut, "wb")) == NULL)
    {
        printf("\nPas d'acces en ecriture sur l'image %s \n", nomProfilOut);
        exit(EXIT_FAILURE);
    }
    else
    {
        for(int i=0; i<255; i++)
        {
            fprintf(f, "%d %d\n", i, histo[i]);
        }
        fclose(f);
    }

    free(ImgIn);
    return 0;
}