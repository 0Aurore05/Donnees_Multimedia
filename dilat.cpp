#include <stdio.h>
#include "image_ppm.h"

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

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);


    for (int i=0; i < nH; i++)
    {
        for (int j=0; j < nW; j++)
        {
            int p = i*nW+j;
            ImgOut[p] = ImgIn[p];
            int h = (i-1)*nW+j;
            int b = (i+1)*nW+j;
            int d = (i*nW)+j+1;
            int g = (i*nW)+j-1;

            if(i>=0 && ImgIn[h]==255) ImgOut[p]=255;
            else if(i<nH-1 && ImgIn[b]==255) ImgOut[p]=255;
            else if(j>=0 && ImgIn[g]==255) ImgOut[p]=255;
            else if(j<nW-1 && ImgIn[d]==255) ImgOut[p]=255;
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn); free(ImgOut);

    return 1;
}
