#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char nomImgY[250], nomImgCb[250], nomImgCr[250]; 
    int nH, nW, taille;
    
    if (argc != 4) 
        {
        printf("Usage: ImageY.pgm ImageCb.pgm ImageCr.pgm\n"); 
        exit (1) ;
        }
    
    sscanf (argv[1],"%s",nomImgY);
    sscanf (argv[2],"%s",nomImgCb);
    sscanf (argv[3],"%s",nomImgCr);

    OCTET *ImgY, *ImgCb, *ImgCr, *ImgRgb, *ImgR, *ImgG, *ImgB;
    lire_nb_lignes_colonnes_image_pgm(nomImgY, &nH, &nW);
    taille = nH * nW;
    int taille3 = taille * 3;
    //faire truc de contrôle pour le nb de lignes / colonnes des autres images 

    allocation_tableau(ImgY, OCTET, taille);
    lire_image_pgm(nomImgY, ImgY, taille);
    allocation_tableau(ImgCb, OCTET, taille);
    lire_image_pgm(nomImgCb, ImgCb, taille);
    allocation_tableau(ImgCr, OCTET, taille);
    lire_image_pgm(nomImgCr, ImgCr, taille);
    allocation_tableau(ImgRgb, OCTET, taille3);
    allocation_tableau(ImgR, OCTET, taille3);
    allocation_tableau(ImgG, OCTET, taille3);
    allocation_tableau(ImgB, OCTET, taille3);

    for(int i=0; i<taille3; i=i+3)
    {
        int p = i/3;
        int r = int( int(ImgY[p]) + 1.402*( int(ImgCr[p])-128));
        int g =  int( int(ImgY[p]) - 0.34414*( int(ImgCb[p])-128) - 0.714414*(int(ImgCr[p])-128));
        int b = int( int(ImgY[p]) + 1.772*(int(ImgCb[p])-128));

        if(r<0) r=0; 
        if(r>255) r=255;
        if(g<0) g=0;
        if(g>255) g=255;
        if(b<0) b=0;
        if(b>255) b=255;

        ImgRgb[i] = r;
        ImgRgb[i+1] = g;
        ImgRgb[i+2] = b;

        ImgR[i] = r; ImgR[i+1] = 0; ImgR[i+2] = 0;

        ImgG[i] = 0; ImgG[i+1] = g; ImgG[i+2] = 0;

        ImgB[i] = 0; ImgB[i+1] = 0; ImgB[i+2] = b;
    }

    ecrire_image_ppm("rgb.ppm", ImgRgb,  nH, nW);
    ecrire_image_ppm("r.ppm", ImgR,  nH, nW);
    ecrire_image_ppm("g.ppm", ImgG,  nH, nW);
    ecrire_image_ppm("b.ppm", ImgB,  nH, nW);

    free(ImgRgb); free(ImgR); free(ImgG); free(ImgB); 
    free(ImgY); free(ImgCb); free(ImgCr);

    return 0;
}