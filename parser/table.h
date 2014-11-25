

#include "str.h"
int dek(string *NazevFunkce,string *NazevTokenu, int TypTokenu);
int searchvar(string *variable, int typevar);
struct LokTabSymbolu {
   string nazev;
   int typ;            // ( Integer = i, String - s )
   int hodnota;
};
typedef struct
{
  string nazev;
   int typ;            // ( Integer = i, Funkce - f, String - s )
   //param;
   int hodnota;
}tData;
typedef struct  GlobTabitem
{
 //   string key;
    tData data;
   struct  GlobTabitem *next;
}SGlobTabitem;

typedef struct
{
  struct  GlobTabitem *first ;
}tglobsymboltable;
void tableinit();

