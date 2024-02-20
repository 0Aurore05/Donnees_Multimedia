#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250];
    int nH, nW, taille;
    
    if (argc != 2) 
        {
        printf("Usage: ImageIn.ppm\n"); 
        exit (1) ;
        }
    
    sscanf (argv[1],"%s",cNomImgLue) ;

    OCTET *ImgIn, *ImgY, *ImgCb, *ImgCr;
    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    taille = nH * nW;
    int taille3 = taille * 3;

    allocation_tableau(ImgIn, OCTET, taille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgY, OCTET, taille);
    allocation_tableau(ImgCb, OCTET, taille);
    allocation_tableau(ImgCr, OCTET, taille);

    for(int i=0; i<taille3; i=i+3)
    {
        int r = ImgIn[i]; 
        int g = ImgIn[i+1]; 
        int b = ImgIn[i+2];
        
        ImgY[i/3]= int(0.299*r + 0.587*g + 0.114*b);
        ImgCb[i/3]= int(-0.1687*r - 0.3313*g + 0.5*b + 128);
        ImgCr[i/3]= int(0.5*r - 0.4187*g - 0.0813*b + 128);
    }

    ecrire_image_pgm("Y.pgm", ImgY,  nH, nW);
    ecrire_image_pgm("Cb.pgm", ImgCb,  nH, nW);
    ecrire_image_pgm("Cr.pgm", ImgCr,  nH, nW);

    free(ImgIn); free(ImgY); free(ImgCb); free(ImgCr);

    return 0;
}