

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
    int def; // 1 = definov�n, 0 = nedefinov�n
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
//sGlobTableItem *pomfun;
sLokTableItem *aktiv;
void GlobTableInit(tGlobSymbolTable *T);
void GlobVypis(tGlobSymbolTable *T);
int GlobTableInsert(tGlobSymbolTable *T, string *nazev, int typ);   // ov���, zda u� je v tabulce a m� stejn� typ a nebo vlo�� novou

tData *TableSearch(tGlobSymbolTable *T, string *nazev);
void TableFree(tGlobSymbolTable *T);

