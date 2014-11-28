
#define INTEGER 71
#define REAL 72
#define BOOLEAN 73
#define STRING 74
#define FUNCTION_HEADER 75
#define FUNCTION_END 76
#include "str.h"
string funciden;
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
int LokTableInsert(tGlobSymbolTable *T, string *nazev, int typ);
int pomlog;
int deklaration;
string typarg;
//sGlobTableItem *pomfun;
sLokTableItem *aktiv;
sGlobTableItem *aktivG;
void GlobTableInit(tGlobSymbolTable *T);
void GlobVypis(tGlobSymbolTable *T);
int GlobTableInsert(tGlobSymbolTable *T, string *nazev, int typ);   // ovìøí, zda už je v tabulce a má stejný typ a nebo vloží novou

int tableSearch(tGlobSymbolTable *T, string *nazev,int def);// 1 volam na definici
void TableFree(tGlobSymbolTable *T);

