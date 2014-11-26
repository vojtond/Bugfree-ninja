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
    printf("Ptr je %i\n",ptr);
    if (ptr==NULL){
        printf("Nechapu proc je ptr null!!\n");
    }
    while((ptr != NULL)&&(!nasel)){
        printf("Proc mi to kurwa pica nemeni ten posranej ptr..proc je porad null?\n");
        nasel = (strCmpString(&(ptr->nazev), nazev) == 0);
        if(!nasel) {
            ptr = ptr->next;
            printf("Kdyz se nenasel, tak se jde na dalsi prvek.!!\n");
            }
    }

    if (!nasel) {
        sGlobTableItem *novy;
        novy = (sGlobTableItem*) malloc(sizeof(sGlobTableItem));
        strInit(&(novy->nazev));
        strCopyString(&(novy->nazev), nazev);
        novy->data.typ = typ;
        novy->next = T->first;
        printf("Pridany prvek ma nazev  %s\n",strGetStr(&(novy->nazev)));
        printf("Pridany prvek ma typ  %i\n\n",novy->data.typ);
        T->first = novy;
    }

    return 1;



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
