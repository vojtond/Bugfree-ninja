#include "scanner.h"

#define INTEGER 71
#define REAL 72
#define BOOLEAN 73
#define STRING 74
#define FUNCTION_HEADER 75
#define FUNCTION_END 76
int parser(tGlobSymbolTable *ST);
 int START (tGlobSymbolTable *ST);
int FUNC (tGlobSymbolTable *ST);
int FORWAR (tGlobSymbolTable *ST);
int ARG (tGlobSymbolTable *ST);
int ARGDAL (tGlobSymbolTable *ST);
int CYKLUS (tGlobSymbolTable *ST);
int KDYZ (tGlobSymbolTable *ST);
int ELSEP (tGlobSymbolTable *ST);
int SEKVENCE (tGlobSymbolTable *ST);
int POKYN (tGlobSymbolTable *ST);
int SLOZ (tGlobSymbolTable *ST);
int PRVNI (tGlobSymbolTable *ST);
int DALSI (tGlobSymbolTable *ST);
int PRIKAZ (tGlobSymbolTable *ST);
int DEK (tGlobSymbolTable *ST);
int DEKDAL (tGlobSymbolTable *ST);
int TYPE (tGlobSymbolTable *ST);
int BOOLEANP (tGlobSymbolTable *ST);
int VYPIS (tGlobSymbolTable *ST);
int DVYPIS (tGlobSymbolTable *ST);
int GLOBDEK (tGlobSymbolTable *ST);
int GLOBDEKDAL (tGlobSymbolTable *ST);
int VYRAZ();
int ARGVOL(tGlobSymbolTable *ST);
int ARGVOLDAL(tGlobSymbolTable *ST);

int token;
void generateVariable(string *var);
string attr;
  double hodnota;
  int error;
int key(string *klic,string *master);
