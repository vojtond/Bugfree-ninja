
#define INTEGER 71
#define REAL 72
#define BOOLEAN 73
#define STRING 74
#define FUNCTION_HEADER 75
#define FUNCTION_END 76
#include "str.h"
int key(string *klic,string *master);
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
    struct GlobTabItem *lptr;
    struct GlobTabItem *rptr;
    struct LokTabitem *link;
    tData data;

}sGlobTableItem;

typedef struct  LokTabitem
{
    tData   data;
    int     poradi_argumentu;
    struct  LokTabItem *lptr;
    struct  LokTabItem *rptr;
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
     int    pocet_argumentu;
}Tridic;
void GlobTableInit(tGlobSymbolTable *T,Tridic *ridic);
void GlobVypis(tGlobSymbolTable *T,Tridic *ridic,sGlobTableItem *koren);
int GlobTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic);   // ovìøí, zda už je v tabulce a má stejný typ a nebo vloží novou
int LokTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic);
int tableSearch(tGlobSymbolTable *T, string *nazev,int def,Tridic *ridic);// 1 volam na definici
void TableFree(tGlobSymbolTable *T,Tridic *ridic);

void LokVypis(tGlobSymbolTable *T,Tridic *ridic,struct LokTabitem *koren);
