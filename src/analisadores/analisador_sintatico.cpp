#include "analisador_sintatico.h"
#include "analisador_lexico.h"

#include <cstring>
#include "csv.h"
#include <stack>
#include <vector>
#include <errno.h>
#include <unordered_map>

using namespace std;

stack<int> pilhaEstado;
int CSVdict[79];

vector<unordered_map<int,int>> Action(160);

int LEFT[] = {P, LDE, LDE, DE, DE, DT, DT, DT, TP, TP, TP, TP, TP, DC, DC, DF, LP, LP, B, LDV, LDV, LS, LS, DV, LI, LI, S, S, S, S, S, S, S, S, E, E, E, L, L, L, L, L, L, L, R, R, R, TM, TM, TM, F, F, F, F, F, F, F, F, F, F, F, F, F, F, LE, LE, LV, LV, LV, IDD, IDU, ID, NT_TRUE, NT_FALSE, NT_CHR, NT_STR, NT_NUM, NB};
int LEN[] = {1, 2, 1, 1, 1, 9, 8, 4, 1, 1, 1, 1, 1, 5, 3, 9, 5, 3, 4, 2, 1, 2, 1, 5, 3, 1, 5, 7, 5, 7, 1, 4, 2, 2, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 3, 3, 1, 3, 3, 1, 1, 2, 2, 2, 2, 3, 4, 2, 2, 1, 1, 1, 1, 1, 3, 1, 3, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0};

int column = 0;
int row = 0;

void SyntaxError(){
    printf("Deu ruim!\n");
    exit(1);
}

void cb1 (void *s, size_t len, void *data) {
  if (len){
    string str((char *)s, len);
    Action[row][CSVdict[column]] = stoi(str);
  }
  column++;
}
void cb2 (int c, void *data) { row++; column=0;}

void PopulaCSVDict(){
    CSVdict[0] = TYPE;
    CSVdict[1] = EQUALS;
    CSVdict[2] = ARRAY;
    CSVdict[3] = LEFT_SQUARE;
    CSVdict[4] = RIGHT_SQUARE;
    CSVdict[5] = OF;
    CSVdict[6] = STRUCT;
    CSVdict[7] = LEFT_BRACES;
    CSVdict[8] = RIGHT_BRACES;
    CSVdict[9] = INTEGER;
    CSVdict[10] = CHAR;
    CSVdict[11] = BOOLEAN;
    CSVdict[12] = STRING;
    CSVdict[13] = SEMI_COLON;
    CSVdict[14] = COLON;
    CSVdict[15] = FUNCTION;
    CSVdict[16] = LEFT_PARENTHESIS;
    CSVdict[17] = RIGHT_PARENTHESIS;
    CSVdict[18] = COMMA;
    CSVdict[19] = VAR;
    CSVdict[20] = IF;
    CSVdict[21] = ELSE;
    CSVdict[22] = WHILE;
    CSVdict[23] = DO;
    CSVdict[24] = BREAK;
    CSVdict[25] = CONTINUE;
    CSVdict[26] = AND;
    CSVdict[27] = OR;
    CSVdict[28] = LESS_THAN;
    CSVdict[29] = GREATER_THAN;
    CSVdict[30] = LESS_OR_EQUAL;
    CSVdict[31] = GREATER_OR_EQUAL;
    CSVdict[32] = EQUAL_EQUAL;
    CSVdict[33] = NOT_EQUAL;
    CSVdict[34] = PLUS;
    CSVdict[35] = MINUS;
    CSVdict[36] = TIMES;
    CSVdict[37] = DIVIDE;
    CSVdict[38] = PLUS_PLUS;
    CSVdict[39] = MINUS_MINUS;
    CSVdict[40] = NOT;
    CSVdict[41] = DOT;
    CSVdict[42] = IDT;
    CSVdict[43] = TRUE;
    CSVdict[44] = FALSE;
    CSVdict[45] = CHARACTER;
    CSVdict[46] = STRINGVAL;
    CSVdict[47] = NUMERAL;
    CSVdict[48] = END;
    CSVdict[49] = P;
    CSVdict[50] = LDE;
    CSVdict[51] = DE;
    CSVdict[52] = DT;
    CSVdict[53] = TP;
    CSVdict[54] = DC;
    CSVdict[55] = DF;
    CSVdict[56] = LP;
    CSVdict[57] = B;
    CSVdict[58] = LDV;
    CSVdict[59] = LS;
    CSVdict[60] = DV;
    CSVdict[61] = LI;
    CSVdict[62] = S;
    CSVdict[63] = E;
    CSVdict[64] = L;
    CSVdict[65] = R;
    CSVdict[66] = TM;
    CSVdict[67] = F;
    CSVdict[68] = LE;
    CSVdict[69] = LV;
    CSVdict[70] = IDD;
    CSVdict[71] = IDU;
    CSVdict[72] = ID;
    CSVdict[73] = NT_TRUE;
    CSVdict[74] = NT_FALSE;
    CSVdict[75] = NT_CHR;
    CSVdict[76] = NT_STR;
    CSVdict[77] = NT_NUM;
    CSVdict[78] = NB;

}

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
    } while(q != 300);
    printf("Passou\n");
}