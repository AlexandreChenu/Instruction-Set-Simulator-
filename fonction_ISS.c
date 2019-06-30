//
//  fonction_ISS.c
//  brouillon
//
//  Created by AlexandreChenu on 18/02/2018.
//  Copyright © 2018 AlexandreChenu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction_ISS.h"
#include "fonction_operation.h"
#include "Cache_memory.h"
#define NumRegs 32
#define Nbr_label 20
#define TailleMemoire 1024
#define TAILLE_MAX 100
#define Nbr_set_cache 4

/* _____________________________________________________________________________________________________*/


//Détail des fonctions

//Fonction pour lecture préliminaire et détéction des labels

void detect_label(char NomFichier[],struct dictionnaire_label dic_lab[])
{
    FILE* InstructionLine =NULL;
    char line[TAILLE_MAX];
    int i = 0;
    int adresse = 0;
    int num_label = 0;
    InstructionLine = fopen(NomFichier, "r");
    if (InstructionLine != NULL)
    {
        while ( fgets(line, sizeof line,InstructionLine)!=NULL ){
            
            for (i=0;i<20;i++){
                
                if (line[i] == ':'){
                    
                    char line1[100];
                    dic_lab[num_label].adresse = adresse;
                    
                    strcpy(line1,line);
                    strcpy(line,&line1[i+1]);
                    line1[i] = '\0';
                    
                    strcpy(dic_lab[num_label].name_label,line1);
                    num_label++;
            
                }}
            adresse ++;
        }}
    else
    {
        printf(" ouverture du fichier assembleur %s  impossible, verifier qu'il soit ecrit correctement\n", NomFichier);}}

// Fonction de découpage d'une ligne du code assembleur

struct decoupage analyse (char phrase[],struct dictionnaire_label dico_label[],int *num_label,int *adresse){
    
    struct decoupage result; //Initialisation du découpage
    result.imm = 0;
    result.reg[0] = 0;
    result.reg[1] = 0;
    result.reg[2] = 0;
    result.adresse = 0;
    
    char opé[7];
    char chaine_registres[15];
    int i;
    
    
    //Si il y a un loop : on ne s'occupe que de ce qu'il y a après les deux points
    
    for (i=0;i<20;i++){
        
        if (phrase[i] == ':'){
            
            char phrase1[100];
            
            strcpy(phrase1,phrase);
            strcpy(phrase,&phrase1[i+1]);}
    }
    
    //Elimination du cas du STOP
    
    if (strcmp(phrase,"STOP")==0){
        
        strlcpy(result.instr,phrase,5);
        return( result );}
    
    //decoupage de la chaine de caractère en 2 : partie opération / partie registre
    
    for (i=0;i<20;i++){
        
        if (phrase[i] == ' '){
            
            strcpy(chaine_registres,&phrase[i+1]);
            
            phrase[i] = '\0';
            
            strcpy(opé,phrase);}
        }
    
    //l'instruction est rentrée dans le resultat
    
    strcpy(result.instr,opé);
    
    //découpage des registres en fonction de l'instruction
    
    if(strcmp(opé, "SCALL")==0){
        
        result.reg[0] = atoi(chaine_registres);
        return(result);
    }
    
    //decoupage d'une ligne JMP
    
