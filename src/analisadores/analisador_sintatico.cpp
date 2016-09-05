#include "analisador_sintatico.h"
#include <stack>
stack<int> pilhaEstado;
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