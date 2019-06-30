//
//  fonction_operation.h
//  brouillon
//
//  Created by AlexandreChenu on 18/02/2018.
//  Copyright © 2018 AlexandreChenu. All rights reserved.
//

#ifndef fonction_operation_h
#define fonction_operation_h
#include <stdio.h>
#include "Cache_memory.h"

void ADD ( int regs[], char reg1[] , char o[], char reg3[], char imm[] );
void SUB ( int regs[], char reg1[] , char o[], char reg3[], char imm[] );
void MULT ( int regs[], char reg1[] , char o[], char reg3[], char imm[] );
void DIV ( int regs[], char reg1[] , char o[], char reg3[], char imm[] );
void AND ( int regs[], char reg1[] , char o[], char reg3[], char imm[] );
void OR ( int regs[], char reg1[] , char o[], char reg3[], char imm[] );
void XOR ( int regs[], char reg1[] , char o[], char reg3[], char imm[] );
void SHL ( int regs[], char reg1[] , char o[], char reg3[], char imm[] );
void SHR ( int regs[], char reg1[] , char o[], char reg3[], char imm[] );
void SLT ( int regs[], char reg1[] , char o[], char reg3[], char imm[] );
void SLE ( int regs[], char reg1[] , char o[], char reg3[], char imm[] );
void SEQ ( int regs[], char reg1[] , char o[], char reg3[], char imm[] );
void LOAD ( int regs[], char reg1[] , char o[], char reg3[], char imm[], struct Memory mem_data[], struct Cache_memory mem_cache[] );
void STORE ( int regs[], char reg1[] , char o[], char reg3[], char imm[], struct Memory mem_data[], struct Cache_memory mem_cache[] );
void JMP ( int regs[], char o[], char reg3[], char imm[], int *p_line_inst);
void BRAZ ( int regs[], char reg3[], char adresse[], int *p_line_inst);
void BRANZ ( int regs[], char reg3[], char adresse[], int *p_line_inst);
void STOP (int *running);
int SCALL (char n[]);

#endif /* fonction_operation_h */
