
#define INTEGER 71
#define REAL 72
#define BOOLEAN 73
#define STRING 74
#define FUNCTION_HEADER 75
#define FUNCTION_END 76
#include "str.h"

int dek(string *NazevFunkce,string *NazevTokenu, int TypTokenu);
//int searchvar(string *variable, int typevar);


/*
struct LokTabSymbolu {
    string nazev;
    int typ;            // ( Integer = i, String - s )
    int hodnota;
};
*/

typedef struct
{
    string nazev;
    int typ;             // ( Integer = i, Funkce - f, String - s )
    int def; // 1 = definován, 0 = nedefinován
}tData;

typedef struct  GlobTabitem
{
    string arg;
    struct GlobTabItem *next;
    struct LokTabItem *link;
    tData data;

}sGlobTableItem;

typedef struct  LokTabitem
{
    tData data;
    struct  LokTabItem *next;
}sLokTableItem;

typedef struct
{
    struct  GlobTabItem *first ;
}tGlobSymbolTable;




//sGlobTableItem *pomfun;
typedef struct
{
    int pomlog;
    int deklaration;
     string nazev_ident;
     string attr_token;
     string nazev_func;
     string typarg;
     sLokTableItem *aktiv;
     sGlobTableItem *aktivG;
}Tridic;
void GlobTableInit(tGlobSymbolTable *T,Tridic *ridic);
void GlobVypis(tGlobSymbolTable *T,Tridic *ridic);
int GlobTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic);   // ovìøí, zda už je v tabulce a má stejný typ a nebo vloží novou
int LokTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic);
int tableSearch(tGlobSymbolTable *T, string *nazev,int def,Tridic *ridic);// 1 volam na definici
void TableFree(tGlobSymbolTable *T);

