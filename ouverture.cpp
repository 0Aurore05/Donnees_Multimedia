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

OCTET* erosion(OCTET* ImgIn, OCTET* ImgOut, int nW, int nH)
{
    for (int i=0; i < nH; i++)
    {
        for (int j=0; j < nW; j++)
        {
            int p = indice(i,j,nW,nH);

            int h = (i-1)*nW+j;
            int b = (i+1)*nW+j;
            int d = (i*nW)+j+1;
            int g = (i*nW)+j-1;

            if(i>0 && ImgIn[h]==0) ImgOut[p]=0;
            else if(i<nH-1 && ImgIn[b]==0) ImgOut[p]=0;
            else if(j>0 && ImgIn[g]==0) ImgOut[p]=0;
            else if(j<nW-1 && ImgIn[d]==0) ImgOut[p]=0;
            else ImgOut[p]=255;
        }
    }
    return ImgOut;
}

OCTET* dilatation(OCTET* ImgIn, OCTET* ImgOut, int nW, int nH)
{    
    for (int i=0; i < nH; i++)
    {
        for (int j=0; j < nW; j++)
        {
            int p = indice(i,j,nW,nH);

            int h = (i-1)*nW+j;
            int b = (i+1)*nW+j;
            int d = (i*nW)+j+1;
            int g = (i*nW)+j-1;

            if(i>0 && ImgIn[h]==255) ImgOut[p]=255;
            else if(i<nH-1 && ImgIn[b]==255) ImgOut[p]=255;
            else if(j>0 && ImgIn[g]==255) ImgOut[p]=255;
            else if(j<nW-1 && ImgIn[d]==255) ImgOut[p]=255;
            else ImgOut[p]=0;
        }
    }
    return ImgOut;
}

//##########################################################################################

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm\n"); 
       exit (1) ;
     }
   
    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite);

    OCTET *ImgIn, *ImgOut, *ImgTemp;
   
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
  
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);
    allocation_tableau(ImgTemp, OCTET, nTaille);
/*
    for(int i=0; i<nH; i++) //initialisation
    {
        for(int j=0; j<nW; j++)
        {
            int p = indice(i, j, nW, nH);
            ImgOut[p] = ImgIn[p];
            ImgTemp[p] = ImgIn[p];
        }
    }
*/
    ImgTemp = dilatation(ImgIn, ImgTemp, nW, nH);
    ImgOut = erosion(ImgTemp, ImgOut, nW, nH);

    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn); free(ImgOut); free(ImgTemp);

    return 0;
}
