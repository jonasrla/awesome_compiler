#include "analisador_lexico.h"
#include <list>

using namespace std;

char nextChar = '\x20';
t_token token = UNKNOWN;
int tokenSecundario = 0;
FILE *program;
list<t_const> constantList;

token_dict ReservedWords;
sec_token_dict UnreservedWords;

t_token nextToken(){

    while (isspace(nextChar)){
        nextChar = readChar();
    }
    if (isalpha(nextChar)){
        string text = "";
        
        do {
            text += nextChar;
            nextChar = readChar();
        } while (isalnum(nextChar) || nextChar == '_');

        token = searchKeyWord(text);
        
        if(token == ID)
            tokenSecundario = searchName(text);

    } else if (isdigit(nextChar)){
        string numeral = "";
        do {
            numeral += nextChar;
            nextChar = readChar();
        } while (isdigit(nextChar));

        token = NUMERAL;
        tokenSecundario = addIntConst(stoi(numeral));

    } else if (nextChar == '"') {
        string str;
        nextChar = readChar();
        do {
            str += nextChar;
            nextChar = readChar();
        } while (nextChar != '"');

        token = STRING;
        tokenSecundario = addStringConst(str);
    } else if (nextChar == '\0') {
        return END;
    } else {
        switch(nextChar) {
            case '\'':
                nextChar = readChar();
                token = CHARACTER;
                tokenSecundario = addCharConst(nextChar);
                readChar();
                nextChar = readChar();
                break;
     
            case ':':
                nextChar = readChar();
                token = COLON;
                break;

            case ';':
                nextChar = readChar();
                token = SEMI_COLON;
                break;

            case ',':
                nextChar = readChar();
                token = COMMA;
                break;

            case '[':
                nextChar = readChar();
                token = LEFT_SQUARE;
                break;

            case ']':
                nextChar = readChar();
                token = RIGHT_SQUARE;
                break;

            case '{':
                nextChar = readChar();
                token = LEFT_BRACES;
                break;

            case '}':
                nextChar = readChar();
                token = RIGHT_BRACES;
                break;

            case '(':
                nextChar = readChar();
                token = LEFT_PARENTHESIS;
                break;

            case ')':
                nextChar = readChar();
                token = RIGHT_PARENTHESIS;
                break;

            case '&':
                nextChar = readChar();
                token = AND;
                break;

            case '|':
                nextChar = readChar();
                token = OR;
                break;

            case '*':
                nextChar = readChar();
                token = TIMES;
                break;

            case '/':
                nextChar = readChar();
                token = DIVIDE;
                break;

            case '.':
                nextChar = readChar();
                token = DOT;
                break;

            case '+':
                nextChar = readChar();
                if ( nextChar == '+'){
                    token = PLUS_PLUS;
                    nextChar = readChar();
                } else {
                    token = PLUS;
                }
                break;

            case '!':
                nextChar = readChar();
                if ( nextChar == '='){
                    token = NOT_EQUAL;
                    nextChar = readChar();
                } else {
                    token = NOT;
                }
                break;

            case '=':
                nextChar = readChar();
                if ( nextChar == '='){
                    token = EQUAL_EQUAL;
                    nextChar = readChar();
                } else {
                    token = EQUALS;
                }
                break;

            case '-':
                nextChar = readChar();
                if ( nextChar == '-'){
                    token = MINUS_MINUS;
                    nextChar = readChar();
                } else {
                    token = MINUS;
                }
                break;

            case '<':
                nextChar = readChar();
                if ( nextChar == '='){
                    token = LESS_OR_EQUAL;
                    nextChar = readChar();
                } else {
                    token = LESS_THAN;
                }
                break;

            case '>':
                nextChar = readChar();
                if ( nextChar == '='){
                    token = GREATER_OR_EQUAL;
                    nextChar = readChar();
                } else {
                    token = GREATER_THAN;
                }
                break;
            default:
                token = UNKNOWN;
        }
    }
    return token;
}

int searchName(string name){
    if (UnreservedWords.count(name) == 0)
        UnreservedWords[name] = UnreservedWords.size();
    return UnreservedWords[name];
}

int addIntConst(int value){
    t_const instance;
    instance._.nVal = value;
    constantList.push_back(instance);
    return constantList.size();
}

int addCharConst(char value){
    t_const instance;
    instance._.cVal = value;
    constantList.push_back(instance);
    return constantList.size();
}

int addStringConst(char * s){
    t_const instance;
    instance._.sVal = s;
    constantList.push_back(instance);
    return constantList.size();
}

void populateReservedWords(){
    ReservedWords["array"] = ARRAY;
    ReservedWords["boolean"] = BOOLEAN;
    ReservedWords["break"] = BREAK;
    ReservedWords["char"] = CHAR;
    ReservedWords["continue"] = CONTINUE;
    ReservedWords["do"] = DO;
    ReservedWords["else"] = ELSE;
    ReservedWords["false"] = FALSE;
    ReservedWords["function"] = FUNCTION;
    ReservedWords["if"] = IF;
    ReservedWords["integer"] = INTEGER;
    ReservedWords["of"] = OF;
    ReservedWords["string"] = STRING;
    ReservedWords["struct"] = STRUCT;
    ReservedWords["true"] = TRUE;
    ReservedWords["type"] = TYPE;
    ReservedWords["var"] = VAR;
    ReservedWords["while"] = WHILE;
    ReservedWords["return"] = RETURN;
}

t_token searchKeyWord(string name){
    if  (ReservedWords.empty())
        populateReservedWords();
    if (ReservedWords.count(name)) {
        return ReservedWords[name];
    }
    return ID;
}

char readChar(){
    char res = fgetc(program);
    if (res != EOF){
        return res;
    } else {
        return '\0';
    }
}