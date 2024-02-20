#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char imgLue[250]; char histoOut[250];
    int nH, nW, taille;

    if (argc != 3) 
    {
       printf("Usage: ImageIn.pgm histoOut.txt \n"); 
       exit (1) ;
    }

    sscanf(argv[1],"%s", imgLue) ;
    sscanf(argv[2], "%s", histoOut);

    lire_nb_lignes_colonnes_image_pgm(imgLue, &nH, &nW);
    taille = nH * nW;

    OCTET *ImgIn;
    allocation_tableau(ImgIn, OCTET, taille);
    lire_image_pgm(imgLue, ImgIn, nH * nW);

    int histo[255];
    for (int i=0; i<255; i++){ histo[i]=0; }

    for(int i=0; i<nH; i++)
    {
        for(int j=0; j<nW; j++)
        {
            int p = i*nW+j;
            histo[ImgIn[p]] += 1;
        }
    }

    FILE* f;
    if( (f = fopen(histoOut, "wb")) == NULL)
    {
        printf("\nPas d'acces en ecriture sur l'image %s \n", histoOut);
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