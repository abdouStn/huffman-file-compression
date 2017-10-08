#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman_fonctions.h"



NOEUD Arbre[511];
unsigned int NbNoeuds=256;
char codes[256][256];


void initialisation(void)
 {
  int i;
  for (i=0;i<511;i++){
	Arbre[i].frequence = 0;
	Arbre[i].parent = -1;
	Arbre[i].filsD = -1;
	Arbre[i].filsG = -1;
	}
 }

void compteuroccurence(char *fichier, int *tabOccur, int *nbCaractere)
{
  int i;
  *nbCaractere = 0;
  int caractere=0;
  FILE *file = fopen(fichier, "r");



   if( file == NULL)
    {
      printf("\nfichier impossible a ouvrir\n");
      exit(EXIT_FAILURE);
    }

   for(i=0;i<256;i++) tabOccur[i]= 0; //initialisation de chaque case du tableau des occurances a 0

  while((caractere=fgetc(file)) != EOF)
	{
	     //printf("putin de carac vaut %d\n",caractere);
	     (*nbCaractere)++;
	     tabOccur[caractere]++;

	}
   fclose(file);
	// printf("nbcaractere Totale= %d ", *nbCaractere);
	
   // calcul de frequences:	
  int j=0;  
  for(j=0;j<256;j++)
    {
      Arbre[j].frequence = (float)tabOccur[j]/(float)(*nbCaractere); 

      if(Arbre[j].frequence != 0) printf("caract [%c] a pour frequence : %f \t et pour nbrOccurence: %d\n",j,Arbre[j].frequence,tabOccur[j]);
    }

}

 /****** Etape 2 construction de l'arbre ******/

int constArbre()
{
  int min1=-1;
  int min2=-1;
  int i;

  do   // Recherche des deux min
  {
	  min1 = min2 = -1;

	  for (i=0; i<NbNoeuds;i++)
		if((Arbre[i].frequence>0 && Arbre[i].parent == -1 ) && ((min1==-1) || (Arbre[i].frequence<Arbre[min1].frequence))) 
		     {
			min1 = i;
		      }

	  for (i=0; i<NbNoeuds;i++)
		if((Arbre[i].frequence>0 && Arbre[i].parent == -1 ) && ((min2==-1) || (Arbre[i].frequence<Arbre[min1].frequence)) && (i!=min1 ))
		  {
		    min2 = i;
		  }

	 	if ((min1>=0) && (min2 >= 0))
	 	{
		  // fusion de noeuds les plus faible en frequence/occurrence
		    Arbre[NbNoeuds].parent = -1;
		    Arbre[NbNoeuds].filsG = min1;
		    Arbre[NbNoeuds].filsD = min2;
		    Arbre[NbNoeuds].frequence = Arbre[min1].frequence + Arbre[min2].frequence; // somme des frequences
		    Arbre[min1].parent = NbNoeuds;
		    Arbre[min2].parent = NbNoeuds;
		    NbNoeuds++;
		}


  }	while ((min1>=0) && (min2 >= 0)); // tant qu'on a pas atteint la racine
  
	/*int a=0;
	for(a=0;a<NbNoeuds;a++)
		printf(" caractere %d: parent: %d FG: %d FD: %d frequence: %f \n", a,Arbre[a].parent,Arbre[a].filsG,Arbre[a].filsD,Arbre[a].frequence);*/

  return NbNoeuds-1; // renvoie la racine ainsi créée
  
}

 /************************* Etape 3   ****************************************/

void parcours(int noeudCourant,char* encodage) // fonction recursive
{

	if  (Arbre[noeudCourant].filsG == -1)     // si c'est une feuille
	{
		strcpy(codes[noeudCourant],encodage);   //stocker encodage dans codes[256][256]
		printf("noeudcourant : %d\t encodage: %s\n",noeudCourant,encodage);
	}
	else
	{

		int len = strlen(encodage);

		//rajouter 0 si on va a gauche

		encodage[len]='0';
		encodage[len+1]='\0';
	 	parcours(Arbre[noeudCourant].filsG, encodage);

	 	//rajouter 1 si on va a droite

	 	encodage[len]='1';
		encodage[len+1]='\0';
	 	parcours(Arbre[noeudCourant].filsD, encodage);
	}

}

