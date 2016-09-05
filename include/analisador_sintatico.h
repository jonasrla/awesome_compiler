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

void parse();