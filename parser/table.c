#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int pom;

void TableInit(tGlobSymbolTable *T)
{
  T->first = NULL;
}
int dek(string *NazevFunkce,string *NazevTokenu, int TypTokenu){

//    strInit(&(GlobTabulka.nazev));
//    pom=strCopyString(&(GlobTabulka.nazev) , NazevTokenu);
//     printf("nazevf: %s\n",strGetStr(NazevFunkce));
//    printf("String je: %s\n",strGetStr(&(GlobTabulka.nazev)));
 //    printf("typ je: %i\n",TypTokenu);
   //   printf("typ ***je: %i\n",TypTokenu);

    return 1;

}

int GlobTableInsert(tGlobSymbolTable *T, string *nazev, int typ){
    tGlobTableItem *ptr;
    tGlobTableItem *novy;
    int nasel;
    ptr = T->first;
    if(ptr == NULL){
        novy = (sGlobTableItem*) malloc(sizeof(sGlobTableItem));

     //&&(nasel == 0)
    }


}

int searchvar(string *variable, int typevar){
return 1;
}