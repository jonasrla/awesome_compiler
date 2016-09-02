#pragma once

#include <string>

using namespace std;

typedef enum {
// palavras reservadas
ARRAY, BOOLEAN, BREAK, CHAR, CONTINUE, DO, ELSE, FALSE, FUNCTION, IF, INTEGER, OF, STRING,
STRUCT, TRUE, TYPE, VAR, WHILE, RETURN , 

// simbolos
COLON, SEMI_COLON, COMMA, EQUALS, LEFT_SQUARE, RIGHT_SQUARE, LEFT_BRACES, RIGHT_BRACES,
LEFT_PARENTHESIS, RIGHT_PARENTHESIS, AND, OR, LESS_THAN, GREATER_THAN, LESS_OR_EQUAL,
GREATER_OR_EQUAL, NOT_EQUAL, EQUAL_EQUAL, PLUS, PLUS_PLUS, MINUS, MINUS_MINUS, TIMES,
DIVIDE, DOT, NOT,

// tokens regulares
CHARACTER, NUMERAL, STRINGVAL, ID,

// token deconhecido
UNKNOWN,

// fim do arquivo
END
} t_token;

typedef struct
{
    char type; //0-char, 1-int, 2-string
    union{
        char cVal;
        int nVal;
        char* sVal;
    } _ ;
} t_const;

extern char nextChar;
extern t_token token;
extern int tokenSecundario;
extern FILE* program;

// Busca entre as palavras reservadas
t_token searchKeyWord(string name);             

// busca um token secundário
int searchName(string name);                    

int addCharConst(char c);                       //
int addIntConst(int n);                         //
int addStringConst(char* s);                   

char getCharConst(int n);
int  getIntConst(int n);
string getStringConst(int n);

char readChar();                                //

t_token nextToken();                            //