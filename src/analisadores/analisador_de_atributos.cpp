#include "analisador_de_atributos.h"
#include <iostream>
#include <stack>

stack<t_attrib> StackSem;

bool hasError = false;

void Error(errorcode code){
    hasError = true;
    std::cout << "Linha: " << currentLine << " - ";
    switch(code){
        case ERR_NO_DECL:
            std::cout << "Variavel nao declarada";
            break;
        case ERR_REDCL:
            std::cout << "Variavel ja foi declarada";
            break;
        case ERR_TYPE_EXPECTED:
            std::cout << "Type Expected: Um tipo nao foi declarado anteriormente";
            break;
        case ERR_BOOL_TYPE_EXPECTED:
            std::cout << "Bool Expected: Um tipo booleano e esperado para expressao";
            break;
        case ERR_INVALID_TYPE:
            std::cout << "Invalid Type: O tipo e invalido para a operacao";
            break;
        case ERR_TYPE_MISMATCH:
            std::cout << "Type Mismatch: O tipo e invalido para a operacao";
            break;
        case ERR_KIND_NOT_STRUCT:
            std::cout << "Kind not Struct: A operacao so pode ser realizada em tipos Struct";
            break;
        case ERR_FIELD_NOT_DECL:
            std::cout << "Field not Declared: O campo nao foi declarado na estrutura";
            break;
        case ERR_KIND_NOT_ARRAY:
            std::cout << "Kind not Array: A operacao so pode ser realizada para um Array";
            break;
        case ERR_INVALID_INDEX_TYPE:
            std::cout << "Invalid Index: O Indice especificado para o Array e invalido";
            break;
        case ERR_KIND_NOT_VAR:
            std::cout << "Kind not Var: A operacao so e valida com tipos Var";
            break;
        case ERR_KIND_NOT_FUNCTION:
            std::cout << "Kind not Function: A operacao so e valida com tipos Function";
            break;
        case ERR_TOO_FEW_ARGS:
            std::cout << "Too Few Args: O numero de parametros especificado nao e suficiente";
            break;
        case ERR_TOO_MANY_ARGS:
            std::cout << "Too Many Args: O numero de parametros especificado e maior que o especificado";
            break;
        case ERR_PARAM_TYPE:
            std::cout << "Param Type: O tipo especificado para o parametro e invalido";
            break;
        case ERR_RETURN_TYPE_MISMATCH:
            std::cout << "Return Type Mismatch: O tipo de retorno não corresponde ao tipo especificado para a função" << endl;
            break;
        default:
            break;
    }
    std::cout << std::endl;
}

void semantics(int rule){
    static int name,n,l,l1,l2;
    static pobject p,t,f;
    static t_attrib IDD_,IDU_,ID_,T_,LI_,LI0_,LI1_,TRU_,FALS_,STR_,CHR_,NUM_,DC_,DC0_,DC1_,LP_,LP0_,LP1_,E_,E0_,E1_,L_,L0_,L1_,R_,R0_,R1_,K_,K0_,K1_,F_,F0_,F1_,LV_,LV0_,LV1_,MC_,LE_,LE0_,LE1_,MT_,ME_,MW_;
    switch(rule){
        case IDD_IDENTIFIER_RULE:
            name = tokenSecundario;
            IDD_.nont = IDD;
            IDD_._.ID.name = name;
            if( (p = Search(name)) != NULL){
                Error(ERR_REDCL);
            }
            else{
                p = Define(name);
            }
            p->eKind = NO_KIND_DEF_;
            IDD_._.ID.obj = p;
            StackSem.push(IDD_);
            break;
        case IDU_IDENTIFIER_RULE:
            name = tokenSecundario;
            IDU_.nont = IDU;
            IDU_._.ID.name = name;
            
            //cout << "TOKENSECUNDARIO" << name << endl;
            if((p = Find(name)) == NULL){
                Error(ERR_NO_DECL);
                p = Define(name);
            }
            IDU_._.ID.obj = p;
            StackSem.push(IDU_);
            break;
        case ID_IDENTIFIER_RULE:
            ID_.nont = ID;
            name = tokenSecundario;
            ID_._.ID.name = name;
            ID_._.ID.obj = NULL;
            StackSem.push(ID_);
            break;

        }
}