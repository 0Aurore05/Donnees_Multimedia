#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImg1[250], cNomImg2[250];
    int nH, nW, taille;
    double eqm=0;
    
    if (argc != 3) 
        {
        printf("Usage: Image1.ppm Image2.pgm\n"); 
        exit (1) ;
        }
    
    sscanf (argv[1],"%s",cNomImg1) ;
    sscanf (argv[2],"%s",cNomImg2);

    OCTET *Img1, *Img2;
    lire_nb_lignes_colonnes_image_pgm(cNomImg1, &nH, &nW);
    taille = nH * nW;
    
    {
        int tmp1, tmp2;
        lire_nb_lignes_colonnes_image_pgm(cNomImg2, &tmp1, &tmp2);
        if(tmp1!=nH || tmp2!=nW)
        {
            perror("pas le même nombre de lignes ou colonnes");
            exit(1);
        }
    }

    allocation_tableau(Img1, OCTET, taille);
    lire_image_pgm(cNomImg1, Img1, taille);
    allocation_tableau(Img2, OCTET, taille);
    lire_image_pgm(cNomImg2, Img2, taille);

    for(int i=0; i<nH; i++)
    {
        for(int j=0; j<nW; j++)
        {
            int p = (i*nW) + j;
            eqm += (Img1[p]-Img2[p])*(Img1[p]-Img2[p]); 
        }
    }
    eqm/=taille;
    printf("EQM : %f\n", eqm);

    free(Img1); free(Img2);

    return 0;
}