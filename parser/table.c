#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//int pom;

void TableInit(tGlobSymbolTable *T)
{
  T->first = NULL;
  if (T->first==NULL){
    printf("TableInit probehl\n");

  }
}

int GlobTableInsert(tGlobSymbolTable *T, string *nazev, int typ){
    sGlobTableItem *ptr;
    int nasel = 0;
    ptr = T->first;
    while((ptr != NULL)&&(!nasel)){
        nasel = (strCmpString(&(ptr->nazev), nazev) == 0);
        if(!nasel) {ptr = ptr->next;}
    }
    if (!nasel) {
        sGlobTableItem *novy;
        novy = (sGlobTableItem*) malloc(sizeof(sGlobTableItem));
        strInit(&(novy->nazev));
        strCopyString(&(novy->nazev), nazev);
        novy->data.typ = typ;
        novy->next = T->first;
        T->first = novy;
    }
    return 1;
}


tData *tableSearch(tGlobSymbolTable *T, string *nazev){
    sGlobTableItem *ptr;
    ptr = T->first;
    int nasel = 0;
    while((ptr != NULL)&&(!nasel)){
        nasel = (strCmpString(&(ptr->nazev), nazev) == 0);
        if(!nasel) {ptr = ptr->next;}
    }
}

void Vypis(tGlobSymbolTable *T){
    sGlobTableItem *ptr;
    ptr = T->first;

    printf("\n\nVYPIS\n");
    while(ptr != NULL) {
        printf("Pridany prvek ma nazev  %s\n",strGetStr(&(ptr->nazev)));
        printf("   a dany prvek ma typ  %i\n\n",ptr->data.typ);
        ptr = ptr->next;
    }
    return;
    }
