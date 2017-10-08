#ifndef HUFFMAN_FONCTION_H
#define HUFFMAN_FONCTION_H

typedef struct NOEUD NOEUD;
struct NOEUD
{
   int parent;
   int filsD,filsG;
   float frequence;
};
void initialisation(void);
void compteuroccurence(char *fichier, int *tabOccur, int *nbCaractere);
int constArbre();
void parcours(int noeudCourant,char* encodage);
unsigned char stringToBinary(char* str, int len);
void compression(char *fsource,int *tailleFcomp);
char * decToBin(int n);
void ReverseStr(char *machaine);
void decompression(char *fichier);
#endif 
