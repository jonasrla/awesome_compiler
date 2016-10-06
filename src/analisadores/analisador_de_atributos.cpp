#include "analisador_de_atributos.h"
#include <iostream>
#include <stack>
#include "analisador_de_escopo.h"
#include <list>



/*Global Variables*/ 

/*Output File*/
bool hasError = false;
fpos_t functionVarPos;
/*Semantic Stack*/

list<t_attrib> StackSem;
/*Functions*/

int nFuncs = 0;
pobject curFunction;

//int nCurrentLevel = 0; //TIREI PQ TAVA DANDO CONFLITO DE REDECLARAÇÃO - JA TINHA SIDO DECLARADA NO ANALISADOR DE ESCOPO

//SCALAR TYPES

object int_ = {-1, NULL, SCALAR_TYPE_};
pobject pInt = &int_;

object char_ = {-1, NULL, SCALAR_TYPE_};
pobject pChar = &char_;

object bool_ = {-1, NULL, SCALAR_TYPE_};
pobject pBool = &bool_;

object string_ = {-1, NULL, SCALAR_TYPE_};
pobject pString = &string_;

object universal_ = {-1, NULL, SCALAR_TYPE_};

pobject pUniversal = &universal_;

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

bool CheckTypes(pobject t1,pobject t2){
    if(t1 == t2){
        return true;
    }
    else if(t1 == pUniversal || t2 == pUniversal){
        return true;
    }
    else if(t1->eKind == UNIVERSAL_ || t2->eKind == UNIVERSAL_){
        return true;
    }
    else if(t1->eKind == ALIAS_TYPE_ && t2->eKind != ALIAS_TYPE_){
        return CheckTypes(t1->_.Alias.pBaseType,t2);
    }
    else if(t1->eKind != ALIAS_TYPE_ && t2->eKind == ALIAS_TYPE_){
        return CheckTypes(t1,t2->_.Alias.pBaseType);
    }
    else if(t1->eKind == t2->eKind){
        //alias
        if(t1->eKind == ALIAS_TYPE_){
            return CheckTypes(t1->_.Alias.pBaseType,t2->_.Alias.pBaseType);
        }
        //array
        else if(t1->eKind == ARRAY_TYPE_){
            if(t1->_.Array.nNumElems == t2->_.Array.nNumElems){
                return CheckTypes(t1->_.Array.pElemType,t2->_.Array.pElemType);
            }
        }
        //struct
        else if(t1->eKind == STRUCT_TYPE_){
            pobject f1 = t1->_.Struct.pFields;
            pobject f2 = t2->_.Struct.pFields;
            
            while( f1 != NULL && f2 != NULL){
                if( ! CheckTypes(f1->_.Field.pType,f2->_.Field.pType)){
                    return false;
                }
            }
            return (f1 == NULL && f2 == NULL);
        }
    }
    
    return false;
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
            StackSem.push_front(IDD_);
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
            StackSem.push_front(IDU_);
            break;

        case ID_IDENTIFIER_RULE:
            ID_.nont = ID;
            name = tokenSecundario;
            ID_._.ID.name = name;
            ID_._.ID.obj = NULL;
            StackSem.push_front(ID_);
            break;


        case INTEGER_RULE:
          T_._.T.type = pInt;
          T_.nont = T;
          //T_.nSize = 1;
          StackSem.push_front(T_);
          break;

        case CHAR_RULE:
          T_._.T.type = pChar;
          T_.nont = T;
          //T_.nSize = 1;
          StackSem.push_front(T_);
          break;

        case BOOLEAN_RULE:
          T_._.T.type = pBool;
          T_.nont = T;
          //T_.nSize = 1;
          StackSem.push_front(T_);
          break;

        case STRING_RULE:
          T_._.T.type = pString;
          T_.nont = T;
          StackSem.push_front(T_);
          break;

        case TP_IDU_RULE: //************************************
          IDU_ = StackSem.front();
          p = IDU_._.ID.obj;
          StackSem.pop_front();
          
          if( IS_TYPE_KIND(p->eKind) || p->eKind == UNIVERSAL_) {
            T_._.T.type = p;
          } else {
            T_._.T.type = pUniversal;
            Error(ERR_TYPE_EXPECTED);
          }
          T_.nont = T;
          StackSem.push_front(T_);
          break;

        case IDD_RULE:
          IDD_ = StackSem.front();
          StackSem.pop_front();
          LI_.nont = LI;
          LI_._.LI.list = IDD_._.ID.obj;
          StackSem.push_front(LI_);
          break;

        case LI_IDD_RULE:
          IDD_ = StackSem.front();
          StackSem.pop_front();
          LI1_ = StackSem.front();
          StackSem.pop_front();
          LI0_._.LI.list = IDD_._.ID.obj;
          LI0_._.LI.list->pNext = LI1_._.LI.list;
          LI0_.nont = LI;
          StackSem.push_front(LI0_);
          break;

        case VAR_LI_TP_RULE:
          T_ = StackSem.front();
          StackSem.pop_front();
          LI_ = StackSem.front();
          StackSem.pop_front();
          p = LI_._.LI.list;
          t = T_._.T.type;
          while( p != NULL && p->eKind == NO_KIND_DEF_ ) {
            p->eKind = VAR_;
            p->_.Var.pType = t;
            p = p->pNext;
            //p->_.Var.nSize = T_.nSize;
            //p->_.Var.nIndex = n;
            //n += T_.nSize;
          }
          break;

        case NT_TRUE_RULE:
          TRU_._.TRU.type = pBool;
          TRU_._.TRU.val = true;
          TRU_.nont = TRU;
          StackSem.push_front(TRU_);
          break;
        case NT_FALSE_RULE:
          FALS_._.FALS.type = pBool;
          FALS_._.FALS.val = false;
          FALS_.nont = FALS;
          StackSem.push_front(FALS_);
          break;
        case NT_CHR_RULE:
          CHR_._.CHR.type = pChar;
          CHR_._.CHR.pos = tokenSecundario;
          CHR_._.CHR.val = getCharConst(tokenSecundario);
          CHR_.nont = CHR;
          StackSem.push_front(CHR_);
          break;
        case STR_RULE:
          STR_._.STR.type = pString;
          STR_._.STR.pos = tokenSecundario;
          STR_._.STR.val = getStringConst(tokenSecundario);
          STR_.nont = STR;
          StackSem.push_front(STR_);
          break;
        case NT_NUM_RULE:
          NUM_._.NUM.type = pInt;
          NUM_._.NUM.pos = tokenSecundario;
          NUM_._.NUM.val = getIntConst(tokenSecundario);
          NUM_.nont = NUM;
          StackSem.push_front(NUM_);
          break;


        case IF_E_S_RULE:
            MT_ = StackSem.front();
            StackSem.pop_front();
            E_ = StackSem.front();
            StackSem.pop_front();
            
            t = E_._.E.type;
            if( !CheckTypes(t,pBool)){
                Error(ERR_BOOL_TYPE_EXPECTED);
            }
            
            break;

        case L_GREATER_THAN_R_RULE:
            R_ = StackSem.front();
            StackSem.pop_front();
            L1_ = StackSem.front();
            StackSem.pop_front();
            
            if( !CheckTypes(L1_._.L.type,R_._.R.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            L0_._.L.type = pBool;
            L0_.nont = L;
            StackSem.push_front(L0_);
            break;


    }
}