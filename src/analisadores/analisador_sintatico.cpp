#include "analisador_sintatico.h"


#include "csv.h"
#include <stack>
#include <vector>
#include <errno.h>
#include <unordered_map>

using namespace std;

stack<int> pilhaEstado;
vector<unordered_map<int,int>> Action(160);

int LEN[] = {P, LDE, LDE, DE, DE, DT, DT, DT, TP, TP, TP, TP, TP, DC, DC, DF, LP, LP, B, LDV, LDV, LS, LS, DV, LI, LI, S, S, S, S, S, S, S, S, E, E, E, L, L, L, L, L, L, L, R, R, R, TM, TM, TM, F, F, F, F, F, F, F, F, F, F, F, F, F, F, LE, LE, LV, LV, LV, IDD, IDU, ID, NT_TRUE, NT_FALSE, NT_CHR, NT_STR, NT_NUM, NB};
int LEFT[] = {1, 2, 1, 1, 1, 9, 8, 4, 1, 1, 1, 1, 1, 5, 3, 9, 5, 3, 4, 2, 1, 2, 1, 5, 3, 1, 5, 7, 5, 7, 1, 4, 2, 2, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 3, 3, 1, 3, 3, 1, 1, 2, 2, 2, 2, 3, 4, 2, 2, 1, 1, 1, 1, 1, 3, 1, 3, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

int column = 0;
int row = 0;
void cb1 (void *s, size_t len, void *data) {
  if (len){
    string str((char *)s);
    Action[row][CSVdict[column]] = stoi(str);
  }
  column++;
}
void cb2 (int c, void *data) { row++; column=0;}

void PopulaAction(){
    PopulaCSVDict();
    char buf[1024];
    struct csv_parser p;
    unsigned char options = 0;
    size_t bytes_read;

    FILE *fp = fopen("slr_table.csv","r");
    if (!fp) {
        fprintf(stderr, "Failed to open slr_table.csv: %s\n", strerror(errno));
    }
    if (csv_init(&p, options) != 0) {
        fprintf(stderr, "Failed to initialize csv parser\n");
        exit(EXIT_FAILURE);
    }

    options = CSV_STRICT;
    csv_set_opts(&p, options);

    while ((bytes_read=fread(buf, 1, 1024, fp)) > 0) {
        if (csv_parse(&p, buf, bytes_read, cb1, cb2, &Action) != bytes_read) {
            fprintf(stderr, "Error while parsing file: %s\n", csv_strerror(csv_error(&p)));
        }
    }
}

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