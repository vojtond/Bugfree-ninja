#include "scanner.h"

#define INTEGER 71
#define REAL 72
#define BOOLEAN 73
#define STRING 74
#define FUNCTION_HEADER 75
#define FUNCTION_END 76
int parser(tGlobSymbolTable *ST,Tridic *ridic);
 int START (tGlobSymbolTable *ST,Tridic *ridic);
int FUNC (tGlobSymbolTable *ST,Tridic *ridic);
int FORWAR (tGlobSymbolTable *ST,Tridic *ridic);
int ARG (tGlobSymbolTable *ST,Tridic *ridic);
int ARGDAL (tGlobSymbolTable *ST,Tridic *ridic);
int CYKLUS (tGlobSymbolTable *ST,Tridic *ridic);
int KDYZ (tGlobSymbolTable *ST,Tridic *ridic);
int ELSEP (tGlobSymbolTable *ST,Tridic *ridic);
int SEKVENCE (tGlobSymbolTable *ST,Tridic *ridic);
int POKYN (tGlobSymbolTable *ST,Tridic *ridic);
int SLOZ (tGlobSymbolTable *ST,Tridic *ridic);
int PRVNI (tGlobSymbolTable *ST,Tridic *ridic);
int DALSI (tGlobSymbolTable *ST,Tridic *ridic);
int PRIKAZ (tGlobSymbolTable *ST,Tridic *ridic);
int DEK (tGlobSymbolTable *ST,Tridic *ridic);
int DEKDAL (tGlobSymbolTable *ST,Tridic *ridic);
int TYPE (tGlobSymbolTable *ST,Tridic *ridic);
int BOOLEANP (tGlobSymbolTable *ST,Tridic *ridic);
int VYPIS (tGlobSymbolTable *ST,Tridic *ridic);
int DVYPIS (tGlobSymbolTable *ST,Tridic *ridic);
int GLOBDEK (tGlobSymbolTable *ST,Tridic *ridic);
int GLOBDEKDAL (tGlobSymbolTable *ST,Tridic *ridic);
int VYRAZ(tGlobSymbolTable *ST,Tridic *ridic);
int ARGVOL(tGlobSymbolTable *ST,Tridic *ridic);
int ARGVOLDAL(tGlobSymbolTable *ST,Tridic *ridic);

int token;
void generateVariable(string *var);

  double hodnota;
  int error;

