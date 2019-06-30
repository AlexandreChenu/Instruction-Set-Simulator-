//
//  main.c
//  brouillon
//
//  Created by AlexandreChenu on 15/11/2017.
//  Copyright © 2017 AlexandreChenu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonction_ISS.h"
#include "fonction_operation.h"
#include "Cache_memory.h"
#define NumRegs 32
#define Nbr_label 20
#define TailleMemoire 1024
#define TAILLE_MAX 100
#define Nbr_set_cache 4


/* _____________________________________________________________________________________________________*/

//Définition du main

int main(int argc, const char * argv[]) {
    
    //Initialisation
    
    time_t start_t, end_t;
    double diff_t;
    
    time(&start_t); //début du calcul de temps écoulé
    
    int n = 0;
    
    int nbr_cycle = 0; //Initialisation nombre de cycle
    int *p_nbr_cycle = &nbr_cycle;
    
    int regs[NumRegs]; // Mémoire de registre
    initRegs(regs); // Initialisation mémoire de registre
    
    struct dictionnaire dico[25]; //Dictionnaire
    initDico(dico); // Initialisation du dictionnaire
    
    struct dictionnaire_label dico_label[20]; //Dictionnaire label/adresse
    initLabel(dico_label);
    int num_label = 0;
    int *p_num_label = &num_label;
    
    // définition de la mémoire et du cache
    struct Memory donnee[TailleMemoire];
    initData1(donnee);

    struct Cache_memory cache[Nbr_set_cache];
    initCache(cache);
    
    int data[1500]; //Mémoire de données
    initData(data); //Initialisation mémoire de données
    
    struct decoupage resultat; // Définition d'une structure de découpage
    
    struct  FieldInstruction trame_binaire; // Définition d'une structure de trame binaire
    
    int running = 1;//Initialisation de la boucle
    int *p_running = &running; //Pointeur vers la variable running
    
    int ligne_instruction = 0;//Initialisation de l'adresse de la mémoire d'instruction
    int *p_ligne_instruction = &ligne_instruction; //Pointeur vers la variable add

/*_____________________________________________________________________________________________________*/
    
    //Corps du programme
    
    char nomFichier[] ="/Users/AlexandreChenu/Documents/workspace_Xcode/brouillon/brouillon/suite_syracuse.txt";
    
    detect_label(nomFichier, dico_label);
    
    //printf("voici les labels : %s_%d,%s_%d,%s_%d\n",dico_label[0].name_label,dico_label[0].adresse,dico_label[1].name_label,dico_label[1].adresse,dico_label[2].name_label,dico_label[2].adresse);
    
    while(running == 1){
    
        
        // Exemple de texte assembleur
        
        char nom[] ="/Users/AlexandreChenu/Documents/workspace_Xcode/brouillon/brouillon/suite_syracuse.txt";
        
        char phrase [100];
    
        //Lecture du fichier .txt
        
        
        strcpy(phrase,Traitement(nom , ligne_instruction));
        
    
        //Decoupage du texte assembleur

        
        resultat = analyse(phrase,dico_label,p_num_label,p_ligne_instruction);
        
        
        //printf("opération : %s\nregistres : %d,%d,%d\nimmédiat : %d\nadresse : %d\n",resultat.instr,resultat.reg[0],resultat.reg[1],resultat.reg[2],resultat.imm,resultat.adresse);
    
        
        //Ecriture du texte binaire

        
        trame_binaire = identification_bin(resultat.instr, resultat.reg, resultat.adresse, resultat.imm, dico);
        
        //printf("\nopé bin : %s\narguments : %s,%s,%s \nimm binaire : %s\nadresse : %s\n",trame_binaire.instrNum, trame_binaire.Arg_1, trame_binaire.Arg_2, trame_binaire.Arg_3 ,trame_binaire.imm, trame_binaire.Adresse);
        
        
        //Ecriture de la trame binaire
    
        
        printf("Ob%s\n",full_trame_bin(trame_binaire));

        
        //Evaluation de la trame
    
        
        evaluation(regs,donnee,cache,p_ligne_instruction,p_running,trame_binaire,p_nbr_cycle);
        
        ligne_instruction ++;
        
        n++;
    
    }
    
    //Tests de fonctionnement
    
    //Calcul de performance
    
    time(&end_t); //fin du calcul de temps écoulé
    diff_t = difftime(end_t,start_t);
    

    printf("La performance de l'ISS est de : %f\n", 1000*nbr_cycle/diff_t);
    
    
    //Affichage des registres pour vérification
    
    
    //for (dec=0;dec < NumRegs;dec++){
        
        //printf("registre %d : %d\n",dec, regs[dec]);}
    
    
    //Affichage des blocks de la mémoire cache pour vérification
    
    
    //for (dec=0;dec <Nbr_set_cache;dec++){
        
        //printf("cache no :%d\nblock %d :%d\nblock %d:%d\n",dec,1,cache[dec].block[0],2,cache[dec].block[1]);}

    
}
/* _____________________________________________________________________________________________________*/