    if (strcmp(opé,"JMP")==0){
        
        char *token = NULL;
        const char s[2] = ","; // caractère de comparaison pour le strtok
        int cnt = 0;
        char buffer[10];
        
        token = strtok(chaine_registres,s);
  
        strcpy(buffer,token);
        
        if (buffer[0] == 'r'){
            result.reg[0] = atoi(&buffer[1]);}
        
        if (buffer[0] == 'L'){ // cas d'une adresse d'instruction sous la forme d'un label
            
            for (i=0;i<Nbr_label;i++){
                
                if (strcmp(dico_label[i].name_label,buffer)==0){
                
                    result.reg[0] = dico_label[i].adresse;}
            }}
        
        else{
            result.imm = 1;
            result.reg[0] = atoi(buffer);}
        
        while( token != NULL ) {
            cnt ++;
            token = strtok(NULL, s);
            if (token == NULL){
                break;}
            strcpy(buffer,token);
            if (buffer[0] == 'r'){
                result.reg[cnt] = atoi(&buffer[1]);}
            
            if (buffer[0] == 'L'){ // cas d'une adresse d'instruction sous la forme d'un label
                
                for (i=0;i<Nbr_label;i++){
                    
                    if (strcmp(dico_label[i].name_label,buffer)==0){
                        
                        result.reg[cnt] = dico_label[i].adresse;}
                }}
            
            else{
                result.imm = 1;
                result.reg[cnt] = atoi(buffer);}}
        return(result);}
    
    //decoupage BRAZ
    
    if ((strcmp(opé,"BRAZ")==0) || (strcmp(opé,"BRANZ")==0)){
        
        char *token = NULL;
        const char s[2] = ","; // caractère de comparaison pour le strtok
        int cnt = 0;
        char buffer[10];
        
        token = strtok(chaine_registres,s);
        
        strcpy(buffer,token);
        
        if (buffer[0] == 'r'){
            result.reg[0] = atoi(&buffer[1]);}
        
        if (buffer[0] == 'L'){ // cas d'une adresse d'instruction sous la forme d'un label
            
            
            for (i=0;i<Nbr_label;i++){
                
                if (strcmp(dico_label[i].name_label,buffer)==0){
                    
                    result.adresse = dico_label[i].adresse;}
            }}
        
        else{
            result.adresse = atoi(buffer);}
        
        while( token != NULL ) {
            cnt ++;
            token = strtok(NULL, s);
            if (token == NULL){
                break;}
            strcpy(buffer,token);
            if (buffer[0] == 'r'){
                result.reg[cnt] = atoi(&buffer[1]);}
            
            if (buffer[0] == 'L'){ // cas d'une adresse d'instruction sous la forme d'un label
                
                for (i=0;i<Nbr_label;i++){
                    
                    if (strcmp(dico_label[i].name_label,buffer)==0){
                        
                        result.adresse = dico_label[i].adresse;}
                }}
            
            else{
                result.adresse = atoi(buffer);}}
        return(result);}
    
    
    //découpage des registres pour les cas ordinaires ( 1 instruction + 3 arguments )
    
    char *token = NULL;
    const char s[2] = ","; // caractère de comparaison pour le strtok
    int cnt = 0;
    char buffer[5];
    
    token = strtok(chaine_registres,s);
    
    //verification registre ou constante
    
    strcpy(buffer,token);
    
    if (buffer[0] == 'r'){
        
        result.reg[0] = atoi(&buffer[1]);}
    
    else{
        
        result.imm = 1;
        result.reg[0] = atoi(buffer);
    }
    
    while( token != NULL ) {
        
        cnt ++;
        token = strtok(NULL, s);
        
        if (token == NULL){
            break;
        }
        
        strcpy(buffer,token);
        
        if (buffer[0] == 'r'){
            
            result.reg[cnt] = atoi(&buffer[1]);
        }
        
        else{
            result.imm = 1;
            result.reg[cnt] = atoi(buffer);
        }
    }
    return(result);
}

//Fonction d'identification de l'opération et traduction binaire de l'opération et des registres


struct FieldInstruction identification_bin( char op[], int reg[], int adresse, int imm, struct dictionnaire dic[]){
    
    //Initialisation d'une nouvelle trame binaire
    
    struct FieldInstruction trame_bin;
    strcpy(trame_bin.Arg_1,"0");
    strcpy(trame_bin.Arg_2,"0");
    strcpy(trame_bin.Arg_3,"0");
    strcpy(trame_bin.Adresse,"0");
    strcpy(trame_bin.imm,"0");
    strcpy(trame_bin.instrNum,"0");
    
