//
//  fonction_operation.c
//  brouillon
//
//  Created by AlexandreChenu on 18/02/2018.
//  Copyright © 2018 AlexandreChenu. All rights reserved.
//

#include "fonction_operation.h"
#include "fonction_ISS.h"
#include "Cache_memory.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Addition entière

void ADD ( int regs[], char reg1[] , char o[], char reg3[], char imm[] ){
    
    int r1 = binaryToInt(reg1);
    int o1 = binaryToInt(o);
    int r3 = binaryToInt(reg3);
    int imm1 = binaryToInt(imm);

    if ( imm1 == 1){
        regs[r3] = regs[r1] + o1;
    }
    else {
        regs[r3] = regs[r1] + regs[o1];
    }
}

//Soustraction entière

void SUB ( int regs[], char reg1[] , char o[], char reg3[], char imm[] ){
    
    int r1 = binaryToInt(reg1);
    int o1 = binaryToInt(o);
    int r3 = binaryToInt(reg3);
    int imm1 = binaryToInt(imm);
    
    if ( imm1 == 1){
        regs[r3] = regs[r1] - o1;
    }
    else {
        regs[r3] = regs[r1] - regs[o1];
    }
}

//Multiplication entière

void MULT ( int regs[], char reg1[] , char o[], char reg3[], char imm[] ){
    
    int r1 = binaryToInt(reg1);
    int o1 = binaryToInt(o);
    int r3 = binaryToInt(reg3);
    int imm1 = binaryToInt(imm);
    
    if ( imm1 == 1){
        regs[r3] = regs[r1] * o1;
    }
    else {
        regs[r3] = regs[r1] * regs[o1];
    }
}

//Division entière

void DIV ( int regs[], char reg1[] , char o[], char reg3[], char imm[] ){
    
    int r1 = binaryToInt(reg1);
    int o1 = binaryToInt(o);
    int r3 = binaryToInt(reg3);
    int imm1 = binaryToInt(imm);
    
    if ( imm1 == 1){
        regs[r3] = regs[r1] / o1;
    }
    else {
        regs[r3] = regs[r1] / regs[o1];
    }
}

//ET logique

void AND ( int regs[], char reg1[] , char o[], char reg3[], char imm[] ){

    int r1 = binaryToInt(reg1);
    int o1 = binaryToInt(o);
    int r3 = binaryToInt(reg3);
    int imm1 = binaryToInt(imm);
    
    if ( imm1 == 1){
        regs[r3] = regs[r1] & o1;
    }
    else {
        regs[r3] = regs[r1] & regs[o1];
    }
}

//OU logique

void OR ( int regs[], char reg1[] , char o[], char reg3[], char imm[] ){
    
    int r1 = binaryToInt(reg1);
    int o1 = binaryToInt(o);
    int r3 = binaryToInt(reg3);
    int imm1 = binaryToInt(imm);
    
    if ( imm1 == 1){
        regs[r3] = regs[r1] | o1;
    }
    else {
        regs[r3] = regs[r1] | regs[o1];
    }
}

//OU exclusif logique

void XOR ( int regs[], char reg1[] , char o[], char reg3[], char imm[] ){
    
    int r1 = binaryToInt(reg1);
    int o1 = binaryToInt(o);
    int r3 = binaryToInt(reg3);
    int imm1 = binaryToInt(imm);
    
    if ( imm1 == 1){
        regs[r3] = regs[r1] ^ o1;
    }
    else {
        regs[r3] = regs[r1] ^ regs[o1];
    }
}

//Décalage à gauche

void SHL ( int regs[], char reg1[] , char o[], char reg3[], char imm[] ){
    
    int r1 = binaryToInt(reg1);
    int o1 = binaryToInt(o);
    int r3 = binaryToInt(reg3);
    int imm1 = binaryToInt(imm);
    
    if ( imm1 == 1){
        regs[r3] = regs[r1] << o1;
    }
    else {
        regs[r3] = regs[r1] << regs[o1];
    }
}

//Décalage à droit

void SHR ( int regs[], char reg1[] , char o[], char reg3[], char imm[] ){
    
    int r1 = binaryToInt(reg1);
    int o1 = binaryToInt(o);
    int r3 = binaryToInt(reg3);
    int imm1 = binaryToInt(imm);
    
    if ( imm1 == 1){
        regs[r3] = regs[r1] >> o1;
    }
    else {
        regs[r3] = regs[r1] >> regs[o1];
    }
}

//Test inférieur

