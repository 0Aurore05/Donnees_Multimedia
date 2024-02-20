#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, taille, Sr, Sg, Sb;
  
    if (argc != 6) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm Sr Sg Sb \n"); 
       exit (1) ;
     }
   
    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite);
    sscanf (argv[3],"%d",&Sr);
    sscanf (argv[4],"%d",&Sg);
    sscanf (argv[5],"%d",&Sb);

    OCTET *ImgIn, *ImgOut;
    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    taille = nH * nW;

    int taille3 = taille * 3;
    allocation_tableau(ImgIn, OCTET, taille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, taille3);

    	
    for (int i=0; i < taille3; i+=3)
    {
        int r = ImgIn[i]; 
        int g = ImgIn[i+1]; 
        int b = ImgIn[i+2];
        if(r<Sr) ImgOut[i] = 0; else ImgOut[i] = 255;
        if(g<Sg) ImgOut[i+1] = 0; else ImgOut[i+1] = 255;
        if(b<Sb) ImgOut[i+2] = 0; else ImgOut[i+2] = 255;
    }

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}

