#include "ial.h"

typedef struct {
    int inst;
    string op1;
    string op2;
    string result;
    int pozice;
    int label;

}Trdata;
typedef struct{
     Trdata  data;
    struct tTroj *next ;
}tTroj;
tTroj*Trfirst;
tTroj*Trlast;

typedef struct skok
{
  int Pomlabel;
  int Pomlabelx;
  struct skok *next;
} SKOK;
SKOK*Tfirst;


void trojvypis();
void trojinsert(int i, string op1, string op2, string result);
void trojinit();
int trojfindfce(string fce);
int trojfindlab(string o);


