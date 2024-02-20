#include <stdio.h>
#include "image_ppm.h"

bool voisin255(OCTET* img, int i, int j, int nW)
{
    int p = i*nW+j;

    int h = img[(i-1)*nW+j];
    int b = img[(i+1)*nW+j];
    int d = img[(i*nW)+j+1];
    int g = img[(i*nW)+j-1];
    int hd = img[(i-1)*nW+(j+1)];
    int hg = img[(i-1)*nW+(j-1)];
    int bd = img[(i+1)*nW + (j+1)];
    int bg = img[(i+1)*nW + (j-1)];

    return (h==255 || b == 255 || g==255 || d==255 || hd==255 || hg==255 || bd==255 || bg==255);
}

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, Sb, Sh;
    
    if (argc != 5) 
        {
        printf("Usage: ImageIn.pgm ImageOut.pgm SeuilBas SeuilHaut \n"); 
        exit (1) ;
        }
    
    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite);
    sscanf (argv[3],"%d",&Sb);
    sscanf (argv[4],"%d",&Sh);

        if(Sb>=Sh)
        {
            perror("le seuil bas doit être inférieur au seuil haut bolosse");
            int tmp = Sh;
            Sh = Sb;
            Sb = tmp;
        }

    OCTET *ImgIn, *ImgOut, *ImgTemp;
    
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
  
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);
    allocation_tableau(ImgTemp, OCTET, nTaille);

    for (int i=0; i < nH; i++)
    {
        for (int j=0; j < nW; j++)
        {
            int p = i*nW+j;
            if ( ImgIn[p] <= Sb) 
            {
                ImgTemp[p]= 0;
            }
            else if( ImgIn[p] >= Sh)
            {
                ImgTemp[p]= 255;
            }
        }
    }

    for (int i=0; i < nH; i++)
    {
        for (int j=0; j < nW; j++)
        {
            int p = i*nW+j;
            if(ImgTemp[p]>Sb && ImgTemp[p]<Sh)
            {
                if(voisin255(ImgTemp, i, j,nW))
                {
                    ImgOut[p]=255;
                }
                else {
                    ImgOut[p]=0;
                }
            }
            else ImgOut[p] = ImgTemp[p];
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);   

    free(ImgIn); free(ImgOut); free(ImgTemp);

    return 1;
}
