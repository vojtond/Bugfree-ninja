#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "ial.h"


int lenght(string *str)
{
    return str->length;
}

string copy(string *str, int i, int j)
{
    string strback;
    if ((i < 1) || ((i+j-1) > str->length))
    {
        i=1;
    }
    if ((i+j-1) > str->length)
    {
        i=str->length;
    }
    int p;
    strInit(&strback);
    for (p = 0; p < j; p++)
    {
        strAddChar(&strback,str->str[i+p-1]);
    }
    return strback;
}

int find(string *str, string *vzorek)
{
    int Fail[str->length];
    int TInd = 0;
    int PInd = 0;
    int k,r;

    Fail[0] = -1;
    for (k = 1; k <= vzorek->length; k++)
    {
        r = Fail[k-1];
        while ((r > -1) && (vzorek->str[r] != vzorek->str[k-1]))
        {
            r = Fail[r];
        }
        Fail[k] = r+1;
    }



    while ((TInd < str->length) && (PInd < vzorek->length))
    {
        if ((PInd == -1) || (str->str[TInd] == vzorek->str[PInd]))
        {

            TInd++;
            PInd++;
        }
        else
        {
            PInd = Fail[PInd];

        }
    }
        if (PInd > vzorek->length-1)
        {
            return TInd-vzorek->length+1;
        }
        else
            return 0;


}


string sort(string *str)
{
    int step = str->length / 2;
    int i, j;
    char c;
    while (step > 0)
    {
        for (i = step; i < str->length; i++)
        {
            j = i-step;
            while ((j >= 0) && (str->str[j] > str->str[j+step]))
            {
                c=str->str[j];
                str->str[j] = str->str[j+step];
                str->str[j+step] = c;
                j=j-step;
            }
        }
        step = step / 2;
    }
    return *str;
}






void GlobTableInit(tGlobSymbolTable *T,Tridic *ridic)
{
    Rfirst=NULL;
    T->first = NULL;
    strInit(&(ridic->typarg));
    ridic->aktiv= NULL;
    ridic->pomlog = 0;
    ridic->pocet_argumentu=0;
    ridic->deklaration=0;

}

int GlobTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic){
    if (typ==FUNCTION_END){
        ridic->aktivG->data.def=1;
        ridic->aktiv=NULL;
        ridic->pomlog = 0;
        ridic->pocet_argumentu=0;
        ridic->deklaration=0;
        return 1;
    }
    if (typ==FUNCTION_FORWARD){
            sGlobTableItem *pomg;
            pomg=ridic->aktivG;
            ridic->pomlog = 0;
            ridic->pocet_argumentu=0;
            ridic->deklaration=0;
            if (pomg->data.def==1){
                error(T,TAB_ERR,ridic);
            }

        return 1;
    }
    int koren=0;
    struct GlobTabItem *novy;
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
        koren=tableSearchGlob(ridic,&pomglob,&(novy->data.nazev));
        if (koren==0){
            if (typ==FUNCTION_HEADER){
                if (pomglob->data.typ==FUNCTION_HEADER){
                    if (pomglob->data.def==0){
                        pomglob->data.def=1;
                        ridic->pomlog = 1;
                        ridic->aktivG=pomglob;
                        ridic->aktiv=ridic->aktivG->link;
                        ridic->deklaration=1;
                        ItemFreeAktu(novy,NULL);
                        return 1;
                    }else {printf("1\n");ItemFreeAktu(novy,NULL);error(T,TAB_ERR,ridic);}
                }else {printf("2\n");ItemFreeAktu(novy,NULL);error(T,TAB_ERR,ridic);}
            }else {printf("3\n");ItemFreeAktu(novy,NULL);error(T,TAB_ERR,ridic);}
        }else
        if (koren==1){
            sGlobTableItem *pomll;
            pomglob->lptr=novy;
            pomll=T->first;
            pomll=pomll->lptr;
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
}
int LokTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic){
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
       sGlobTableItem *pomgl;
         koren=0;
        pomgl = T->first;
        koren= tableSearchGlob(ridic,&pomgl,&(novy->data.nazev));
         if (koren==0 && nazev!=NULL){
            if (pomgl->data.typ==FUNCTION_HEADER){
                return 0;
            }
        }
		/* 																marek*/
    if (ridic->deklaration>0){
        printf("volam\n");
        sLokTableItem *poml;
        sGlobTableItem *pomgl;
        pomgl = ridic->aktivG;
        poml=pomgl->link;
        koren=0;
        printf("volam\n");
        koren=tableSearchLok(ridic,&poml,&(novy->data.nazev));
        printf("volam\n");
        if (koren==2){
            printf("**c\n");
            ItemFreeAktu(NULL, novy);
            error(T,TAB_ERR,ridic);
        }
        else if (koren==1){
            printf("**d\n");
            ItemFreeAktu(NULL, novy);
            error(T,TAB_ERR,ridic);
        }
        printf("volam3\n");
        ridic->deklaration++;
        if (ridic->deklaration==strGetLength(&(pomgl->arg))+1) {printf("**d\n");ridic->deklaration=0;}
        printf("volam4\n");
        if (poml->data.typ==typ){
            if (poml->poradi_argumentu==novy->poradi_argumentu){
                if (nazev!=NULL){
                    if ((strCmpString(&(poml->data.nazev), nazev)==0)) {
                        printf("volam5\n");
                        ItemFreeAktu(NULL, novy);
                        printf("volam6\n");
                        return 1;
                    }else {
                        printf("c\n");
                        ItemFreeAktu(NULL, novy);
                        error(T,TAB_ERR,ridic);
                    }
                }else{
                    if (ridic->deklaration==strGetLength(&(ridic->aktivG->arg))) {
                        printf("d\n");
                        ItemFreeAktu(NULL, novy);
                        error(T,TAB_ERR,ridic);
                    }
                    ridic->aktivG=pomgl;
                    ItemFreeAktu(NULL,novy);
                    printf("volam3\n");
                    return 1;
                }
            }else {
                ItemFreeAktu(NULL, novy);
                error(T,TAB_ERR,ridic);

            }
        }
    }
    else{

     if (ridic->aktivG->link==NULL){
            novy->lptr=NULL;
            novy->rptr=NULL;
            ridic->aktivG->link=novy;
    }else{
        pomloka=ridic->aktivG->link;
        koren=0;
        koren=tableSearchLok(ridic,&pomloka,&(novy->data.nazev));
        if (koren==0){
                ItemFreeAktu(NULL, novy);
                error(T,TAB_ERR,ridic);
               return 0;
        }
        if (koren==1){
            pomloka->lptr=novy;
        }else if (koren==2) {pomloka->rptr=novy;}
        novy->lptr=NULL;
        novy->rptr=NULL;
    }
    if ( ridic->pomlog){
        switch(typ){
            case TP_INT:
                if (strAddChar(&(ridic->aktivG->arg),'i'));
            break;
            case TP_REAL:
                if (strAddChar(&(ridic->aktivG->arg),'r'));
            break;
            case TP_STRING:
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
    return 0;
}

int tableSearch(tGlobSymbolTable *T, string *nazev, int def,Tridic *ridic){
    struct GlobTabItem *Gpom;
    sLokTableItem *poml;
     int nasel = 1;
     if (ridic->aktivG->link!=NULL){
        poml=ridic->aktivG->link;
        nasel=tableSearchLok(ridic,&poml,nazev);
        if (!nasel) {if (def==1)poml->data.def=1;else if (poml->data.def==0)error(T,RUNN_NOIN_ERR,ridic);}else nasel=1;

     }
     if (nasel!=0){
        Gpom = T->first;
         nasel=tableSearchGlob(ridic,&Gpom,nazev);
        if (!nasel) {if (def==1){Gpom->data.def=1;}else if (Gpom->data.def==0)error(T,RUNN_NOIN_ERR,ridic);}
    }
        if(!nasel) return 1; else return 0;
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
void LokVypis(tGlobSymbolTable *T,Tridic *ridic,sLokTableItem *koren){
     if (koren!=NULL){
                printf("        lokalni prvek ma nazev %s\n",strGetStr(&(koren->data.nazev)));
                printf("        argument je  %i\n",koren->poradi_argumentu);
                printf("        lokalni typ je %i\n",koren->data.typ);

                LokVypis(T,ridic,koren->lptr);
                LokVypis(T,ridic,koren->rptr);
    }

}

int tableSearchLok(Tridic *ridic,sLokTableItem **poml,string *nazev){
    int koren=0;
    while(!koren){
        if (key(nazev,&((*poml)->data.nazev))==2){
            if ((*poml)->rptr!=NULL){
                (*poml)=(*poml)->rptr;
            }else{
                return 2;
            }
        }else   if  (key(nazev,&((*poml)->data.nazev))==1){
            if ((*poml)->lptr!=NULL){
                (*poml)=(*poml)->lptr;
            }else{
                return 1;
            }
        }else if (key((nazev),&((*poml)->data.nazev))==0){
            return 0;
        }
    }
    return 0;
}
int tableSearchGlob(Tridic *ridic,sGlobTableItem **pomgl,string *nazev){
    int koren=0;
    while (!koren){
        if (key(nazev,&((*pomgl)->data.nazev))==2){
            if ((*pomgl)->rptr!=NULL){
                (*pomgl)=(*pomgl)->rptr;
            }else {
                return 2;
            }
        } else if  (key(nazev,&((*pomgl)->data.nazev))==1){
            if ((*pomgl)->lptr!=NULL){
                    (*pomgl)=(*pomgl)->lptr;
            }else {
                return 1;
            }
        }else if (key(nazev,&((*pomgl)->data.nazev))==0){
            return 0;
        }
    }
    return 0;
}

void TableFree(tGlobSymbolTable *T,Tridic *ridic,sGlobTableItem *koren){
	if((koren)!= NULL) {

        if(koren->data.typ == FUNCTION_HEADER){
            if(koren->data.def == 0) error(NULL,RUNN_NOIN_ERR,ridic);
            TableFreeLok(T,ridic,(koren->link));
        }

		TableFree(T,ridic,(koren->lptr));
		TableFree(T,ridic,(koren->rptr));

        printf("provadim free nad nad glob %s\n",strGetStr(&(koren->data.nazev)));
        strFree(&(koren->data.nazev));
        strFree(&(koren->arg));

         free(koren);
        //printf("-- Globalni prvek je po FREE na adrese: %i\n",koren);
            koren = NULL;
        //printf("-- Globalni prvek je po prirazeni NULL na adrese: %i\n\n",koren);
	}

}

void TableFreeLok(tGlobSymbolTable *T,Tridic *ridic,sLokTableItem *koren){
    if(koren != NULL){
		TableFreeLok(T,ridic,(koren->lptr));
		TableFreeLok(T,ridic,(koren->rptr));
		printf("        provadim free v lok tab nad  %s\n",strGetStr(&(koren->data.nazev)));
        strFree(&(koren->data.nazev));
		free(koren);
        koren = NULL;
    }

}
void ItemFreeAktu(sGlobTableItem *pomg,sLokTableItem *poml){
    printf("vleylo");
    if (pomg!=NULL){
        printf("            provadim free nad glob novym %s\n",strGetStr(&(pomg->data.nazev)));
        strFree(&(pomg->data.nazev));
        strFree(&(pomg->arg));
        free(pomg);
         printf("free probehlo novym glob\n");
    }else
    if (poml!=NULL){
      printf("              provadim free nad lok novym %s\n",strGetStr(&(poml->data.nazev)));
      strFree(&(poml->data.nazev));
      free(poml);
    }

}
void ItemFreeAktuL(sLokTableItem *poml){
}

sRamec* RamecInit(){
    sRamec *novy;
    printf("INICIALIZACE RAMCE\n\n");
    novy = (sRamec*) malloc(sizeof(sRamec));
    PushR(novy);
    novy->lptr = NULL;
    novy->rptr = NULL;
    return novy;
}

void RamecCopy(sLokTableItem *koren, sRamec *novy){
    if(koren != NULL){
        printf("CO SE CHYSTAM KOPIROVAT\n");
        printf("  -nazev je: %s\n",strGetStr(&(koren->data.nazev)));
        strInit(&(novy->nazev));
        strCopyString((&novy->nazev), (&koren->data.nazev));
        novy->typ = koren->data.typ;
        printf("KOPIRUJI PRVEK\n");
        printf("  -jeho nazev je: %s\n",strGetStr(&(novy->nazev)));
        printf("  -jeho typ je:   %i\n\n",novy->typ);
        sRamec *pom;

        if(koren->lptr != NULL){
            pom = (sRamec*) malloc(sizeof(sRamec));
            novy->lptr = pom;
            RamecCopy(koren->lptr, novy->lptr);
        }
        if(koren->rptr != NULL){
            pom = (sRamec*) malloc(sizeof(sRamec));
            novy->rptr = pom;
            RamecCopy(koren->rptr, novy->rptr);
        }
    }


}
void PushR(sRamec *Ritem){
    tRamec *pom;
    pom=(tRamec*) malloc(sizeof(tRamec ));
    pom->Ritem=Ritem;
    pom->next=Rfirst;
    Rfirst=pom;
  //novy = (sLokTableItem*) malloc(sizeof(sLokTableItem));
}
void PopTopR(sRamec **Ritem){
    tRamec *pom;
    if (Rfirst!=NULL){
      pom=Rfirst;
      Rfirst=Rfirst->next;
      *Ritem=pom->Ritem;
      free(pom);
    }

}
