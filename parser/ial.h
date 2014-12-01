
#define TP_MUL 0            //*
#define TP_MOD 1            //MODULO
#define TP_PLUS 2           //+
#define TP_MINUS 3          //-
#define TP_LESS 4           //<
#define TP_MORE 5           //>
#define TP_LESSQ 6          //<=
#define TP_MOREQ 7          //>=
#define TP_EQU 8            //=
#define TP_NEQU 9           //<>
#define TP_LBRA 10          //(
#define TP_RBRA 11          //)
#define TP_IDENT 12         //IDENIFIKÁROR
#define TP_DOLL 13          //$
#define TP_INT 14           //0..9
#define TP_REAL_EXP 15      //0..9 . 0..9 +-E 0..9
#define TP_REAL 16          //0..9 . 0..9
#define TP_EOF 17           //EOF
#define TP_EOL 18           //EOL
#define TP_SEM 19           //;
#define TP_DOT 20           //.
#define TP_COL 21           //:
#define TP_SGNMNT 22        //:=
#define TP_CHAR 23          //#0..255
#define TP_STRING 24        //a..z A..Z
#define TP_COMMA 25         //,

#define ST_START 30
#define	ST_NUMBER 31
#define	ST_REAL_EXP 32
#define	ST_REAL 33
#define	ST_KOMENT 34
#define	ST_IDENT_KEY 35
#define	ST_GREATER 36
#define	ST_STRING 37
#define	ST_CHAR 38
#define	ST_SEM 39
#define	ST_LESS 40
#define	ST_COLONS 41
#define	ST_MORE 42


#define KEY_DO			 	51
#define KEY_IF			 	52
#define KEY_END             53
#define KEY_VAR             54
#define KEY_ELSE            55
#define KEY_FIND            56
#define KEY_REAL            57
#define KEY_SORT            58
#define KEY_THEN            59
#define KEY_TRUE            60
#define KEY_BEGIN           61
#define KEY_FALSE           62
#define KEY_WHILE           63
#define KEY_WRITE           64
#define KEY_READLN          65
#define KEY_STRING          66
#define KEY_BOOLEAN         67
#define KEY_FORWARD         68
#define KEY_INTEGER         69
#define KEY_FUNCTION        70
#define BOOLEAN 73
#define STRING 74
#define FUNCTION_HEADER 75
#define FUNCTION_END 76
#define FUNCTION_FORWARD 77
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
    int     poradi_argumentu;// 0-není argument, jinak pořadí
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
    int token;
    float hodnota;
}Tridic;
void GlobTableInit(tGlobSymbolTable *T,Tridic *ridic);
void GlobVypis(tGlobSymbolTable *T,Tridic *ridic,sGlobTableItem *koren);
int GlobTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic);   // ovìøí, zda už je v tabulce a má stejný typ a nebo vloží novou
int LokTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic);
int tableSearch(tGlobSymbolTable *T, string *nazev,int def,Tridic *ridic);// 1 volam na definici
void TableFree(tGlobSymbolTable *T,Tridic *ridic,sGlobTableItem *koren);
void TableFreeLok(tGlobSymbolTable *T,Tridic *ridic,sLokTableItem *koren);

void LokVypis(tGlobSymbolTable *T,Tridic *ridic,struct LokTabitem *koren);
int lenght(string *str);
int copy(string *str, int i, int j, string *strback);
int find(string *str, string *vzorek, int *ind);
void sort(string *str);

