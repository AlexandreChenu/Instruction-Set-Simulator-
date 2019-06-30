//
//  fonction_ISS.h
//  brouillon
//
//  Created by AlexandreChenu on 18/02/2018.
//  Copyright © 2018 AlexandreChenu. All rights reserved.
//

#ifndef fonction_ISS_h
#define fonction_ISS_h

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

/*______________________________________________________________________________________________________*/

//Définition des différentes structures

//Structure pour le découpage du code assembleur

typedef struct decoupage dec;
struct decoupage
{
    char instr [7]; //type d'instruction
    int reg[3]; //registre
    int imm;
    int adresse;
    int ad_lab;
};

//Structure pour l'identification du type d'opération

typedef struct dictionnaire dico;
struct dictionnaire
{
    char name_op [7]; //nom de l'instruction
    int eq; //equivalent de son numéro dans le jeu d'instruction
    
};

//Structure pour l'association d'un label à une adresse

typedef struct dictionnaire_label lab;
struct dictionnaire_label
{
    char name_label[10];
    int adresse;
};

//Champs d'instruction en binaire

typedef struct FieldInstruction FieldIn;
struct FieldInstruction
{
    char instrNum[100]; //numéro d'instruction
    char Arg_1[100]   ; //argument 1 qui est très souvent un régistre
    char Arg_2[100]   ;
    char Arg_3[100]   ;
    char Adresse[100] ;
    char imm[100]     ; // nous informe sur la nature de l'argument( registe ou constante)
};
/* _____________________________________________________________________________________________________*/

/* _____________________________________________________________________________________________________*/

//Prototype des fonctions

void detect_label(char NomFichier[],struct dictionnaire_label dic_lab[]);
struct decoupage analyse (char phrase[],struct dictionnaire_label dico_label[],int *num_label,int *adresse);
struct FieldInstruction identification_bin( char op[], int reg[], int imm, int adresse, struct dictionnaire dic[]);
char * Traitement(char NomFichier[], int AdressInstr);
void evaluation( int reg[], struct Memory mem_data[], struct Cache_memory mem_cache[], int *p_ligne_instr, int *p_running, struct FieldInstruction trame_binaire,int *p_nbr_cycle);

void initRegs (int regs[]);
void initDico ( struct dictionnaire dico[]);
void initData (int data[]);
void initLabel (struct dictionnaire_label dico_label[]);

char *full_trame_bin (struct FieldInstruction trame_binaire );

int puiss(int n, int k);
void strinv(char *st);
char *decimalToBinary(int n1, int taille_bin);
char *unsgdDecimalToBinary(int n1, int taille_bin);
int binaryToInt ( char binary[]);


/* _____________________________________________________________________________________________________*/


#endif /* fonction_ISS_h */
