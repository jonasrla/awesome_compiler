#pragma once

#include "analisador_lexico.h"
#include "analisador_sintatico.h"
#include "analisador_de_escopo.h"
#include <fstream>

extern bool hasError;

extern std::fstream fs;

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
        } E,L,R,TM,F,LV;
        struct {
            pobject type;
            int nSize;
        } T;
        struct{
            pobject list;
        } LI;
        struct{
            pobject list;
            int nSize;
        } LP,DC;
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
        struct{
            long offset;
        }MF;
        struct{
            int label;
        }MT,ME;
    }_;
} t_attrib;

void print_nterm(t_nterm val);

void print_eKind(t_kind);