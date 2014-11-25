

#include "str.h"
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
