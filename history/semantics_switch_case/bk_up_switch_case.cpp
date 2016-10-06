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
            StackSem.push_front(IDD_);
            
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
            StackSem.push_front(IDU_);

            break;

        case ID_IDENTIFIER_RULE:                      // ID -> IDENTIFIER

            ID_.nont = ID;
            name = tokenSecundario;
            ID_._.ID.name = name;
            ID_._.ID.obj = NULL;
            StackSem.push_front(ID_);

            break;
        case INTEGER_RULE:                             // TP -> INTEGER

            TP_.nont = TP;
            TP_._.T.type = pInt;
            StackSem.push_front(TP_);

            break;

        case CHAR_RULE:                                // TP -> CHAR

            TP_.nont = TP;
            TP_._.T.type = pChar;
            StackSem.push_front(TP_);

            break;

        case BOOLEAN_RULE:                            // TP -> BOOLEAN

            TP_.nont = TP;
            TP_._.T.type = pBool;
            StackSem.push_front(TP_);

            break;

        case STRING_RULE:                             // TP -> STRING

            TP_.nont = TP;
            TP_._.T.type = pString;
            StackSem.push_front(TP_);

            break;

        case TP_IDU_RULE:                             // TP -> IDU

            IDU_ = StackSem.front();
            StackSem.pop_front();
            p = IDU_._.ID.obj;
            if (IS_TYPE_KIND(p->eKind) || p->eKind == UNIVERSAL_) {
                TP_._.T.type = p;
            } else {
                TP_._.T.type = pUniversal;
                Error( ERR_TYPE_EXPECTED );
            }
            TP_.nont = TP;
            StackSem.push_front(TP_);

            break;

        case IDD_RULE:                                // LI -> IDD

            IDD_ = StackSem.front();
            StackSem.pop_front();
            LI_.nont = LI;
            LI_._.LI.list = IDD_._.ID.obj;
            StackSem.push_front(LI_);

            break;

        case LI_IDD_RULE:                             // LI -> LI COMMA IDD

            IDD_ = StackSem.front();
            StackSem.pop_front();
            LI1_ = StackSem.front();
            StackSem.pop_front();
            LI0_._.LI.list = LI1_._.LI.list;
            LI0_.nont = LI;
            StackSem.push_front(LI0_);

            break;

        case VAR_LI_TP_RULE:                          // DV -> VAR LI COLON TP SEMI_COLON

            TP_ = StackSem.front();
            StackSem.pop_front();
            t = TP_._.T.type;
            LI_ = StackSem.front();
            StackSem.pop_front();
            p = LI_._.LI.list;
            while (p != NULL && p->eKind == NO_KIND_DEF_){
                p->eKind = VAR_;
                p->_.Var.pType = t;
                p = p->pNext;
            }

            break;

        case TYPE_IDD_EQUALS_ARRAY_NT_NUM_OF_TP_RULE:  // DT -> TYPE IDD EQUALS ARRAY LEFT_SQUARE NT_NUM RIGHT_SQUARE OF TP

            TP_ = StackSem.front();
            t = TP_._.T.type;
            StackSem.pop_front();
            
            NUM_ = StackSem.front();
            n = NUM_._.CONST.val.n;
            StackSem.pop_front();

            IDD_ = StackSem.front();
            p = IDD_._.ID.obj;
            StackSem.pop_front();

            p->eKind = ARRAY_TYPE_;
            p->_.Array.nNumElems = n;
            p->_.Array.pElemType = t;

            break;

        case TYPE_IDD_EQUALS_STRUCT_NB_DC_RULE:        // DT -> TYPE IDD EQUALS STRUCT NB LEFT_BRACES DC RIGHT_BRACES

            DC_ = StackSem.front();
            StackSem.pop_front();

            IDD_ = StackSem.front();
            p = IDD_._.ID.obj;
            StackSem.pop_front();

            p->eKind = STRUCT_TYPE_;
            p->_.Struct.pFields = DC_._.DC.list;

            EndBlock();

            break;

        case TYPE_IDD_EQUALS_TP_RULE:                  // DT -> TYPE IDD EQUALS TP

            TP_ = StackSem.front();
            t = TP_._.T.type;
            StackSem.pop_front();

            IDD_ = StackSem.front();
            p = IDD_._.ID.obj;
            StackSem.pop_front();

            p->eKind =ALIAS_TYPE_;
            p->_.Alias.pBaseType = t;

            break;

        case DC_LI_TP_RULE:                           // DC -> DC SEMI_COLON LI COLON TP

            TP_ = StackSem.front();
            t = TP_._.T.type;
            StackSem.pop_front();
            
            LI_ = StackSem.front();
            p = LI_._.LI.list;
            StackSem.pop_front();

            DC1_ = StackSem.front();
            StackSem.pop_front();

            while (p != NULL && p->eKind == NO_KIND_DEF_){
                p->eKind = FIELD_;
                p->_.Field.pType = t;
                p = p->pNext;
            }
            
            DC0_._.DC.list = DC1_._.DC.list;
            DC0_.nont = DC;
            StackSem.push_front(DC0_);

            break;

        case LI_TP_RULE:                              // DC -> LI COLON TP

            TP_ = StackSem.front();
            t = TP_._.T.type;
            StackSem.pop_front();
            
            LI_ = StackSem.front();
            p = LI_._.LI.list;
            StackSem.pop_front();

            while (p != NULL && p->eKind == NO_KIND_DEF_){
                p->eKind = FIELD_;
                p->_.Field.pType = t;
                p = p->pNext;
            }
            
            DC_._.DC.list = LI_._.LI.list;
            DC_.nont = DC;
            StackSem.push_front(DC_);
            
            break;

        case FUNCTION_IDD_NB_LP_TP_B_RULE:            // DF -> FUNCTION IDD NB LEFT_PARENTHESIS LP RIGHT_PARENTHESIS COLON TP MF B

            EndBlock();

            break;

        case LP_IDD_TP_RULE:                          // LP -> LP COMMA IDD COLON TP

            TP_ = StackSem.front();
            t = TP_._.T.type;
            StackSem.pop_front();

            IDD_ = StackSem.front();
            p = IDD_._.ID.obj;
            StackSem.pop_front();

            LP1_ = StackSem.front();
            StackSem.pop_front();

            p->eKind = PARAM_;
            p->_.Param.pType = t;

            LP0_._.LP.list = LP1_._.LP.list;
            LP0_.nont = LP;

            StackSem.push_front(LP_);

            break;

        case IDD_TP_RULE:                             // LP -> IDD COLON TP

            TP_ = StackSem.front();
            t = TP_._.T.type;
            StackSem.pop_front();

            IDD_ = StackSem.front();
            p = IDD_._.ID.obj;
            StackSem.pop_front();

            p->eKind = PARAM_;
            p->_.Param.pType = t;

            LP_._.LP.list = p;
            LP_.nont = LP;

            StackSem.push_front(LP_);

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

        case IF_E_S_RULE:                             // S -> IF LEFT_PARENTHESIS E RIGHT_PARENTHESIS S

            E_ = StackSem.front();
            t = E_._.E.type;
            
            if( !CheckTypes(t,pBool)){
                Error(ERR_BOOL_TYPE_EXPECTED);
            }

            break;

        case IF_E_S_ELSE_S_RULE:                      // S -> IF LEFT_PARENTHESIS E RIGHT_PARENTHESIS S ELSE S

            E_ = StackSem.front();
            t = E_._.E.type;
            
            if( !CheckTypes(t,pBool)){
                Error(ERR_BOOL_TYPE_EXPECTED);
            }

            break;

        case WHILE_E_S_RULE:                          // S -> WHILE LEFT_PARENTHESIS E RIGHT_PARENTHESIS S

            E_ = StackSem.front();
            t = E_._.E.type;
            
            if( !CheckTypes(t,pBool)){
                Error(ERR_BOOL_TYPE_EXPECTED);
            }

            break;

        case DO_S_WHILE_E_RULE:                       // S -> DO S WHILE LEFT_PARENTHESIS E RIGHT_PARENTHESIS SEMI_COLON

            E_ = StackSem.front();
            t = E_._.E.type;
            
            if( !CheckTypes(t,pBool)){
                Error(ERR_BOOL_TYPE_EXPECTED);
            }

            break;

        case B_RULE:                                  // S -> B

            EndBlock();

            break;

        case LV_EQUALS_E_RULE:                        // S -> LV EQUALS E SEMI_COLON

            E_ = StackSem.front();
            t1 = E_._.E.type;
            StackSem.pop_front();

            LV_ = StackSem.front();
            t2 = LV_._.LV.type;
            StackSem.pop_front();

            if(!CheckTypes(t1,t2)){
                Error(ERR_TYPE_MISMATCH);
            }

            F_._.F.type = t2;
            F_.nont = F;
            StackSem.push_front(F_); //COMMENT?

            break;

        case BREAK_RULE:                              // S -> BREAK SEMI_COLON
        //TODO


            break;

        case CONTINUE_RULE:                           // S -> CONTINUE SEMI_COLON
        //TODO


            break;

        case E_AND_L_RULE:                            // E -> E AND L

            L_ = StackSem.front();
            if (!CheckTypes(L_._.L.type, pBool)){
                Error(ERR_BOOL_TYPE_EXPECTED);
            }
            StackSem.pop_front();

            E1_ = StackSem.front();
            if (!CheckTypes(E1_._.E.type, pBool)){
                Error(ERR_BOOL_TYPE_EXPECTED);
            }
            StackSem.pop_front();

            E0_._.E.type = pBool;
            E0_.nont = E;

            StackSem.push_front(E0_);

            break;

        case E_OR_L_RULE:                             // E -> E OR L

            L_ = StackSem.front();
            if (!CheckTypes(L_._.L.type, pBool)){
                Error(ERR_BOOL_TYPE_EXPECTED);
            }
            StackSem.pop_front();

            E1_ = StackSem.front();
            if (!CheckTypes(E1_._.E.type, pBool)){
                Error(ERR_BOOL_TYPE_EXPECTED);
            }
            StackSem.pop_front();

            E0_._.E.type = pBool;
            E0_.nont = E;

            StackSem.push_front(E0_);

            break;

        case L_RULE:                                  // E -> L

            L_ = StackSem.front();
            E_._.E.type = L_._.L.type;
            StackSem.pop_front();
            
            E_.nont = E;
            StackSem.push_front(E_);

            break;

        case L_LESS_THAN_R_RULE:                      // L -> L LESS_THAN R

            R_ = StackSem.front();
            StackSem.pop_front();
            L1_ = StackSem.front();
            StackSem.pop_front();
            
            if(!CheckTypes(L1_._.L.type,R_._.R.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            L0_._.L.type = pBool;
            L0_.nont = L;
            StackSem.push_front(L0_);


            break;

        case L_GREATER_THAN_R_RULE:                   // L -> L GREATER_THAN R

            R_ = StackSem.front();
            StackSem.pop_front();
            L1_ = StackSem.front();
            StackSem.pop_front();
            
            if(!CheckTypes(L1_._.L.type,R_._.R.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            L0_._.L.type = pBool;
            L0_.nont = L;
            StackSem.push_front(L0_);

            break;

        case L_LESS_OR_EQUAL_R_RULE:                  // L -> L LESS_OR_EQUAL R

            R_ = StackSem.front();
            StackSem.pop_front();
            L1_ = StackSem.front();
            StackSem.pop_front();
            
            if(!CheckTypes(L1_._.L.type,R_._.R.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            L0_._.L.type = pBool;
            L0_.nont = L;
            StackSem.push_front(L0_);

            break;

        case L_GREATER_OR_EQUAL_R_RULE:               // L -> L GREATER_OR_EQUAL R

            R_ = StackSem.front();
            StackSem.pop_front();
            L1_ = StackSem.front();
            StackSem.pop_front();
            
            if(!CheckTypes(L1_._.L.type,R_._.R.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            L0_._.L.type = pBool;
            L0_.nont = L;
            StackSem.push_front(L0_);

            break;

        case L_EQUAL_EQUAL_R_RULE:                    // L -> L EQUAL_EQUAL R

            R_ = StackSem.front();
            StackSem.pop_front();
            L1_ = StackSem.front();
            StackSem.pop_front();
            
            if(!CheckTypes(L1_._.L.type,R_._.R.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            L0_._.L.type = pBool;
            L0_.nont = L;
            StackSem.push_front(L0_);

            break;

        case L_NOT_EQUAL_R_RULE:                      // L -> L NOT_EQUAL R

            R_ = StackSem.front();
            StackSem.pop_front();
            L1_ = StackSem.front();
            StackSem.pop_front();
            
            if(!CheckTypes(L1_._.L.type,R_._.R.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            L0_._.L.type = pBool;
            L0_.nont = L;
            StackSem.push_front(L0_);

            break;

        case R_RULE:                                  // L -> R

            R_ = StackSem.front();
            L_._.L.type = R_._.R.type;
            StackSem.pop_front();
            
            L_.nont = L;
            StackSem.push_front(L_);

            break;

        case R_PLUS_TM_RULE:                          // R -> R PLUS TM

            TM_ = StackSem.front();
            StackSem.pop_front();

            R1_ = StackSem.front();
            StackSem.pop_front();

            if (!CheckTypes(TM_._.TM.type, R1_._.R.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            if (!CheckTypes(R1_._.R.type, pInt) && !CheckTypes(R1_._.R.type, pString)){
                Error(ERR_INVALID_TYPE);
            }
            
            R0_._.R.type = R1_._.R.type;
            R0_.nont = R;
            StackSem.push_front(R0_);

            break;

        case R_MINUS_TM_RULE:                         // R -> R MINUS TM

            TM_ = StackSem.front();
            StackSem.pop_front();

            R1_ = StackSem.front();
            StackSem.pop_front();

            if (!CheckTypes(TM_._.TM.type, R1_._.R.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            if (!CheckTypes(R1_._.R.type, pInt)){
                Error(ERR_INVALID_TYPE);
            }

            R0_._.R.type = R1_._.R.type;
            R0_.nont = R;
            StackSem.push_front(R0_);

            break;

        case TM_RULE:                                 // R -> TM

            TM_ = StackSem.front();
            R_._.R.type = TM_._.TM.type;
            StackSem.pop_front();
            
            R_.nont = R;
            StackSem.push_front(R_);

            break;

        case TM_TIMES_F_RULE:                         // TM -> TM TIMES F

            F_ = StackSem.front();
            StackSem.pop_front();

            TM1_ = StackSem.front();
            StackSem.pop_front();

            if (!CheckTypes(TM1_._.TM.type, F_._.F.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            if (!CheckTypes(TM1_._.TM.type, pInt) && !CheckTypes(TM1_._.R.type, pString)){
                Error(ERR_INVALID_TYPE);
            }

            TM0_._.TM.type = TM1_._.TM.type;
            TM0_.nont = TM;
            StackSem.push_front(TM0_);

            break;

        case TM_DIVIDE_F_RULE:                        // TM -> TM DIVIDE F

            F_ = StackSem.front();
            StackSem.pop_front();

            TM_ = StackSem.front();
            StackSem.pop_front();

            if (!CheckTypes(TM_._.TM.type, F_._.F.type)){
                Error(ERR_TYPE_MISMATCH);
            }
            if (!CheckTypes(TM_._.TM.type, pInt) && !CheckTypes(TM_._.R.type, pString)){
                Error(ERR_INVALID_TYPE);
            }

            TM0_._.TM.type = TM1_._.TM.type;
            TM0_.nont = TM;
            StackSem.push_front(TM0_);

            break;

        case F_RULE:                                  // TM -> F

            F_ = StackSem.front();
            TM_._.TM.type = F_._.F.type;
            StackSem.pop_front();
            
            TM_.nont = TM;
            StackSem.push_front(TM_);

            break;

        case LV_RULE:                                 // F -> LV

            LV_ = StackSem.front();
            F_._.F.type = LV_._.LV.type;
            StackSem.pop_front();
            
            F_.nont = F;
            StackSem.push_front(F_);

            break;

        case PLUS_PLUS_LV_RULE:                       // F -> PLUS_PLUS LV

            LV_ = StackSem.front();
            t = LV_._.LV.type;
            StackSem.pop_front();

            if(!CheckTypes(t,pInt)){
                Error(ERR_INVALID_TYPE);
            }
            
            F_._.F.type = pInt;
            F_.nont = F;
            StackSem.push_front(F_);

            break;

        case MINUS_MINUS_LV_RULE:                     // F -> MINUS_MINUS LV

            LV_ = StackSem.front();
            t = LV_._.LV.type;
            StackSem.pop_front();

            if(!CheckTypes(t,pInt)){
                Error(ERR_INVALID_TYPE);
            }
            
            F_._.F.type = pInt;
            F_.nont = F;
            StackSem.push_front(F_);

            break;

        case LV_PLUS_PLUS_RULE:                       // F -> LV PLUS_PLUS

            LV_ = StackSem.front();
            t = LV_._.LV.type;
            StackSem.pop_front();

            if(!CheckTypes(t,pInt)){
                Error(ERR_INVALID_TYPE);
            }
            
            F_._.F.type = pInt;
            F_.nont = F;
            StackSem.push_front(F_);


            break;

        case LV_MINUS_MINUS_RULE:                     // F -> LV MINUS_MINUS

            LV_ = StackSem.front();
            t = LV_._.LV.type;
            StackSem.pop_front();

            if(!CheckTypes(t,pInt)){
                Error(ERR_INVALID_TYPE);
            }
            
            F_._.F.type = pInt;
            F_.nont = F;
            StackSem.push_front(F_);


            break;

        case MINUS_F_RULE:                            // F -> MINUS F

            F1_ = StackSem.front();
            t = F1_._.F.type;
            StackSem.pop_front();

            if(!CheckTypes(t,pInt)){
                Error(ERR_INVALID_TYPE);
            }
            
            F0_._.F.type = pInt;
            F0_.nont = F;
            StackSem.push_front(F0_);

            break;

        case NOT_F_RULE:                              // F -> NOT F

            F1_ = StackSem.front();
            t = F1_._.F.type;
            StackSem.pop_front();

            if(!CheckTypes(t,pBool)){
                Error(ERR_INVALID_TYPE);
            }
            
            F0_._.F.type = pInt;
            F0_.nont = F;
            StackSem.push_front(F0_);

            break;

        case NT_TRUE_RULE:                            // F -> NT_TRUE

            TRUE_ = StackSem.front();
            StackSem.pop_front();
            
            F_._.F.type = pBool;
            F_.nont = F;
            StackSem.push_front(F_);

            break;

        case NT_FALSE_RULE:                           // F -> NT_FALSE

            FALSE_ = StackSem.front();
            StackSem.pop_front();
            
            F_._.F.type = pBool;
            F_.nont = F;
            StackSem.push_front(F_);

            break;

        case NT_CHR_RULE:                             // F -> NT_CHR

            CHR_ = StackSem.front();
            StackSem.pop_front();
            
            F_._.F.type = pChar;
            F_.nont = F;
            StackSem.push_front(F_);

            break;

        case NT_STR_RULE:                             // F -> NT_STR

            STR_ = StackSem.front();
            StackSem.pop_front();
            
            F_._.F.type = pString;
            F_.nont = F;
            StackSem.push_front(F_);

            break;

        case NT_NUM_RULE:                             // F -> NT_NUM

            NUM_ = StackSem.front();
            StackSem.pop_front();
            
            F_._.F.type = pChar;
            F_.nont = F;
            StackSem.push_front(F_);

            break;

        case F_E_RULE:                                // F -> LEFT_PARENTHESIS E RIGHT_PARENTHESIS

            E_ = StackSem.front();
            StackSem.pop_front();
            
            F_._.F.type = E_._.E.type;
            F_.nont = F;
            StackSem.push_front(F_);

            break;

        case IDU_LE_RULE:                             // F -> IDU MC LEFT_PARENTHESIS LE RIGHT_PARENTHESIS

            LE_ = StackSem.front();
            StackSem.pop_front();
            MC_ = StackSem.front();
            StackSem.pop_front();
            IDU_ = StackSem.front();
            StackSem.pop_front();

            F_._.F.type = MC_._.MC.type;
            if( !MC_._.MC.err ) {
                if( LE_._.LE.param != NULL ) {
                    Error(ERR_TOO_FEW_ARGS);
                }
            }
            F_.nont = F;
            StackSem.push_front(F_);
            
            break;

        case LE_COMMA_E_RULE:                         // LE -> LE COMMA E

            E_ = StackSem.front();
            StackSem.pop_front();
            LE1_ = StackSem.front();
            StackSem.pop_front();
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
            StackSem.push_front(LE0_);

            break;

        case LE_E_RULE:                               // LE -> E

            E_ = StackSem.front();
            StackSem.pop_front();
            MC_ = StackSem.front();
            
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
            StackSem.push_front(LE_);

            break;

        case LV_DOT_ID_RULE:                          // LV -> LV DOT ID

            ID_ = StackSem.front();
            StackSem.pop_front();

            LV1_ = StackSem.front();
            t = LV1_._.LV.type;
            StackSem.pop_front();

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
                }
            }
            LV0_.nont = LV;
            StackSem.push_front(LV0_);
            break;

        case LV_E_RULE:                               // LV -> LV LEFT_SQUARE E RIGHT_SQUARE

            E_ = StackSem.front();
            StackSem.pop_front();

            LV1_ = StackSem.front();
            t = LV1_._.LV.type;
            StackSem.pop_front();
            
            if(t == pString){
                LV0_._.LV.type = pChar;
            
            } else if(t->eKind != ARRAY_TYPE_){
                if(t->eKind != UNIVERSAL_){
                    Error(ERR_KIND_NOT_ARRAY);
                }
                LV0_._.LV.type = pUniversal;
            } else {
                LV0_._.LV.type = t->_.Array.pElemType;
            }
            if(!CheckTypes(E_._.E.type, pInt)){
                Error( ERR_INVALID_INDEX_TYPE );
            }

            LV0_.nont = LV;
            StackSem.push_front(LV0_);
            
            break;

        case LV_IDU_RULE:                             // LV -> IDU

            IDU_ = StackSem.front();
            p = IDU_._.ID.obj;
            StackSem.pop_front();

            if(p->eKind != VAR_ && p->eKind != PARAM_){
                if(p->eKind != UNIVERSAL_) Error(ERR_KIND_NOT_VAR);
                LV_._.LV.type = pUniversal;
            } else {
                LV_._.LV.type = p->_.Var.pType;
            }
            
            LV_.nont = LV;
            StackSem.push_front(LV_);

            break;

        case TRUE_RULE:                               // NT_TRUE -> TRUE

            TRUE_.nont = NT_TRUE;
            TRUE_._.BOOL.val = true;
            TRUE_._.BOOL.type = pBool;
            StackSem.push_front(TRUE_);

            break;

        case FALSE_RULE:                              // NT_FALSE -> FALSE
            
            FALSE_.nont = NT_FALSE;
            FALSE_._.BOOL.val = false;
            FALSE_._.BOOL.type = pBool;
            StackSem.push_front(FALSE_);

            break;

        case CHARACTER_RULE:                          // NT_CHR -> CHARACTER

            CHR_.nont = NT_CHR;
            CHR_._.CONST.pos = tokenSecundario;
            CHR_._.CONST.type = pChar;
            CHR_._.CONST.val.c = getCharConst(tokenSecundario);
            StackSem.push_front(CHR_);

            break;

        case STRINGVAL_RULE:                          // NT_STR -> STRINGVAL

            STR_.nont = NT_STR;
            STR_._.CONST.pos = tokenSecundario;
            STR_._.CONST.type = pChar;
            STR_._.CONST.val.s = new string(getStringConst(tokenSecundario));
            StackSem.push_front(CHR_);
            break;

        case NUMERAL_RULE:                            // NT_NUM -> NUMERAL
            
            NUM_.nont = NT_CHR;
            NUM_._.CONST.pos = tokenSecundario;
            NUM_._.CONST.type = pInt;
            NUM_._.CONST.val.n = getIntConst(tokenSecundario);
            StackSem.push_front(NUM_);

            break;

        case NB_RULE:                                   // NB -> ''

            NewBlock();

            break;

        case MF_RULE:                                   // MF -> ''

            TP_ = StackSem.front();
            StackSem.pop_front();

            LP_ = StackSem.front();
            StackSem.pop_front();

            IDD_ = StackSem.front();
            f = IDD_._.ID.obj;
            StackSem.pop_front();

            f->eKind = FUNCTION_;
            f->_.Function.pRetType = TP_._.T.type;
            f->_.Function.pParams = LP_._.LP.list;

            break;

        case MC_RULE:                                   // MC -> ''

            IDU_ = StackSem.front();
            f = IDU_._.ID.obj;
            StackSem.pop_front(); //COMMENT

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
            StackSem.push_front(MC_);

            break;