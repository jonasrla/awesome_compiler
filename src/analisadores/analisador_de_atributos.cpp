#include "analisador_de_atributos.h"
#include <iostream>
#include <list>
#include "analisador_de_escopo.h"


bool hasError = false;
fpos_t functionVarPos;

list<t_attrib> StackSem;


int nFuncs = 0;
pobject curFunction;

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
    static int name;//,n,l,l1,l2;
    static pobject p,f,t;
    static t_attrib IDD_,IDU_,ID_,MC_,LE_,F_,DC_,MT_,T_,LI_,LI0_,LI1_,TRU_,FALS_,STR_,CHR_,NUM_,DC0_,DC1_,LP_,LP0_,LP1_,E_,E0_,E1_,L_,L0_,L1_,R_,R0_,R1_,K_,K0_,K1_,F0_,F1_,LV_,LV0_,LV1_,LE0_,LE1_,ME_,MW_;
    switch(rule){
        case TYPE_IDD_EQUALS_ARRAY_NT_NUM_OF_TP_RULE:  // DT -> TYPE IDD EQUALS ARRAY LEFT_SQUARE NT_NUM RIGHT_SQUARE OF TP

            T_ = StackSem.front();
            StackSem.pop_front();
            IDD_ = StackSem.front();
            StackSem.pop_front();
            p = IDD_._.ID.obj;
            t = T_._.T.type;
            p->eKind = ALIAS_TYPE_;
            p->_.Alias.pBaseType = t;

            break;

        case TYPE_IDD_EQUALS_STRUCT_NB_DC_RULE:        // DT -> TYPE IDD EQUALS STRUCT NB LEFT_BRACES DC RIGHT_BRACES

            DC_ = StackSem.front();
            StackSem.pop_front();
            IDD_ = StackSem.front();
            StackSem.pop_front();
            p = IDD_._.ID.obj;
            p->eKind = STRUCT_TYPE_;
            p->_.Struct.pFields = DC_._.DC.list;
            EndBlock();

            break;

        case TYPE_IDD_EQUALS_TP_RULE:                  // DT -> TYPE IDD EQUALS TP
        //TODO


            break;

        case INTEGER_RULE:                             // TP -> INTEGER
        //TODO


            break;

        case CHAR_RULE:                                // TP -> CHAR
        //TODO


            break;

        case BOOLEAN_RULE:                            // TP -> BOOLEAN
        //TODO


            break;

        case STRING_RULE:                             // TP -> STRING
        //TODO


            break;

        case TP_IDU_RULE:                             // TP -> IDU
        //TODO


            break;

        case DC_LI_TP_RULE:                           // DC -> DC SEMI_COLON LI COLON TP
        //TODO


            break;

        case LI_TP_RULE:                              // DC -> LI COLON TP
        //TODO


            break;

        case FUNCTION_IDD_NB_LP_TP_B_RULE:            // DF -> FUNCTION IDD NB LEFT_PARENTHESIS LP RIGHT_PARENTHESIS COLON TP MF B

            EndBlock();

            break;

        case LP_IDD_TP_RULE:                          // LP -> LP COMMA IDD COLON TP
        //TODO


            break;

        case IDD_TP_RULE:                             // LP -> IDD COLON TP
        //TODO


            break;

        case LDV_LS_RULE:                             // B -> LEFT_BRACES LDV LS RIGHT_BRACES
        //TODO


            break;

        case LDV_DV_RULE:                             // LDV -> LDV DV
        //TODO


            break;

        case DV_RULE:                                 // LDV -> DV
        //TODO


            break;

        case LS_S_RULE:                               // LS -> LS S
        //TODO


            break;

        case S_RULE:                                  // LS -> S
        //TODO


            break;

        case VAR_LI_TP_RULE:                          // DV -> VAR LI COLON TP SEMI_COLON
        //TODO


            break;

        case LI_IDD_RULE:                             // LI -> LI COMMA IDD
        //TODO


            break;

        case IDD_RULE:                                // LI -> IDD
        //TODO


            break;

        case IF_E_S_RULE:                             // S -> IF LEFT_PARENTHESIS E RIGHT_PARENTHESIS S

            MT_ = StackSem.front();
            StackSem.pop_front();
            E_ = StackSem.front();
            StackSem.pop_front();
            
            t = E_._.E.type;
            if( !CheckTypes(t,pBool)){
                Error(ERR_BOOL_TYPE_EXPECTED);
            }

            break;

        case IF_E_S_ELSE_S_RULE:                      // S -> IF LEFT_PARENTHESIS E RIGHT_PARENTHESIS S ELSE S
        //TODO


            break;

        case WHILE_E_S_RULE:                          // S -> WHILE LEFT_PARENTHESIS E RIGHT_PARENTHESIS S
        //TODO


            break;

        case DO_S_WHILE_E_RULE:                       // S -> DO S WHILE LEFT_PARENTHESIS E RIGHT_PARENTHESIS SEMI_COLON
        //TODO


            break;

        case B_RULE:                                  // S -> B
        //TODO


            break;

        case LV_EQUALS_E_RULE:                        // S -> LV EQUALS E SEMI_COLON
        //TODO


            break;

        case BREAK_RULE:                              // S -> BREAK SEMI_COLON
        //TODO


            break;

        case CONTINUE_RULE:                           // S -> CONTINUE SEMI_COLON
        //TODO


            break;

        case E_AND_L_RULE:                            // E -> E AND L
        //TODO


            break;

        case E_OR_L_RULE:                             // E -> E OR L
        //TODO


            break;

        case L_RULE:                                  // E -> L
        //TODO


            break;

        case L_LESS_THAN_R_RULE:                      // L -> L LESS_THAN R
        //TODO


            break;

        case L_GREATER_THAN_R_RULE:                   // L -> L GREATER_THAN R
        //TODO


            break;

        case L_LESS_OR_EQUAL_R_RULE:                  // L -> L LESS_OR_EQUAL R
        //TODO


            break;

        case L_GREATER_OR_EQUAL_R_RULE:               // L -> L GREATER_OR_EQUAL R
        //TODO


            break;

        case L_EQUAL_EQUAL_R_RULE:                    // L -> L EQUAL_EQUAL R
        //TODO


            break;

        case L_NOT_EQUAL_R_RULE:                      // L -> L NOT_EQUAL R
        //TODO


            break;

        case R_RULE:                                  // L -> R
        //TODO


            break;

        case R_PLUS_TM_RULE:                          // R -> R PLUS TM
        //TODO


            break;

        case R_MINUS_TM_RULE:                         // R -> R MINUS TM
        //TODO


            break;

        case TM_RULE:                                 // R -> TM
        //TODO


            break;

        case TM_TIMES_F_RULE:                         // TM -> TM TIMES F
        //TODO


            break;

        case TM_DIVIDE_F_RULE:                        // TM -> TM DIVIDE F
        //TODO


            break;

        case F_RULE:                                  // TM -> F
        //TODO


            break;

        case LV_RULE:                                 // F -> LV
        //TODO


            break;

        case PLUS_PLUS_LV_RULE:                       // F -> PLUS_PLUS LV
        //TODO


            break;

        case MINUS_MINUS_LV_RULE:                     // F -> MINUS_MINUS LV
        //TODO


            break;

        case LV_PLUS_PLUS_RULE:                       // F -> LV PLUS_PLUS
        //TODO


            break;

        case LV_MINUS_MINUS_RULE:                     // F -> LV MINUS_MINUS
        //TODO


            break;

        case F_E_RULE:                                // F -> LEFT_PARENTHESIS E RIGHT_PARENTHESIS
        //TODO


            break;

        case IDU_LE_RULE:                             // F -> IDU MC LEFT_PARENTHESIS LE RIGHT_PARENTHESIS

            std::cout << "IDU_LE_RULE " << currentLine << std::endl;
            LE_ = StackSem.front();
            StackSem.pop_front();
            MC_ = StackSem.front();
            StackSem.pop_front();
            IDU_ = StackSem.front();
            StackSem.pop_front();
            f = IDU_._.ID.obj;
            F_._.F.type = MC_._.MC.type;
            if(!LE_._.LE.err){
                if(LE_._.LE.n-1 < f->_.Function.nParams && LE_._.LE.n != 0){
                    Error(ERR_TOO_FEW_ARGS);
                }
               else if(LE_._.LE.n-1 > f->_.Function.nParams){
                    Error(ERR_TOO_MANY_ARGS);
                }
            }
            F_.nont = F;
            StackSem.push_front(F_);

            break;

        case MINUS_F_RULE:                            // F -> MINUS F
        //TODO


            break;

        case NOT_F_RULE:                              // F -> NOT F
        //TODO


            break;

        case NT_TRUE_RULE:                            // F -> NT_TRUE
        //TODO


            break;

        case NT_FALSE_RULE:                           // F -> NT_FALSE
        //TODO


            break;

        case NT_CHR_RULE:                             // F -> NT_CHR
        //TODO


            break;

        case NT_STR_RULE:                             // F -> NT_STR
        //TODO


            break;

        case NT_NUM_RULE:                             // F -> NT_NUM
        //TODO


            break;

        case LE_COMMA_E_RULE:                         // LE -> LE COMMA E
        //TODO


            break;

        case LE_E_RULE:                               // LE -> E
        //TODO


            break;

        case LV_DOT_ID_RULE:                          // LV -> LV DOT ID
        //TODO


            break;

        case LV_E_RULE:                               // LV -> LV LEFT_SQUARE E RIGHT_SQUARE
        //TODO


            break;

        case LV_IDU_RULE:                             // LV -> IDU
        //TODO


            break;

        case IDD_IDENTIFIER_RULE:                     // IDD -> IDENTIFIER

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

        case IDU_IDENTIFIER_RULE:                     // IDU -> IDENTIFIER

            name = tokenSecundario;
            IDU_.nont = IDU;
            IDU_._.ID.name = name;
            
            if((p = Find(name)) == NULL){
                Error(ERR_NO_DECL);
                p = Define(name);
            }
            IDU_._.ID.obj = p;
            StackSem.push_front(IDU_);

            break;

        case ID_IDENTIFIER_RULE:                      // ID -> IDENTIFIER

            ID_.nont = ID;
            name = tokenSecundario;
            ID_._.ID.name = name;
            ID_._.ID.obj = NULL;
            StackSem.push_front(ID_);

            break;

        case TRUE_RULE:                               // NT_TRUE -> TRUE
        //TODO


            break;

        case FALSE_RULE:                              // NT_FALSE -> FALSE
        //TODO


            break;

        case CHARACTER_RULE:                          // NT_CHR -> CHARACTER
        //TODO


            break;

        case STRINGVAL_RULE:                          // NT_STR -> STRINGVAL
        //TODO


            break;

        case NUMERAL_RULE:                            // NT_NUM -> NUMERAL
        //TODO


            break;

        case NB_RULE:                                   // NB -> ''

            NewBlock();

            break;

        case MF_RULE:                                   // MF -> ''
        //TODO


            break;

        case MC_RULE:                                   // MC -> ''
        //TODO


            break;
            
        default:
            break;
    }
}