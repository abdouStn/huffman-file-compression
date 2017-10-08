#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman_fonctions.h"

int main(int argc,char **argv)
{
   char encodage[256]="";
   int TableauOcc[256];
   int caracTotal=0;
   int tailleFcomp=0;
   int racine = 0;

       if(argc < 3)
	 	{
	 	 puts("\nERREUR ! Veuillez Respecter La syntaxe : \"./huffman nomFichier 1 ou 2\"\n");
	 	 return (-1); 
	 	}

 	int choix=atoi(argv[2]);
 	
	if (choix==1)
	  {
	   initialisation();
	   char NOM_FICH[1000];
	   strcpy(NOM_FICH,argv[1]);
	   
	   compteuroccurence(argv[1],TableauOcc,&caracTotal);



	   racine=constArbre();
	   //printf("La racine de l'arbre a pour ind: %d\n", racine);
	   parcours(racine,encodage);
	   /*int i;
	   for (i=0;i<strlen(encodage);i++)
		printf("%c \t",encodage[i]);*/

	   compression(argv[1],&tailleFcomp);
	 

	
		printf(" \n!!!! INFORMATIONS SUR LA COMPRESSION !!!!\n\n");
		printf("\tNom du fichier qui a été compressé : %s\n\n",NOM_FICH); 
		printf("\tTaille Fichier Compressé : %d octets\n\n",tailleFcomp);
	  }
        else if (choix==2)
	  {
 		decompression(argv[1]);	  
	  }
	else printf("Veuillez Rentrez 1 ou 2 svp !!!\n\n");
	
return 0;
}
