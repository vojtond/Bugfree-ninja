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
    Rfirst=NULL;/* zasobn�k r�mc� je pr�zdn�*/

    T->first = NULL;/*glob�ln� tabulka je pr�zdn�*/
    ridic->aktiv= NULL;/*ukazatel na aktivn� uzel glob�ln� tabulky*/
    ridic->pomlog = 0;/*pomocn� prom�nn�*/
    ridic->pocet_argumentu=0;/*pocet argument� fce je nula*/
    ridic->deklaration=0;/*pomocn� prom�nn� pro definici funkc�*/

}

int GlobTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic){
    if (typ==FUNCTION_END){/*pokud je konec t�la funkce*/
        ridic->aktivG->data.def=1;/*definuj danou funkci*/
        ridic->aktiv=NULL;/*uzel ztr�c� aktivitu*/
        ridic->pomlog = 0;/*vynulov�n� ��d�c�ch prom�nn�ch*/
        ridic->pocet_argumentu=0;
        ridic->deklaration=0;
        return 1;
    }
    if (typ==FUNCTION_FORWARD){/*pokud se jedn� o dop�ednou deklaraci funkce*/
            sGlobTableItem *pomg;
            pomg=ridic->aktivG;
            ridic->pomlog = 0;/*vynulov�n� ��d�c�ch prom�nn�ch*/
            ridic->pocet_argumentu=0;
            ridic->deklaration=0;
            if (pomg->data.def==1){/*pokud ji� byla funkce definov�na, plat� i pro dvakr�t deklarovanou funkci*/
                error(T,TAB_ERR,ridic);/*chyba v r�mci tabulky*/
            }

        return 1;
    }
    int koren=0;
    struct GlobTabItem *novy;
    sGlobTableItem *pomglob;
    novy = (sGlobTableItem*) malloc(sizeof(sGlobTableItem));/*alokov�n� m�sta pro nov� glob�ln� uzel*/
    strInit(&(novy->data.nazev));/*pln�n� uzlu*/
    strCopyString(&(novy->data.nazev), nazev);
    novy->data.typ = typ;
    pomglob=NULL;
    novy->lptr=NULL;
    novy->rptr=NULL;
    strInit(&(novy->arg));
    if (T->first==NULL){/*pokud je strom pr�zdn�*/
        T->first=novy;/*p�id�me nov� uzel na vrchol stromu*/
    }else{
        pomglob=T->first;/*nastav�me pomocn� ukazatel na vrchol stromu*/
        koren=tableSearchGlob(ridic,&pomglob,&(novy->data.nazev));/*projdeme strom*/
        if (koren==0){/*uzel se stejn�m kl��em ji� byl nalezen*/
            if (typ==FUNCTION_HEADER){/*p�id�van� prvek je funkce*/
                if (pomglob->data.typ==FUNCTION_HEADER){/*nalezen� prvek je funkce*/
                    if (pomglob->data.def==0){/*funkce je�t� nebyla definov�na*/
                        pomglob->data.def=1;/*nadefinujeme funkci*/
                        ridic->pomlog = 1;/*nastav�me, �e se nachaz�me v hlavi�ce funkce*/
                        ridic->aktivG=pomglob;/*nastav�me aktivitu na n� prvek*/
                        ridic->aktiv=ridic->aktivG->link;/*jako aktivn� lok�ln� tabulku nastav�me  ukazatel na lok tabulku  aktivn� glob�ln� tabullky*/
                        ridic->deklaration=1;/*nastav�me, �e budeme ��st prvn� argument fce*/
                        ItemFreeAktu(novy,NULL);/*uvoln�me p�ipravovan� uzel glob. tabulky*/
                        return 1;
                    }else {ItemFreeAktu(novy,NULL);error(T,TAB_ERR,ridic);}/*chyba v r�mci tabulky*/
                }else {ItemFreeAktu(novy,NULL);error(T,TAB_ERR,ridic);}/*chyba v r�mci tabulky*/
            }else {ItemFreeAktu(novy,NULL);error(T,TAB_ERR,ridic);}/*chyba v r�mci tabulky*/
        }else
        if (koren==1){
            pomglob->lptr=novy;/*uzel vlo��me nalevo*/
        }else if (koren==2) {
            pomglob->rptr=novy;/*uzel vlo��me napravo*/
        }
    }
        novy->link=NULL;
        novy->data.def=0;/*nov� prvek nen� definovan�*/
        if(typ == FUNCTION_HEADER) {/*pokud se jedn� o funkci*/
            ridic->aktivG=novy;/*nastav�me jako aktivn�*/
            ridic->pomlog = 1;/*jsme v hlavi�ce fce*/
        } else {novy->link = NULL;}/*neobsahuje lok�ln� tabulku*/
        return 1;
}
int LokTableInsert(tGlobSymbolTable *T, string *nazev, int typ,Tridic *ridic){
    sLokTableItem *novy;
    sLokTableItem *pomloka;
    int koren=0;
    novy = (sLokTableItem*) malloc(sizeof(sLokTableItem));/*alokace m�sta na nov� lok�ln� prvek*/
    ridic->aktiv=novy;/*nastaven� aktivity na nov� prvek*/
    novy->data.def=1;/*pln�n� prvku*/
    strInit(&(novy->data.nazev));
    novy->data.typ=typ;
    novy->lptr=NULL;
    novy->rptr=NULL;

    if ( ridic->pomlog){/*pokud se jedn� o hlavi�ku fce*/
            ridic->pocet_argumentu++;
            novy->data.def=1;/*argument je inicialyzovan�*/
            novy->poradi_argumentu=ridic->pocet_argumentu;/*po�ad� argumentu*/
    }else {
        novy->data.def=0;/*lok�ln� prom�nn� nen� inicializovan�*/
        novy->poradi_argumentu=0;/*nejedn� se o argument funkce*/
    }
     if (nazev!=NULL){/*pokud se jedn� nejedn� o  n�vratov� typ*/
        strCopyString((&novy->data.nazev), nazev);/*napln�m n�zev*/
    }else {
        strCopyString((&novy->data.nazev), &(ridic->nazev_func));/*jinak z�sk�m n�zev z glob�n� tabulky z aktu�ln�ho prvku*/
         novy->data.def=3;
    }
       sGlobTableItem *pomgl;
         koren=0;
        pomgl = T->first;/*nastav�me ko�en stromu*/
        koren= tableSearchGlob(ridic,&pomgl,&(novy->data.nazev));/*prohled�me glob tabulku kv�li shodn�m n�zv�m fc�*/
         if (koren==0 && nazev!=NULL){/*pokud byl prvek nalezen a lok prom�nn� nen� n�vratov� typ*/
            if (pomgl->data.typ==FUNCTION_HEADER){/*pokud byla nalezena glob uzel kter� je funkce*/
                ItemFreeAktu(NULL, novy);/*uvolni p�id�van� prvek*/
                error(T,TAB_ERR,ridic);/*chyba v r�mci tabulky*/
            }
        }
		/* 																marek*/
    if (ridic->deklaration>0){/*pokud jsme v hlavi�ce funkce*/
        sLokTableItem *poml;
        sGlobTableItem *pomgl;
        pomgl = ridic->aktivG;/*jako pomocn� glob uzel nastav�me aktivn� glob uzel*/
        poml=pomgl->link;/*jako pomocnou lok. tabulku nastav�me odkaz z aktivn�ho glob  uzlu*/
        koren=0;
        koren=tableSearchLok(ridic,&poml,&(novy->data.nazev));
        if (!koren){

            ItemFreeAktu(NULL, novy);/*uvoln�me p�id�van� prvek*/
            error(T,TAB_ERR,ridic);/*chyba v r�mci tabulky*/
        }
        ridic->deklaration++;/*kontrola po�tu argument�*/
        if (ridic->deklaration==strGetLength(&(pomgl->arg))+1) {ridic->deklaration=0;}/*po�et prvk� deklrovan� a definovan� funkce je jin�*/
        if (poml->data.typ==typ){/*pokud sed� typ argumentu deklarovan� a definovan� funkce*/
            if (poml->poradi_argumentu==novy->poradi_argumentu){/*pokud je na stejn�m m�st�*/
                if (nazev!=NULL){/*pokud se nejedn� o n�vratov� parametr*/
                    if ((strCmpString(&(poml->data.nazev), nazev)==0)) {/*pokud sed� n�zev*/
                        ItemFreeAktu(NULL, novy);/*uvoln�me vkl�dan� argument*/
                        return 1;/*agrumnet je toto�n�*/
                    }else {

                        ItemFreeAktu(NULL, novy);/*uvoln�me vkl�dan� argument*/
                        error(T,TAB_ERR,ridic);/*error v r�mci tabulky*/
                    }
                }else{/*pokud se jedn� o n�vratov� parametr*/
                    if (ridic->deklaration==strGetLength(&(ridic->aktivG->arg))) {/*pokud nen� stejn� po�et argument�*/

                        ItemFreeAktu(NULL, novy);/*uvoln�me vkl�dan� argument*/
                        error(T,TAB_ERR,ridic);/*error v r�mci tabulky*/
                    }
                    ridic->aktivG=pomgl;/*uvoln�me vkl�dan� argument*/
                    ItemFreeAktu(NULL,novy);/*error v r�mci tabulky*/

                    return 1;/*agrumnet je toto�n�*/
                }
            }else {/*nejedn� se o stejn� typ*/
                ItemFreeAktu(NULL, novy);/*uvoln�me vkl�dan� argument*/
                error(T,TAB_ERR,ridic);/*error v r�mci tabulky*/

            }
        }
    }
    else{/*pokud p�id�v�me lok�ln� prom�nnou*/

     if (ridic->aktivG->link==NULL){/*pokud je strom pr�zdn�*/
            ridic->aktivG->link=novy;/*p�id�me jako ko�en*/
    }else{
        pomloka=ridic->aktivG->link;
        koren=0;
        koren=tableSearchLok(ridic,&pomloka,&(novy->data.nazev));
        if (koren==0){/*pokud ji� tprvek se stejn�m kl��em  existuje*/
                ItemFreeAktu(NULL, novy);/*uvoln�me vkl�dan� argument*/
                error(T,TAB_ERR,ridic);/*error v r�mci tabulky*/

        }
        if (koren==1){/*p�d�me do lev�ho podstromu*/
            pomloka->lptr=novy;
        }else if (koren==2) {pomloka->rptr=novy;}/*p�id�me do prav�ho podstromu*/
    }
    if ( ridic->pomlog){/*pokud jsme v hlavi�ce funkce*/
        switch(typ){/*p�id�me typ argumnet� do glob tabulky*/
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
    if (nazev==NULL)  {/*pokud u� by� p�ed�n i n�vratov� typ*/
            ridic->pocet_argumentu=0; /*n�sleduj� lok prom�nn�*/
            ridic->pomlog=0;/*nejsme ji� v hlavi�ce funkce*/
    };
    return 1;
    }
    return 0;
}

int tableSearch(tGlobSymbolTable *T, string *nazev, int def,Tridic *ridic){
    struct GlobTabItem *Gpom;
    sLokTableItem *poml;
     int nenasel = 1;
     if (ridic->aktivG->link!=NULL){/*pokud existuje aktivn� lok tabulka*/
        poml=ridic->aktivG->link;
        nenasel=tableSearchLok(ridic,&poml,nazev);/*hled�me v lok tabulce*/
        if (!nenasel) {/*pokud jsme na�li*/
            if (def==1)/*pokud je volan� jako inicializace*/
                poml->data.def=1;/*nastav�me, �e ji� byla inicializovan�*/
            else if (poml->data.def==0)/*pokud je neinicializovan�*/
                error(T,RUNN_NOIN_ERR,ridic);/*pokus o p��stup na neinicializovanou prom*/
        }

     }
     if (nenasel){/*pokud st�le nena�el*/
        Gpom = T->first;/*hled�me v glob tabulce*/
         nenasel=tableSearchGlob(ridic,&Gpom,nazev);
        if (!nenasel) {/*pokud jsme na�li*/
                if (def==1){/*pokud je volan� jako inicializace*/
                    Gpom->data.def=1;/*nastav�me, �e ji� byla inicializovan�*/
                }else if (Gpom->data.def==0)/*pokud je neinicializovan�*/
                    error(T,RUNN_NOIN_ERR,ridic);/*pokus o p��stup na neinicializovanou prom*/
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

int tableSearchLok(Tridic *ridic,sLokTableItem **poml,string *nazev){
    int koren=0;
    while(!koren){/*dokud nen� nalezeno m�sto nebo shoda*/
        if (key(nazev,&((*poml)->data.nazev))==2){/*pokud je vkl�dan� v�t�� ne� vlo�en�*/
            if ((*poml)->rptr!=NULL){/*pokud je vpravo je�t� uzel*/
                (*poml)=(*poml)->rptr;/*jdu vpravo*/
            }else{/*jinak vrac�m �e je vpravo m�sto*/
                return 2;
            }
        }else   if  (key(nazev,&((*poml)->data.nazev))==1){/*pokud je vkl�dan� men�� ne� vlo�en�*/
            if ((*poml)->lptr!=NULL){/*pokud je vlevo je�t� uzel*/
                (*poml)=(*poml)->lptr;/*jdu vlevo*/
            }else{/*jinak vrac�m �e je vlevo m�sto*/
                return 1;
            }
        }else if (key((nazev),&((*poml)->data.nazev))==0){/*shoda*/
            return 0;
        }
    }
    return 0;
}
int tableSearchGlob(Tridic *ridic,sGlobTableItem **pomgl,string *nazev){
    int koren=0;
    while (!koren){/*dokud nen� nalezeno m�sto nebo shoda*/
        if (key(nazev,&((*pomgl)->data.nazev))==2){/*pokud je vkl�dan� v�t�� ne� vlo�en�*/
            if ((*pomgl)->rptr!=NULL){/*pokud je vpravo je�t� uzel*/
                (*pomgl)=(*pomgl)->rptr;/*jdu vpravo*/
            }else {/*jinak vrac�m �e je vpravo m�sto*/
                return 2;
            }
        } else if  (key(nazev,&((*pomgl)->data.nazev))==1){/*pokud je vkl�dan� men�� ne� vlo�en�*/
            if ((*pomgl)->lptr!=NULL){/*pokud je vlevo je�t� uzel*/
                    (*pomgl)=(*pomgl)->lptr;/*jdu vlevo*/
            }else {/*jinak vrac�m �e je vlevo m�sto*/
                return 1;
            }
        }else if (key(nazev,&((*pomgl)->data.nazev))==0){/*shoda*/
            return 0;
        }
    }
    return 0;
}

void  TableFree(tGlobSymbolTable *T,Tridic *ridic,sGlobTableItem *koren,int *in){/*rekurzivn� maz�n� tabulek*/
     if((koren)!= NULL) {/*pokud nen� glob�ln� tabulka pr�zdn�*/
        if(koren->data.typ == FUNCTION_HEADER){/*pokud je glob. prvek funkce*/
            if(koren->data.def == 0 ) *in=0;/*pokud nen� definov�na*/
            TableFreeLok(T,ridic,(koren->link));/*zavol�m maz�n� lok�ln� tabulky*/
        }
		TableFree(T,ridic,(koren->lptr),in);/*posouv�m se vlevo*/
		TableFree(T,ridic,(koren->rptr),in);/*posouv�m se vpravo*/
        strFree(&(koren->data.nazev));/*ma�u*/
        strFree(&(koren->arg));
        free(koren);
        koren = NULL;
	}
return ;
}

void TableFreeLok(tGlobSymbolTable *T,Tridic *ridic,sLokTableItem *koren){
    if(koren != NULL){/*pokud nen� lok�ln� pr�zdn�*/
		TableFreeLok(T,ridic,(koren->lptr));/*posouv�m se vlevo*/
		TableFreeLok(T,ridic,(koren->rptr));/*posouv�m se vpravo*/
        strFree(&(koren->data.nazev));/*ma�u*/
		free(koren);
        koren = NULL;
    }

}
void ItemFreeAktu(sGlobTableItem *pomg,sLokTableItem *poml){/*maz�n� alokovan�ho prvku p�i chyb�*/
    if (pomg!=NULL){/*pokud ma�u glob�ln� prvek*/
        strFree(&(pomg->data.nazev));/*sma�*/
        strFree(&(pomg->arg));
        free(pomg);
    }else
    if (poml!=NULL){/*pokud ma�u lok�ln� prvek*/
      strFree(&(poml->data.nazev));/*sma�*/
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

