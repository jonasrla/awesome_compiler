#pragma once

#include "analisador_lexico.h"
#include "analisador_sintatico.h"
#include "analisador_de_escopo.h"

extern bool hasError;


#define MAX_NEST_LEVEL 50
#define IS_TYPE_KIND(k) ((k)==ARRAY_TYPE_ || \
                         (k)==STRUCT_TYPE_|| \
                         (k)==ALIAS_TYPE_ || \
                         (k)==SCALAR_TYPE_)

typedef enum {
    ERR_REDCL,ERR_NO_DECL,ERR_TYPE_EXPECTED,ERR_BOOL_TYPE_EXPECTED,ERR_TYPE_MISMATCH,ERR_INVALID_TYPE,ERR_KIND_NOT_STRUCT,ERR_FIELD_NOT_DECL,ERR_KIND_NOT_ARRAY,ERR_INVALID_INDEX_TYPE,ERR_KIND_NOT_VAR,ERR_KIND_NOT_FUNCTION,ERR_TOO_MANY_ARGS,ERR_PARAM_TYPE,ERR_TOO_FEW_ARGS,ERR_RETURN_TYPE_MISMATCH
} errorcode;

void semantics(int rule);
void Error(errorcode code);

typedef struct {
    t_nterm nont;
    union {
        struct {
            pobject obj;
            int name;
        } ID;
        struct {
            pobject type;
        } T,E,L,R,TM,F,LV;
        struct{
            pobject list;
        } LI,DC;
        struct{
            pobject list;
            int nSize;
        } LP;
        struct{
            bool val;
            pobject type;
        } BOOL;
        struct {
            pobject type;
            int pos;
            union {
                int n;
                char c;
                string* s;
            } val;
        } CONST;
        struct{
            pobject type;
            pobject param;
            bool err;
        }MC;
        struct{
            pobject type;
            pobject param;
            bool err;
            int n;
        } LE;
    }_;
} t_attrib;