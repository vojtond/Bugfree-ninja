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
    Rfirst=NULL;/* zasobnik ramcu je prazdny*/

    T->first = NULL;/*globalni tabulka je prazdna*/
    ridic->aktiv= NULL;/*ukazatel na aktivni uzel globalni tabulky*/
    ridic->pomlog = 0;/*pomocna promenna*/
    ridic->pocet_argumentu=0;/*pocet argumentu fce je nula*/
    ridic->deklaration=0;/*pomocna promenna pro definici funkci*/

}

int GlobTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic){/*vlozeni noveho uzlu do glob table*/
    if (typ==FUNCTION_END){/*pokud je konec tela funkce*/
        ridic->aktivG->data.def=1;/*definuj danou funkci*/
        ridic->aktiv=NULL;/*uzel ztraci aktivitu*/
        ridic->pomlog = 0;/*vynulovani ridicich promennych*/
        ridic->pocet_argumentu=0;
        ridic->deklaration=0;
        return 1;
    }
    if (typ==FUNCTION_FORWARD){/*pokud se jedna o doprednou deklaraci funkce*/
            sGlobTableItem *pomg;
            pomg=ridic->aktivG;
            ridic->pomlog = 0;/*vynulování ridicich promennych*/
            ridic->pocet_argumentu=0;
            ridic->deklaration=0;
            if (pomg->data.def==1){/*pokud jiz byla funkce definovana, plati i pro dvakrat deklarovanou funkci*/
                error(T,TAB_ERR,ridic);/*chyba v ramci tabulky*/
            }

        return 1;
    }
    int koren=0;
    struct GlobTabItem *novy;
    sGlobTableItem *pomglob;
    novy = (sGlobTableItem*) malloc(sizeof(sGlobTableItem));/*alokovani mista pro novy globálni uzel*/
    strInit(&(novy->data.nazev));/*plneni uzlu*/
    strCopyString(&(novy->data.nazev), nazev);
    novy->data.typ = typ;
    pomglob=NULL;
    novy->lptr=NULL;
    novy->rptr=NULL;
    strInit(&(novy->arg));
    if (T->first==NULL){/*pokud je strom prazdny*/
        T->first=novy;/*pridame novy uzel na vrchol stromu*/
    }else{
        pomglob=T->first;/*nastavime pomocny ukazatel na vrchol stromu*/
        koren=tableSearchGlob(ridic,&pomglob,&(novy->data.nazev));/*projdeme strom*/
        if (koren==0){/*uzel se stejnym klicem jiz byl nalezen*/
            if (typ==FUNCTION_HEADER){/*pridavany prvek je funkce*/
                if (pomglob->data.typ==FUNCTION_HEADER){/*nalezeny prvek je funkce*/
                    if (pomglob->data.def==0){/*funkce jeste nebyla definována*/
                        pomglob->data.def=1;/*nadefinujeme funkci*/
                        ridic->pomlog = 1;/*nastavime, že se nachazime v hlavicce funkce*/
                        ridic->aktivG=pomglob;/*nastavime aktivitu na nas prvek*/
                        ridic->aktiv=ridic->aktivG->link;/*jako aktivni lokalni tabulku nastavime  ukazatel na lok tabulku  aktivni globalni tabullky*/
                        ridic->deklaration=1;/*nastavime, že budeme cist první argument fce*/
                        ItemFreeAktu(novy,NULL);/*uvolnime pripravovany uzel glob. tabulky*/
                        return 1;
                    }else {ItemFreeAktu(novy,NULL);error(T,TAB_ERR,ridic);}/*chyba v ramci tabulky*/
                }else {ItemFreeAktu(novy,NULL);error(T,TAB_ERR,ridic);}/*chyba v ramci tabulky*/
            }else {ItemFreeAktu(novy,NULL);error(T,TAB_ERR,ridic);}/*chyba v ramci tabulky*/
        }else
        if (koren==1){
            pomglob->lptr=novy;/*uzel vlozime nalevo*/
        }else if (koren==2) {
            pomglob->rptr=novy;/*uzel vlozime napravo*/
        }
    }
        novy->link=NULL;
        novy->data.def=0;/*novy prvek neni definovany*/
        if(typ == FUNCTION_HEADER) {/*pokud se jedna o funkci*/
            ridic->aktivG=novy;/*nastavime jako aktivni*/
            ridic->pomlog = 1;/*jsme v hlavicce fce*/
        } else {novy->link = NULL;}/*neobsahuje lokalni tabulku*/
        return 1;
}
int LokTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic){/*vlození noveho uzlu do lok table*/
    sLokTableItem *novy;
    sLokTableItem *pomloka;
    int koren=0;
    novy = (sLokTableItem*) malloc(sizeof(sLokTableItem));/*alokace mista na novy lokalni prvek*/
    ridic->aktiv=novy;/*nastaveni aktivity na novy prvek*/
    novy->data.def=1;/*plneni prvku*/
    strInit(&(novy->data.nazev));
    novy->data.typ=typ;
    novy->lptr=NULL;
    novy->rptr=NULL;

    if ( ridic->pomlog){/*pokud se jedna o hlavicku fce*/
            ridic->pocet_argumentu++;
            novy->data.def=1;/*argument je inicialyzovany*/
            novy->poradi_argumentu=ridic->pocet_argumentu;/*poradí argumentu*/
    }else {
        novy->data.def=0;/*lokalni promenna neni inicializovana*/
        novy->poradi_argumentu=0;/*nejedna se o argument funkce*/
    }
     if (nazev!=NULL){/*pokud se  nejedna o  navratovy typ*/
        strCopyString((&novy->data.nazev), nazev);/*naplnim nazev*/
    }else {
        strCopyString((&novy->data.nazev), &(ridic->nazev_func));/*jinak ziskam nazev z globalni tabulky z aktualniho prvku*/
         novy->data.def=3;
    }
       sGlobTableItem *pomgl;
         koren=0;
        pomgl = T->first;/*nastavime koren stromu*/
        koren= tableSearchGlob(ridic,&pomgl,&(novy->data.nazev));/*prohledame glob tabulku kvuli shodnym nazvum fci*/
         if (koren==0 && nazev!=NULL){/*pokud byl prvek nalezen a lok promenna neni navratovy typ*/
            if (pomgl->data.typ==FUNCTION_HEADER){/*pokud byla nalezena glob uzel ktery je funkce*/
                ItemFreeAktu(NULL, novy);/*uvolni pridavany prvek*/
                error(T,TAB_ERR,ridic);/*chyba v ramci tabulky*/
            }
        }
    if (ridic->deklaration>0){/*pokud jsme v hlavicce funkce*/
        sLokTableItem *poml;
        sGlobTableItem *pomgl;
        pomgl = ridic->aktivG;/*jako pomocný glob uzel nastavime aktivni glob uzel*/
        poml=pomgl->link;/*jako pomocnou lok. tabulku nastavime odkaz z aktivniho glob  uzlu*/
        koren=0;
        koren=tableSearchLok(ridic,&poml,&(novy->data.nazev));
        if (!koren){

            ItemFreeAktu(NULL, novy);/*uvolnime pridávany prvek*/
            error(T,TAB_ERR,ridic);/*chyba v ramci tabulky*/
        }
        ridic->deklaration++;/*kontrola poctu argumentu*/
        if (ridic->deklaration==strGetLength(&(pomgl->arg))+1) {ridic->deklaration=0;}/*pocet prvku deklrovane a definovane funkce je jiny*/
        if (poml->data.typ==typ){/*pokud sedi typ argumentu deklarovane a definovane funkce*/
            if (poml->poradi_argumentu==novy->poradi_argumentu){/*pokud je na stejnem miste*/
                if (nazev!=NULL){/*pokud se nejedna o navratovy parametr*/
                    if ((strCmpString(&(poml->data.nazev), nazev)==0)) {/*pokud sedi nazvy*/
                        ItemFreeAktu(NULL, novy);/*uvolnime vkladany argument*/
                        return 1;/*agrumnet je totozny*/
                    }else {

                        ItemFreeAktu(NULL, novy);/*uvolnime vkladany argument*/
                        error(T,TAB_ERR,ridic);/*error v ramci tabulky*/
                    }
                }else{/*pokud se jedna o navratovy parametr*/
                    if (ridic->deklaration==strGetLength(&(ridic->aktivG->arg))) {/*pokud neni stejny pocet argumentu*/

                        ItemFreeAktu(NULL, novy);/*uvolnime vkladany argument*/
                        error(T,TAB_ERR,ridic);/*error v ramci tabulky*/
                    }
                    ridic->aktivG=pomgl;/*uvolnime vkládaný argument*/
                    ItemFreeAktu(NULL,novy);/*error v ramci tabulky*/
                    return 1;/*agrumnet je totozny*/
                }
            }else {/*nejedna se o stejny typ*/
                ItemFreeAktu(NULL, novy);/*uvolníme vkladany argument*/
                error(T,TAB_ERR,ridic);/*error v ramci tabulky*/
            }
        }
    }
    else{/*pokud pridavame lokalni promennou*/

     if (ridic->aktivG->link==NULL){/*pokud je strom prazdny*/
            ridic->aktivG->link=novy;/*pridame jako koren*/
    }else{
        pomloka=ridic->aktivG->link;
        koren=0;
        koren=tableSearchLok(ridic,&pomloka,&(novy->data.nazev));
        if (koren==0){/*pokud jiz prvek se stejnym klicem  existuje*/
                ItemFreeAktu(NULL, novy);/*uvolnime vkladany argument*/
                error(T,TAB_ERR,ridic);/*error v ramci tabulky*/

        }
        if (koren==1){/*pridame do leveho podstromu*/
            pomloka->lptr=novy;
        }else if (koren==2) {pomloka->rptr=novy;}/*pridáme do praveho podstromu*/
    }
    if ( ridic->pomlog){/*pokud jsme v hlavicce funkce*/
        switch(typ){/*pridame typ argumnetu do glob tabulky*/
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
    if (nazev==NULL)  {/*pokud uz byl predan i navratovy typ*/
            ridic->pocet_argumentu=0; /*nasleduji lok promenne*/
            ridic->pomlog=0;/*nejsme jiz v hlavicce funkce*/
    }
    return 1;
    }
    return 0;
}

int tableSearch(tGlobSymbolTable *T, string *nazev, int def,Tridic *ridic){/*hledani v glob i lok table*/
    struct GlobTabItem *Gpom;
    sLokTableItem *poml;
     int nenasel = 1;
     if (ridic->aktivG->link!=NULL){/*pokud existuje aktivni lok tabulka*/
        poml=ridic->aktivG->link;
        nenasel=tableSearchLok(ridic,&poml,nazev);/*hledame v lok tabulce*/
        if (!nenasel) {/*pokud jsme nasli*/
            if (def==1)/*pokud je volana jako inicializace*/
                poml->data.def=1;/*nastavime, ze jiz byla inicializovana*/
            else if (poml->data.def==0)/*pokud je neinicializovana*/
                error(T,RUNN_NOIN_ERR,ridic);/*pokus o pristup na neinicializovanou prom*/
        }

     }
     if (nenasel){/*pokud stale nenasel*/
        Gpom = T->first;/*hledame v glob tabulce*/
         nenasel=tableSearchGlob(ridic,&Gpom,nazev);
        if (!nenasel) {/*pokud jsme nasli*/
                if (def==1){/*pokud je volana jako inicializace*/
                    Gpom->data.def=1;/*nastavime, ze již byla inicializovana*/
                }else if (Gpom->data.def==0)/*pokud je neinicializovana*/
                    error(T,RUNN_NOIN_ERR,ridic);/*pokus o prístup na neinicializovanou prom*/
                }
    }
        if(!nenasel) return 1; else error(T,TAB_ERR,ridic);
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

int tableSearchLok(Tridic *ridic,sLokTableItem **poml,string *nazev){/*hledání v lok table*/
    int koren=0;
    while(!koren){/*dokud neni nalezeno misto nebo shoda*/
        if (key(nazev,&((*poml)->data.nazev))==2){/*pokud je vkladany vetsí nez vlozeny*/
            if ((*poml)->rptr!=NULL){/*pokud je vpravo jeste uzel*/
                (*poml)=(*poml)->rptr;/*jdu vpravo*/
            }else{/*jinak vracim ze je vpravo misto*/
                return 2;
            }
        }else   if  (key(nazev,&((*poml)->data.nazev))==1){/*pokud je vkladany mensi nez vlozeny*/
            if ((*poml)->lptr!=NULL){/*pokud je vlevo jeste uzel*/
                (*poml)=(*poml)->lptr;/*jdu vlevo*/
            }else{/*jinak vracim ze je vlevo misto*/
                return 1;
            }
        }else if (key((nazev),&((*poml)->data.nazev))==0){/*shoda*/
            return 0;
        }
    }
    return 0;
}
int tableSearchGlob(Tridic *ridic,sGlobTableItem **pomgl,string *nazev){/*hledani v glob table*/
    int koren=0;
    while (!koren){/*dokud není nalezeno místo nebo shoda*/
        if (key(nazev,&((*pomgl)->data.nazev))==2){/*pokud je vkladany vetsi nez vlozeny*/
            if ((*pomgl)->rptr!=NULL){/*pokud je vpravo ještì uzel*/
                (*pomgl)=(*pomgl)->rptr;/*jdu vpravo*/
            }else {/*jinak vracím že je vpravo místo*/
                return 2;
            }
        } else if  (key(nazev,&((*pomgl)->data.nazev))==1){/*pokud je vkládaný menší než vložený*/
            if ((*pomgl)->lptr!=NULL){/*pokud je vlevo ještì uzel*/
                    (*pomgl)=(*pomgl)->lptr;/*jdu vlevo*/
            }else {/*jinak vracím že je vlevo místo*/
                return 1;
            }
        }else if (key(nazev,&((*pomgl)->data.nazev))==0){/*shoda*/
            return 0;
        }
    }
    return 0;
}

void  TableFree(tGlobSymbolTable *T,Tridic *ridic,sGlobTableItem *koren,int *in){/*rekurzivni mazani tabulek*/
     if((koren)!= NULL) {/*pokud neni globalni tabulka prazdna*/
        if(koren->data.typ == FUNCTION_HEADER){/*pokud je glob. prvek funkce*/
            if(koren->data.def == 0 ) *in=0;/*pokud neni definovana*/
            TableFreeLok(T,ridic,(koren->link));/*zavolam mazani lokalni tabulky*/
        }
		TableFree(T,ridic,(koren->lptr),in);/*posouvam se vlevo*/
		TableFree(T,ridic,(koren->rptr),in);/*posouvam se vpravo*/
        strFree(&(koren->data.nazev));/*mazu*/
        strFree(&(koren->arg));
        free(koren);
        koren = NULL;
	}
return ;
}

void TableFreeLok(tGlobSymbolTable *T,Tridic *ridic,sLokTableItem *koren){/*uvolneni lokalni tabulky*/
    if(koren != NULL){/*pokud neni lokalni prazdna*/
		TableFreeLok(T,ridic,(koren->lptr));/*posouvam se vlevo*/
		TableFreeLok(T,ridic,(koren->rptr));/*posouvam se vpravo*/
        strFree(&(koren->data.nazev));/*mazu*/
		free(koren);
        koren = NULL;
    }

}
void ItemFreeAktu(sGlobTableItem *pomg,sLokTableItem *poml){/*mazani alokovaneho prvku pri chybe*/
    if (pomg!=NULL){/*pokud mazu globalni prvek*/
        strFree(&(pomg->data.nazev));/*smaz*/
        strFree(&(pomg->arg));
        free(pomg);
    }else
    if (poml!=NULL){/*pokud mazu lokalni prvek*/
      strFree(&(poml->data.nazev));/*smaz*/
      free(poml);
    }

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

void PushR(sRamec *Ritem){/*vlozeni ramce do zasobniku*/
    tRamec *pom;
    pom=(tRamec*) malloc(sizeof(tRamec ));/*alukuji prostor*/
    pom->Ritem=Ritem;/*pridani ramce do zasobniku*/
    pom->next=Rfirst;
    Rfirst=pom;
  //novy = (sLokTableItem*) malloc(sizeof(sLokTableItem));
}
void PopTopR(sRamec **Ritem){/*vybrani ramce ze zasobniku*/
    tRamec *pom;
    if (Rfirst!=NULL){/*pokud zasobnik neni prazdny*/
        pom=Rfirst;/*vybereme vrchol*/
        Rfirst=Rfirst->next;/*jako vrchol dame nasledovnika prvniho*/
        *Ritem=pom->Ritem;/*do promenne volane odkazem vlozime vrchol*/
        free(pom);/*uvolnime*/
    }

}

