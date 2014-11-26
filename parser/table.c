#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//int pom;

void TableInit(tGlobSymbolTable *T)
{
  T->first = NULL;
  if (T->first==NULL){
    printf("dsds");

  }
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

    printf("Typ jenaz je %i\n",typ);

    printf("Typ je nazev je %i\n",typ);
    // printf("Typ je nazesdsdsv je %i\n",typ);

    printf("Typ je nazev je %s\n",strGetStr(nazev));

    sGlobTableItem *ptr;
    sGlobTableItem *novy;
    int nasel = 0;
    ptr = T->first;
        if (T->first==NULL){
    printf("T je null");

  }
    if (ptr==NULL){
    printf("ptr je null");

  }
    /*while((ptr != NULL)&&(nasel == 0)){
        printf("Nasel se!!!\n");
        printf("PTR nazev je %s\n\n",strGetStr(&(ptr->nazev)));
        nasel = strCmpString(&(ptr->nazev), &nazev);
        printf("Nasel %i\n",nasel);
        if(nasel == 0) {
            ptr = ptr->next;
            printf("vlezl sem!!!\n");
            }
        else {
            if(typ != ptr->data.typ) {
                printf("Chyba, stejnej nazev, spatnej typ!!!\n");
                return 0;
                }
            else {
                printf("Nasel se!!!\n");
                return 1;}
        }
    }*/
    // nenasel
    printf("1\n");
    novy = (sGlobTableItem*) malloc(sizeof(sGlobTableItem));
    if(novy != NULL) {
        printf("2\n");
        strInit(&(novy->nazev));


        strCopyString(&(novy->nazev),nazev);
         printf("novy->nazev je: **%s**\n",strGetStr(&(novy->nazev)));
        printf("3\n");
        printf("typ tokenu je: **%i**\n",typ);
        ptr->data.typ = typ;
        printf("3.4\n");
        ptr->next = novy;
        printf("3.5\n");
        novy->next = NULL;
         printf("4\n");
        printf("Typ je nazev je %i\n",ptr->data.typ);
        printf("Typ je nazev je %s\n\n",strGetStr(&(novy->nazev)));
        return 1;
    } else {
        printf("Zkurvenej else dole!!\n");
        return 0;}


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
