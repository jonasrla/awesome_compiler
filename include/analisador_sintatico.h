#pragma once

#ifndef IS_SHIFT
#define IS_SHIFT(p) (p>0)
#endif

#ifndef IS_REDUCTION
#define IS_REDUCTION(p) (p<0)
#endif

#ifndef RULE
#define RULE(p) (-(p))
#endif

#ifndef PUSH
#define PUSH(p) (pilhaEstado.push(p))
#endif

#ifndef POP
#define POP(p) for(int i=0;i<p;i++){pilhaEstado.pop();}
#endif

#ifndef TOP
#define TOP() (pilhaEstado.top())
#endif

typedef enum{
    P = 51,LDE,DE,DT,TP,DC,DF,LP,B,LDV,LS,DV,LI,S,E,L,R,TM,F,LE,LV,IDD,IDU,ID,NT_TRUE,NT_FALSE,NT_CHR,NT_STR,NT_NUM,NB
} t_nterm;

void parse();