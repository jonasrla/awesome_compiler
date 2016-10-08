#pragma once

#include "analisador_lexico.h"

typedef enum { 
    NO_KIND_DEF_=-1, VAR_, PARAM_, FUNCTION_, FIELD_, ARRAY_TYPE_, STRUCT_TYPE_, ALIAS_TYPE_, SCALAR_TYPE_ , UNIVERSAL_
} t_kind;

typedef struct object
{
    int nName;
    struct object *pNext;
    t_kind eKind;
    
    union {
        struct {
            struct object *pType;
        } Var, Param, Field;
        struct {
            struct object *pRetType;
            struct object *pParams;
            int nParams;
        } Function;
        struct {
            struct object *pElemType;
            int nNumElems;
        } Array;
        struct {
            struct object *pFields;
        } Struct;
        struct {
            struct object *pBaseType;
        } Alias,Type;
    }_;
    
} object, *pobject;

int NewBlock(void);
int EndBlock(void);
pobject Define(int aName);
pobject Search (int aName);
pobject Find (int aName);