#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char nomImgY[250];
    int nH, nW, taille, k;
    
    if (argc != 3) 
        {
        printf("Usage: ImageY.pgm k\n"); 
        exit (1) ;
        }
    
    sscanf (argv[1],"%s",nomImgY);
    sscanf (argv[2],"%d",&k);

    if(k<=-128 || k>=128)
    {
        perror("k doit être entre -128 et 128 immense bolosse");
        exit(1);
    }

    OCTET *ImgY, *ImgYmod;
    lire_nb_lignes_colonnes_image_pgm(nomImgY, &nH, &nW);
    taille = nH * nW;

    allocation_tableau(ImgY, OCTET, taille);
    lire_image_pgm(nomImgY, ImgY, taille);
    allocation_tableau(ImgYmod, OCTET, taille);

    for(int i=0; i<nH; i++)
    {
        for(int j=0; j<nW; j++)
        {
            int p = (i*nW)+j;
            if(ImgY[p]+k<0) 
            {
                ImgYmod[p]=0;
            }
            else 
            {
                ImgYmod[p] = (ImgY[p]+k <= 255) ? ImgY[p]+k : 255;
            }
        }
    }

    ecrire_image_pgm("Ymodif.pgm", ImgYmod,  nH, nW);

    free(ImgY); free(ImgYmod);

    return 0;
}