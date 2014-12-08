/*#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void GlobTableInit(tGlobSymbolTable *T,Tridic *ridic)
{
  T->first = NULL;
  strInit(&(ridic->typarg));
 ridic->aktiv= NULL;
ridic->pomlog = 0;
ridic->pocet_argumentu=0;
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
    int koren=0;
    sGlobTableItem *ptr;
    sLokTableItem *poml;
    int nasel = 0;
    ptr = T->first;
    if(!nasel) {
        sGlobTableItem *novy;
        sGlobTableItem *pomglob;
        novy = (sGlobTableItem*) malloc(sizeof(sGlobTableItem));
        strInit(&(novy->data.nazev));
        strCopyString(&(novy->data.nazev), nazev);
        novy->data.typ = typ;
        pomglob=NULL;
        strInit(&(novy->arg));
        if (T->first==NULL){
            novy->lptr=NULL;
            novy->rptr=NULL;
            T->first=novy;
        }else{
            pomglob=T->first;
            while(!koren){
                if (key(&(novy->data.nazev),&(pomglob->data.nazev))==2){
                    if (pomglob->rptr!=NULL){
                        pomglob=pomglob->rptr;
                    }else
                    {
                      koren=2;
                    }
                }else
                if  (key(&(novy->data.nazev),&(pomglob->data.nazev))==1){
                        if (pomglob->lptr!=NULL){
                            pomglob=pomglob->lptr;
                        }else
                        {
                            koren=1;
                        }
                }
                else if (key(&(novy->data.nazev),&(pomglob->data.nazev))==0){
                    if (typ==FUNCTION_HEADER){
                        if (pomglob->data.typ==FUNCTION_HEADER){
                            if (pomglob->data.def==0){
                                pomglob->data.def==1;
                                poml=pomglob->link;
                                ridic->pomlog = 1;
                                ridic->aktivG=pomglob;
                                ridic->aktiv=ridic->aktivG->link;
                                ridic->deklaration=1;
                                return 1;
                            }else return 0;
                        }else return 0;
                    }else return 0;
                }
           }
           if (koren==1){
                sGlobTableItem *pomll;
                pomglob->lptr=novy;
                pomll=T->first;
                pomll=pomll->lptr;
            //    printf("doplneni jedna je%s\n",strGetStr(&(novy->data.nazev)));
             }else if (koren==2) {pomglob->rptr=novy;};
            novy->lptr=NULL;
            novy->rptr=NULL;
        }
        novy->link=NULL;
        novy->data.def=0;
        if(typ == FUNCTION_HEADER) {
            ridic->aktivG=novy;
            ridic->pomlog = 1;
        } else {novy->link = NULL;}
        return 1;
    }else return 0;
}
int LokTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic){
   sLokTableItem *novlok;
   // novlok=ridic->aktivG->link;
    sLokTableItem *novy;
    sLokTableItem *pomloka;
    int koren=0;
    novy = (sLokTableItem*) malloc(sizeof(sLokTableItem));
    ridic->aktiv=novy;
    novy->data.def=1;
    strInit(&(novy->data.nazev));
    novy->data.typ=typ;
    novy->lptr=NULL;
    novy->rptr=NULL;
    if (nazev!=NULL){
        strCopyString((&novy->data.nazev), nazev);
    }else strCopyString((&novy->data.nazev), &(ridic->nazev_func));
    if ( ridic->pomlog){
            ridic->pocet_argumentu++;
            novy->data.def=1;
            novy->poradi_argumentu=ridic->pocet_argumentu;
    }else {
        novy->data.def=0;
        novy->poradi_argumentu=0;
    }
    if (ridic->deklaration>0){
        sLokTableItem *poml;
        sGlobTableItem *pomgl;
        pomgl = ridic->aktivG;
        poml=pomgl->link;
        int nasel=0;
        while (!nasel){
           if (key(&(novy->data.nazev),&(poml->data.nazev))==2){
              if (poml->rptr!=NULL){
                        poml=poml->rptr;
              }else { return 0;}
           } else
                if  (key(&(novy->data.nazev),&(poml->data.nazev))==1){
                        if (poml->lptr!=NULL){
                            poml=poml->lptr;
                        }else {  return 0;}
                }else if (key(&(novy->data.nazev),&(poml->data.nazev))==0){nasel=1;}
        }
        ridic->deklaration++;
        if (ridic->deklaration>strGetLength(&(pomgl->arg))+1) {ridic->deklaration=0;return 0;}
        if (poml->data.typ==typ){
            if (poml->poradi_argumentu==novy->poradi_argumentu){
                if (nazev!=NULL){
                    if ((strCmpString(&(poml->data.nazev), nazev)==0)) {
                        return 1;
                    }else return 0;
                }else{
                    if (ridic->deklaration==strGetLength(&(ridic->aktivG->arg))) {
                        return 0;
                    }
                    ridic->aktivG=pomgl;
                    return 1;
                }
            }else return 0;
        }
    }

    else{

     if (ridic->aktivG->link==NULL){
            novy->lptr=NULL;
            novy->rptr=NULL;
            ridic->aktivG->link=novy;
    }else{
        pomloka=ridic->aktivG->link;
            while(!koren){
                if (key(&(novy->data.nazev),&(pomloka->data.nazev))==2){
                    if (pomloka->rptr!=NULL){
                        pomloka=pomloka->rptr;
                    }else
                    {
                      koren=2;
                    }
                }else
                if  (key(&(novy->data.nazev),&(pomloka->data.nazev))==1){

                        if (pomloka->lptr!=NULL){
                            pomloka=pomloka->lptr;
                        }else
                        {
                            koren=1;
                        }
                }
                else if (key(&(novy->data.nazev),&(pomloka->data.nazev))==0){return 0;}
            }
            if (koren==1){
                sLokTableItem *pomll;
                pomloka->lptr=novy;
             }else if (koren==2) {pomloka->rptr=novy;};
            novy->lptr=NULL;
            novy->rptr=NULL;
        }

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
    }
    if (nazev==NULL)  {ridic->pocet_argumentu=0; ridic->pomlog=0;};

    return 1;
    }
}

int tableSearch(tGlobSymbolTable *T, string *nazev, int def,Tridic *ridic){
    sGlobTableItem *Gpom;
    sLokTableItem *poml;
     int nasel = 0;
     if (ridic->aktivG->link!=NULL){
        poml=ridic->aktivG->link;
        while (!nasel&& poml!=NULL){
           if (key((nazev),&(poml->data.nazev))==2){
              if (poml->rptr!=NULL){
                        poml=poml->rptr;
              }else { poml=NULL;}
           } else
                if  (key((nazev),&(poml->data.nazev))==1){
                        if (poml->lptr!=NULL){
                            poml=poml->lptr;
                        }else {  poml=NULL;}
                }else if (key((nazev),&(poml->data.nazev))==0){nasel=1;}
        }
        if (nasel) {if (def==1)poml->data.def=1;else if (poml->data.def==0)return 0;}

     }
     if (!nasel){

        if (!nasel){
            Gpom = T->first;
            while (!nasel){
            if (key((nazev),&(Gpom->data.nazev))==2){
                if (Gpom->rptr!=NULL){
                    Gpom=Gpom->rptr;
                }else { return 0;}
            } else
                if  (key((nazev),&(Gpom->data.nazev))==1){
                    if (Gpom->lptr!=NULL){
                        Gpom=Gpom->lptr;
                    }else {  return 0;}
                }else if (key((nazev),&(Gpom->data.nazev))==0){nasel=1;}
            }
            if (nasel) if (def==1)Gpom->data.def=1;else if (Gpom->data.def==0)return 0;
        }
     }
        if(nasel) return 1; else return 0;
}

void GlobVypis(tGlobSymbolTable *T,Tridic *ridic,sGlobTableItem *koren){
      //  printf("   a dany prvek ****  %s\n",strGetStr((ptr->arg)));
    if (koren!=NULL){
        printf("\n\nVYPIS - globalni tabulka\n");
        printf("Pridany prvek ma nazev  %s\n",strGetStr(&(koren->data.nazev)));
        printf("   a dany prvek ma typ  %i\n",koren->data.typ);
        printf("   a dany prvek ****  %s\n",strGetStr(&(koren->arg)));
       if (koren->link!=NULL){
            LokVypis(T,ridic,koren->link);


       }
    GlobVypis(T,ridic,koren->lptr);
    GlobVypis(T,ridic,koren->rptr);
    }
}
void LokVypis(tGlobSymbolTable *T,Tridic *ridic,struct LokTabitem *koren){
     if (koren!=NULL){
                printf("        lokalni prvek ma nazev %s\n",strGetStr(&(koren->data.nazev)));
                printf("        argument je  %i\n",koren->poradi_argumentu);
                printf("        lokalni typ je %i\n",koren->data.typ);

                LokVypis(T,ridic,koren->lptr);
                LokVypis(T,ridic,koren->rptr);
    }

}
void TableFree(tGlobSymbolTable *T,Tridic *ridic){
    sGlobTableItem *ptr;
     sLokTableItem *pomlok;
     sLokTableItem *ptrlok;
    ptr = T->first;
    printf("\n\nVYPIS - globalni tabulka\n");
    while(ptr!=NULL) {
        if (ptr->link!=NULL){

            sLokTableItem *pomlok;
            pomlok=ptr->link;
            while (pomlok!=NULL){

                ptrlok=pomlok;
                pomlok=pomlok->next;
                strFree(&ptrlok->data.nazev);
                free(ptrlok);
            }


        }
        free(ptr->link);
//        ptr = ptr->next;

    }
    return;


}*/
