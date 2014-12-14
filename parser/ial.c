#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "ial.h"



int lenght(string *str)														//Funkce, která vrací délu řetězce.
{
    return str->length;														//Vracíme délku řetězce ze struktury string.
}

string copy(string *str, int i, int j)										//Funkce vrací podřetězec z řetězce str od i o délce j.
{
    string strback;															//Pomocná proměnná typu string.
	int p;																	//Řídící proměnná for cyklu.

    if (i < 1)																//Pokud je i menší než 1, přiřadíme mu hodnotu 1, aby jsme nepřistupovali mimo string.
    {
        i=1;
    }
    if ((i+j-1) > str->length)												//Pokud je j větší než délka řetězce, upravíme jej, aby jsme nekopírovali prvky za rozsahem stringu.
    {
        j=str->length-i+1;
    }

    strInit(&strback);														//Inicializace stringu.
    for (p = 0; p < j; p++)													//For cyklus o j opakováních.
    {
        strAddChar(&strback,str->str[i+p-1]);								//Jednotlivé znaky přidáváme do strback.
    }
    return strback;															//Vracíme string.
}

int find(string *str, string *vzorek)										//Funkce která najde vzorek v str.
{
    int Fail[str->length];													//Pole Fail o délce str->lenght.
    int TInd = 0;															//Index prvku v str.
    int PInd = 0;															//Index prvku ve vzorku.
    int k,r;																//Pomocné proměnné.

    Fail[0] = -1;															//Do prvního prvku pole si přiřadíme -1.
    for (k = 1; k <= vzorek->length; k++)
    {
        r = Fail[k-1];														//Do r si přiřadíme hodnotu z prvku k-1.
        while ((r > -1) && (vzorek->str[r] != vzorek->str[k-1]))			//Procházíme vzorek a zjišťujeme na kterou pozici se můžeme vrátit při neshodě na každé pozici.
        {
            r = Fail[r];
        }
        Fail[k] = r+1;
    }



    while ((TInd < str->length) && (PInd < vzorek->length))					//Samotné vyhledávání podřetězce.
    {
        if ((PInd == -1) || (str->str[TInd] == vzorek->str[PInd]))			//Pokud se str na indexu TInd rovná vzorku na indexu PInd..
        {

            TInd++;															//Inkrementujeme obě počítadla.
            PInd++;
        }
        else
        {
            PInd = Fail[PInd];												//Pokud se nerovná, vracíme se na index, který je uložem v poli Fail.

        }
    }
        if (PInd > vzorek->length-1)										//Ppokud je PInd větší než délka vzorku -1, prošli jsme vzorek až na konec a mám eshodu.
        {
            return TInd-vzorek->length+1;									//Vracíme index, na kterém jsme našli podřetězec.
        }
        else
            return 0;														//Nenašli jsme podřetězec, vracíme 0.


}


string sort(string *str)
{
    int step = str->length / 2;												//Proměnná v které máme uložený krok, pro procházení řetězce.
    int i, j;																//Pomocné proměnné pro průchod.
    char c;

    while (step > 0)														//Procházíme, dokud je krok větší než 0.
    {
        for (i = step; i < str->length; i++)
        {
            j = i-step;														//Posun na další prvek.
            while ((j >= 0) && (str->str[j] > str->str[j+step]))			//Bubble sort pro prvky vzdálené o step.
            {
                c=str->str[j];												//Výměna dvou prvku.
                str->str[j] = str->str[j+step];
                str->str[j+step] = c;
                j=j-step;													//Snížení indexu o krok.
            }
        }
        step = step / 2;													//Po všech průchodech vždy rozpůlíme krok.
    }
    return *str;															//Vracíme seřazený string.
}