    char tmp_imm[10];
    int found = 0;
    int i = 0;
    
    //identification de l'opération par comparaison
    
    while (found == 0){
        
        if (strcmp(op,dic[i].name_op) == 0){
            
            found = 1;
            strcpy(trame_bin.instrNum, decimalToBinary(dic[i].eq,4));}
        
        else {
            i++;}
    }
    
    //Ecriture des arguments sous forme binaire en fonction du type d'opération
    
    //Cas particuliers
    
    if (strcmp(op,"STOP")==0){
        
        return(trame_bin);}
    
    if (strcmp(op,"SCALL")==0){
        
        strcpy(trame_bin.Arg_1, decimalToBinary(reg[0], 26));
        return(trame_bin);}
    
    if (strcmp(op,"JMP")==0){
        
        strcpy(trame_bin.Arg_2,decimalToBinary(reg[0],5));
        strcpy(trame_bin.Arg_3,decimalToBinary(reg[1],14));
        
        sprintf(tmp_imm,"%d",imm);
        strcpy(trame_bin.imm,tmp_imm);
        
        return(trame_bin);}
    
    if ((strcmp(op,"BRAZ")==0) || (strcmp(op,"BRANZ")==0)){
        
        strcpy(trame_bin.Arg_3,decimalToBinary(reg[0],5));
        strcpy(trame_bin.Adresse,decimalToBinary(adresse,19));
        
        return(trame_bin);}
    
    //Cas Normal

    strcpy(trame_bin.Arg_1,decimalToBinary(reg[0],5));
    strcpy(trame_bin.Arg_2,decimalToBinary(reg[1],14));
    strcpy(trame_bin.Arg_3,decimalToBinary(reg[2],5));
    
    sprintf(tmp_imm,"%d",imm);
    
    strcpy(trame_bin.imm,tmp_imm);
    
    return(trame_bin);}

//Fonction de conversion d'un entier en binaire

char *decimalToBinary(int n1, int taille_bin) {
    
    char remainder[20]="";
    char binary[42]="";
    int i = 1;
    int n;
    char zero[2] = "0";
    char ajout_zero[60] ="0";
    
    n = abs(n1);
    
    if (n1 == 0){
        
        strcpy(binary,"0");
        
    }
    
    else {
    
        while( n != 0) {
        
            sprintf(remainder,"%d",n%2);
            strcat(binary,remainder);
            n = n/2;}
    }
    
    strinv(binary);
    
    //ajout de zeros pour écrire sur le nombre de bits voulu
    
    int longueur = strlen(binary);
    
    int l = taille_bin - longueur; //nombre de zeros à rajouter
    
    for (i=1;i<l;i++){
        strcat(ajout_zero,zero);}
    
    strcat(ajout_zero,binary);
    
    if (n1 < 0){ //ajoute quand même un zéro pour le BRAZ et le BRANZ -> équivalents binaires trop grands de 1
        ajout_zero[0] = '1';
        } // ajout d'un 1 tout devant si chiffre négatif
    
    ajout_zero[strlen(ajout_zero)] = '\0';
    
    return ajout_zero;}

//Fonction de conversion d'un entier en binaire non signé

char *unsgdDecimalToBinary(int n1, int taille_bin){
    
    char remainder[20]="";
    char binary[42]="";
    int n;
    
    n = abs(n1);
    
    if (n1 == 0){
        
        strcpy(binary,"0");}
    
    else {
        
        while( n != 0) {
            
            sprintf(remainder,"%d",n%2);
            strcat(binary,remainder);
            n = n/2;}}
    
    strinv(binary);
    
    return binary;}

//Fonction de conversion d'un binaire signé en entier

