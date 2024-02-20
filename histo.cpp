#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char imgLue[250];
    int nH, nW, taille;

    if (argc != 2) 
    {
       printf("Usage: ImageIn.pgm \n"); 
       exit (1) ;
    }

    sscanf (argv[1],"%s", imgLue) ;

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

    for (int i = 0; i < 255; i++){
		printf("%d : %d \n", i, histo[i]);
	}

    free(ImgIn);
    return 0;
}