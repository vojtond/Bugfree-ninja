#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//int pom;

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
    printf("Typ je nazev je %i\n",typ);
    printf("Typ je nazev je %s\n",strGetStr(nazev));
    sGlobTableItem *ptr;
    sGlobTableItem *novy;
    int nasel = 0;
    ptr = T->first;
    while((ptr != NULL)&&(nasel != 0)){
        nasel = (strCmpString(&(ptr->nazev), nazev) == 0);
        if(nasel == 0) {ptr = ptr->next;}
        else {
            if(typ != ptr->data.typ) {return 0;}
            else {return 1;}
        }
    }
    // nenasel
    novy = (sGlobTableItem*) malloc(sizeof(sGlobTableItem));
    if(novy != NULL) {

        strInit(&(novy->nazev));


        strCopyString(&(novy->nazev),nazev);

        //ptr->data.typ = typ;
        printf("Nasel se!!!\n");
        //ptr->next = novy;
        novy->next = NULL;


        return 1;
    } else {return 0;}


}

tData *tableSearch(tGlobSymbolTable *T, string *nazev){
    sGlobTableItem *ptr;
    ptr = T->first;
    int nasel = 0;
    while((ptr != NULL)&&(nasel != 0)){
        nasel = (strCmpString(&(ptr->nazev), nazev) == 0);
    }
    if(nasel == 1){printf("Nasel se!!!\n"); return ptr->data.typ;}
    else {return 0;}
}
