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
//sRamec *Ritem;
     Trdata  data;
    struct tTroj *next ;
}tTroj;
tTroj*Trfirst;
tTroj*Trlast;


void trojvypis();
void trojinsert(int i, string op1, string op2, string result);
void trojinit();
void trojfindpoz(int pozice);
int trojfindfce(string fce);
int trojfindlab(string o);
void generatelabel(tTroj *pom);

