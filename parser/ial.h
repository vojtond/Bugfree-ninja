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
 #define  WHILE_BEGIN 91
 #define  WHILE_COND 92
 #define  WHILE_END 93
 #define  IF_COND 94
 #define  IF_END 95
 #define  ELSE_BEGIN 96
  #define  ELSE_END 97
   #define  ASSIGN 98
#include "str.h"
int key(string *klic,string *master);/*generování klíče*/


//*************************** TABULKA SYMBOLŮ **********************************
typedef struct
{
    string nazev;
    int typ;             /* ( Integer = TP_int, Funkce - FUNCTION_HEADER, String - TP_STRING, float-TP_REAL, boolean-BOOLEAN )*/
    int def; /* 1 = definován, 0 = nedefinován*/
}tData;

typedef struct{
    int cisloh;
    string stringh;
}tHodnota;

typedef struct GlobTabItem/*globální tabulka*/
{
    string arg;/*pokud je funkce, tak agrumnet volání*/
    struct GlobTabItem *lptr;/*ukazaten na levý podstrom*/
    struct GlobTabItem *rptr;/*ukazatel na pravý podstrom*/
    struct LokTabItem *link;/*ukazatel na lokální binární strom*/
    tData data;
    tHodnota *hodnota;

}sGlobTableItem;

typedef struct LokTabItem/*lokální tabulka*/
{
    tData   data;
    int     poradi_argumentu;/* 0-není argument, jinak 1-n*/
    struct  LokTabItem *lptr;/*ukazatel na levý podstrom*/
    struct  LokTabItem *rptr;/*ukazatel na pravý podstrom*/
}sLokTableItem;

typedef struct
{
    struct  GlobTabItem *first ;/*ukazatel na kořen glob tabulky*/
}tGlobSymbolTable;

typedef struct/*řídící struktura*/
{
    int pomlog;/*jsme v hlavičce funkce*/
    int deklaration;/*pořadí argumentu*/
    string nazev_ident;/*pomocný název tokenu*/
    string attr_token;/*název tokenu*/
    string nazev_func;/*název funkce*/
    sLokTableItem *aktiv;/*kořen aktivní lokázní tabulka*/
    sGlobTableItem *aktivG;/*aktivní glob. uzel*/
    int    pocet_argumentu;/*pořadí argumnetu*/
    int token;/*typ tokenu*/
    double hodnota;/*hodnota tokenu*/
}Tridic;

//****************************** RAMCE *************************************


typedef struct sTRamec{
    string nazev;
    int typ;
    tHodnota *hodnota;
    struct sTRamec *lptr;
    struct sTRamec *rptr;
}sRamec;
typedef struct tTRamec{
     sRamec  *Ritem;
    struct tTRamec *next ;
}tRamec;
tRamec *Rfirst;





// ************************* DEKLARACE FUNKCÍ *******************************
// *** PRO TABULKU SYMBOLŮ
void GlobItemInsert(tGlobSymbolTable *T,string *nazev, int typ,Tridic *ridic, sGlobTableItem **novy);
void GlobTableInit(tGlobSymbolTable *T,Tridic *ridic);/*inicializace glo table*/
void GlobVypis(tGlobSymbolTable *T,Tridic *ridic,sGlobTableItem *koren);
int GlobTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic); /*vložení uzlu do glob table*/
int LokTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic);/*vložení uzlu do lok table*/
int tableSearch(tGlobSymbolTable *T, string *nazev,int def,Tridic *ridic);/*hledání v obouch tabulkách*/
void TableFree(tGlobSymbolTable *T,Tridic *ridic,sGlobTableItem *koren, int *in);/*uvolňování tabulek*/
void TableFreeLok(tGlobSymbolTable *T,Tridic *ridic,sLokTableItem *koren);/*uvolnění lokální tabulky*/
int tableSearchGlob(Tridic *ridic,sGlobTableItem **pomgl,string *nazev);/*hledání v globální tabulce*/
int tableSearchLok(Tridic *ridic,sLokTableItem **poml,string *nazev);/*hledání v lokální tabulce*/
void ItemFreeAktu(sGlobTableItem *pomg,sLokTableItem *poml);/*uvolnění aktuálního prvku*/
void LokVypis(tGlobSymbolTable *T,Tridic *ridic,sLokTableItem *koren);



// *** PRO RÁMCE
sRamec* RamecInit();
void VytvorRamec(sLokTableItem *koren, sRamec *novy);
sRamec* CopyRamec(sRamec *staryramec, sRamec *novy);
int SearchRamec(sRamec **ramec, string *nazev);
void PridatPom(sRamec *ramec, string *nazev, int typ, double cisloh, string *stringh);
void PridatHodnotu(sRamec *ramec, int typ, double cisloh, string *stringh);
void FreeRamec(sRamec *ramec);
void VypisRamce(sRamec *ramec);
// *** PRO VESTAVĚNNÉ FUNKCE

int lenght(string *str);
string copy(string *str, int i, int j);
int find(string *str, string *vzorek);
string sort(string *str);
void error(tGlobSymbolTable *ST,int error_num,Tridic *ridic);
void pomoc();
void PushR(sRamec *Ritem);/*operace vložení rámce do zásobníku*/
void PopTopR(sRamec **Ritem);/*operace výběr ze zásobníku*/
int get_line();

int get_token(FILE *F, double *num, string *stri);/*načtení tokenu*/
