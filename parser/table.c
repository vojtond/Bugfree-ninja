#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void GlobTableInit(tGlobSymbolTable *T,Tridic *ridic)
{
  T->first = NULL;
  strInit(&(ridic->typarg));
 ridic->aktiv= NULL;
ridic->pomlog = 0;
   ridic->deklaration=0;
  if (T->first==NULL){
  }
}

int GlobTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic){
    if (typ==FUNCTION_END){
        ridic->aktivG->data.def=1;
        ridic->aktiv=NULL;
        return 1;
    }

    sGlobTableItem *ptr;
    sLokTableItem *poml;
    int nasel = 0;
    ptr = T->first;
    while((ptr != NULL)&&(!nasel)){
        printf("aaa");
        nasel = (strCmpString(&(ptr->data.nazev), nazev) == 0);
        if(!nasel) {ptr = ptr->next;}
        else if (typ==FUNCTION_HEADER){
           if (ptr->data.def==0){
                ptr->data.def==1;
                poml=ptr->link;
                ridic->aktivG=ptr;
                ridic->aktiv=ridic->aktivG->link;
                ridic->deklaration=1;
               /* while (poml!=NULL){

                    poml->data.def=1;
                    poml=poml->next;
                    return 1;
                }*/
                return 1;
           }

        }
    }
    if(!nasel) {
        sGlobTableItem *novy;
        novy = (sGlobTableItem*) malloc(sizeof(sGlobTableItem));
        strInit(&(novy->data.nazev));
        strCopyString(&(novy->data.nazev), nazev);
        novy->data.typ = typ;
        novy->next = T->first;
        novy->link=NULL;
        novy->data.def=0;
        if(typ == 75) {
            sLokTableItem *novlok;
            strInit(&(novy->arg));
            ridic->aktivG=novy;
            novlok = (sLokTableItem*) malloc(sizeof(sLokTableItem));
            novlok->data.typ = 90;
             novlok->next=NULL;
            strInit(&(novlok->data.nazev));
          //  strCopyString((&novlok->data.nazev), nazev);
            novy->link = novlok;
            ridic->pomlog = 1;
            ridic->aktiv= novlok;
            //printf("%i\n",pomfun);
        } else {novy->link = NULL;}
        T->first = novy;
        return 1;
    }else return 0;

}

int LokTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic){
   sLokTableItem *novlok;
    novlok=ridic->aktivG->link;
     int nasel = 0;
      if (ridic->deklaration>0){
        sLokTableItem *poml;
        sGlobTableItem *pomgl;
        pomgl = ridic->aktivG;
       // while((pomgl != NULL)&&(!nasel)){
         //   nasel = (strCmpString(&(pomgl->data.nazev), &funciden) == 0);
           // if(!nasel) {pomgl = pomgl->next;}
        //}

        int i=1;
        poml=pomgl->link;
        while (i<ridic->deklaration && poml!=NULL){
           poml=poml->next;
           i++;
        }
        ridic->deklaration++;

        if (ridic->deklaration>strGetLength(&(pomgl->arg))) {ridic->deklaration=0; if (poml->next!=NULL) {return 0;}}
        if (poml->data.typ==typ){
           if (nazev!=NULL){
                if ((strCmpString(&(poml->data.nazev), nazev)==0)) {return 1;}else return 0;
           }else{
            if (ridic->deklaration==strGetLength(&(ridic->aktivG->arg))) {return 0;}
            ridic->aktivG=pomgl;
           return 1;
           }

        }
        else
        return 0;
        return 0;
    }
    nasel = 0;
    if (nazev!=NULL){
        while(( novlok!= NULL)&&(!nasel) ){
            nasel = (strCmpString((&novlok->data.nazev), nazev) == 0);
            if(!nasel) {novlok = novlok->next;}

        }

        if (!nasel){
            if ( ridic->pomlog){
                switch(typ){
                    case INTEGER:
                        if (strAddChar(&(ridic->aktivG->arg),'i'));
                    break;
                    case REAL:
                        if (strAddChar(&(ridic->aktivG->arg),'r'));
                    break;
                    case STRING:
                        if (strAddChar(&(ridic->aktivG->arg),'s'));
                    break;
                    case BOOLEAN:
                        if (strAddChar(&(ridic->aktivG->arg),'b'));
                    break;
                }
                if (ridic->aktiv->data.typ==90){
                    ridic->aktiv->data.typ=typ;
                    ridic->aktiv->data.def=1;
                    ridic->aktiv->next=NULL;
                    strInit(&(ridic->aktiv->data.nazev));
                    strCopyString((&(ridic->aktiv->data.nazev)), nazev);
                } else {
                    sLokTableItem *pomlok;
                    pomlok = (sLokTableItem*) malloc(sizeof(sLokTableItem));
                    ridic->aktiv->next=pomlok;
                    ridic->aktiv=pomlok;
                    pomlok->data.def=1;
                    strInit(&(pomlok->data.nazev));
                    pomlok->data.typ=typ;
                    pomlok->next=NULL;
                    strCopyString((&pomlok->data.nazev), nazev);
                }



            }else if ( !ridic->pomlog){
                sLokTableItem *pomlok;
                pomlok = (sLokTableItem*) malloc(sizeof(sLokTableItem));
                ridic->aktiv->next=pomlok;
                ridic->aktiv=pomlok;
                strInit(&(pomlok->data.nazev));
                pomlok->data.def=0;
                pomlok->data.typ=typ;
                pomlok->next=NULL;
                strCopyString((&pomlok->data.nazev), nazev);
            }
        }else return 0;
    }else {
              sLokTableItem *pomlok;
                pomlok = (sLokTableItem*) malloc(sizeof(sLokTableItem));
                ridic->aktiv->next=pomlok;
                ridic->aktiv=pomlok;
                strInit(&(pomlok->data.nazev));
                pomlok->data.def=1;
                pomlok->data.typ=typ;
                pomlok->next=NULL;
                strCopyString((&pomlok->data.nazev), &(ridic->nazev_func));
            switch(typ){
                case INTEGER:
                    if (strAddChar(&(ridic->aktivG->arg),'i'));
                break;
                case REAL:
                    if (strAddChar(&(ridic->aktivG->arg),'r'));
                break;
                case STRING:
                    if (strAddChar(&(ridic->aktivG->arg),'s'));
                break;
                case BOOLEAN:
                    if (strAddChar(&(ridic->aktivG->arg),'b'));
                break;
            }

            ridic->pomlog=0;
    }
    return 1;
}

int tableSearch(tGlobSymbolTable *T, string *nazev, int def,Tridic *ridic){
    sGlobTableItem *Gpom;
    sLokTableItem *Lpom;
    int nasel = 0;
    printf("probehlo\n");
    if (ridic->aktivG->link!=NULL){
        Lpom=ridic->aktivG->link;
        while (Lpom!=NULL&&(!nasel)){
             nasel = (strCmpString(&(Lpom->data.nazev), nazev) == 0);
            if(!nasel) Lpom = Lpom->next;
            else if (def==1)Lpom->data.def=1;else if (Lpom->data.def==0)return 0;
        }
    }

    if (!nasel && !ridic->deklaration){
        Gpom = T->first;
        while((Gpom != NULL)&&(!nasel)){
            nasel = (strCmpString(&(Gpom->data.nazev), nazev) == 0);
            if(!nasel) Gpom = Gpom->next;
            else if (def==1) Gpom->data.def=1; else if (Gpom->data.def==0)return 0;
        }
    }
    if(nasel) return 1; else return NULL;
}

void GlobVypis(tGlobSymbolTable *T,Tridic *ridic){
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
