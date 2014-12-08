#include "ial.h"

typedef struct {    /* Struktura pro uložení dat */
    int inst;
    string op1;
    string op2;
    string result;
    int pozice;
    int label;

}Trdata;

typedef struct sTroj{         /* Struktura pro lineární seznam */
     Trdata  data;
    struct sTroj *next ;
}tTroj;
tTroj*Trfirst;
tTroj*Trlast;

typedef struct skok     /* Struktura pro zásobník */
{
  int Pomlabel;
  int Pomlabelx;
  struct skok *next;
} SKOK;
SKOK*Tfirst;

void trojinit();        /* Funkce pro inicializaci lineárního seznamu */
void trojvypis();       /* Funkce pro výpis lineárního seznamu */
int trojfindfce(string fce);    /* Funkce pro hledání funkce */
int trojfindlab(string o);      /* Funkce pro hledání návìští */
void Generate(int inst, string op1, string op2, string result); /* Funkce pro generování kódu */
