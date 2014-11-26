

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
    int def; // 1 = definován, 0 = nedefinován
}sLokTableItem;

typedef struct
{
    struct  GlobTabItem *first ;
}tGlobSymbolTable;

void GlobTableInit(tGlobSymbolTable *T);
void GlobVypis(tGlobSymbolTable *T);
int GlobTableInsert(tGlobSymbolTable *T, string *nazev, int typ);   // ovìøí, zda už je v tabulce a má stejný typ a nebo vloží novou
tData *TableSearch(tGlobSymbolTable *T, string *nazev);
void TableFree(tGlobSymbolTable *T);

