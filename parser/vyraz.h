

#include "parser.h"

typedef struct{
    int type;
    string nazev;
}spom;

typedef struct{
    int type;
    string nazev;
}pomv;

void reduction(tGlobSymbolTable *ST,Tridic *ridic, pomv *pomv1, pomv *pomv2, pomv *pomv3, spom *spom1, spom *spom2, spom *spom3, spom *spom4, spom *spom5);
void shifting(tGlobSymbolTable *ST,Tridic *ridic);
int typecontrol(tGlobSymbolTable *ST,Tridic *ridic, int op, int oper1, int oper2);
