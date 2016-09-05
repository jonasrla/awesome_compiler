/*#include <string>
#include <iostream>
#include <stack>
using namespace std;
#define MAX_NEST_LEVEL 50

extern FILE *out;
bool hasError = false;


typedef struct object
{
    int nName;
    struct object *pNext;
    struct obj;
} object, *pobject;

pobject    SymbolTable[MAX_NEST_LEVEL]; 
pobject    SymbolTableLast[MAX_NEST_LEVEL]; 
int        nCurrentLevel = 0; 

int newBlock(void){
    SymbolTable[++nCurrentLevel] = NULL;
    SymbolTableLast[nCurrentLevel] = NULL;
    return nCurrentLevel;
}

int endBlock(void){
    return --nCurrentLevel;
}

pobject define(int aName){
    pobject obj = new object();
    obj->nName = aName;
    obj->pNext = NULL;
    
    if( SymbolTable[nCurrentLevel] == NULL){
        SymbolTable[nCurrentLevel] = obj;
        SymbolTableLast[nCurrentLevel] = obj;
    }
    else{
        SymbolTableLast[nCurrentLevel]->pNext = obj;
        SymbolTableLast[nCurrentLevel] = obj;
    }
    return obj;
}

pobject search (int aName){
    pobject obj = SymbolTable[nCurrentLevel];
    while(obj != NULL){
        if(obj-> nName == aName)
            break;
        else
            obj = obj->pNext;
    }
    return obj;
}

pobject find (int aName)
{
    int i;
    pobject obj = NULL;
    for( i = nCurrentLevel; i >= 0; --i ) {
        obj = SymbolTable[i];
        while( obj != NULL )
        {
            if( obj->nName == aName )
                break;
            else
                obj = obj->pNext;
        }
        if( obj != NULL ) break;
    }
    return obj;
}

typedef enum {
    ERR_REDCL,ERR_NO_DECL
} errorcode;

void Error(errorcode code){
    hasError = true;
    //cout << "Linha: " << currentLine << " - ";
    switch(code){
        case ERR_NO_DECL:
            cout << "Variavel nao declarada";
            break;
        case ERR_REDCL:
            cout << "Variavel ja foi declarada";
            break;
        default:
            break;
    }
    cout << endl;
}

void semantics(int rule){
    static object IDD,IDU,ID;
    static int name
    static pobject p;
    switch(rule){
        case IDD:
            name = tokenSecundario;
            IDD.nName = name;
            if( (p = search(name)) != NULL){
                Error(ERR_REDCL);
            }
            else{
                p = define(name);
            }
            
            IDD.obj = p;
            break;
        case IDU:
            name = tokenSecundario;
            IDU.nName = name;
            
            //cout << "TOKENSECUNDARIO" << name << endl;
            if((p = find(name)) == NULL){
                Error(ERR_NO_DECL);
                p = define(name);
            }
            IDU.obj = p;
            break;
        case ID:
            name = tokenSecundario;
            ID.nName = name;
            ID.obj = NULL;
            break;
   
        case NB:
            newBlock();
            break;
        case DT:
            endBlock();
            break;

        case DF:
            endBlock();
            break;
        default:
            break;
    }
}*/