/* *************************** Etape 4  réencodage ***************************** */

unsigned char stringToBinary(char* str, int len)  // convertie une chaine en binaire
 {
  unsigned char code = 0;
  int i;

	 for(i=0;i<len;i++)
	 	{
		 	 code <<=1;  // decalage d un cran vers la droite
		 	 code |= str[i] -'0';  // ou binaire logique
	 	 }
	  for ( ;i<8; i++)
	  	code <<= 1;
	  	
  return (code);
 }

/* ********************************************************************** */

  void compression(char *fsource,int *tailleFcomp)  // scan du fichier
  {

    char buffer[263]="";
    char caracterelu;
    int i=0;
    char dernierCaractere[9] = {0};
    dernierCaractere[8] = '\0';

    FILE *fichiercomp= fopen("fcompresse", "wb");
    if (fichiercomp==NULL)
         { printf("ecriture impossible");
           exit (0);
           }
    else {

    	/* Boucler sur les caracteres de fichiersrc
    		recuperer le code huffman du cararctere lu
    		inserer le code huffman dans le buffer de travail
    		tant que longueur du buffer de travail >= 8
    			encoder le premier octet
    			ecrire l'octet dans fichiercomp
    			supprimer les 8 premiers caracteres du buffer de travail

  	Ecire les chars restants eventuels du buffer de travail*/


		printf("\n\tATTENTION DEBUT DE LA COMPRESSION...\n");
  		FILE *fichiersrc = fopen(fsource,"rb");

		if (fichiersrc==NULL)
	         { printf("lecture fichier impossible");
	           exit (0);
	           }

		else
		{
			fprintf(fichiercomp,"%c",36); // delimiter debut table de compression dans le fichier compressé ($)
			fprintf(fichiercomp,"%c",'\n');
			 while(i<256)// ecriture de notre tab de compress
				{
				  if(Arbre[i].frequence != 0)
				    {
				      fprintf(fichiercomp,"%d ",i);
				      fprintf(fichiercomp,"%s",codes[i]);
				      fprintf(fichiercomp,"%c",'\n');
				    }
				  i++;
				  }
			fprintf(fichiercomp,"%c",36); // delimiteur fin de table compression dans le fichier compressé ($)
			fprintf(fichiercomp,"%c",'\n');

			while ( (caracterelu = fgetc(fichiersrc)) != EOF)
				{
				//printf("%c\n",caracterelu);
				

				strcat(buffer, codes[caracterelu]); // concatener

				//printf("buffer: %s\n",buffer);

				while (strlen(buffer) >=8)
					{
					//printf("conversion de buffer en bin : %c\n",stringToBinary(buffer,8));
					fputc(stringToBinary(buffer,8),fichiercomp);
					strcpy(buffer, buffer+8);


					}
		 		}


			  /*s'il reste des caracteres dans le buffer :*/
			for(i=0; i < strlen(buffer); i++)
				 dernierCaractere[i] = buffer[i];


			fputs(dernierCaractere,fichiercomp);

			
		}


fseek(fichiercomp,0,SEEK_END);
*tailleFcomp=ftell(fichiercomp);

fclose(fichiersrc);
fclose(fichiercomp);
	printf("\n!!!!!  BINGO ... COMPRESSION REALISEE  !!!!!\n");
 }
}

/* ****************************************************************************** *

                                DECOMPRESSEUR

* ****************************************************************************** */

char * decToBin(int n)
{
  char *chaine = malloc(8 * sizeof(char*));
  int str = n,k=0;
  while(str > 0)
    {
      if (str % 2 == 0)
	{
	  strcat(chaine,"0");
	}
      else strcat(chaine,"1");
      str=str/2;
      k++;
    }
  while(k<8)  // on complete le manque eventuel par des 0
    {
      strcat(chaine,"0");
      k++;
    }
  *(chaine+k)= '\0';    // caractere de fin de chaine
  
  
  return chaine;
}

/* ****************************************************************************** */
void ReverseStr(char *machaine) // renverse une chaine de caractere
{
    int i = 0, j = strlen(machaine) - 1;
    char tmp;

    while(i < j){
        tmp= machaine[i];
        machaine[i] = machaine[j];
        machaine[j] = tmp;
        i++;
        j--;
    }
}

