

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
    int typ;             // ( Integer = i, Funkce - f, String - s )
    //param;
    int hodnota;
}tData;

typedef struct  GlobTabitem
{
    string nazev;
    tData data;
    struct GlobTabItem *next;
    struct LokTabItem *link;

}sGlobTableItem;

typedef struct  LokTabitem
{
    string nazev;
    tData data;
    struct  LokTabItem *next;
    int def; // 1 = definov�n, 0 = nedefinov�n
}sLokTableItem;

typedef struct
{
    struct  GlobTabItem *first ;
}tGlobSymbolTable;

void GlobTableInit(tGlobSymbolTable *T);
void GlobVypis(tGlobSymbolTable *T);
int GlobTableInsert(tGlobSymbolTable *T, string *nazev, int typ);   // ov���, zda u� je v tabulce a m� stejn� typ a nebo vlo�� novou
tData *TableSearch(tGlobSymbolTable *T, string *nazev);
void TableFree(tGlobSymbolTable *T);

