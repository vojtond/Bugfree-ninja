#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void GlobTableInit(tGlobSymbolTable *T)
{
  T->first = NULL;
  aktiv= NULL;
  pomlog = 0;
  if (T->first==NULL){
    printf("TableInit probehl\n");

  }
}

int GlobTableInsert(tGlobSymbolTable *T, string *nazev, int typ){
     printf("Pridany prvek ma nazev  %s\n",strGetStr((nazev)));
     printf("Pridany prvek ma nazev  %i\n",typ);
    sGlobTableItem *ptr;
    int nasel = 0;
    ptr = T->first;
    while((ptr != NULL)&&(!nasel)){
        printf("aaa");
        nasel = (strCmpString(&(ptr->data.nazev), nazev) == 0);
        if(!nasel) {ptr = ptr->next;}
    }
    if(!nasel) {
        sGlobTableItem *novy;
        novy = (sGlobTableItem*) malloc(sizeof(sGlobTableItem));
        strInit(&(novy->data.nazev));
        strCopyString(&(novy->data.nazev), nazev);
        novy->data.typ = typ;
        novy->next = T->first;
        if(typ == 75) {
            sLokTableItem *novlok;
            novlok = (sLokTableItem*) malloc(sizeof(sLokTableItem));
            novlok->data.typ = 90;
            strInit(&(novlok->data.nazev));
            strCopyString((&novlok->data.nazev), nazev);
            novy->link = novlok;
            pomlog = 1;
            aktiv= novlok;
            //printf("%i\n",pomfun);
        } else {novy->link = NULL;}
        T->first = novy;
    }
    return 1;
}

int LokTableInsert(tGlobSymbolTable *T, string *nazev, int typ){

/*    sLokTableItem *ptrlok;
    sGlobTableItem *ptr;
    int nasel = 0;
    ptrlok = pomfun;
    while((ptrlok != NULL)&&(!nasel)){
        nasel = (strCmpString(&(ptrlok->data.nazev), nazev) == 0);
        if(!nasel) {ptrlok = ptrlok->next;}
    }
    ptr = T->first;
    while((ptr != NULL)&&(!nasel)){
        nasel = (strCmpString(&(ptr->data.nazev), nazev) == 0);
        if(!nasel) {ptr = ptr->next;}
    }

    if(!nasel) {
        sLokTableItem *novlok;
        novlok = (sLokTableItem*) malloc(sizeof(sLokTableItem));
        ptrlok->next = novlok;
        strInit(&(novlok->data.nazev));
        strCopyString(&(novlok->data.nazev), nazev);
        novlok->data.typ = typ;

    }*/
}


tData *tableSearch(tGlobSymbolTable *T, string *nazev){
    sGlobTableItem *ptr;
    ptr = T->first;
    int nasel = 0;
    while((ptr != NULL)&&(!nasel)){
        nasel = (strCmpString(&(ptr->data.nazev), nazev) == 0);
        if(!nasel) ptr = ptr->next; ;
        printf("aaa");
    }
    if(nasel) return &(ptr->data); else return NULL;
}

void GlobVypis(tGlobSymbolTable *T){
    sGlobTableItem *ptr;
    ptr = T->first;
int i=2;
    printf("\n\nVYPIS - globalni tabulka\n");
    while(ptr!=NULL) {
        printf("Pridany prvek ma nazev  %s\n",strGetStr(&(ptr->data.nazev)));
        printf("   a dany prvek ma typ  %i\n\n",ptr->data.typ);
        ptr = ptr->next;
        i++;
        printf("aaa");
    }
    return;
}
