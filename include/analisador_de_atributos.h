#pragma once

#include "analisador_lexico.h"
#include "analisador_sintatico.h"
#include "analisador_de_escopo.h"

extern bool hasError;

typedef enum {
    ERR_REDCL,ERR_NO_DECL,ERR_TYPE_EXPECTED,ERR_BOOL_TYPE_EXPECTED,ERR_TYPE_MISMATCH,ERR_INVALID_TYPE,ERR_KIND_NOT_STRUCT,ERR_FIELD_NOT_DECL,ERR_KIND_NOT_ARRAY,ERR_INVALID_INDEX_TYPE,ERR_KIND_NOT_VAR,ERR_KIND_NOT_FUNCTION,ERR_TOO_MANY_ARGS,ERR_PARAM_TYPE,ERR_TOO_FEW_ARGS,ERR_RETURN_TYPE_MISMATCH
} errorcode;

void semantics(int rule);
void Error(errorcode code);

typedef struct {
    t_nterm nont;
    int nSize;
    union {
        struct {
            pobject obj;
            int name;}
        ID;
        struct {
            pobject type;
        } T, E,L,R,K,F,LV;
        struct {
            pobject type;
            pobject param;
            bool err;
        } MC;
        struct {
            int label;
        } MT,ME,MW,MA;
        struct{
            pobject type;
            pobject param;
            bool err;
            int n;
        } LE;
        struct {
            pobject list;
        } LI,DC,LP;
        struct {
            pobject type;
            bool val;
        } TRU,FALS;
        struct {
            pobject type;
            int pos;
            char val;
        } CHR;
        struct {
            pobject type;
            char* val;
            int pos;
        } STR;
        struct {
            pobject type;
            int val;
            int pos;
        } NUM;  
    }_;
} t_attrib;