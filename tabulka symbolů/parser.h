#include "scanner.h"
#define INTEGER 71
#define REAL 72
#define BOOLEAN 73
#define STRING 74
int parser();
 int START ();
int FUNC ();
int FORWAR ();
int ARG ();
int ARGDAL ();
int CYKLUS ();
int KDYZ ();
int ELSEP ();
int SEKVENCE ();
int POKYN ();
int SLOZ ();
int PRVNI ();
int DALSI ();
int PRIKAZ ();
int DEK ();
int DEKDAL ();
int TYPE ();
int BOOLEANP ();
int VYPIS ();
int DVYPIS ();
int GLOBDEK ();
int GLOBDEKDAL ();
int VYRAZ();
int ARGVOL();
int ARGVOLDAL();

int dek(string *NazevFunkce,string *NazevTokenu, int TypTokenu);

struct LokTabSymbolu {
   string nazev;
   int typ;            // ( Integer = i, String - s )
   int hodnota;
};

struct GlobTabSymbolu {
   string nazev;
   int typ;            // ( Integer = i, Funkce - f, String - s )
   //param;
   int hodnota;
};

