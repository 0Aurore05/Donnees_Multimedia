// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"

void xy(int i, int* x, int* y, int nW, int nH)
{
    *x = int(i%(nW*3)); 
    *y = int(i/(nW*3));
}

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);
	
    for (int i=0; i < nTaille3; i+=3)
    {
        int x,y;
        xy(i,&x,&y,nW,nH);
    
        if(x>0 && x<nH*3-1 && y>0 && y<3*nW-1) //si pas au  bord de l'image
        {
            int r = ImgIn[i];
            int rH = ImgIn[i-nW*3];
            int rB = ImgIn[i+nW*3];
            int rD = ImgIn[i+3];
            int rG = ImgIn[i-3];

            int g = ImgIn[i+1];
            int gH = ImgIn[i+1-nW*3];
            int gB = ImgIn[i+1+nW*3];
            int gD = ImgIn[i+1+3];
            int gG = ImgIn[i+1-3];

            int b = ImgIn[i+2];
            int bH = ImgIn[i+2-nW*3];
            int bB = ImgIn[i+2+nW*3];
            int bD = ImgIn[i+2+3];
            int bG = ImgIn[i+2-3];

            int vR = (r+rH+rB+rD+rG)/5;
            int vG = (g+gH+gB+gD+gG)/5;
            int vB = (b+bH+bB+bD+bG)/5;
        

            ImgOut[i] = vR;
            ImgOut[i+1] = vG;
            ImgOut[i+2] = vB;
        }
        else {
        
            ImgOut[i]=ImgIn[i];
            ImgOut[i+1]=ImgIn[i+1];
            ImgOut[i+2]=ImgIn[i+2];
        }
    }

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