/* ****************************************************************************** */
void decompression(char *fichier)
{
   char NOM_F[100]="fDecomp";
   int i=0,CaractBin=0;
   char delimiteur[100]="";
   char tabc[256][256]={};

  FILE* file =fopen(fichier,"r");
  if(file == NULL)
    {
      printf("ouverturne du fichier impossible\n");
      exit(EXIT_FAILURE);
    }
  else
    {
	fscanf(file,"%s",delimiteur);  // recupere le delimiteur $ dans le fichier compressé
	
	//printf("le delimiteur : %s\n",delimiteur);
	int EDT=1;
	
       while (EDT!=0)
	{
	  char indiceChar[1000],codeHuff[1000];
	  int indiceInt=0;
	  fscanf(file,"%s ",indiceChar);
	  
	  EDT=strcmp(indiceChar,delimiteur); 
	  if(EDT==0)   // si l'indice est egale au delimiteur on sort de la boucle
	    {
	      break;
	    }
	  else
	    {
	      fscanf(file," %s",codeHuff);
	      indiceInt =atoi(indiceChar);
	      strcat(tabc[indiceInt],codeHuff); // reconstruire la table de compression
	    }
	  
	}
}
      
 ///**** CREATION FICHIER QUI CONTIENTDRA LE CODE HUFF EQUIVALENT A CHAQUE CARACTERE COMPRESSE LU ***/////
	
      FILE * fichierBin = fopen("fichierBin","w+");
      if(fichierBin==NULL)
	{
	  printf("ouverturne du fichier impossible\n");
	  exit(EXIT_FAILURE);
	}
      else
	{
	  
	  int nb=0;
	  while((nb=fgetc(file))!=EOF)
	    {
	      
	      char *tt;
	      tt=decToBin(nb);
	      printf("\nencodage : %s", tt);
	      ReverseStr(tt);
	      printf("\nrvrse encodage : %s", tt);
	      fprintf(fichierBin,"%s",tt);	      
	    } 
	  rewind(fichierBin);
	  while(fgetc(fichierBin)!=EOF)
	    {
	      CaractBin++;
	    }
	  rewind(fichierBin);
	  char *buffer=malloc(sizeof(char*));
	  char NomDecomp[]="(d)";                 // pour differencier le fichier compressé
	  strcat(NomDecomp,NOM_F);
	  FILE* fileDecomp=fopen(NomDecomp,"w+");
	  int d=0;
	
	 
	  if( fileDecomp == NULL)
	  {
	  	printf(" Probleme ecriture de fichier\n");
	  	exit(2);
	  
	  }
	  else
	  {
	  	/**** DEBUT DE LA DECOMPRESSION ****/
	 
	  	// ON LIT NOTRE FICHIER BIN CREER
		printf("\n\tDecompression de %s en cours .....\n",NOM_F);
	  	while((d=fgetc(fichierBin))!=EOF )
	    	{
	    		
	      		i=0;
	      		char o=(char)d;
	      		char temp[2];
	      		temp[0]=o;
	      		temp[1]='\0';
	      		int trouve=1;
	      		strcat(buffer,temp);
	      		while(trouve!=0 && i<256)
			{
			  trouve=strcmp(buffer,tabc[i]);
			  if (trouve==0)
			  {
		      		break;
		    	  }
		  		i++;	      
			}
			//printf("trouve : %d\n",trouve);
	      		if(trouve==0)
			{
			  fprintf(fileDecomp,"%c",i);   // reconstitution du fichier original
			  free(buffer);
			  buffer=malloc(sizeof(char*));  // on formate notre buffer et on le recrée pour continuer la boucle
		  	
			}
	      		
	    	}
	    
	  	free(buffer);
	  	fclose(fileDecomp);
	   }
	
      fclose(fichierBin);  // fermeture de fichiers et suppression du fichier temporaire 
      remove("fichierBin");
      printf("\n!!!!  DECOMPRESSION DE %s REALISEE !!!!! \n\n",NOM_F);
    }
  fclose(file);

 
  
}
