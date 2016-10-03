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

#define TYPE_IDD_EQUALS_ARRAY_NT_NUM_OF_TP_RULE 6
#define TYPE_IDD_EQUALS_STRUCT_NB_DC_RULE 7
#define TYPE_IDD_EQUALS_TP_RULE 8
#define INTEGER_RULE 9
#define CHAR_RULE 10
#define BOOLEAN_RULE 11
#define STRING_RULE 12
#define TP_IDU_RULE 13
#define DC_LI_TP_RULE 14
#define LI_TP_RULE 15
#define FUNCTION_IDD_NB_LP_TP_B_RULE 16
#define LP_IDD_TP_RULE 17
#define IDD_TP_RULE 18
#define LDV_LS_RULE 19
#define LDV_DV_RULE 20
#define DV_RULE 21
#define LS_S_RULE 22
#define S_RULE 23
#define VAR_LI_TP_RULE 24
#define LI_IDD_RULE 25
#define IDD_RULE 26
#define IF_E_S_RULE 27
#define IF_E_S_ELSE_S_RULE 28
#define WHILE_E_S_RULE 29
#define DO_S_WHILE_E_RULE 30
#define B_RULE 31
#define LV_EQUALS_E_RULE 32
#define BREAK_RULE 33
#define CONTINUE_RULE 34
#define E_AND_L_RULE 35
#define E_OR_L_RULE 36
#define L_RULE 37
#define L_LESS_THAN_R_RULE 38
#define L_GREATER_THAN_R_RULE 39
#define L_LESS_OR_EQUAL_R_RULE 40
#define L_GREATER_OR_EQUAL_R_RULE 41
#define L_EQUAL_EQUAL_R_RULE 42
#define L_NOT_EQUAL_R_RULE 43
#define R_RULE 44
#define R_PLUS_TM_RULE 45
#define R_MINUS_TM_RULE 46
#define TM_RULE 47
#define TM_TIMES_F_RULE 48
#define TM_DIVIDE_F_RULE 49
#define F_RULE 50
#define LV_RULE 51
#define PLUS_PLUS_LV_RULE 52
#define MINUS_MINUS_LV_RULE 53
#define LV_PLUS_PLUS_RULE 54
#define LV_MINUS_MINUS_RULE 55
#define F_E_RULE 56
#define IDU_LE_RULE 57
#define MINUS_F_RULE 58
#define NOT_F_RULE 59
#define NT_TRUE_RULE 60
#define NT_FALSE_RULE 61
#define NT_CHR_RULE 62
#define NT_STR_RULE 63
#define NT_NUM_RULE 64
#define LE_COMMA_E_RULE 65
#define LE_E_RULE 66
#define LV_DOT_ID_RULE 67
#define LV_E_RULE 68
#define LV_IDU_RULE 69
#define IDD_IDENTIFIER_RULE 70
#define IDU_IDENTIFIER_RULE 71
#define ID_IDENTIFIER_RULE 72
#define TRUE_RULE 73
#define FALSE_RULE 74
#define CHARACTER_RULE 75
#define STRINGVAL_RULE 76
#define NUMERAL_RULE 77