#include <math.h>
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

    /*
        gradient :
        ...  ...  ...
        
        ...  p  ->...
             \/
        ...  ...  ... 
    
        Dx = 
        Dy = 
        D = sqrt(Dx² + Dy²)
    */
    for (int i=0; i < nH; i++)
    {
        for (int j=0; j < nW; j++)
        {
            int p = i*nW+j;
            if(i<nH-1 && j<nW-1)
            {
                int droite = (i*nW)+j+1;
                int bas = (i+1)*nW+j;

                int Di = ImgIn[bas]-ImgIn[p];
                int Dj = ImgIn[droite]-ImgIn[p];
                ImgOut[p] = int(sqrt(Di*Di + Dj*Dj));
            }
            else 
            {
                ImgOut[p] = 0;
            }
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn); free(ImgOut);

    return 1;
}