int binaryToInt ( char binary[]){
    
    int integer = 0;
    int i = 0;
    
    if (strlen(binary)<2){
        
        if (binary[0] == '1'){
            
            integer = 1;
            
        }
        
        else {
            
            integer = 0;
            
        }
    }
    
    else {
    
        char binary2[100]="";
    
        strcpy(binary2, binary);
    
        strinv(binary2);
        int n = strlen(binary2);
    
        while (i <= n-2)
        {
            
            if (binary2[i] == '1'){
                integer += puiss(2,i);
                i ++;}
            
            else {
                i ++;}
        }
    
        if (binary2[n-1] == '1'){
        
            integer = -integer;}
    }
    
    return integer;}

//int unsgdBinaryToInt(char binary[]){

//Fonction de génération d'une trame complète au format binaire

char *full_trame_bin (struct FieldInstruction trame_binaire ){
    
    char bin_output[100]="";
    int num_instr = binaryToInt(trame_binaire.instrNum);
    
    if (0<num_instr && num_instr<15){ //Cas des opérations basiques
        
        strcat(bin_output, trame_binaire.instrNum);
        strcat(bin_output, trame_binaire.Arg_1);
        strcat(bin_output, trame_binaire.imm);
        strcat(bin_output, trame_binaire.Arg_2);
        strcat(bin_output, trame_binaire.Arg_3);
        return bin_output;}
    
    if (num_instr == 0){ //Cas du STOP
        strcpy(bin_output,"00000000000000000000000000000");
        return bin_output;}
    
    if ( num_instr == 15){ //Cas du JMP
        
        strcat(bin_output,trame_binaire.instrNum);
        strcat(bin_output,trame_binaire.imm);
        strcat(bin_output,trame_binaire.Arg_2);
        strcat(bin_output,trame_binaire.Arg_3);
        return bin_output;}
    
    if ( num_instr == 16 || num_instr == 17 ){ //Cas du BRAZ/BRANZ
        strcat(bin_output, trame_binaire.instrNum);
        strcat(bin_output, trame_binaire.Arg_3);
        strcat(bin_output, trame_binaire.Adresse);
        return bin_output;}
    
    if (num_instr == 18){
        strcat(bin_output, trame_binaire.instrNum);
        strcat(bin_output, trame_binaire.Arg_1);
        return bin_output;}
    
    else{
        return bin_output;}
    
    }

//Fonction d'appel des opérations en fonction du numéro d'instruction

