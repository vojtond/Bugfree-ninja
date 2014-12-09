

#include "parser.h"

typedef struct{
    int type;
    string nazev;
}spom;

void reduction(tGlobSymbolTable *ST,Tridic *ridic, string *pomv1, string *pomv2, string *pomv3, spom *spom1, spom *spom2, spom *spom3, spom *spom4, spom *spom5);
void shifting(tGlobSymbolTable *ST,Tridic *ridic);
