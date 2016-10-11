#include "analisador_de_atributos.h"
#include <iostream>
#include <vector>
#include "analisador_de_escopo.h"

bool hasError = false;

vector<t_attrib> StackSem;

object int_ = { -1, NULL, SCALAR_TYPE_ };       pobject pInt = &int_;
object char_ = { -1, NULL, SCALAR_TYPE_ };      pobject pChar = &char_;
object bool_ = { -1, NULL, SCALAR_TYPE_ };      pobject pBool = &bool_;
object string_ = { -1, NULL, SCALAR_TYPE_ };    pobject pString = &string_;
object universal_= { -1, NULL, SCALAR_TYPE_ };  pobject pUniversal = &universal_;

int newLabel(){
    static int labelNo = 0;
    return labelNo++;
}


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
    static int name, n, nFuncs, l, l1, l2;
    static long current, offset;
    static pobject p, t, f, t1, t2, o, func;
    static t_attrib IDD_, IDU_, ID_, TP_, LI_, LI0_, LI1_,\
                    TRUE_, FALSE_, CHR_, STR_, NUM_, DC_, \
                    DC0_, DC1_, LP_, LP0_, LP1_, E_, L_,  \
                    E1_, E0_, L0_, L1_, R_, TM_, F_, LV_, \
                    F0_, F1_, LV0_, LV1_, MC_, LE_, LE0_, \
                    LE1_, R0_, R1_, TM0_, TM1_, MF_, MT_, \
                    ME_, MW_;

    switch(rule){

        case IDD_IDENTIFIER_RULE:                     // IDD -> IDENTIFIER

            IDD_.nont = IDD;
            name = tokenSecundario;
            IDD_._.ID.name = name;
            if( (p = Search(name)) != NULL){
                Error(ERR_REDCL);
            }
            else{
                p = Define(name);
            }
            p->eKind = NO_KIND_DEF_;
            IDD_._.ID.obj = p;
            StackSem.push_back(IDD_);
            
            break;

        case IDU_IDENTIFIER_RULE:                     // IDU -> IDENTIFIER

            IDU_.nont = IDU;
            name = tokenSecundario;
            IDU_._.ID.name = name;
            
            if((p = Find(name)) == NULL){
                Error(ERR_NO_DECL);
                p = Define(name);
            }
            IDU_._.ID.obj = p;
            StackSem.push_back(IDU_);

            break;

        case ID_IDENTIFIER_RULE:                      // ID -> IDENTIFIER

            ID_.nont = ID;
            name = tokenSecundario;
            ID_._.ID.name = name;
            ID_._.ID.obj = NULL;
            StackSem.push_back(ID_);

            break;

        case NB_RULE:                                   // NB -> ''

            NewBlock();

            break;

        case INTEGER_RULE:                             // TP -> INTEGER

            TP_.nont = TP;
            TP_._.T.type = pInt;
            TP_._.T.nSize = 1;
            StackSem.push_back(TP_);

            break;

        case CHAR_RULE:                                // TP -> CHAR

            TP_.nont = TP;
            TP_._.T.type = pChar;
            TP_._.T.nSize = 1;
            StackSem.push_back(TP_);

            break;

        case BOOLEAN_RULE:                            // TP -> BOOLEAN

            TP_.nont = TP;
            TP_._.T.type = pBool;
            TP_._.T.nSize = 1;
            StackSem.push_back(TP_);

            break;

        case STRING_RULE:                             // TP -> STRING

            TP_.nont = TP;
            TP_._.T.type = pString;
            TP_._.T.nSize = 1;
            StackSem.push_back(TP_);

            break;

        case TP_IDU_RULE:                             // TP -> IDU

            IDU_ = StackSem.back();
            StackSem.pop_back();
            p = IDU_._.ID.obj;
            if (IS_TYPE_KIND(p->eKind) || p->eKind == UNIVERSAL_) {
                TP_._.T.type = p;
                TP_._.T.nSize = p->_.Alias.nSize;
            } else {
                TP_._.T.type = pUniversal;
                TP_._.T.nSize = 0;
                Error( ERR_TYPE_EXPECTED );
            }
            TP_.nont = TP;
            StackSem.push_back(TP_);

            break;

        case IDD_RULE:                                // LI -> IDD

            IDD_ = StackSem.back();
            StackSem.pop_back();
            LI_.nont = LI;
            LI_._.LI.list = IDD_._.ID.obj;
            StackSem.push_back(LI_);

            break;

        case LI_IDD_RULE:                             // LI -> LI COMMA IDD

            IDD_ = StackSem.back();
            StackSem.pop_back();
            LI1_ = StackSem.back();
            StackSem.pop_back();
            LI0_._.LI.list = LI1_._.LI.list;
            LI0_.nont = LI;
            StackSem.push_back(LI0_);

            break;

        case VAR_LI_TP_RULE:                          // DV -> VAR LI COLON TP SEMI_COLON

            TP_ = StackSem.back();
            t = TP_._.T.type;
            StackSem.pop_back();
            
            LI_ = StackSem.back();
            p = LI_._.LI.list;
            StackSem.pop_back();

            n = f->_.Function.nVars;

            while (p != NULL && p->eKind == NO_KIND_DEF_){
                p->eKind = VAR_;
                p->_.Var.pType = t;

                p->_.Var.nIndex = n;
                p->_.Var.nSize = TP_._.T.nSize;

                n += TP_._.T.nSize;
                p = p->pNext;
            }
            
            f->_.Function.nVars = n;
            
            break;

        case TRUE_RULE:                               // NT_TRUE -> TRUE

            TRUE_.nont = NT_TRUE;
            TRUE_._.BOOL.val = true;
            TRUE_._.BOOL.type = pBool;
            StackSem.push_back(TRUE_);

            break;

        case FALSE_RULE:                              // NT_FALSE -> FALSE
            
            FALSE_.nont = NT_FALSE;
            FALSE_._.BOOL.val = false;
            FALSE_._.BOOL.type = pBool;
            StackSem.push_back(FALSE_);

            break;

        case CHARACTER_RULE:                          // NT_CHR -> CHARACTER

            CHR_.nont = NT_CHR;
            CHR_._.CONST.pos = tokenSecundario;
            CHR_._.CONST.type = pChar;
            CHR_._.CONST.val.c = getCharConst(tokenSecundario);
            StackSem.push_back(CHR_);

            break;

        case STRINGVAL_RULE:                          // NT_STR -> STRINGVAL

            STR_.nont = NT_STR;
            STR_._.CONST.pos = tokenSecundario;
            STR_._.CONST.type = pChar;
            STR_._.CONST.val.s = new string(getStringConst(tokenSecundario));
            StackSem.push_back(STR_);
            break;

        case NUMERAL_RULE:                            // NT_NUM -> NUMERAL
            
            NUM_.nont = NT_NUM;
            NUM_._.CONST.pos = tokenSecundario;
            NUM_._.CONST.type = pInt;
            NUM_._.CONST.val.n = getIntConst(tokenSecundario);
            StackSem.push_back(NUM_);

            break;

        case TYPE_IDD_EQUALS_ARRAY_NT_NUM_OF_TP_RULE:  // DT -> TYPE IDD EQUALS ARRAY LEFT_SQUARE NT_NUM RIGHT_SQUARE OF TP

            TP_ = StackSem.back();
            t = TP_._.T.type;
            StackSem.pop_back();
            
            NUM_ = StackSem.back();
            n = NUM_._.CONST.val.n;
            StackSem.pop_back();

            IDD_ = StackSem.back();
            p = IDD_._.ID.obj;
            StackSem.pop_back();

            p->eKind = ARRAY_TYPE_;
            p->_.Array.nNumElems = n;
            p->_.Array.pElemType = t;
            p->_.Array.nSize = n * TP_._.T.nSize;

            break;

        case TYPE_IDD_EQUALS_TP_RULE:                  // DT -> TYPE IDD EQUALS TP

            TP_ = StackSem.back();
            t = TP_._.T.type;
            StackSem.pop_back();

            IDD_ = StackSem.back();
            p = IDD_._.ID.obj;
            StackSem.pop_back();

            p->eKind =ALIAS_TYPE_;
            p->_.Alias.pBaseType = t;
            p->_.Array.nSize = TP_._.T.nSize;

            break;

        case TYPE_IDD_EQUALS_STRUCT_NB_DC_RULE:        // DT -> TYPE IDD EQUALS STRUCT NB LEFT_BRACES DC RIGHT_BRACES

            DC_ = StackSem.back();
            StackSem.pop_back();

            IDD_ = StackSem.back();
            p = IDD_._.ID.obj;
            StackSem.pop_back();

            p->eKind = STRUCT_TYPE_;
            p->_.Struct.pFields = DC_._.DC.list;
            p->_.Struct.nSize = DC_._.DC.nSize;

            EndBlock();

            break;

        case LI_TP_RULE:                              // DC -> LI COLON TP

            TP_ = StackSem.back();
            t = TP_._.T.type;
            StackSem.pop_back();
            
            LI_ = StackSem.back();
            p = LI_._.LI.list;
            StackSem.pop_back();

            n = 0;

            while (p != NULL && p->eKind == NO_KIND_DEF_){
                p->eKind = FIELD_;
                p->_.Field.pType = t;
                p->_.Field.nIndex = n;
                p->_.Field.nSize = TP_._.T.nSize;
                n = n + TP_._.T.nSize;
                p = p->pNext;
            }
            
            DC_._.DC.list = LI_._.LI.list;
            DC_._.DC.nSize = n;
            DC_.nont = DC;
            StackSem.push_back(DC_);
            
            break;

        case DC_LI_TP_RULE:                           // DC -> DC SEMI_COLON LI COLON TP

            TP_ = StackSem.back();
            t = TP_._.T.type;
            StackSem.pop_back();
            
            LI_ = StackSem.back();
            p = LI_._.LI.list;
            StackSem.pop_back();

            DC1_ = StackSem.back();
            StackSem.pop_back();

            n = DC1_._.DC.nSize;

            while (p != NULL && p->eKind == NO_KIND_DEF_){
                p->eKind = FIELD_;
                p->_.Field.pType = t;
                p->_.Field.nIndex = n;
                p->_.Field.nSize = TP_._.T.nSize;
                n = n + TP_._.T.nSize;
                p = p->pNext;
            }

            DC0_.nont = DC;
            DC0_._.DC.list = DC1_._.DC.list;
            DC_._.DC.nSize = n;
            StackSem.push_back(DC0_);

            break;

        case IDD_TP_RULE:                             // LP -> IDD COLON TP

            TP_ = StackSem.back();
            t = TP_._.T.type;
            StackSem.pop_back();

            IDD_ = StackSem.back();
            p = IDD_._.ID.obj;
            StackSem.pop_back();

            p->eKind = PARAM_;
            p->_.Param.pType = t;
            p->_.Param.nIndex = 0;
            p->_.Param.nSize = TP_._.T.nSize;

            LP_._.LP.list = p;
            LP_._.LP.nSize = TP_._.T.nSize;
            LP_.nont = LP;
            
            StackSem.push_back(LP_);

            break;

        case LP_IDD_TP_RULE:                          // LP -> LP COMMA IDD COLON TP

            TP_ = StackSem.back();
            t = TP_._.T.type;
            StackSem.pop_back();

            IDD_ = StackSem.back();
            p = IDD_._.ID.obj;
            StackSem.pop_back();

            LP1_ = StackSem.back();
            n = LP1_._.LP.nSize;
            StackSem.pop_back();
            
            
            p->eKind = PARAM_;
            p->_.Param.pType = t;
            p->_.Param.nIndex = n;
            p->_.Param.nSize = TP_._.T.nSize;
            
            LP0_._.LP.list = LP1_._.LP.list;
            LP0_._.LP.nSize = n + TP_._.T.nSize;
            LP0_.nont = LP;
            
            StackSem.push_back(LP0_);

            break;

        case MF_RULE:                                   // MF -> ''

            TP_ = StackSem.back();
            StackSem.pop_back();

            LP_ = StackSem.back();
            StackSem.pop_back();

            IDD_ = StackSem.back();
            f = IDD_._.ID.obj;

            f->eKind = FUNCTION_;
            f->_.Function.pRetType = TP_._.T.type;
            f->_.Function.pParams = LP_._.LP.list;
            f->_.Function.nParams = LP_._.LP.nSize;
            f->_.Function.nVars = 0;

            fs << "BEGIN_FUNC " << f->_.Function.nIndex << " " << f->_.Function.nParams << "   " << std::endl;
            offset = fs.tellg();
            offset -= 4;
            MF_._.MF.offset = offset;
            MF_.nont = MF;
            StackSem.push_back(MF_);

            break;

        case FUNCTION_IDD_NF_LP_TP_B_RULE:            // DF -> FUNCTION IDD NF LEFT_PARENTHESIS LP RIGHT_PARENTHESIS COLON TP MF B
            EndBlock();
            
            MF_ = StackSem.back();
            offset = MF_._.MF.offset;
            StackSem.pop_back();

            IDD_ = StackSem.back();
            o = IDD_._.ID.obj;
            StackSem.pop_back();

            current = fs.tellp();
            fs.seekp(offset, ios_base::beg);
            fs << " " << o->_.Function.nVars << std::endl;
            fs.seekp(current, ios_base::beg);
            fs << "END_FUNC" << std::endl;

            break;

        case B_RULE:                                  // S -> NB B

            EndBlock();

            break;

        case IF_E_S_RULE:                             // S -> IF LEFT_PARENTHESIS E RIGHT_PARENTHESIS MT S

            MT_ = StackSem.back();
            l = MT_._.MT.label;
            StackSem.pop_back();

            E_ = StackSem.back();
            t = E_._.E.type;
            StackSem.pop_back();

            if( !CheckTypes(t,pBool)){
                Error(ERR_BOOL_TYPE_EXPECTED);
            }

            fs << "L" << l << ":" << std::endl;

            break;

        case IF_E_S_ELSE_S_RULE:                      // S -> IF LEFT_PARENTHESIS E RIGHT_PARENTHESIS MT S ELSE ME S

            ME_ = StackSem.back();
            l = ME_._.ME.label;
            StackSem.pop_back();

            E_ = StackSem.back();
            t = E_._.E.type;
            StackSem.pop_back();
            
            if( !CheckTypes(t,pBool)){
                Error(ERR_BOOL_TYPE_EXPECTED);
            }

            fs << "L" << l << ":" << std::endl;

            break;

        case WHILE_E_S_RULE:                          // S -> WHILE MW LEFT_PARENTHESIS E RIGHT_PARENTHESIS MT S

            MT_ = StackSem.back();
            l2 = MT_._.MT.label;
            StackSem.pop_back();

            E_ = StackSem.back();
            t = E_._.E.type;
            StackSem.pop_back();

            MW_ = StackSem.back();
            l1 = MW_._.MW.label;
            StackSem.pop_back();
            
            if( !CheckTypes(t,pBool)){
                Error(ERR_BOOL_TYPE_EXPECTED);
            }

            fs << "\tJMP_BW L" << l1 << std::endl << "L" << l2 << std::endl;

            break;

        case DO_S_WHILE_E_RULE:                       // S -> DO MW S WHILE LEFT_PARENTHESIS E RIGHT_PARENTHESIS SEMI_COLON

            E_ = StackSem.back();
            t = E_._.E.type;
            StackSem.pop_back();

            MW_ = StackSem.back();
            l = MW_._.MW.label;
            StackSem.pop_back();
            
            if( !CheckTypes(t,pBool)){
                Error(ERR_BOOL_TYPE_EXPECTED);
            }

            fs << "\tNOT" << std::endl << "\tJMP_BW L" << l << std::endl;

            break;

        case E_AND_L_RULE:                            // E -> E AND L

            L_ = StackSem.back();
            if (!CheckTypes(L_._.L.type, pBool)){
                Error(ERR_BOOL_TYPE_EXPECTED);
            }
            StackSem.pop_back();

            E1_ = StackSem.back();
            if (!CheckTypes(E1_._.E.type, pBool)){
                Error(ERR_BOOL_TYPE_EXPECTED);
            }
            StackSem.pop_back();

            E0_._.E.type = pBool;
            E0_.nont = E;

            fs << "\tAND" << std::endl;

            StackSem.push_back(E0_);

            break;

        case E_OR_L_RULE:                             // E -> E OR L

            L_ = StackSem.back();
            if (!CheckTypes(L_._.L.type, pBool)){
                Error(ERR_BOOL_TYPE_EXPECTED);
            }
            StackSem.pop_back();

            E1_ = StackSem.back();
            if (!CheckTypes(E1_._.E.type, pBool)){
                Error(ERR_BOOL_TYPE_EXPECTED);
            }
            StackSem.pop_back();

            E0_._.E.type = pBool;
            E0_.nont = E;

            fs << "\tOR" << std::endl;

            StackSem.push_back(E0_);

            break;

        case L_RULE:                                  // E -> L

            L_ = StackSem.back();
            E_._.E.type = L_._.L.type;
            StackSem.pop_back();
            
            E_.nont = E;
            StackSem.push_back(E_);

            break;

        case L_LESS_THAN_R_RULE:                      // L -> L LESS_THAN R

            R_ = StackSem.back();
            StackSem.pop_back();
            L1_ = StackSem.back();
            StackSem.pop_back();
            
            if(!CheckTypes(L1_._.L.type,R_._.R.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            L0_._.L.type = pBool;
            L0_.nont = L;
            
            fs << "\tLT" << std::endl;

            StackSem.push_back(L0_);


            break;

        case L_GREATER_THAN_R_RULE:                   // L -> L GREATER_THAN R

            R_ = StackSem.back();
            StackSem.pop_back();
            L1_ = StackSem.back();
            StackSem.pop_back();
            
            if(!CheckTypes(L1_._.L.type,R_._.R.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            L0_._.L.type = pBool;
            L0_.nont = L;
            
            fs << "\tGT" << std::endl;

            StackSem.push_back(L0_);

            break;

        case L_LESS_OR_EQUAL_R_RULE:                  // L -> L LESS_OR_EQUAL R

            R_ = StackSem.back();
            StackSem.pop_back();
            L1_ = StackSem.back();
            StackSem.pop_back();
            
            if(!CheckTypes(L1_._.L.type,R_._.R.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            L0_._.L.type = pBool;
            L0_.nont = L;
            
            fs << "\tLE" << std::endl;

            StackSem.push_back(L0_);

            break;

        case L_GREATER_OR_EQUAL_R_RULE:               // L -> L GREATER_OR_EQUAL R

            R_ = StackSem.back();
            StackSem.pop_back();
            L1_ = StackSem.back();
            StackSem.pop_back();
            
            if(!CheckTypes(L1_._.L.type,R_._.R.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            L0_._.L.type = pBool;
            L0_.nont = L;

            fs << "\tGE" << std::endl;

            StackSem.push_back(L0_);

            break;

        case L_EQUAL_EQUAL_R_RULE:                    // L -> L EQUAL_EQUAL R

            R_ = StackSem.back();
            StackSem.pop_back();
            L1_ = StackSem.back();
            StackSem.pop_back();
            
            if(!CheckTypes(L1_._.L.type,R_._.R.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            L0_._.L.type = pBool;
            L0_.nont = L;

            fs << "\tEQ" << std::endl;

            StackSem.push_back(L0_);

            break;

        case L_NOT_EQUAL_R_RULE:                      // L -> L NOT_EQUAL R

            R_ = StackSem.back();
            StackSem.pop_back();
            L1_ = StackSem.back();
            StackSem.pop_back();
            
            if(!CheckTypes(L1_._.L.type,R_._.R.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            L0_._.L.type = pBool;
            L0_.nont = L;

            fs << "\tNE" << std::endl;

            StackSem.push_back(L0_);

            break;

        case R_RULE:                                  // L -> R

            R_ = StackSem.back();
            L_._.L.type = R_._.R.type;
            StackSem.pop_back();
            
            L_.nont = L;
            StackSem.push_back(L_);

            break;

        case R_PLUS_TM_RULE:                          // R -> R PLUS TM

            TM_ = StackSem.back();
            StackSem.pop_back();

            R1_ = StackSem.back();
            StackSem.pop_back();

            if (!CheckTypes(TM_._.TM.type, R1_._.R.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            if (!CheckTypes(R1_._.R.type, pInt) && !CheckTypes(R1_._.R.type, pString)){
                Error(ERR_INVALID_TYPE);
            }
            
            R0_._.R.type = R1_._.R.type;
            R0_.nont = R;
            
            fs << "\tADD" << std::endl;

            StackSem.push_back(R0_);

            break;

        case R_MINUS_TM_RULE:                         // R -> R MINUS TM

            TM_ = StackSem.back();
            StackSem.pop_back();

            R1_ = StackSem.back();
            StackSem.pop_back();

            if (!CheckTypes(TM_._.TM.type, R1_._.R.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            if (!CheckTypes(R1_._.R.type, pInt)){
                Error(ERR_INVALID_TYPE);
            }

            R0_._.R.type = R1_._.R.type;
            R0_.nont = R;

            fs << "\tSUB" << std::endl;

            StackSem.push_back(R0_);

            break;

        case TM_RULE:                                 // R -> TM

            TM_ = StackSem.back();
            R_._.R.type = TM_._.TM.type;
            StackSem.pop_back();
            
            R_.nont = R;
            StackSem.push_back(R_);

            break;

        case TM_TIMES_F_RULE:                         // TM -> TM TIMES F

            F_ = StackSem.back();
            StackSem.pop_back();

            TM1_ = StackSem.back();
            StackSem.pop_back();

            if (!CheckTypes(TM1_._.TM.type, F_._.F.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            if (!CheckTypes(TM1_._.TM.type, pInt) && !CheckTypes(TM1_._.R.type, pString)){
                Error(ERR_INVALID_TYPE);
            }

            TM0_._.TM.type = TM1_._.TM.type;
            TM0_.nont = TM;

            fs << "\tMUL" << std::endl;

            StackSem.push_back(TM0_);

            break;

        case TM_DIVIDE_F_RULE:                        // TM -> TM DIVIDE F

            F_ = StackSem.back();
            StackSem.pop_back();

            TM_ = StackSem.back();
            StackSem.pop_back();

            if (!CheckTypes(TM_._.TM.type, F_._.F.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            if (!CheckTypes(TM_._.TM.type, pInt) && !CheckTypes(TM_._.R.type, pString)){
                Error(ERR_INVALID_TYPE);
            }

            TM0_._.TM.type = TM1_._.TM.type;
            TM0_.nont = TM;

            fs << "\tDIV" << std::endl;

            StackSem.push_back(TM0_);

            break;

        case F_RULE:                                  // TM -> F

            F_ = StackSem.back();
            TM_._.TM.type = F_._.F.type;
            StackSem.pop_back();
            
            TM_.nont = TM;
            StackSem.push_back(TM_);

            break;

        case LV_RULE:                                 // F -> LV

            LV_ = StackSem.back();
            F_._.F.type = LV_._.LV.type;
            StackSem.pop_back();

            n = LV_._.LV.type->_.Var.nSize;

            fs << "\tDE_REF " << n << std::endl;

            F_.nont = F;
            StackSem.push_back(F_);

            break;

        case PLUS_PLUS_LV_RULE:                       // F -> PLUS_PLUS LV

            LV_ = StackSem.back();
            t = LV_._.LV.type;
            StackSem.pop_back();

            if(!CheckTypes(t,pInt)){
                Error(ERR_INVALID_TYPE);
            }
            
            F_._.F.type = pInt;
            F_.nont = F;
            
            fs << "\tDUP" << std::endl << "\tDUP\tDE_REF 1" << std::endl;
            fs << "\tINC" << std::endl << "\tSTORE_REF 1\tDE_REF 1" << std::endl;

            StackSem.push_back(F_);

            break;

        case MINUS_MINUS_LV_RULE:                     // F -> MINUS_MINUS LV

            LV_ = StackSem.back();
            t = LV_._.LV.type;
            StackSem.pop_back();

            if(!CheckTypes(t,pInt)){
                Error(ERR_INVALID_TYPE);
            }
            
            F_._.F.type = pInt;
            F_.nont = F;

            fs << "\tDUP" << std::endl << "\tDUP\tDE_REF 1" << std::endl;
            fs << "\tDEC" << std::endl << "\tSTORE_REF 1\tDE_REF 1" << std::endl;

            StackSem.push_back(F_);

            break;

        case LV_PLUS_PLUS_RULE:                       // F -> LV PLUS_PLUS

            LV_ = StackSem.back();
            t = LV_._.LV.type;
            StackSem.pop_back();

            if(!CheckTypes(t,pInt)){
                Error(ERR_INVALID_TYPE);
            }
            
            F_._.F.type = pInt;
            F_.nont = F;
            StackSem.push_back(F_);

            fs << "\tDUP" << std::endl << "\tDUP\tDE_REF 1" << std::endl << "\tINC" << std::endl;
            fs << "\tSTORE_REF 1\tDE_REF 1" << std::endl << "\tDEC" << std::endl;

            break;

        case LV_MINUS_MINUS_RULE:                     // F -> LV MINUS_MINUS

            LV_ = StackSem.back();
            t = LV_._.LV.type;
            StackSem.pop_back();

            if(!CheckTypes(t,pInt)){
                Error(ERR_INVALID_TYPE);
            }
            
            F_._.F.type = pInt;
            F_.nont = F;

            fs << "\tDUP" << std::endl << "\tDUP\tDE_REF 1" << std::endl << "\tDEC" << std::endl;
            fs << "\tSTORE_REF 1\tDE_REF 1" << std::endl << "\tINC" << std::endl;

            StackSem.push_back(F_);


            break;

        case MINUS_F_RULE:                            // F -> MINUS F

            F1_ = StackSem.back();
            t = F1_._.F.type;
            StackSem.pop_back();

            if(!CheckTypes(t,pInt)){
                Error(ERR_INVALID_TYPE);
            }
            
            F0_._.F.type = pInt;
            F0_.nont = F;

            fs << "\tNEG" << std::endl;

            StackSem.push_back(F0_);

            break;

        case NOT_F_RULE:                              // F -> NOT F

            F1_ = StackSem.back();
            t = F1_._.F.type;
            StackSem.pop_back();

            if(!CheckTypes(t,pBool)){
                Error(ERR_INVALID_TYPE);
            }
            
            F0_._.F.type = pInt;
            F0_.nont = F;

            fs << "\tNOT" << std::endl;

            StackSem.push_back(F0_);

            break;

        case NT_TRUE_RULE:                            // F -> NT_TRUE

            TRUE_ = StackSem.back();
            StackSem.pop_back();
            
            F_._.F.type = pBool;
            F_.nont = F;

            n = tokenSecundario;
            fs << "\tLOAD_CONST " << n << std::endl;

            StackSem.push_back(F_);

            break;

        case NT_FALSE_RULE:                           // F -> NT_FALSE

            FALSE_ = StackSem.back();
            StackSem.pop_back();
            
            F_._.F.type = pBool;
            F_.nont = F;

            n = tokenSecundario;
            fs << "\tLOAD_CONST " << n << std::endl;

            StackSem.push_back(F_);

            break;

        case NT_CHR_RULE:                             // F -> NT_CHR

            CHR_ = StackSem.back();
            StackSem.pop_back();
            
            F_._.F.type = pChar;
            F_.nont = F;

            n = tokenSecundario;
            fs << "\tLOAD_CONST " << n << std::endl;

            StackSem.push_back(F_);

            break;

        case NT_STR_RULE:                             // F -> NT_STR

            STR_ = StackSem.back();
            StackSem.pop_back();
            
            F_._.F.type = pString;
            F_.nont = F;

            n = tokenSecundario;
            fs << "\tLOAD_CONST " << n << std::endl;

            StackSem.push_back(F_);

            break;

        case NT_NUM_RULE:                             // F -> NT_NUM

            NUM_ = StackSem.back();
            StackSem.pop_back();
            
            F_._.F.type = pInt;
            F_.nont = F;

            n = tokenSecundario;
            fs << "\tLOAD_CONST " << n << std::endl;

            StackSem.push_back(F_);

            break;

        case LV_DOT_ID_RULE:                          // LV -> LV DOT ID

            ID_ = StackSem.back();
            StackSem.pop_back();

            LV1_ = StackSem.back();
            t = LV1_._.LV.type;
            StackSem.pop_back();

            if (t->eKind != STRUCT_TYPE_){
                if(t->eKind != UNIVERSAL_){
                    Error(ERR_KIND_NOT_STRUCT);
                }
                LV0_._.LV.type = pUniversal;
            } else {
                p = t->_.Struct.pFields;
                while (p != NULL){
                    if(p->nName == ID_._.ID.name) break;
                    p = p->pNext;
                }
                if (p == NULL){
                    Error(ERR_FIELD_NOT_DECL);
                    LV0_._.LV.type = pUniversal;
                } else {
                    LV0_._.LV.type = p->_.Field.pType;
                    fs << "\tADD " << p->_.Field.nIndex << std::endl;
                }
            }
            LV0_.nont = LV;
            StackSem.push_back(LV0_);
            
            break;

        case LV_E_RULE:                               // LV -> LV LEFT_SQUARE E RIGHT_SQUARE

            E_ = StackSem.back();
            StackSem.pop_back();

            LV1_ = StackSem.back();
            t = LV1_._.LV.type;
            StackSem.pop_back();
            
            if(t == pString){
                LV0_._.LV.type = pChar;
            
            } else if(t->eKind != ARRAY_TYPE_){
                if(t->eKind != UNIVERSAL_){
                    Error(ERR_KIND_NOT_ARRAY);
                }
                LV0_._.LV.type = pUniversal;
            } else {
                LV0_._.LV.type = t->_.Array.pElemType;
                fs << "\tMUL " << t->_.Array.pElemType->_.Type.nSize << std::endl;
                fs << "\tADD" << std::endl;
            }
            if(!CheckTypes(E_._.E.type, pInt)){
                Error( ERR_INVALID_INDEX_TYPE );
            }

            LV0_.nont = LV;
            StackSem.push_back(LV0_);
            
            break;

        case LV_IDU_RULE:                             // LV -> IDU

            IDU_ = StackSem.back();
            p = IDU_._.ID.obj;
            StackSem.pop_back();

            if(p->eKind != VAR_ && p->eKind != PARAM_){
                if(p->eKind != UNIVERSAL_) Error(ERR_KIND_NOT_VAR);
                LV_._.LV.type = pUniversal;
            } else {
                LV_._.LV.type = p->_.Var.pType;
                fs << "\tLOAD_REF " << p->_.Var.nIndex << std::endl;
            }
            
            LV_.nont = LV;
            StackSem.push_back(LV_);

            break;




        case LE_E_RULE:                               // LE -> E

            E_ = StackSem.back();
            StackSem.pop_back();
            MC_ = StackSem.back();
            
            LE_._.LE.param = NULL;
            LE_._.LE.err = MC_._.MC.err;
            n = 1;
            if( !MC_._.MC.err){
                p = MC_._.MC.param;
                if(p == NULL){
                    Error(ERR_TOO_MANY_ARGS);
                    LE_._.LE.err = true;
                }
                else{
                    if(!CheckTypes(p->_.Param.pType,E_._.E.type)){
                        Error(ERR_PARAM_TYPE);
                    }
                    LE_._.LE.param = p->pNext;
                    LE_._.LE.n = n+1;
                }
            }
            LE_.nont = LE;
            StackSem.push_back(LE_);

            break;

        case IDU_LE_RULE:                             // F -> IDU MC LEFT_PARENTHESIS LE RIGHT_PARENTHESIS

            LE_ = StackSem.back();
            StackSem.pop_back();
            MC_ = StackSem.back();
            StackSem.pop_back();
            IDU_ = StackSem.back();
            StackSem.pop_back();

            func = IDU_._.ID.obj;

            F_._.F.type = MC_._.MC.type;
            if( !MC_._.MC.err ) {
                if( LE_._.LE.n-1 < f->_.Function.nParams && LE_._.LE.n != 0) {
                    Error(ERR_TOO_FEW_ARGS);
                }
               else if(LE_._.LE.n-1 > f->_.Function.nParams){
                    Error(ERR_TOO_MANY_ARGS);
                }
            }
            F_.nont = F;

            fs << "\tCALL " << func->_.Function.nIndex << std::endl;

            StackSem.push_back(F_);
            
            break;

            case LE_COMMA_E_RULE:                         // LE -> LE COMMA E

            E_ = StackSem.back();
            StackSem.pop_back();
            LE1_ = StackSem.back();
            StackSem.pop_back();
            LE0_._.LE.param = NULL;
            LE0_._.LE.err = L1_._.LE.err;

            n = LE1_._.LE.n;
            if(!LE1_._.LE.err){
                p = LE1_._.LE.param;
                if(p == NULL){
                    Error(ERR_TOO_MANY_ARGS);
                    LE0_._.LE.err = true;
                }
                else{
                    if(!CheckTypes(p->_.Param.pType,E_._.E.type)){
                        Error(ERR_PARAM_TYPE);
                    }
                    LE0_._.LE.param = p->pNext;
                    LE0_._.LE.n = n + 1;
                }
            }
            LE0_.nont = LE;
            StackSem.push_back(LE0_);

            break;

        case MC_RULE:                                   // MC -> ''

            IDU_ = StackSem.back();
            f = IDU_._.ID.obj;

            if(f->eKind != FUNCTION_){
                Error(ERR_KIND_NOT_FUNCTION);
                MC_._.MC.type = pUniversal;
                MC_._.MC.param = NULL;
                MC_._.MC.err = true;
            } else {
                MC_._.MC.type = f->_.Function.pRetType;
                MC_._.MC.param = f->_.Function.pParams;
                MC_._.MC.err = false;
            }

            MC_.nont = MC;
            StackSem.push_back(MC_);

            break;

        case LV_EQUALS_E_RULE:                        // S -> LV EQUALS E SEMI_COLON

            E_ = StackSem.back();
            t1 = E_._.E.type;
            StackSem.pop_back();

            LV_ = StackSem.back();
            t2 = LV_._.LV.type;
            StackSem.pop_back();

            if(!CheckTypes(t1,t2)){
                Error(ERR_TYPE_MISMATCH);
            }

            F_._.F.type = t2;
            F_.nont = F;

            fs << "\tSTORE_REF " << t2->_.Type.nSize << std::endl;
            fs << "\tDE_REF " << t2->_.Type.nSize << std::endl;

            break;

        case NF_RULE:                                  // NF -> ''

            IDD_ = StackSem.back();
            f = IDD_._.ID.obj;

            f->eKind = FUNCTION_;
            f->_.Function.pParams = NULL;
            f->_.Function.nParams = 0;
            f->_.Function.nIndex = nFuncs++;
            NewBlock();

            break;

        case MT_RULE:                                  // MT -> ''

            l = newLabel();
            MT_._.MT.label = l;
            MT_.nont = MT;
            
            fs << "\tJMP_FW L" << l << std::endl;

            StackSem.push_back(MT_);

            break;

        case ME_RULE:                                  // ME -> ''

            MT_ = StackSem.back();
            l1 = MT_._.MT.label;
            StackSem.pop_back();

            l2 = newLabel();
            ME_._.ME.label = l2;
            ME_.nont = ME;
            
            fs << "\tJMP_FW L" << l2 << std::endl << "L" << l1 << std::endl;

            StackSem.push_back(ME_);

            break;

        case MW_RULE:                                  // MW -> ''

            l = newLabel();
            MW_._.MW.label = l;
            MW_.nont = MW;

            fs << "L" << l << std::endl;

            StackSem.push_back(MW_);

            break;

        case MA_RULE:                                  // MA -> ''

            fs << "\tDUP" << std::endl;

            break;

        case LDV_LS_RULE:                             // B -> LEFT_BRACES LDV LS RIGHT_BRACES
        //TODO

            break;

        case LDV_DV_RULE:                             // LDV -> LDV DV
        


            break;

        case DV_RULE:                                 // LDV -> DV
        


            break;

        case LS_S_RULE:                               // LS -> LS S
        


            break;

        case S_RULE:                                  // LS -> S
        


        default:
            break;
    }
}

void print_nterm(t_nterm val){
    switch (val){
    
    case P:

        std::cout << "P" << std::endl;
        break;
    case LDE:

        std::cout << "LDE" << std::endl;
        break;
    case DE:

        std::cout << "DE" << std::endl;
        break;
    case DT:

        std::cout << "DT" << std::endl;
        break;
    case TP:

        std::cout << "TP" << std::endl;
        break;
    case DC:

        std::cout << "DC" << std::endl;
        break;
    case DF:

        std::cout << "DF" << std::endl;
        break;
    case LP:

        std::cout << "LP" << std::endl;
        break;
    case B:

        std::cout << "B" << std::endl;
        break;
    case LDV:

        std::cout << "LDV" << std::endl;
        break;
    case LS:

        std::cout << "LS" << std::endl;
        break;
    case DV:

        std::cout << "DV" << std::endl;
        break;
    case LI:

        std::cout << "LI" << std::endl;
        break;
    case S:

        std::cout << "S" << std::endl;
        break;
    case E:

        std::cout << "E" << std::endl;
        break;
    case L:

        std::cout << "L" << std::endl;
        break;
    case R:

        std::cout << "R" << std::endl;
        break;
    case TM:

        std::cout << "TM" << std::endl;
        break;
    case F:

        std::cout << "F" << std::endl;
        break;
    case LE:

        std::cout << "LE" << std::endl;
        break;
    case LV:

        std::cout << "LV" << std::endl;
        break;
    case IDD:

        std::cout << "IDD" << std::endl;
        break;
    case IDU:

        std::cout << "IDU" << std::endl;
        break;
    case ID:

        std::cout << "ID" << std::endl;
        break;
    case NT_TRUE:

        std::cout << "NT_TRUE" << std::endl;
        break;
    case NT_FALSE:

        std::cout << "NT_FALSE" << std::endl;
        break;
    case NT_CHR:

        std::cout << "NT_CHR" << std::endl;
        break;
    case NT_STR:

        std::cout << "NT_STR" << std::endl;
        break;
    case NT_NUM:

        std::cout << "NT_NUM" << std::endl;
        break;
    case NB:

        std::cout << "NB" << std::endl;
        break;
    case MF:

        std::cout << "MF" << std::endl;
        break;
    case MC:

        std::cout << "MC" << std::endl;
        break;
    case NF:

        std::cout << "NF" << std::endl;
        break;
    default:
        break;
    }
}

void print_eKind(t_kind val){
    switch (val){
        case NO_KIND_DEF_:
            std::cout << "NO_KIND_DEF_" << std::endl;
            break;
        case VAR_:
            std::cout << "VAR_" << std::endl;
            break;
        case PARAM_:
            std::cout << "PARAM_" << std::endl;
            break;
        case FUNCTION_:
            std::cout << "FUNCTION_" << std::endl;
            break;
        case FIELD_:
            std::cout << "FIELD_" << std::endl;
            break;
        case ARRAY_TYPE_:
            std::cout << "ARRAY_TYPE_" << std::endl;
            break;
        case STRUCT_TYPE_:
            std::cout << "STRUCT_TYPE_" << std::endl;
            break;
        case ALIAS_TYPE_:
            std::cout << "ALIAS_TYPE_" << std::endl;
            break;
        case SCALAR_TYPE_:
            std::cout << "SCALAR_TYPE_" << std::endl;
            break;
        case UNIVERSAL_:
            std::cout << "UNIVERSAL_" << std::endl;
            break;
    }
}