void evaluation( int reg[], struct Memory mem_data[], struct Cache_memory mem_cache[], int *p_ligne_instr, int *p_running, struct FieldInstruction trame_binaire, int *p_nbr_cycle) {
    
    int num_instr = binaryToInt(trame_binaire.instrNum);
    
    switch (num_instr)
    {
        case 0:
            
            STOP(p_running);
            *p_nbr_cycle = *p_nbr_cycle+1;
            
            break;
        case 1:
            
            ADD ( reg, trame_binaire.Arg_1 , trame_binaire.Arg_2, trame_binaire.Arg_3, trame_binaire.imm );
            *p_nbr_cycle = *p_nbr_cycle+1;
            break;
            
        case 2:
            
            SUB ( reg, trame_binaire.Arg_1 , trame_binaire.Arg_2, trame_binaire.Arg_3, trame_binaire.imm );
            *p_nbr_cycle = *p_nbr_cycle+1;
            break;
            
        case 3:
            
            MULT ( reg, trame_binaire.Arg_1 , trame_binaire.Arg_2, trame_binaire.Arg_3, trame_binaire.imm );
            *p_nbr_cycle = *p_nbr_cycle+1;
            *p_nbr_cycle = *p_nbr_cycle+1;
            
            break;
            
        case 4:
            
            DIV ( reg, trame_binaire.Arg_1 , trame_binaire.Arg_2, trame_binaire.Arg_3, trame_binaire.imm );
            *p_nbr_cycle = *p_nbr_cycle+1;
            *p_nbr_cycle = *p_nbr_cycle+1;
            
            break;
            
        case 5:
            
            AND(reg, trame_binaire.Arg_1 , trame_binaire.Arg_2, trame_binaire.Arg_3, trame_binaire.imm );
            *p_nbr_cycle = *p_nbr_cycle+1;
            
            break;
        
        case 6:
            
            OR(reg, trame_binaire.Arg_1 , trame_binaire.Arg_2, trame_binaire.Arg_3, trame_binaire.imm );
            *p_nbr_cycle = *p_nbr_cycle+1;
            
            break;
        
        case 7:
            
            OR(reg, trame_binaire.Arg_1 , trame_binaire.Arg_2, trame_binaire.Arg_3, trame_binaire.imm );
            *p_nbr_cycle = *p_nbr_cycle+1;
            
            break;
        
        case 8:
            
            SHL(reg, trame_binaire.Arg_1 , trame_binaire.Arg_2, trame_binaire.Arg_3, trame_binaire.imm );
            *p_nbr_cycle = *p_nbr_cycle+1;
            
            break;
        
        case 9:
            
            SHR(reg, trame_binaire.Arg_1 , trame_binaire.Arg_2, trame_binaire.Arg_3, trame_binaire.imm );
            *p_nbr_cycle = *p_nbr_cycle+1;
            
            break;
        
        case 10:
            
            SLT(reg, trame_binaire.Arg_1 , trame_binaire.Arg_2, trame_binaire.Arg_3, trame_binaire.imm );
            *p_nbr_cycle = *p_nbr_cycle+1;
            
            break;
        
        case 11:
            
            SLE(reg, trame_binaire.Arg_1 , trame_binaire.Arg_2, trame_binaire.Arg_3, trame_binaire.imm );
            *p_nbr_cycle = *p_nbr_cycle+1;
            
            break;
        
        case 12:
            
            SEQ(reg, trame_binaire.Arg_1 , trame_binaire.Arg_2, trame_binaire.Arg_3, trame_binaire.imm );
            *p_nbr_cycle = *p_nbr_cycle+1;
            
            break;
        
        case 13:
            
            LOAD(reg, trame_binaire.Arg_1, trame_binaire.Arg_2, trame_binaire.Arg_3, trame_binaire.imm, mem_data, mem_cache);
            *p_nbr_cycle = *p_nbr_cycle+1;
            
            break;
        
        case 14:
            
            STORE(reg, trame_binaire.Arg_1, trame_binaire.Arg_2, trame_binaire.Arg_3, trame_binaire.imm, mem_data, mem_cache);
            *p_nbr_cycle = *p_nbr_cycle+1;
            
            break;
        
        case 15:
            
            JMP(reg, trame_binaire.Arg_2, trame_binaire.Arg_3, trame_binaire.imm, p_ligne_instr);
            *p_nbr_cycle = *p_nbr_cycle+1;
            
            break;
        
        case 16:
            
            BRAZ(reg, trame_binaire.Arg_3, trame_binaire.Adresse, p_ligne_instr);
            *p_nbr_cycle = *p_nbr_cycle+1;
            
            break;
        
        case 17:
            
            BRANZ(reg, trame_binaire.Arg_3, trame_binaire.Adresse, p_ligne_instr);
            *p_nbr_cycle = *p_nbr_cycle+1;
            
            break;
        
        case 18:
            
            SCALL(trame_binaire.Arg_1);
            *p_nbr_cycle = *p_nbr_cycle+1;
            
            break;
    }
}

//Fonction d'initialisation des registres

void initRegs (int regs[]){
    
    int i = 0;
    
    for (i=0;i<NumRegs;i++){
        
        regs[i] = 0;}
    }

//Fonction d'initialisation de la mémoire de données (version avant le cache)
void initData (int data[]){
    
    int i = 0;
    
    for (i=0;i<TailleMemoire;i++){
        
        data[i] = 0;}
}

