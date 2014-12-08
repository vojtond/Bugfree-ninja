#include "ial.h"

typedef struct {    /* Struktura pro ulo�en� dat */
    int inst;
    string op1;
    string op2;
    string result;
    int pozice;
    int label;

}Trdata;

typedef struct sTroj{         /* Struktura pro line�rn� seznam */
     Trdata  data;
    struct sTroj *next ;
}tTroj;
tTroj*Trfirst;
tTroj*Trlast;

typedef struct skok     /* Struktura pro z�sobn�k */
{
  int Pomlabel;
  int Pomlabelx;
  struct skok *next;
} SKOK;
SKOK*Tfirst;

void trojinit();        /* Funkce pro inicializaci line�rn�ho seznamu */
void trojvypis();       /* Funkce pro v�pis line�rn�ho seznamu */
int trojfindfce(string fce);    /* Funkce pro hled�n� funkce */
int trojfindlab(string o);      /* Funkce pro hled�n� n�v�t� */
void Generate(int inst, string op1, string op2, string result); /* Funkce pro generov�n� k�du */
