#pragma once

#include "analisador_lexico.h"

typedef struct object {
    int nName;
    struct object *pNext;
    struct obj;
} object, *pobject;

int NewBlock(void);
int EndBlock(void);
pobject Define(int aName);
pobject Search (int aName);
pobject Find (int aName);