//Fonction d'initialisation du dictionnaire de correspondance nom d'opération/numéro d'opération
void initDico ( struct dictionnaire dico[]){
    
    strcpy(dico[0].name_op,"STOP");
    dico[0].eq = 0;
    
    strcpy(dico[1].name_op,"ADD");
    dico[1].eq = 1;
    
    strcpy(dico[2].name_op,"SUB");
    dico[2].eq = 2;
    
    strcpy(dico[3].name_op,"MUL");
    dico[3].eq = 3;
    
    strcpy(dico[4].name_op,"DIV");
    dico[4].eq = 4;
    
    strcpy(dico[5].name_op,"AND");
    dico[5].eq = 5;
    
    strcpy(dico[6].name_op,"OR");
    dico[6].eq = 6;
    
    strcpy(dico[7].name_op,"XOR");
    dico[7].eq = 7;
    
    strcpy(dico[8].name_op,"SHL");
    dico[8].eq = 8;
    
    strcpy(dico[9].name_op,"SHR");
    dico[9].eq = 9;
    
    strcpy(dico[10].name_op,"SLT");
    dico[10].eq = 10;
    
    strcpy(dico[11].name_op,"SLE");
    dico[11].eq = 11;
    
    strcpy(dico[12].name_op,"SEQ");
    dico[12].eq = 12;
    
    strcpy(dico[13].name_op,"LOAD");
    dico[13].eq = 13;
    
    strcpy(dico[14].name_op,"STORE");
    dico[14].eq = 14;
    
    strcpy(dico[15].name_op,"JMP");
    dico[15].eq = 15;
    
    strcpy(dico[16].name_op,"BRAZ");
    dico[16].eq = 16;
    
    strcpy(dico[17].name_op,"BRANZ");
    dico[17].eq = 17;
    
    strcpy(dico[18].name_op,"SCALL");
    dico[18].eq = 18;
}

//Fonction d'initialisation du dictionnaire de correspondance nom de label/adresse de la mémoire d'instruction
void initLabel (struct dictionnaire_label dico_label[]){
    
    strcpy(dico_label[0].name_label,"Label0");
    dico_label[0].adresse = 0;
    
    strcpy(dico_label[1].name_label,"Label1");
    dico_label[1].adresse = 1;
    
    strcpy(dico_label[2].name_label,"Label2");
    dico_label[2].adresse = 2;
    
}

//Fonction de calcul de puissance
int puiss(int n, int k)
    {
        if (k == 0)
            return 1;
        else
            return  (n * puiss(n,k-1)) ;
    };

//Fonction d'inversion d'une chaine de caractère
void strinv(char *st)
{
    char tmp;
    unsigned int d = 0;
    unsigned int f = strlen(st)-1;
    while(d<f)
    {
        tmp = st[d];
        st[d] = st[f];
        st[f]= tmp;
        d++;
        f--;
    }
}

//Fonction de lecture du fichier assembleur ligne par ligne
char * Traitement(char NomFichier[], int AdressInstr)
{
    FILE* InstructionLine =NULL;
    char line[TAILLE_MAX];
    int i = 0;
    InstructionLine = fopen(NomFichier, "r");
    if (InstructionLine != NULL)
    {
        int compteurline =0;
        while ( fgets(line, sizeof line,InstructionLine)!=NULL )
        {
            
            if (compteurline == AdressInstr)
            {
                char ligne [TAILLE_MAX];
                strcpy(ligne, line);
                fclose(InstructionLine);
                
                for (i=0;i<strlen(ligne);i++){
                    
                    if(ligne[i]=='\n'){
                        
                        ligne[i] = '\0';}}
                
                return ligne;
            }
            else
            {
                compteurline++;
            }
            
        }
        printf("adresse  %d non existante\n", AdressInstr);
        fclose(InstructionLine);
        return 0;
    }
    else
    {
        printf(" ouverture du fichier assembleur %s  impossible, verifier qu'il soit ecrit correctement\n", NomFichier);
        return 0;
    }
}



/* _____________________________________________________________________________________________________*/

