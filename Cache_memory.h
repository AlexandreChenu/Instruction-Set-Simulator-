//
//  Cache_memory.h
//  brouillon
//
//  Created by AlexandreChenu on 16/03/2018.
//  Copyright © 2018 AlexandreChenu. All rights reserved.
//

#ifndef Cache_memory_h
#define Cache_memory_h

#include <stdio.h>
#include "Cache_memory.h"

/*______________________________________________________________________________________________________*/

//Définition des différentes structures associées à la mémoire cache

// une structure de mémoire basique
typedef struct Memory Data;
struct Memory {
    
    //int adresse;
    int tag;
    int index;
    int offset;
    int block;
    int data;};

// une structure de cache contenant plusieurs mémoire de petite taille
typedef struct Cache_memory Cache;
struct Cache_memory {
    int valid;
    int tag;
    int block[];};

/* _____________________________________________________________________________________________________*/

/* _____________________________________________________________________________________________________*/

//Prototype des fonctions

void initData1( struct Memory data[]);
void initCache( struct Cache_memory cache[]);
int get_data(int adresse, struct Memory mem_data[], struct Cache_memory mem_cache[]);
void updateCache( int adresse, struct Memory mem_data[], struct Cache_memory mem_cache[]);

/* _____________________________________________________________________________________________________*/

#endif /* Cache_memory_h */
