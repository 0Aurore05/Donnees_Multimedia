#include <bits/types/FILE.h>
#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char nomImgLue[250];
    char* nomImgOut = "inverse.pgm";
    int nH, nW, nTaille;

    if (argc != 2) 
    {
        printf("Usage: ImageIn.ppm \n"); 
        exit (1) ;
    }
    sscanf(argv[1], "%s", nomImgLue);

    OCTET *ImgIn, *ImgOut;
    lire_nb_lignes_colonnes_image_pgm(nomImgLue, &nH, &nW);
    nTaille = nH * nW;
    allocation_tableau(ImgIn, OCTET, nW*nH);
    lire_image_pgm(nomImgLue, ImgIn, nH*nW);    
    allocation_tableau(ImgOut, OCTET, nTaille);

    for (int i=0; i < nH; i++)
    {
        for (int j=0; j < nW; j++)
        {
            int p = i*nW+j;
            ImgOut[p] = 255-ImgIn[p];
        }
    }

    ecrire_image_pgm(nomImgOut, ImgOut,  nH, nW);

    free(ImgIn);
    return 0;
}