#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char imgLue[250]; char histoOut[250];
    int nH, nW, taille;

    if (argc != 2) 
    {
       printf("Usage: ImageIn.ppm\n"); 
       exit (1) ;
    }

    sscanf(argv[1],"%s", imgLue) ;

    lire_nb_lignes_colonnes_image_ppm(imgLue, &nH, &nW);
    taille = nH * nW;
    int taille3 = taille*3;

    OCTET *ImgIn;
    allocation_tableau(ImgIn, OCTET, taille3);
    lire_image_ppm(imgLue, ImgIn, taille3);

    int histoR[255]; int histoG[255]; int histoB[255];
    for (int i=0; i<255; i++){ 
        histoR[i]=0;
        histoG[i]=0;
        histoB[i]=0; 
    }

    for(int i=0; i<taille3; i=i+3)
    {
        histoR[ImgIn[i]] += 1;
        histoG[ImgIn[i+1]] += 1;
        histoB[ImgIn[i+2]] += 1;
    }

    FILE *fR, *fG, *fB;
    fR = fopen("r.txt", "wb"); fG = fopen("g.txt", "wb"); fB = fopen("b.txt", "wb");
    if( fR == NULL || fG == NULL || fB == NULL )
    {
        printf("\nPas d'acces en ecriture sur l'image %s \n", histoOut);
        exit(EXIT_FAILURE);
    }
    else
    {
        for(int i=0; i<255; i++)
        {
            fprintf(fR, "%d %d\n", i, histoR[i]);
            fprintf(fG, "%d %d\n", i, histoG[i]);
            fprintf(fB, "%d %d\n", i, histoB[i]);
        }
        fclose(fR); fclose(fG); fclose(fB);
    }

    free(ImgIn);
    return 0;
}