#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, taille;
    
    if (argc != 3) 
        {
        printf("Usage: ImageIn.ppm ImageOut.pgm\n"); 
        exit (1) ;
        }
    
    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite);

    OCTET *ImgIn, *ImgOut;
    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    taille = nH * nW;
    int taille3 = taille * 3;

    allocation_tableau(ImgIn, OCTET, taille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, taille);

    for(int i=0; i<taille3; i=i+3)
    {
        int r = ImgIn[i]; 
        int g = ImgIn[i+1]; 
        int b = ImgIn[i+2];
        
        ImgOut[i/3]= int(0.299*r + 0.587*g + 0.114*b);
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn); free(ImgOut);

    return 0;
}