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






void GlobTableInit(tGlobSymbolTable *T,Tridic *ridic)/*inicializace globalni tabilky*/
{
    Rfirst=NULL;/* zasobník rámcù je prázdný*/

    T->first = NULL;/*globální tabulka je prázdná*/
    ridic->aktiv= NULL;/*ukazatel na aktivní uzel globální tabulky*/
    ridic->pomlog = 0;/*pomocná promìnná*/
    ridic->pocet_argumentu=0;/*pocet argumentù fce je nula*/
    ridic->deklaration=0;/*pomocná promìnná pro definici funkcí*/

}

int GlobTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic){
    if (typ==FUNCTION_END){/*pokud je konec tìla funkce*/
        ridic->aktivG->data.def=1;/*definuj danou funkci*/
        ridic->aktiv=NULL;/*uzel ztrácí aktivitu*/
        ridic->pomlog = 0;/*vynulování øídících promìnných*/
        ridic->pocet_argumentu=0;
        ridic->deklaration=0;
        return 1;
    }
    if (typ==FUNCTION_FORWARD){/*pokud se jedná o dopøednou deklaraci funkce*/
            sGlobTableItem *pomg;
            pomg=ridic->aktivG;
            ridic->pomlog = 0;/*vynulování øídících promìnných*/
            ridic->pocet_argumentu=0;
            ridic->deklaration=0;
            if (pomg->data.def==1){/*pokud již byla funkce definována, platí i pro dvakrát deklarovanou funkci*/
                error(T,TAB_ERR,ridic);/*chyba v rámci tabulky*/
            }

        return 1;
    }
    int koren=0;
    struct GlobTabItem *novy;
    sGlobTableItem *pomglob;
    novy = (sGlobTableItem*) malloc(sizeof(sGlobTableItem));/*alokování místa pro nový globální uzel*/
    strInit(&(novy->data.nazev));/*plnìní uzlu*/
    strCopyString(&(novy->data.nazev), nazev);
    novy->data.typ = typ;
    pomglob=NULL;
    novy->lptr=NULL;
    novy->rptr=NULL;
    strInit(&(novy->arg));
    if (T->first==NULL){/*pokud je strom prázdný*/
        T->first=novy;/*pøidáme nový uzel na vrchol stromu*/
    }else{
        pomglob=T->first;/*nastavíme pomocný ukazatel na vrchol stromu*/
        koren=tableSearchGlob(ridic,&pomglob,&(novy->data.nazev));/*projdeme strom*/
        if (koren==0){/*uzel se stejným klíèem již byl nalezen*/
            if (typ==FUNCTION_HEADER){/*pøidávaný prvek je funkce*/
                if (pomglob->data.typ==FUNCTION_HEADER){/*nalezený prvek je funkce*/
                    if (pomglob->data.def==0){/*funkce ještì nebyla definována*/
                        pomglob->data.def=1;/*nadefinujeme funkci*/
                        ridic->pomlog = 1;/*nastavíme, že se nachazíme v hlavièce funkce*/
                        ridic->aktivG=pomglob;/*nastavíme aktivitu na náš prvek*/
                        ridic->aktiv=ridic->aktivG->link;/*jako aktivní lokální tabulku nastavíme  ukazatel na lok tabulku  aktivní globální tabullky*/
                        ridic->deklaration=1;/*nastavíme, že budeme èíst první argument fce*/
                        ItemFreeAktu(novy,NULL);/*uvolníme pøipravovaný uzel glob. tabulky*/
                        return 1;
                    }else {ItemFreeAktu(novy,NULL);error(T,TAB_ERR,ridic);}/*chyba v rámci tabulky*/
                }else {ItemFreeAktu(novy,NULL);error(T,TAB_ERR,ridic);}/*chyba v rámci tabulky*/
            }else {ItemFreeAktu(novy,NULL);error(T,TAB_ERR,ridic);}/*chyba v rámci tabulky*/
        }else
        if (koren==1){
            pomglob->lptr=novy;/*uzel vložíme nalevo*/
        }else if (koren==2) {
            pomglob->rptr=novy;/*uzel vložíme napravo*/
        }
    }
        novy->link=NULL;
        novy->data.def=0;/*nový prvek není definovaný*/
        if(typ == FUNCTION_HEADER) {/*pokud se jedná o funkci*/
            ridic->aktivG=novy;/*nastavíme jako aktivní*/
            ridic->pomlog = 1;/*jsme v hlavièce fce*/
        } else {novy->link = NULL;}/*neobsahuje lokální tabulku*/
        return 1;
}
int LokTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic){
    sLokTableItem *novy;
    sLokTableItem *pomloka;
    int koren=0;
    novy = (sLokTableItem*) malloc(sizeof(sLokTableItem));/*alokace místa na nový lokální prvek*/
    ridic->aktiv=novy;/*nastavení aktivity na nový prvek*/
    novy->data.def=1;/*plnìní prvku*/
    strInit(&(novy->data.nazev));
    novy->data.typ=typ;
    novy->lptr=NULL;
    novy->rptr=NULL;
    if (nazev!=NULL){/*pokud se jedná nejedná o  návratový typ*/
        strCopyString((&novy->data.nazev), nazev);/*naplním název*/
    }else strCopyString((&novy->data.nazev), &(ridic->nazev_func));/*jinak získám název z globání tabulky z aktuálního prvku*/
    if ( ridic->pomlog){/*pokud se jedná o hlavièku fce*/
            ridic->pocet_argumentu++;
            novy->data.def=1;/*argument je inicialyzovaný*/
            novy->poradi_argumentu=ridic->pocet_argumentu;/*poøadí argumentu*/
    }else {
        novy->data.def=0;/*lokální promìnná není inicializovaná*/
        novy->poradi_argumentu=0;/*nejedná se o argument funkce*/
    }
       sGlobTableItem *pomgl;
         koren=0;
        pomgl = T->first;/*nastavíme koøen stromu*/
        koren= tableSearchGlob(ridic,&pomgl,&(novy->data.nazev));/*prohledáme glob tabulku kvùli shodným názvùm fcí*/
         if (koren==0 && nazev!=NULL){/*pokud byl prvek nalezen a lok promìnná není návratový typ*/
            if (pomgl->data.typ==FUNCTION_HEADER){/*pokud byla nalezena glob uzel který je funkce*/
                ItemFreeAktu(NULL, novy);/*uvolni pøidávaný prvek*/
                error(T,TAB_ERR,ridic);/*chyba v rámci tabulky*/
            }
        }
		/* 																marek*/
    if (ridic->deklaration>0){/*pokud jsme v hlavièce funkce*/
        sLokTableItem *poml;
        sGlobTableItem *pomgl;
        pomgl = ridic->aktivG;/*jako pomocný glob uzel nastavíme aktivní glob uzel*/
        poml=pomgl->link;/*jako pomocnou lok. tabulku nastavíme odkaz z aktivního glob  uzlu*/
        koren=0;
        koren=tableSearchLok(ridic,&poml,&(novy->data.nazev));
        if (!koren){

            ItemFreeAktu(NULL, novy);/*uvolníme pøidávaný prvek*/
            error(T,TAB_ERR,ridic);/*chyba v rámci tabulky*/
        }
        ridic->deklaration++;/*kontrola poètu argumentù*/
        if (ridic->deklaration==strGetLength(&(pomgl->arg))+1) {ridic->deklaration=0;}/*poèet prvkù deklrované a definované funkce je jiný*/
        if (poml->data.typ==typ){/*pokud sedí typ argumentu deklarované a definované funkce*/
            if (poml->poradi_argumentu==novy->poradi_argumentu){/*pokud je na stejném místì*/
                if (nazev!=NULL){/*pokud se nejedná o návratový parametr*/
                    if ((strCmpString(&(poml->data.nazev), nazev)==0)) {/*pokud sedí název*/
                        ItemFreeAktu(NULL, novy);/*uvolníme vkládaný argument*/
                        return 1;/*agrumnet je totožný*/
                    }else {

                        ItemFreeAktu(NULL, novy);/*uvolníme vkládaný argument*/
                        error(T,TAB_ERR,ridic);/*error v rámci tabulky*/
                    }
                }else{/*pokud se jedná o návratový parametr*/
                    if (ridic->deklaration==strGetLength(&(ridic->aktivG->arg))) {/*pokud není stejný poèet argumentù*/

                        ItemFreeAktu(NULL, novy);/*uvolníme vkládaný argument*/
                        error(T,TAB_ERR,ridic);/*error v rámci tabulky*/
                    }
                    ridic->aktivG=pomgl;/*uvolníme vkládaný argument*/
                    ItemFreeAktu(NULL,novy);/*error v rámci tabulky*/

                    return 1;/*agrumnet je totožný*/
                }
            }else {/*nejedná se o stejný typ*/
                ItemFreeAktu(NULL, novy);/*uvolníme vkládaný argument*/
                error(T,TAB_ERR,ridic);/*error v rámci tabulky*/

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

void  TableFree(tGlobSymbolTable *T,Tridic *ridic,sGlobTableItem *koren,int *in){
     if((koren)!= NULL) {

        if(koren->data.typ == FUNCTION_HEADER){

            if(koren->data.def == 0 ) *in=0;
            TableFreeLok(T,ridic,(koren->link));
        }

		TableFree(T,ridic,(koren->lptr),in);
		TableFree(T,ridic,(koren->rptr),in);
        strFree(&(koren->data.nazev));
        strFree(&(koren->arg));

         free(koren);
        //printf("-- Globalni prvek je po FREE na adrese: %i\n",koren);
            koren = NULL;

        //printf("-- Globalni prvek je po prirazeni NULL na adrese: %i\n\n",koren);
	}
return ;
}

void TableFreeLok(tGlobSymbolTable *T,Tridic *ridic,sLokTableItem *koren){
    if(koren != NULL){
		TableFreeLok(T,ridic,(koren->lptr));
		TableFreeLok(T,ridic,(koren->rptr));
        strFree(&(koren->data.nazev));
		free(koren);
        koren = NULL;
    }

}
void ItemFreeAktu(sGlobTableItem *pomg,sLokTableItem *poml){
    if (pomg!=NULL){
        strFree(&(pomg->data.nazev));
        strFree(&(pomg->arg));
        free(pomg);
    }else
    if (poml!=NULL){
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

    novy->lptr = NULL;
    novy->rptr = NULL;
    PushR(novy);
    printf("konec inicialiyce\n**");
    return novy;
}

void RamecCopy(sLokTableItem *koren, sRamec *novy){

    if(koren != NULL){
        sRamec *pom;

        printf("CO SE CHYSTAM KOPIROVAT\n");
        printf("  -nazev je: %s\n",strGetStr(&(koren->data.nazev)));
        strInit(&(novy->nazev));
        strCopyString((&novy->nazev), (&koren->data.nazev));
        novy->typ = koren->data.typ;
        printf("KOPIRUJI PRVEK\n");
        printf("  -jeho nazev je: %s\n",strGetStr(&(novy->nazev)));
        printf("  -jeho typ je:   %i\n\n",novy->typ);


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

int SearchRamec(sRamec **ramec, string *nazev){
    int koren=0;
    while(!koren){
        if (key(nazev,&((*ramec)->nazev))==2){
            if ((*ramec)->rptr!=NULL){
                (*ramec)=(*ramec)->rptr;
            }else{
                return 2;
            }
        }else   if  (key(nazev,&((*ramec)->nazev))==1){
            if ((*ramec)->lptr!=NULL){
                (*ramec)=(*ramec)->lptr;
            }else{
                return 1;
            }
        }else if (key((nazev),&((*ramec)->nazev))==0){
            return 0;
        }
    }
    return 0;
}

void FreeRamec(sRamec *ramec){
    if(ramec != NULL){
		FreeRamec(ramec->lptr);
		FreeRamec(ramec->rptr);
		printf("        provadim free v ramci  %s\n",strGetStr(&(ramec->nazev)));
        strFree(&(ramec->nazev));
		free(ramec);
        ramec = NULL;
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
   //     printf("pop:%i", Ritem->typ);
        free(pom);
    }

}

