#include "analisador_sintatico.h"
#include <stack>
stack<int> pilhaEstado;
int LEN[] = {P, LDE, LDE, DE, DE, DT, DT, DT, TP, TP, TP, TP, TP, DC, DC, DF, LP, LP, B, LDV, LDV, LS, LS, DV, LI, LI, S, S, S, S, S, S, S, S, E, E, E, L, L, L, L, L, L, L, R, R, R, TM, TM, TM, F, F, F, F, F, F, F, F, F, F, F, F, F, F, LE, LE, LV, LV, LV, IDD, IDU, ID, NT_TRUE, NT_FALSE, NT_CHR, NT_STR, NT_NUM, NB};
int LEFT[] = {1, 2, 1, 1, 1, 9, 8, 4, 1, 1, 1, 1, 1, 5, 3, 9, 5, 3, 4, 2, 1, 2, 1, 5, 3, 1, 5, 7, 5, 7, 1, 4, 2, 2, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 3, 3, 1, 3, 3, 1, 1, 2, 2, 2, 2, 3, 4, 2, 2, 1, 1, 1, 1, 1, 3, 1, 3, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
void parse(){
    PopulaAction();
    int p = 0;
    int q = 0;
    int r = 0;
    PUSH(0);
    t_token a = nextToken();
    do {
        if(Action[q].count(a) < 1) {
            SyntaxError();
        } else {
        p = Action[q][a];
        if (IS_SHIFT(p)) {
            PUSH(p);
            a = nextToken();
        } else if(IS_REDUCTION(p)) {
            r = RULE(p);
            POP(LEN[r]);
            PUSH(Action[TOP()][LEFT[r]]);
            // Semantics(r);
        } else {
            SyntaxError();
        }
        q = TOP();
    }
    } while(q != 1);
}