void GlobTableInit(tGlobSymbolTable *T,Tridic *ridic)/*inicializace globalni tabilky*/
{
    string pom;

    sGlobTableItem *novy;
    Rfirst=NULL;/* zasobnik ramcu je prazdny*/

    T->first = NULL;/*globalni tabulka je prazdna*/
    ridic->aktiv= NULL;/*ukazatel na aktivni uzel globalni tabulky*/
    ridic->pomlog = 0;/*pomocna promenna*/
    ridic->pocet_argumentu=0;/*pocet argumentu fce je nula*/
    ridic->deklaration=0;/*pomocna promenna pro definici funkci*/
    strInit(&pom);

    strAddStr(&pom,"length");
    GlobItemInsert(T,&pom,FUNCTION_HEADER,ridic,&novy);
    strAddStr(&(novy->arg),"si");
    strClear(&pom);
    strAddStr(&pom,"copy");
    GlobItemInsert(T,&pom,FUNCTION_HEADER,ridic,&novy);
    strAddStr(&(novy->arg),"siis");
    strClear(&pom);
    strAddStr(&pom,"find");
    GlobItemInsert(T,&pom,FUNCTION_HEADER,ridic,&novy);
    strAddStr(&(novy->arg),"ssi");
    strClear(&pom);
    strAddStr(&pom,"sort");
    GlobItemInsert(T,&pom,FUNCTION_HEADER,ridic,&novy);
    strAddStr(&(novy->arg),"ss");

}
void GlobItemInsert(tGlobSymbolTable *T,string *nazev, int typ,Tridic *ridic, sGlobTableItem **novy){
    int koren=0;
    if (((*novy) = (sGlobTableItem*) malloc(sizeof(sGlobTableItem)))==NULL) error(T,OTHER_RUNN_ERR,ridic);/*alokovani mista pro novy globálni uzel*/
    sGlobTableItem *pomglob;
    strInit(&((*novy)->data.nazev));/*plneni uzlu*/
    strCopyString(&((*novy)->data.nazev), nazev);
    (*novy)->data.typ = typ;
    (*novy)->lptr=NULL;
    (*novy)->rptr=NULL;
    (*novy)->data.def=1;
    strInit(&((*novy)->arg));
    //strInit(&((*novy)->hodnota->stringh));
    ridic->aktivG=(*novy);
    ridic->aktivG->link=NULL;
    if (T->first==NULL){/*pokud je strom prazdny*/
        T->first=(*novy);/*pridame novy uzel na vrchol stromu*/
     }else{
        pomglob=T->first;/*nastavime pomocny ukazatel na vrchol stromu*/
        koren=tableSearchGlob(ridic,&pomglob,&((*novy)->data.nazev));/*projdeme strom*/
     }
      if (koren==1){
            pomglob->lptr=(*novy);/*uzel vlozime nalevo*/
        }else if (koren==2) {
            pomglob->rptr=(*novy);/*uzel vlozime napravo*/
        }
}
int GlobTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic){/*vlozeni noveho uzlu do glob table*/
    if (typ==FUNCTION_END){/*pokud je konec tela funkce*/
        ridic->aktivG->data.def=1;/*definuj danou funkci*/
        ridic->aktiv=NULL;/*uzel ztraci aktivitu*/
        ridic->pomlog = 0;/*vynulovani ridicich promennych*/
        ridic->pocet_argumentu=0;
        ridic->deklaration=0;
       // ridic->aktivG->link=NULL;
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
    if ((novy = (sGlobTableItem*) malloc(sizeof(sGlobTableItem)))==NULL) error(T,OTHER_RUNN_ERR,ridic);/*alokovani mista pro novy globálni uzel*/
    strInit(&(novy->data.nazev));/*plneni uzlu*/
    strCopyString(&(novy->data.nazev), nazev);
    novy->data.typ = typ;
    pomglob=NULL;
    novy->lptr=NULL;
    novy->rptr=NULL;
    strInit(&(novy->arg));
    // strInit(&(novy->hodnota->stringh));
    ridic->aktivG=novy;
    ridic->aktivG->link=NULL;
    pomglob=T->first;/*nastavime pomocny ukazatel na vrchol stromu*/
    koren=tableSearchGlob(ridic,&pomglob,&(novy->data.nazev));/*projdeme strom*/
    if (koren==0){/*uzel se stejnym klicem jiz byl nalezen*/
        if (typ==FUNCTION_HEADER){/*pridavany prvek je funkce*/
            if (pomglob->data.typ==FUNCTION_HEADER){/*nalezeny prvek je funkce*/
                if (pomglob->data.def==0){/*funkce jeste nebyla definována*/
                    pomglob->data.def=1;/*nadefinujeme funkci*/
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
    if ((novy = (sLokTableItem*) malloc(sizeof(sLokTableItem)))==NULL) error(T,OTHER_RUNN_ERR,ridic);/*alokace mista na novy lokalni prvek*/
    ridic->aktiv=novy;/*nastaveni aktivity na novy prvek*/
    novy->data.def=1;/*plneni prvku*/
    strInit(&(novy->data.nazev));
    novy->data.typ=typ;
    novy->lptr=NULL;
    novy->rptr=NULL;

    if ( ridic->pomlog || ridic->deklaration){/*pokud se jedna o hlavicku fce*/
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
        if (koren){
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

    if ( (ridic->pomlog ) || (nazev==NULL) ){/*pokud jsme v hlavicce funkce*/


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

    if (T->first!=NULL){
     if (ridic->aktiv!=NULL){/*pokud existuje aktivni lok tabulka*/

        poml=ridic->aktivG->link;
        nenasel=tableSearchLok(ridic,&poml,nazev);/*hledame v lok tabulce*/
        if (!nenasel) {/*pokud jsme nasli*/
            return poml->data.typ;

        }

     }
    if(!nenasel) {return poml->data.typ;}
    else {
        if (nenasel){/*pokud stale nenasel*/

            Gpom = T->first;/*hledame v glob tabulce*/
            nenasel=tableSearchGlob(ridic,&Gpom,nazev);

        }
        if(!nenasel) return Gpom->data.typ; else error(T,TAB_ERR,ridic);

    }
}
return 0;
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
        //strFree(&(koren->hodnota->stringh));
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

sRamec* RamecInit(){/*inicializace prvniho prvku noveho ramce*/
    sRamec *novy;
     if ((novy = (sRamec*) malloc(sizeof(sRamec)))==NULL) error(NULL,OTHER_RUNN_ERR,NULL);/*malokuje misto pro nove vytvoreny ramec*/

    novy->lptr = NULL; /*nastavi ukazatele prvniho prvku na NULL*/
    novy->rptr = NULL;
    PushR(novy); /*ulozi odkaz na ramec do zasobniku*/
    return novy;
}

sRamec* GlobRamecInit(){ /*inicializace prvniho prvku noveho globalniho ramce*/
    sRamec *novy;
    if ((novy = (sRamec*) malloc(sizeof(sRamec)))==NULL) error(NULL,OTHER_RUNN_ERR,NULL);/*malokuje misto pro nove vytvoeeny ramec*/

    novy->lptr = NULL;/*nastavi ukazatele prvniho prvku na NULL*/
    novy->rptr = NULL;
    GlobRamec = novy;/*globalni ramec je jenom jeden, proto ho staci ulozit do globalni promene*/
    return novy;
}


void VytvorRamec(sLokTableItem *koren, sRamec *novy){

    if(koren != NULL){
        novy->lptr = NULL; /*nastavi defaultne kazdemu novemu prvku ukazatele na NULL*/
        novy->rptr = NULL;
        sRamec *pom;/*vytvori si pomocnou promenou*/

        strInit(&(novy->nazev));
        strCopyString((&novy->nazev), (&koren->data.nazev));/*kopiruje informace z tabulky symbolu*/
        novy->typ = koren->data.typ;
        novy->hodnota.def = 0; /*nastavi definovanost prvku na 0 (tzn. neobsahuje hodnotu)*/
        novy->hodnota.porarg = koren->poradi_argumentu;

        if(koren->lptr != NULL){ /*kdyz ma ukazatel na levy podstrom, tak:*/
            if((pom = (sRamec*) malloc(sizeof(sRamec)))==NULL) error(NULL,OTHER_RUNN_ERR,NULL); /*malokuje misto pro novy prvek ramce*/
            novy->lptr = pom; /*a aktualnimu prvku nastavi ukazatel na novy levy podstrom*/
            VytvorRamec(koren->lptr, novy->lptr);  /*a dale rekurzivne vola funkci VytvorRamec*/
        } else novy->lptr = NULL; /*kdyz nema levy podstrom, pta se na pravy podstrom u ktereho postupuje obdobne jako u leveho*/
        if(koren->rptr != NULL){
            if((pom = (sRamec*) malloc(sizeof(sRamec)))==NULL) error(NULL,OTHER_RUNN_ERR,NULL);
            novy->rptr = pom;
            VytvorRamec(koren->rptr, novy->rptr);
        } else  novy->rptr = NULL;
    } /*v pripade, ze nema ani jeden podstrom, tak se funkce ukonci a vraci se do rekurzivni funkce, v ktere byla predtim volana*/
}

void VytvorRamecGlob(sGlobTableItem *koren, sRamec *novy){

    if(koren != NULL){/*postup je zde obdobny, jako u funkce VytvorRamec pro lokalni tabulky symbolu, ktera se nachazi nad touto funkci*/
        novy->lptr = NULL;
        novy->rptr = NULL;
        sRamec *pom;
        strInit(&(novy->nazev));
        strCopyString((&novy->nazev), (&koren->data.nazev));
        novy->typ = koren->data.typ;
        novy->hodnota.def = 0;
        novy->hodnota.porarg = 0;
        if(koren->lptr != NULL){
            if((pom = (sRamec*) malloc(sizeof(sRamec)))==NULL) error(NULL,OTHER_RUNN_ERR,NULL);
            novy->lptr = pom;
            VytvorRamecGlob(koren->lptr, novy->lptr);
        } else novy->lptr = NULL;
        if(koren->rptr != NULL){
            if((pom = (sRamec*) malloc(sizeof(sRamec)))==NULL) error(NULL,OTHER_RUNN_ERR,NULL);
            novy->rptr = pom;
            VytvorRamecGlob(koren->rptr, novy->rptr);
        } else  novy->rptr = NULL;
    }
}

void SearchRamecPoradi(sRamec *ramec, sRamec **hledanyramec, double poradi){ /*slouzi pro hledani prvku ramce se stejnou hodnotou parametru porarg s argumentem poradi*/
    if(ramec != NULL){  /*zkontroluje, zda mame spravny ukazatel na ramec*/
        if(poradi != ramec->hodnota.porarg){ /*pokud prvek nema stejne poradi argumentu jako je hledane poradi, tak:*/
            if(ramec->lptr != NULL) SearchRamecPoradi(ramec->lptr, hledanyramec, poradi);/*kdyz obsahuje levy podstrom, tak volame rekurzivne funkci s ukazatelem na levy podstrom*/
            if(ramec->rptr != NULL) SearchRamecPoradi(ramec->rptr, hledanyramec, poradi);/*kdyz obsahuje pravy podstrom, tak volame rekurzivne funkci s ukazatelem na levy podstrom*/
        }else{
            *(hledanyramec) = ramec;
        }
    }
}

int SearchRamec(sRamec **ramec, string *nazev){ /*funkce, ktera zjistuje, zda se hledany prvek nachazi v ramcich*/
     if(SearchRamecPom(ramec, nazev) == 0) {/*pomoci funkce SearchRamecPom prohleda aktualni lokalni ramec*/
        (*ramec) = GlobRamec;
        if(SearchRamecPom(ramec, nazev) == 0) {/*kdyz neobjevi nic v lokalnim ramci, tak prohleda globalni ramec*/
            return 0;
        }
        else {
           return 1;
        }
    } else {
        return 1;}
}

int SearchRamecPom(sRamec **ramec, string *nazev){ /*funkce, ktera je volana z funkce SearchRamec a slouzi k prohledani jednoho ramce podle nazvu (klice)*/
    int koren=0;

    while(!koren){/*dokud nezjistime, jestli jsme nasli a nebo konecny podstrom u nikam neukazuje, tak cyklime*/
        if (key(nazev,&((*ramec)->nazev))==2){ /*rozhodne, zda mame jit do praveho podstromu*/
            if ((*ramec)->rptr!=NULL){ /*kdyz ma pravy podstrom, tak se do nej presune, jinak ukonci cyklus*/
                (*ramec)=(*ramec)->rptr;
            }else{
                return 0;
            }
        }else   if  (key(nazev,&((*ramec)->nazev))==1){/*rozhodne, zda mame jit do leveho podstromu*/
            if ((*ramec)->lptr!=NULL){ /*kdyz ma levy podstrom, tak se do nej presune, jinak ukonci cyklus*/
                (*ramec)=(*ramec)->lptr;
            }else{
                return 0;
            }
        }else if (key((nazev),&((*ramec)->nazev))==0){/*kdyz jsme prvek nalezli, ukonci cyklus s 1*/
           if(((*ramec)->typ == TP_INT)||((*ramec)->typ == TP_REAL)||((*ramec)->typ == BOOLEAN))
                    (*ramec)->typ=TP_DOUBLE;
            return 1;
        }
    }
    return 0;
}

void VypisRamce(sRamec *ramec){
    if(ramec != NULL){
        printf("Vypis ramce********************************\n");
        printf("RAMEC  -jeho nazev je: %s\n",strGetStr(&(ramec->nazev)));
        if(ramec->lptr != NULL) VypisRamce(ramec->lptr);
        if(ramec->rptr != NULL) VypisRamce(ramec->rptr);
    }
}

void PridatHodnotu(sRamec *ramec, int typ, double cisloh, string *stringh){
    ramec->typ = typ;       /*priradi prvku v ramci typ*/
    if(typ == TP_STRING) {  /*kdyz je typ string, tak preda retezec*/
        strInit(&ramec->hodnota.stringh);/*kdyz je bool, int, nebo real, tak pouze priradi double*/
        strCopyString(&(ramec->hodnota.stringh),stringh);/*nastavi definovanost prvku na 1*/
    }
    else {
        ramec->hodnota.cisloh = cisloh;
    }
    ramec->hodnota.def = 1;
    return;
}

void PridatPom(sRamec *ramec, string *nazev, int typ, double cisloh, string *stringh){
    int koren=0;
    sRamec *novy;
    while (!koren){/*dokud nezjistime kam podle nazvu novou pomocnou zaradit, tak cyklime*/
        if( key(nazev, &ramec->nazev) == 2) {/*rozhodne, zda mame jit do praveho podstromu*/
            if(ramec->rptr != NULL) ramec = ramec->rptr;/*kdyz neni pravy podstrom prazdny, tak opakujeme dalsi cyklus pro novy ramec*/
            else {
                if((novy = (sRamec*) malloc(sizeof(sRamec)))==NULL) error(NULL,OTHER_RUNN_ERR,NULL);/*kdyz je pravy podstrom prazdny, tak malokujeme novy prvek a nastavime pravy ukazatel aktualniho prvku na novy*/
                strInit(&novy->nazev);
                strCopyString(&(novy->nazev),nazev);
                ramec->rptr = novy;

                PridatHodnotu(novy, typ, cisloh, stringh); /*pomoci funkce PridatHodnotu vyplnime hodnotu prvku*/
                return;                                     /*ukoncime funkci*/
            }
        }
        if( key(nazev, &ramec->nazev) == 1){/*rozhodne, zda mame jit do leveho podstromu*/
            if(ramec->lptr != NULL) ramec = ramec->lptr;  /*kdyz neni levy podstrom prazdny, tak opakujeme dalsi cyklus pro novy ramec*/
            else {
                if((novy = (sRamec*) malloc(sizeof(sRamec)))==NULL) error(NULL,OTHER_RUNN_ERR,NULL);/*kdyz je levy podstrom prazdny, tak malokujeme novy prvek a nastavime levy ukazatel aktualniho prvku na novy*/
                strInit(&novy->nazev);
                strCopyString(&(novy->nazev),nazev);
                ramec->lptr = novy;
                PridatHodnotu(novy, typ, cisloh, stringh); /*pomoci funkce PridatHodnotu vyplnime hodnotu prvku*/
                return;                                       /*ukoncime funkci*/
            }
        }
        if( key(nazev, &ramec->nazev) == 0){ /*v pripade, ze se prvek shoduje, tak pouze nahradime jeho hodnotu volanim funkce PridatHodnotu*/
            PridatHodnotu(ramec, typ, cisloh, stringh);
            return;                          /*ukoncime funkci*/
        }
    }
}



void FreeRamec(sRamec *ramec){
    if(ramec != NULL){
		FreeRamec(ramec->lptr);
		FreeRamec(ramec->rptr);
        strFree(&(ramec->nazev));
		free(ramec);
        ramec = NULL;
    }
}



void PushR(sRamec *Ritem){/*vlozeni ramce do zasobniku*/
    tRamec *pom;
    if((pom=(tRamec*) malloc(sizeof(tRamec ) ))==NULL) error(NULL,OTHER_RUNN_ERR,NULL);/*alukuji prostor*/
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
        FreeRamec(pom->Ritem);
    }

}

