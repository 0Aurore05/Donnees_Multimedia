// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

int indice(int i, int j, int nW, int nH)
{
    if(i>=nW) printf("i trop grand");
    if(i<0) printf("i trop petit");
    if(j>=nH) printf("j trop grand");
    if(j<0) printf("j trop petit");
    return i*nW+j;
}

int main(int argc, char* argv[])
{
    char cNomImgSeuil[250], cNomImgDilat[250];
    int nH, nW, nTaille;
  
    if (argc != 3) 
     {
       printf("Usage: ImageSeuil.pgm ImageDilat.pgm\n"); 
       exit (1) ;
     }
   
    sscanf (argv[1],"%s",cNomImgSeuil) ;
    sscanf (argv[2],"%s",cNomImgDilat);

    OCTET *ImgSeuil, *ImgDilat, *ImgOut;
   
    lire_nb_lignes_colonnes_image_pgm(cNomImgSeuil, &nH, &nW);
    nTaille = nH * nW;
  
    allocation_tableau(ImgSeuil, OCTET, nTaille);    
    allocation_tableau(ImgDilat, OCTET, nTaille);
    lire_image_pgm(cNomImgSeuil, ImgSeuil, nH*nW);
    lire_image_pgm(cNomImgDilat, ImgDilat, nH*nW);
    
    allocation_tableau(ImgOut, OCTET, nTaille);


    for (int i=0; i < nH; i++)
    {
        for (int j=0; j < nW; j++)
        {
            int p = indice(i,j,nW,nH);
            if(ImgSeuil[p]==255 && ImgDilat[p]==255) ImgOut[p]=255; //les deux appartiennent au fond
            else if(ImgSeuil[p]==0 && ImgDilat[p]==0) ImgOut[p]=255;
            else ImgOut[p] = 0;
        }
    }

    ecrire_image_pgm("segmentation.pgm", ImgOut,  nH, nW);
    free(ImgSeuil); free(ImgDilat); free(ImgOut);

    return 1;
}
