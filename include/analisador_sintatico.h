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
    P = 51,LDE,DE,DT,TP,DC,DF,LP,B,LDV,LS,DV,LI,S,E,L,R,TM,F,LE,LV,IDD,IDU,ID,NT_TRUE,NT_FALSE,NT_CHR,NT_STR,NT_NUM,NB,MF,MC
} t_nterm;

void parse();

#define TYPE_IDD_EQUALS_ARRAY_NT_NUM_OF_TP_RULE 5  // DT -> TYPE IDD EQUALS ARRAY LEFT_SQUARE NT_NUM RIGHT_SQUARE OF TP
#define TYPE_IDD_EQUALS_STRUCT_NB_DC_RULE 6        // DT -> TYPE IDD EQUALS STRUCT NB LEFT_BRACES DC RIGHT_BRACES
#define TYPE_IDD_EQUALS_TP_RULE 7                  // DT -> TYPE IDD EQUALS TP

#define INTEGER_RULE 8                             // TP -> INTEGER
#define CHAR_RULE 9                                // TP -> CHAR
#define BOOLEAN_RULE 10                            // TP -> BOOLEAN
#define STRING_RULE 11                             // TP -> STRING
#define TP_IDU_RULE 12                             // TP -> IDU

#define DC_LI_TP_RULE 13                           // DC -> DC SEMI_COLON LI COLON TP
#define LI_TP_RULE 14                              // DC -> LI COLON TP

#define FUNCTION_IDD_NB_LP_TP_B_RULE 15            // DF -> FUNCTION IDD NB LEFT_PARENTHESIS LP RIGHT_PARENTHESIS COLON TP MF B

#define LP_IDD_TP_RULE 16                          // LP -> LP COMMA IDD COLON TP
#define IDD_TP_RULE 17                             // LP -> IDD COLON TP

#define LDV_LS_RULE 18                             // B -> LEFT_BRACES LDV LS RIGHT_BRACES

#define LDV_DV_RULE 19                             // LDV -> LDV DV
#define DV_RULE 20                                 // LDV -> DV

#define LS_S_RULE 21                               // LS -> LS S
#define S_RULE 22                                  // LS -> S

#define VAR_LI_TP_RULE 23                          // DV -> VAR LI COLON TP SEMI_COLON

#define LI_IDD_RULE 24                             // LI -> LI COMMA IDD
#define IDD_RULE 25                                // LI -> IDD

#define IF_E_S_RULE 26                             // S -> IF LEFT_PARENTHESIS E RIGHT_PARENTHESIS S
#define IF_E_S_ELSE_S_RULE 27                      // S -> IF LEFT_PARENTHESIS E RIGHT_PARENTHESIS S ELSE S
#define WHILE_E_S_RULE 28                          // S -> WHILE LEFT_PARENTHESIS E RIGHT_PARENTHESIS S
#define DO_S_WHILE_E_RULE 29                       // S -> DO S WHILE LEFT_PARENTHESIS E RIGHT_PARENTHESIS SEMI_COLON
#define B_RULE 30                                  // S -> NB B
#define LV_EQUALS_E_RULE 31                        // S -> LV EQUALS E SEMI_COLON
#define BREAK_RULE 32                              // S -> BREAK SEMI_COLON
#define CONTINUE_RULE 33                           // S -> CONTINUE SEMI_COLON

#define E_AND_L_RULE 34                            // E -> E AND L
#define E_OR_L_RULE 35                             // E -> E OR L
#define L_RULE 36                                  // E -> L

#define L_LESS_THAN_R_RULE 37                      // L -> L LESS_THAN R
#define L_GREATER_THAN_R_RULE 38                   // L -> L GREATER_THAN R
#define L_LESS_OR_EQUAL_R_RULE 39                  // L -> L LESS_OR_EQUAL R
#define L_GREATER_OR_EQUAL_R_RULE 40               // L -> L GREATER_OR_EQUAL R
#define L_EQUAL_EQUAL_R_RULE 41                    // L -> L EQUAL_EQUAL R
#define L_NOT_EQUAL_R_RULE 42                      // L -> L NOT_EQUAL R
#define R_RULE 43                                  // L -> R

#define R_PLUS_TM_RULE 44                          // R -> R PLUS TM
#define R_MINUS_TM_RULE 45                         // R -> R MINUS TM
#define TM_RULE 46                                 // R -> TM

#define TM_TIMES_F_RULE 47                         // TM -> TM TIMES F
#define TM_DIVIDE_F_RULE 48                        // TM -> TM DIVIDE F
#define F_RULE 49                                  // TM -> F

#define LV_RULE 50                                 // F -> LV
#define PLUS_PLUS_LV_RULE 51                       // F -> PLUS_PLUS LV
#define MINUS_MINUS_LV_RULE 52                     // F -> MINUS_MINUS LV
#define LV_PLUS_PLUS_RULE 53                       // F -> LV PLUS_PLUS
#define LV_MINUS_MINUS_RULE 54                     // F -> LV MINUS_MINUS
#define F_E_RULE 55                                // F -> LEFT_PARENTHESIS E RIGHT_PARENTHESIS
#define IDU_LE_RULE 56                             // F -> IDU MC LEFT_PARENTHESIS LE RIGHT_PARENTHESIS
#define MINUS_F_RULE 57                            // F -> MINUS F
#define NOT_F_RULE 58                              // F -> NOT F
#define NT_TRUE_RULE 59                            // F -> NT_TRUE
#define NT_FALSE_RULE 60                           // F -> NT_FALSE
#define NT_CHR_RULE 61                             // F -> NT_CHR
#define NT_STR_RULE 62                             // F -> NT_STR
#define NT_NUM_RULE 63                             // F -> NT_NUM

#define LE_COMMA_E_RULE 64                         // LE -> LE COMMA E
#define LE_E_RULE 65                               // LE -> E

#define LV_DOT_ID_RULE 66                          // LV -> LV DOT ID
#define LV_E_RULE 67                               // LV -> LV LEFT_SQUARE E RIGHT_SQUARE
#define LV_IDU_RULE 68                             // LV -> IDU

#define IDD_IDENTIFIER_RULE 69                     // IDD -> IDENTIFIER
#define IDU_IDENTIFIER_RULE 70                     // IDU -> IDENTIFIER
#define ID_IDENTIFIER_RULE 71                      // ID -> IDENTIFIER

#define TRUE_RULE 72                               // NT_TRUE -> TRUE
#define FALSE_RULE 73                              // NT_FALSE -> FALSE
#define CHARACTER_RULE 74                          // NT_CHR -> CHARACTER
#define STRINGVAL_RULE 75                          // NT_STR -> STRINGVAL
#define NUMERAL_RULE 76                            // NT_NUM -> NUMERAL

#define NB_RULE 77									// NB -> ''
#define MF_RULE 78									// MF -> ''
#define MC_RULE 79									// MC -> ''