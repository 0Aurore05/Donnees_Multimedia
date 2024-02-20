#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250];
  char cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm\n"); 
       exit (1) ;
     }
   
   sscanf(argv[1],"%s",cNomImgLue) ;
   sscanf(argv[2], "%s", cNomImgEcrite);

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

            if(i>0 && j>0 && i<nH-1 && j<nW-1) //si pas au bord de l'image
            {
                int h = (i-1)*nW+j;
                int b = (i+1)*nW+j;
                int d = (i*nW)+j+1;
                int g = (i*nW)+j-1;
                int hd = (i-1)*nW+(j+1);
                int hg = (i-1)*nW+(j-1);
                int bd = (i+1)*nW + (j+1);
                int bg = (i+1)*nW + (j-1);

                int v = ImgIn[p]+ImgIn[h]+ImgIn[b]+ImgIn[g]+ImgIn[d]+ImgIn[hd]+ImgIn[hg]+ImgIn[bd]+ImgIn[bg];
                ImgOut[p] = int(v/9);
            }       
            else ImgOut[p]=ImgIn[p];
        }
    }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}
