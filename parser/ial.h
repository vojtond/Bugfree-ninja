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

#define FUNCTION_HEADER 75
#define FUNCTION_END 76
#define FUNCTION_FORWARD 77
#define LEX_ERR 78
#define SYN_ERR 79
#define TAB_ERR 80
 #define SEM_ERR 81
 #define OSEM_ERR 82
 #define RUNN_IN_ERR 83
 #define RUNN_NOIN_ERR 84
 #define RUNN_ZERODI_ERR 85
 #define OTHER_ERR 86
 #define OTHER_RUNN_ERR 87

#include "str.h"
int key(string *klic,string *master);
int dek(string *NazevFunkce,string *NazevTokenu, int TypTokenu);

//*************************** TABULKA SYMBOLŮ **********************************
typedef struct
{
    string nazev;
    int typ;             // ( Integer = i, Funkce - f, String - s )
    int def; // 1 = definován, 0 = nedefinován
}tData;

typedef struct GlobTabItem
{
    string arg;
    struct GlobTabItem *lptr;
    struct GlobTabItem *rptr;
    struct LokTabItem *link;
    tData data;

}sGlobTableItem;

typedef struct LokTabItem
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
    double hodnota;
}Tridic;

//****************************** RAMCE *************************************
typedef struct{
    int cisloh;
    string stringh;
}tHodnota;

typedef struct {
    string nazev;
    int typ;
    tHodnota *hodnota;
    struct sRamec *lptr;
    struct sRamec *rptr;
}sRamec;
typedef struct{
//sRamec *Ritem;
     sRamec  *Ritem;
    struct tRamec *next ;
}tRamec;
tRamec *Rfirst;




typedef struct {
    int typ;

}Trdata;
typedef struct{
//sRamec *Ritem;
     Trdata  data;
    struct tTroj *next ;
}tTroj;
tTroj*Trfirst;
tTroj*Trlast;
void trojvypis();
void trojinsert(int i);
void trojinit();
// ************************* DEKLARACE FUNKCÍ *******************************
// *** PRO TABULKU SYMBOLŮ
void GlobTableInit(tGlobSymbolTable *T,Tridic *ridic);
void GlobVypis(tGlobSymbolTable *T,Tridic *ridic,sGlobTableItem *koren);
int GlobTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic);   // ovìøí, zda už je v tabulce a má stejný typ a nebo vloží novou
int LokTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic);
int tableSearch(tGlobSymbolTable *T, string *nazev,int def,Tridic *ridic);// 1 volam na definici
void TableFree(tGlobSymbolTable *T,Tridic *ridic,sGlobTableItem *koren);
void TableFreeLok(tGlobSymbolTable *T,Tridic *ridic,sLokTableItem *koren);
int tableSearchGlob(Tridic *ridic,sGlobTableItem **pomgl,string *nazev);
int tableSearchLok(Tridic *ridic,sLokTableItem **poml,string *nazev);







void ItemFreeAktu(sGlobTableItem *pomg,sLokTableItem *poml);

void LokVypis(tGlobSymbolTable *T,Tridic *ridic,sLokTableItem *koren);



// *** PRO RÁMCE
sRamec* RamecInit();
void RamecCopy(sLokTableItem *koren, sRamec *novy);
// *** PRO VESTAVĚNNÉ FUNKCE

int lenght(string *str);
string copy(string *str, int i, int j);
int find(string *str, string *vzorek);
string sort(string *str);
void error(tGlobSymbolTable *ST,int error_num,Tridic *ridic);
void pomoc();
void PushR(sRamec *Ritem);
void PopTopR(sRamec **Ritem);
int get_line();

int get_token(FILE *F, double *num, string *stri, int *error );