void SLT ( int regs[], char reg1[] , char o[], char reg3[], char imm[] ){
    
    int r1 = binaryToInt(reg1);
    int o1 = binaryToInt(o);
    int r3 = binaryToInt(reg3);
    int imm1 = binaryToInt(imm);
    
    if ( imm1 == 1){
        if (regs[r1] < o1){
            
            regs[r3] = 1;
            
        }
        
        else {
            
            regs[r3] = 0;
            
        }
    }
    else {
        if (regs[r1] < regs[o1]){
            
            regs[r3] = 1;
        }
        
        else{
            
            regs[r3] = 0;
            
        }
    }
}

//Test inférieur ou égal

void SLE ( int regs[], char reg1[] , char o[], char reg3[], char imm[] ){
    
    int r1 = binaryToInt(reg1);
    int o1 = binaryToInt(o);
    int r3 = binaryToInt(reg3);
    int imm1 = binaryToInt(imm);
    
    if ( imm1 == 1){
        if (regs[r1] <= o1){
            
            regs[r3] = 1;
            
        }
        
        else {
            
            regs[r3] = 0;
            
        }
    }
    else {
        if (regs[r1] <= regs[o1]){
            
            regs[r3] = 1;
        }
        
        else{
            
            regs[r3] = 0;
            
        }
    }
}

//Test d'égalité

void SEQ ( int regs[], char reg1[] , char o[], char reg3[], char imm[] ){
    
    int r1 = binaryToInt(reg1);
    int o1 = binaryToInt(o);
    int r3 = binaryToInt(reg3);
    int imm1 = binaryToInt(imm);
    
    if ( imm1 == 1){
        if (regs[r1] == o1){
            
            regs[r3] = 1;
            
        }
        
        else {
            
            regs[r3] = 0;
            
        }
    }
    else {
        if (regs[r1] == regs[o1]){
            
            regs[r3] = 1;
        }
        
        else{
            
            regs[r3] = 0;
            
        }
    }
}


//Lecture en mémoire

void LOAD ( int regs[], char reg1[] , char o[], char reg3[], char imm[], struct Memory mem_data[], struct Cache_memory mem_cache[] ){
    
    int r1 = binaryToInt(reg1);
    int o1 = binaryToInt(o);
    int r3 = binaryToInt(reg3);
    int imm1 = binaryToInt(imm);
    
    if ( imm1 == 1){
     
        regs[r3] = get_data(regs[r1]+o1,mem_data,mem_cache);}
    
    else{
        
        regs[r3] = get_data(regs[r1]+regs[o1],mem_data,mem_cache);}
    
}

//Chargement en mémoire

void STORE ( int regs[], char reg1[] , char o[], char reg3[], char imm[], struct Memory mem_data[], struct Cache_memory mem_cache[] ){
    
    int r1 = binaryToInt(reg1);
    int o1 = binaryToInt(o);
    int r3 = binaryToInt(reg3);
    int imm1 = binaryToInt(imm);
    
    if ( imm1 == 1){
        
        mem_data[regs[r1]+o1].data = regs[r3];
        updateCache(regs[r1]+o1, mem_data, mem_cache);}
    
    else{
        
        mem_data[regs[r1]+regs[o1]].data = regs[r3];
        updateCache(regs[r1]+regs[o1], mem_data, mem_cache);}
}

//Saut d'adresse d'instruction

void JMP ( int regs[], char o[], char reg3[], char imm[], int *p_line_inst){
    
    int o1 = binaryToInt(o);
    int r3 = binaryToInt(reg3);
    int imm1 = binaryToInt(imm);
    
    if ( imm1 == 1){
        
        regs[r3] = *p_line_inst+1;
        
        *p_line_inst = o1-1;}
    
    else{
        
        regs[r3] = *p_line_inst+1;
        
        *p_line_inst = regs[o1]-1;}
}

//Branchement si valeur nulle

void BRAZ ( int regs[], char reg3[], char adresse[], int *p_line_inst){
    
    int r3 = binaryToInt(reg3);
    int ad = binaryToInt(adresse);
    
    if ( regs[r3] == 0){
        
        *p_line_inst = ad-1;}
}

//Branchement si valeur non nulle

void BRANZ ( int regs[], char reg3[], char adresse[], int *p_line_inst){
    
    int r3 = binaryToInt(reg3);
    int ad = binaryToInt(adresse);
    
    if ( regs[r3] != 0){
        
        *p_line_inst = ad-1;}
}


//Arrêt système

void STOP (int *running){
    
    *running = 0;}

//Appel système

int SCALL (char n[]){
    
    int int_n = atoi(n);
    
    return(int_n);}
