#!/usr/bin/python

import sys,os,re,getpass

username = getpass.getuser()
print "\n\n|******  HUFFMAN L2 INFO MONTPELLIER UM2 (DIALLO ABDOULAYE) ******|\n\n\tBonjour !",username,"\n\nQue Desirez Vous faire ? \n\n1- Compresser un Fichier \n2- Decompresser un fichier\n"

choix = input("Rentrez le numero : ")

fichier=raw_input("Rentrez le nom du fichier a compresser/decompresser: ")


def huffm(fichier,choix):

    if (choix == 1):

        if os.path.isfile(fichier):
            comp=os.system("./huffman "+ fichier +" "+str(choix))

            #elif os.path.isdir(fichier):

            #	for files in os.listdir(fichier):
            #		huffm(os.path.join(fichier,files),choix)
        else : print "Rentrez le nom d'un fichier Merci"

    elif choix == 2:

        if os.path.isfile(fichier):

            exp=r"^f"
            res=re.search(exp,fichier)
            if res:
                decomp=os.system("./huffman "+ fichier +" "+str(choix))
            else: print "Le fichier n'as pas ete compresse au prealable "

        else : print "Rentrez le nom d'un fichier"
    else : print "Rentrez le numero 1 ou 2"


huffm(fichier,choix)
