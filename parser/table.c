#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void GlobTableInit(tGlobSymbolTable *T)
{
  T->first = NULL;
  strInit(&typarg);
  aktiv= NULL;
  pomlog = 0;
  if (T->first==NULL){
    printf("TableInit probehl\n");

  }
}

int GlobTableInsert(tGlobSymbolTable *T, string *nazev, int typ){

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
            strInit(&(novy->arg));
            aktivG=novy;
            novlok = (sLokTableItem*) malloc(sizeof(sLokTableItem));
            novlok->data.typ = 90;
             novlok->next=NULL;
            strInit(&(novlok->data.nazev));
          //  strCopyString((&novlok->data.nazev), nazev);
            novy->link = novlok;
            pomlog = 1;
            aktiv= novlok;
            //printf("%i\n",pomfun);
        } else {novy->link = NULL;}
        T->first = novy;
        return 1;
    }else return 0;

}

int LokTableInsert(tGlobSymbolTable *T, string *nazev, int typ){
   sLokTableItem *novlok;
    novlok=aktivG->link;
     int nasel = 0;
    if (nazev!=NULL){
        while(( novlok!= NULL)&&(!nasel) ){
            nasel = (strCmpString((&novlok->data.nazev), nazev) == 0);
            if(!nasel) {novlok = novlok->next;}

        }

        if (!nasel){
            if ( pomlog){
                switch(typ){
                    case INTEGER:
                        if (strAddChar(&(aktivG->arg),'i'));
                    break;
                    case REAL:
                        if (strAddChar(&(aktivG->arg),'r'));
                    break;
                    case STRING:
                        if (strAddChar(&(aktivG->arg),'s'));
                    break;
                    case BOOLEAN:
                        if (strAddChar(&(aktivG->arg),'b'));
                    break;
                }
                if (aktiv->data.typ==90){
                    aktiv->data.typ=typ;
                    aktiv->next=NULL;
                    strInit(&(aktiv->data.nazev));
                    strCopyString((&aktiv->data.nazev), nazev);
                } else {
                    sLokTableItem *pomlok;
                    pomlok = (sLokTableItem*) malloc(sizeof(sLokTableItem));
                    aktiv->next=pomlok;
                    aktiv=pomlok;
                    strInit(&(pomlok->data.nazev));
                    pomlok->data.typ=typ;
                    pomlok->next=NULL;
                    strCopyString((&pomlok->data.nazev), nazev);
                }



            }else if ( !pomlog){
                sLokTableItem *pomlok;
                pomlok = (sLokTableItem*) malloc(sizeof(sLokTableItem));
                aktiv->next=pomlok;
                aktiv=pomlok;
                strInit(&(pomlok->data.nazev));
                pomlok->data.typ=typ;
                pomlok->next=NULL;
                strCopyString((&pomlok->data.nazev), nazev);
            }
        }else return 0;
    }else {
            switch(typ){
                case INTEGER:
                    if (strAddChar(&(aktivG->arg),'i'));
                break;
                case REAL:
                    if (strAddChar(&(aktivG->arg),'r'));
                break;
                case STRING:
                    if (strAddChar(&(aktivG->arg),'s'));
                break;
                case BOOLEAN:
                    if (strAddChar(&(aktivG->arg),'b'));
                break;
            }

            pomlog=0;
    }
    return 1;
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
        printf("   a dany prvek ma typ  %i\n",ptr->data.typ);
        printf("   a dany prvek ****  %s\n",strGetStr(&(ptr->arg)));
        if (ptr->link!=NULL){

            sLokTableItem *pomlok;
            pomlok=ptr->link;
            while (pomlok!=NULL){
                printf("        lokalni prvek ma nazev %s\n",strGetStr(&(pomlok->data.nazev)));
                printf("        lokalni typ je %i\n",pomlok->data.typ);
                pomlok=pomlok->next;

            }


        }
        ptr = ptr->next;
        i++;
    }
    return;
}
