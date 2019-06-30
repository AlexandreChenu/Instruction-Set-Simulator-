//
//  Cache_memory.c
//  brouillon
//
//  Created by AlexandreChenu on 16/03/2018.
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


// fonction de récupération des données en mémoire (cache ou non)

int get_data(int adresse, struct Memory mem_data[], struct Cache_memory mem_cache[]){
    
    int data_output;
    int i = 0;
    
    if (mem_cache[mem_data[adresse].index].valid == 1){
        
        if (mem_cache[mem_data[adresse].index].tag == mem_data[adresse].tag){
            
            //Cache hit -> on reccupère la donnée dans le cache
            
            data_output = mem_cache[mem_data[adresse].index].block[mem_data[adresse].block];}
    
        else {
            
            //Cache miss -> on reccupère la donnée dans la mémoire de donnée et on l'écrit dans le cache
            
            data_output = mem_data[adresse].data;
            mem_cache[mem_data[adresse].index].valid = 1;
            mem_cache[mem_data[adresse].index].tag = mem_data[adresse].tag;
            
            for (i=0;i<TailleMemoire;i++){
                
                if (mem_data[adresse].offset==0){
                    
                    mem_cache[mem_data[adresse].index].block[0] = mem_data[adresse].data;
                    mem_cache[mem_data[adresse].index].block[1] = mem_data[adresse+1].data;
                    mem_cache[mem_data[adresse].index].block[2] = mem_data[adresse+2].data;
                    mem_cache[mem_data[adresse].index].block[3] = mem_data[adresse+3].data;}
                
                if (mem_data[adresse].offset==1){
                    
                    mem_cache[mem_data[adresse].index].block[0] = mem_data[adresse-1].data;
                    mem_cache[mem_data[adresse].index].block[1] = mem_data[adresse].data;
                    mem_cache[mem_data[adresse].index].block[2] = mem_data[adresse+1].data;
                    mem_cache[mem_data[adresse].index].block[3] = mem_data[adresse+2].data;}
                
                if (mem_data[adresse].offset==1){
                    
                    mem_cache[mem_data[adresse].index].block[0] = mem_data[adresse-2].data;
                    mem_cache[mem_data[adresse].index].block[1] = mem_data[adresse-1].data;
                    mem_cache[mem_data[adresse].index].block[2] = mem_data[adresse].data;
                    mem_cache[mem_data[adresse].index].block[3] = mem_data[adresse+1].data;}
                
                if (mem_data[adresse].offset==1){
                    
                    mem_cache[mem_data[adresse].index].block[0] = mem_data[adresse-3].data;
                    mem_cache[mem_data[adresse].index].block[1] = mem_data[adresse-2].data;
                    mem_cache[mem_data[adresse].index].block[2] = mem_data[adresse-1].data;
                    mem_cache[mem_data[adresse].index].block[3] = mem_data[adresse].data;}}}}
    
    else {
        
        //Cache miss -> on réccupère la donnée dans la mémoire de donnée et on l'écrit dans le cache
        
        data_output = mem_data[adresse].data;
        
        mem_cache[mem_data[adresse].index].valid = 1;
        mem_cache[mem_data[adresse].index].tag = mem_data[adresse].tag;
        
        for (i=0;i<TailleMemoire;i++){
            
            if (mem_data[adresse].offset==0){
                
                mem_cache[mem_data[adresse].index].block[0] = mem_data[adresse].data;
                mem_cache[mem_data[adresse].index].block[1] = mem_data[adresse+1].data;
                mem_cache[mem_data[adresse].index].block[2] = mem_data[adresse+2].data;
                mem_cache[mem_data[adresse].index].block[3] = mem_data[adresse+3].data;}
            
            if (mem_data[adresse].offset==1){
                
                mem_cache[mem_data[adresse].index].block[0] = mem_data[adresse-1].data;
                mem_cache[mem_data[adresse].index].block[1] = mem_data[adresse].data;
                mem_cache[mem_data[adresse].index].block[2] = mem_data[adresse+1].data;
                mem_cache[mem_data[adresse].index].block[3] = mem_data[adresse+2].data;}
            
            if (mem_data[adresse].offset==1){
                
                mem_cache[mem_data[adresse].index].block[0] = mem_data[adresse-2].data;
                mem_cache[mem_data[adresse].index].block[1] = mem_data[adresse-1].data;
                mem_cache[mem_data[adresse].index].block[2] = mem_data[adresse].data;
                mem_cache[mem_data[adresse].index].block[3] = mem_data[adresse+1].data;}
            
            if (mem_data[adresse].offset==1){
                
                mem_cache[mem_data[adresse].index].block[0] = mem_data[adresse-3].data;
                mem_cache[mem_data[adresse].index].block[1] = mem_data[adresse-2].data;
                mem_cache[mem_data[adresse].index].block[2] = mem_data[adresse-1].data;
                mem_cache[mem_data[adresse].index].block[3] = mem_data[adresse].data;}}}
        
    return( data_output);}

void initData1( struct Memory data[]){
    
    int i;
    int tag_nbr = 0;
    int tag =0;
    int index_nbr = 0;
    int index=0;
    //int offset = 0;
    //int block = 0;
    
    //Initialisation du tag, de l'index et de l'offset des adresses de mémoire de donnée
    //Les paramètres du cache sont : (S=4,E=1,B=4,m=1024)
    
    for (i=0;i<TailleMemoire;i++){
        
        if ((tag_nbr % 64 ==0)&&tag>0){
            tag++;}
        
        data[i].tag=tag;
        
        if ((index_nbr % 4 ==0)&&index_nbr>0){
            index_nbr ++;
            if (index_nbr>4){
                index_nbr=0;}}
            
        if (index<4&&index_nbr>0){
            index++;}
        
        else{
            index=0;}
        
        data[i].index=index_nbr;
        data[i].block = index;
    }
}

void initCache( struct Cache_memory cache[]){
    
    //Initialisation à 0 de tous les paramètres de la mémoire cache
    
    int i;
    
    for (i=0;i<Nbr_set_cache;i++){
        
        cache[i].block[0]= 0;
        cache[i].block[1]= 0;
        cache[i].block[2]= 0;
        cache[i].block[3]= 0;
        cache[i].tag =0;
        cache[i].valid =0;}}

void updateCache( int adresse, struct Memory mem_data[], struct Cache_memory mem_cache[]){
    
    mem_cache[mem_data[adresse].index].block[mem_data[adresse].block] = mem_data[adresse].data;
}
