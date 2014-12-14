#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Interpret.h"

void PushRamec();
void PopTopRamec();
void MakeInstrucion(int Iinst, string Iop1, string Iop2, string Iresult, int *Ipoz,tGlobSymbolTable *ST);

sRamec *poma=NULL;
int vrch=0; /* Proměnná pro zjištění zda jsme na vrcholu zásobníku */
/* Proměnné pro vestavěné funkce */
int vestav=0;   /* Zda je zadána vestavěná fce */
int argum=0;    /* Pozice argumentu */
string vesstr;  /* Proměnná pro uložení řetězce */
string vesstr2; /* Proměnná pro uložení řetězce */
double vescis;  /* Proměnná pro uložení číselné hodnoty */
double vescis2; /* Proměnná pro uložení číselné hodnoty */

void Interpret(tGlobSymbolTable *ST)
{
tTroj *seznam;
seznam=Trfirst;

int Iinst;      /* Proměnná pro název instrukce */
string Iop1;    /* Proměnná pro první operand */
string Iop2;    /* Proměnná pro první operand */
string Iresult; /* Proměnná pro výsledek */
int Ipoz;       /* Proměnná pro pozici */

 while ( seznam!=NULL ){
        Iinst = seznam->data.inst;  /* Naplnění proměnných hodnotami */
        Iop1 = seznam->data.op1;
        Iop2 = seznam->data.op2;
        Iresult = seznam->data.result;
        Ipoz = 0;
        MakeInstrucion(Iinst, Iop1, Iop2, Iresult, &Ipoz,ST);   /* Volání funkce pro vykonání instrukce */
        if(Ipoz>0)
        {
            seznam=Trfirst;
            while (seznam!=NULL){   /* Procházení seznamu  dokud nedojdu na pozici */
                if (seznam->data.pozice == Ipoz){
                break;
                }
                seznam=seznam->next;    /* Skok na další pozici */
            }
        }
        seznam=seznam->next;     /* Skok na další pozici */
    }
}

void MakeInstrucion(int Iinst, string Iop1, string Iop2, string Iresult, int *Ipoz,tGlobSymbolTable *ST)
{
    /* Inicializace proměnných a jejich naplnění */
    sRamec *pomafce;
    sRamec *Aop1 = poma;
    sRamec *Aop2 = poma;
    sRamec *Aresult = poma;
    /* Proměnné pro uložení hodnoty, když je na vstupu číslo  */
    double PomIop1=0;
    double PomIop2=0;
    double PomResult=0;
    int pomchyba1=0;
    int pomchyba2=0;
    int pomchyba3=0;
    /* Proměnné pro ukládání do rámce */
    double PomDouble = 0;
    string PomString;
    strInit(&PomString);
    /* ************************************ */

    if (Iinst<I_JUMP_FCE){
    /* Převod řetězce na číslo */
        PomIop1 = atof(Iop1.str);
        if (!PomIop1){
        if (Iop1.str[0]== '0'){ /* Zjištění jestli je číslo 0 nebo je chybě zadané */
            PomIop1=0;
            pomchyba1=1;}
        }else pomchyba1=1;  /* Příznak že se podařilo převést číslo */

    PomIop2 = atof(Iop2.str);
        if (!PomIop2){
        if (Iop2.str[0]== '0'){ /* Zjištění jestli je číslo 0 nebo je chybě zadané */
            PomIop2=0;
            pomchyba2=1;}
        }else pomchyba2=1;  /* Příznak že se podařilo převést číslo */

    PomResult = atof(Iresult.str);
        if (!PomResult){
        if (Iresult.str[0]== '0'){  /* Zjištění jestli je číslo 0 nebo je chybě zadané */
            PomResult=0;
            pomchyba3=1;}
        }else pomchyba3=1;  /* Příznak že se podařilo převést číslo */
    }

    switch(Iinst)
    {
    /* Aritmetické operace */
    /* *********************** I_ADD *********************** */
    case TP_PLUS:

        if ((pomchyba1==1)&&(pomchyba2==0)){    /* Provede se když je první operand číslo a druhý proměnná */
            SearchRamec(&Aop2, &Iop2);  /* Hledání proměnné v rámci */
            if (Aop2->hodnota.def == 0) /* Ošetření jestli je proměnná definovaná */
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop2->typ == TP_DOUBLE) /* Ošetření jestli je proměnná číslo */
            {
                PomDouble = PomIop1 + Aop2->hodnota.cisloh;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
            }else{
                    error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){  /* Provede se když je první operand proměnná a druhý číslo */

            SearchRamec(&Aop1, &Iop1);  /* Hledání proměnné v rámci */
            if (Aop1->hodnota.def == 0) /* Ošetření jestli je proměnná definovaná */
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop1->typ == TP_DOUBLE) /* Ošetření jestli je proměnná číslo */
            {
            PomDouble = Aop1->hodnota.cisloh + PomIop2; /* Sečtení proměnných */
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);    /* Uložení do rámce */
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==1)&&(pomchyba2==1)){  /* Provede se když je první operand číslo a druhý číslo */
            PomDouble = PomIop1 + PomIop2;
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }else{  /* Provede se když je první operand proměnná a druhý proměnná */
            SearchRamec(&Aop1, &Iop1);  /* Hledání proměnné v rámci */
            SearchRamec(&Aop2, &Iop2);  /* Hledání proměnné v rámci */
            if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0)) /* Ošetření jestli je proměnná definovaná */
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE)) /* Ošetření jestli je proměnná číslo */
            {
                PomDouble = Aop1->hodnota.cisloh + Aop2->hodnota.cisloh;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
            }
            else if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING)){   /* Ošetření jestli je proměnná řetězec */
                if(strCntStr(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) == 0){ /* Ošetření zřetězení */
                    PomString = Aop1->hodnota.stringh;
                    PridatPom(poma, &Iresult, TP_STRING, PomDouble, &PomString);
                }else{
                    error(NULL,OTHER_ERR,NULL);
                }

            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }
        break;
    /* *********************** I_SUB *********************** */
    case TP_MINUS:

        if ((pomchyba1==1)&&(pomchyba2==0)){    /* Stejné jako operace TP_PLUS, s operací mínus '-' */
            SearchRamec(&Aop2, &Iop2);
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop2->typ == TP_DOUBLE)
            {
                PomDouble = PomIop1 - Aop2->hodnota.cisloh;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
            }else{
                    error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            SearchRamec(&Aop1, &Iop1);
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop1->typ == TP_DOUBLE)
            {
            PomDouble = Aop1->hodnota.cisloh - PomIop2;
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            PomDouble = PomIop1 - PomIop2;
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }else{
            SearchRamec(&Aop1, &Iop1);
            SearchRamec(&Aop2, &Iop2);
            if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE)){
                PomDouble = Aop1->hodnota.cisloh - Aop2->hodnota.cisloh;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }
        break;
    /* *********************** I_MUL *********************** */
    case TP_MUL:
        if ((pomchyba1==1)&&(pomchyba2==0)){        /* Stejné jako operace TP_PLUS, s operací krát '*' */
            SearchRamec(&Aop2, &Iop2);
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop2->typ == TP_DOUBLE)
            {
                PomDouble = PomIop1 * Aop2->hodnota.cisloh;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
            }else{
                    error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            SearchRamec(&Aop1, &Iop1);
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop1->typ == TP_DOUBLE)
            {
            PomDouble = Aop1->hodnota.cisloh * PomIop2;
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            PomDouble = PomIop1 * PomIop2;
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }else{
            SearchRamec(&Aop1, &Iop1);
            SearchRamec(&Aop2, &Iop2);
            if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE)){
                PomDouble = Aop1->hodnota.cisloh * Aop2->hodnota.cisloh;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }
        break;
    /* *********************** I_DIV *********************** */
    case TP_MOD:

        if ((pomchyba1==1)&&(pomchyba2==0)){    /* Stejné jako operace TP_PLUS, s operací děleno '/' */
            SearchRamec(&Aop2, &Iop2);
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop2->hodnota.cisloh == 0)  /* Ošetření dělení nulou */
            {
                error(NULL,RUNN_ZERODI_ERR,NULL);
            }
            if (Aop2->typ == TP_DOUBLE)
            {
                PomDouble = PomIop1 / Aop2->hodnota.cisloh;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
            }else{
                    error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            SearchRamec(&Aop1, &Iop1);
            if (Aop1->hodnota.def == 0) /* Ošetření dělení nulou */
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (PomIop2 == 0)
            {
                error(NULL,RUNN_ZERODI_ERR,NULL);
            }
            if (Aop1->typ == TP_DOUBLE)
            {
            PomDouble = Aop1->hodnota.cisloh / PomIop2;
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            if (PomIop2 == 0)   /* Ošetření dělení nulou */
            {
                error(NULL,RUNN_ZERODI_ERR,NULL);
            }
            PomDouble = PomIop1 / PomIop2;
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }else{
            SearchRamec(&Aop1, &Iop1);
            SearchRamec(&Aop2, &Iop2);
            if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
            {
                if (Aop2->hodnota.cisloh == 0)  /* Ošetření dělení nulou */
                {
                        error(NULL,RUNN_ZERODI_ERR,NULL);
                }
                PomDouble = Aop1->hodnota.cisloh / Aop2->hodnota.cisloh;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
            }
            else
            {
                error(NULL,OTHER_ERR,NULL);
            }
        }
        break;
    /* *********************** I_ASSIGN *********************** */
    case ASSIGN:

       if (vestav == 0){    /* Ošetření zda se nevolá vestavěná funkce */
            switch(Iop2.str[0]){    /* Zjištění jaká je hodnota přiřazení */

            case 's':       /* Řetězec */
                PomString=Iop1;
                PridatPom(poma, &Iresult, TP_STRING,PomDouble, &PomString);
                break;
            case 'p':   /* Proměnná */
                SearchRamec(&Aop1, &Iop1);
                if (Aop1->hodnota.def == 0) /* Ošetření zda je inicializovaná */
                {
                    error(NULL,RUNN_NOIN_ERR,NULL);
                }
                if (Aop1->typ == TP_DOUBLE){    /* Ošetření zda je číslo */
                    PomDouble=Aop1->hodnota.cisloh;
                    PridatPom(poma, &Iresult, TP_DOUBLE,PomDouble, &PomString);
                }
                else if (Aop1->typ == TP_STRING){   /* Ošetření zda je řetězec */
                PomString=Aop1->hodnota.stringh;
                PridatPom(poma, &Iresult, TP_DOUBLE,PomDouble, &PomString);
                }else
                {
                    error(NULL,OTHER_ERR,NULL);
                }
                break;
            default:
                if (pomchyba1==1){  /* Číslo */
                    PridatPom(poma, &Iresult, TP_DOUBLE, PomIop1, &PomString);
                }else{
                    SearchRamec(&Aop1, &Iop1);
                    if (Aop1->hodnota.def == 0) /* Ošetření zda je inicializovaná */
                    {
                        error(NULL,RUNN_NOIN_ERR,NULL);
                    }
                    PridatPom(poma, &Iresult, TP_DOUBLE, Aop1->hodnota.cisloh, &PomString);

                }
                break;
            }

        }else if ((vestav>0)&&(vestav<5)){  /* Pokud je volána vestavěná funkce */
            switch(vestav){
            case 1: /* Find */
                PomDouble = find(&vesstr, &vesstr2);
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                break;
            case 2: /* Sort */
                PomString = sort(&vesstr);
                PridatPom(poma, &Iresult, TP_STRING, PomDouble, &PomString);
                break;
            case 3: /* Length */
                PomDouble = lenght(&vesstr);
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                break;
            case 4: /* Copy */
                PomString = copy(&vesstr, vescis, vescis2);
                PridatPom(poma, &Iresult, TP_STRING, PomDouble, &PomString);
                break;
            }
            vestav=0;
            argum=0;
        }else {error(NULL,OTHER_ERR,NULL);}

    break;
    /* Logické operace */
    /* *********************** I_MORE *********************** */
    case TP_MORE:

        if ((pomchyba1==1)&&(pomchyba2==0)){   /* Provede se když je první operand číslo a druhý proměnná */
            SearchRamec(&Aop2, &Iop2);
            if (Aop2->hodnota.def == 0) /* Ošetření jestli je proměnná definovaná */
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop2->typ == TP_DOUBLE) /* Ošetření jestli je proměnná číslo */
            {
                if(PomIop1 > Aop2->hodnota.cisloh){ /* Porovnání */
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){  /* Provede se když je první operand proměnní a druhý číslo */
            SearchRamec(&Aop1, &Iop1);
            if (Aop1->hodnota.def == 0) /* Ošetření jestli je proměnná definovaná */
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop1->typ == TP_DOUBLE) /* Ošetření jestli je proměnná číslo */
            {
                if(Aop1->hodnota.cisloh > PomIop2){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==1)&&(pomchyba2==1)){  /* Provede se když je první operand číslo a druhý číslo */
            if(PomIop1 > PomIop2){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else{      /* Provede se když je první operand proměnná a druhý proměnná */
            pomchyba1=SearchRamec(&Aop1, &Iop1);
            pomchyba2=SearchRamec(&Aop2, &Iop2);

            if((pomchyba1==1)&&(pomchyba2==0)){ /* Ošetření jestli je proměnná definovaná */
                if (Aop1->hodnota.def == 0)
                {
                    error(NULL,RUNN_NOIN_ERR,NULL);
                }
                if (Aop1->typ == TP_STRING)     /* Ošetření jestli je proměnná řetězec */
                {
                    if(strCmpString(&Aop1->hodnota.stringh, &Iop2) > 0){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
            }
            else if((pomchyba1==0)&&(pomchyba2==1)){    /* Ošetření jestli je proměnná definovaná */
                if (Aop2->hodnota.def == 0)
                {
                    error(NULL,RUNN_NOIN_ERR,NULL);
                }
                if (Aop2->typ == TP_STRING)
                {
                    if(strCmpString(&Iop1, &Aop2->hodnota.stringh) > 0){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
            }
            else if((pomchyba1==1)&&(pomchyba2==1)){
                if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
                {
                    error(NULL,RUNN_NOIN_ERR,NULL);
                }
                if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING)) /* Ošetření jestli je proměnná řetězec */
                {
                    if(strCmpString(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) > 0){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
                else if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))    /* Ošetření jestli je proměnná číslo */
                {
                    if(Aop1->hodnota.cisloh == Aop2->hodnota.cisloh){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }
        PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        break;
    /* *********************** I_LESS *********************** */
    case TP_LESS:

        if ((pomchyba1==1)&&(pomchyba2==0)){    /* Stejné jako TP_MORE akorát s operátorem menší < */
            SearchRamec(&Aop2, &Iop2);
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop2->typ == TP_DOUBLE)
            {
                if(PomIop1 < Aop2->hodnota.cisloh){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            SearchRamec(&Aop1, &Iop1);
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop1->typ == TP_DOUBLE)
            {
                if(Aop1->hodnota.cisloh < PomIop2){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            if(PomIop1 < PomIop2){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else{
            pomchyba1=SearchRamec(&Aop1, &Iop1);
            pomchyba2=SearchRamec(&Aop2, &Iop2);

            if((pomchyba1==1)&&(pomchyba2==0)){
                if (Aop1->hodnota.def == 0)
                {
                    error(NULL,RUNN_NOIN_ERR,NULL);
                }
                if (Aop1->typ == TP_STRING)
                {
                    if(strCmpString(&Aop1->hodnota.stringh, &Iop2) < 0){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
            }
            else if((pomchyba1==0)&&(pomchyba2==1)){
                if (Aop2->hodnota.def == 0)
                {
                    error(NULL,RUNN_NOIN_ERR,NULL);
                }
                if (Aop2->typ == TP_STRING)
                {
                    if(strCmpString(&Iop1, &Aop2->hodnota.stringh) < 0){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
            }
            else if((pomchyba1==1)&&(pomchyba2==1)){
                if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
                {
                    error(NULL,RUNN_NOIN_ERR,NULL);
                }
                if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
                {
                    if(strCmpString(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) < 0){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
                else if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
                {
                    if(Aop1->hodnota.cisloh < Aop2->hodnota.cisloh){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }
        PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        break;
    /* *********************** I_MORE_EQUAL *********************** */
    case TP_MOREQ:

        if ((pomchyba1==1)&&(pomchyba2==0)){    /* Stejné jako TP_MORE akorát s operátorem větí rovno >= */
            SearchRamec(&Aop2, &Iop2);
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop2->typ == TP_DOUBLE)
            {
                if(PomIop1 >= Aop2->hodnota.cisloh){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            SearchRamec(&Aop1, &Iop1);
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop1->typ == TP_DOUBLE)
            {
                if(Aop1->hodnota.cisloh >= PomIop2){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            if(PomIop1 >= PomIop2){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else{
            pomchyba1=SearchRamec(&Aop1, &Iop1);
            pomchyba2=SearchRamec(&Aop2, &Iop2);

            if((pomchyba1==1)&&(pomchyba2>=0)){
                if (Aop1->hodnota.def == 0)
                {
                    error(NULL,RUNN_NOIN_ERR,NULL);
                }
                if (Aop1->typ == TP_STRING)
                {
                    if(strCmpString(&Aop1->hodnota.stringh, &Iop2) >= 0){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
            }
            else if((pomchyba1==0)&&(pomchyba2==1)){
                if (Aop2->hodnota.def == 0)
                {
                    error(NULL,RUNN_NOIN_ERR,NULL);
                }
                if (Aop2->typ == TP_STRING)
                {
                    if(strCmpString(&Iop1, &Aop2->hodnota.stringh) >= 0){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
            }
            else if((pomchyba1==1)&&(pomchyba2==1)){
                if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
                {
                    error(NULL,RUNN_NOIN_ERR,NULL);
                }
                if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
                {
                    if(strCmpString(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) >= 0){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
                else if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
                {
                    if(Aop1->hodnota.cisloh >= Aop2->hodnota.cisloh){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }
        PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        break;
    /* *********************** I_LESS_EQUAL *********************** */
    case TP_LESSQ:

        if ((pomchyba1==1)&&(pomchyba2==0)){    /* Stejné jako TP_MORE akorát s operátorem menší rovno <= */
            SearchRamec(&Aop2, &Iop2);
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop2->typ == TP_DOUBLE)
            {
                if(PomIop1 <= Aop2->hodnota.cisloh){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            SearchRamec(&Aop1, &Iop1);
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop1->typ == TP_DOUBLE)
            {
                if(Aop1->hodnota.cisloh <= PomIop2){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            if(PomIop1 <= PomIop2){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else{
            pomchyba1=SearchRamec(&Aop1, &Iop1);
            pomchyba2=SearchRamec(&Aop2, &Iop2);

            if((pomchyba1==1)&&(pomchyba2==0)){
                if (Aop1->hodnota.def == 0)
                {
                    error(NULL,RUNN_NOIN_ERR,NULL);
                }
                if (Aop1->typ == TP_STRING)
                {
                    if(strCmpString(&Aop1->hodnota.stringh, &Iop2) <= 0){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
            }
            else if((pomchyba1==0)&&(pomchyba2==1)){
                if (Aop2->hodnota.def == 0)
                {
                    error(NULL,RUNN_NOIN_ERR,NULL);
                }
                if (Aop2->typ == TP_STRING)
                {
                    if(strCmpString(&Iop1, &Aop2->hodnota.stringh) <= 0){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
            }
            else if((pomchyba1==1)&&(pomchyba2==1)){
                if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
                {
                    error(NULL,RUNN_NOIN_ERR,NULL);
                }
                if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
                {
                    if(strCmpString(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) <= 0){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
                else if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
                {
                    if(Aop1->hodnota.cisloh <= Aop2->hodnota.cisloh){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }
        PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        break;
    /* *********************** I_EQUAL *********************** */
    case TP_EQU:

        if ((pomchyba1==1)&&(pomchyba2==0)){    /* Stejné jako TP_MORE akorát s operátorem rovná se == */
            SearchRamec(&Aop2, &Iop2);
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop2->typ == TP_DOUBLE)
            {
                if(PomIop1 == Aop2->hodnota.cisloh){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            SearchRamec(&Aop1, &Iop1);
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop1->typ == TP_DOUBLE)
            {
                if(Aop1->hodnota.cisloh == PomIop2){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            if(PomIop1 == PomIop2){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else{
            pomchyba1=SearchRamec(&Aop1, &Iop1);
            pomchyba2=SearchRamec(&Aop2, &Iop2);

            if((pomchyba1==1)&&(pomchyba2==0)){
                if (Aop1->hodnota.def == 0)
                {
                    error(NULL,RUNN_NOIN_ERR,NULL);
                }
                if (Aop1->typ == TP_STRING)
                {
                    if(strCmpString(&Aop1->hodnota.stringh, &Iop2) == 0){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
            }
            else if((pomchyba1==0)&&(pomchyba2==1)){
                if (Aop2->hodnota.def == 0)
                {
                    error(NULL,RUNN_NOIN_ERR,NULL);
                }
                if (Aop2->typ == TP_STRING)
                {
                    if(strCmpString(&Iop1, &Aop2->hodnota.stringh) == 0){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
            }
            else if((pomchyba1==1)&&(pomchyba2==1)){
                if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
                {
                    error(NULL,RUNN_NOIN_ERR,NULL);
                }
                if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
                {
                    if(strCmpString(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) == 0){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
                else if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
                {
                    if(Aop1->hodnota.cisloh == Aop2->hodnota.cisloh){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }
        PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        break;
    /* *********************** I_NOT_EQUAL *********************** */
    case TP_NEQU:

        if ((pomchyba1==1)&&(pomchyba2==0)){    /* Stejné jako TP_MORE akorát s operátorem nerovná se != */
            SearchRamec(&Aop2, &Iop2);
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop2->typ == TP_DOUBLE)
            {
                if(PomIop1 != Aop2->hodnota.cisloh){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            SearchRamec(&Aop1, &Iop1);
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop1->typ == TP_DOUBLE)
            {
                if(Aop1->hodnota.cisloh != PomIop2){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            if(PomIop1 != PomIop2){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else{
            pomchyba1=SearchRamec(&Aop1, &Iop1);
            pomchyba2=SearchRamec(&Aop2, &Iop2);

            if((pomchyba1==1)&&(pomchyba2==0)){
                if (Aop1->hodnota.def == 0)
                {
                    error(NULL,RUNN_NOIN_ERR,NULL);
                }
                if (Aop1->typ == TP_STRING)
                {
                    if(strCmpString(&Aop1->hodnota.stringh, &Iop2) != 0){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
            }
            else if((pomchyba1==0)&&(pomchyba2==1)){
                if (Aop2->hodnota.def == 0)
                {
                    error(NULL,RUNN_NOIN_ERR,NULL);
                }
                if (Aop2->typ == TP_STRING)
                {
                    if(strCmpString(&Iop1, &Aop2->hodnota.stringh) != 0){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
            }
            else if((pomchyba1==1)&&(pomchyba2==1)){
                if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
                {
                    error(NULL,RUNN_NOIN_ERR,NULL);
                }
                if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
                {
                    if(strCmpString(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) != 0){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
                else if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
                {
                    if(Aop1->hodnota.cisloh != Aop2->hodnota.cisloh){
                        PomDouble = 1;
                    }else{
                        PomDouble = 0;
                    }
                }
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }
        PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        break;
    /* *********************** I_WRITE *********************** */
    case I_WRITE:

        switch (Iop2.str[0])    /* Zjištění jakého typu je proměnná */
        {
        case 'p':   /* Proměnná */
            SearchRamec(&Aop1, &Iop1);
            if (Aop1->hodnota.def == 0) /* Ošetření zda je definovaná */
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop1->typ == TP_STRING){    /* Ošetření zda je řetězec */
                printf("%s",strGetStr(&Aop1->hodnota.stringh));
            }
            else if (Aop1->typ == TP_DOUBLE){   /* Ošetření zda je číslo */
                printf("%g",Aop1->hodnota.cisloh);
            }else
            {
                error(NULL,OTHER_ERR,NULL);
            }
            break;
        default:  /* Ostatní */
            printf("%s",strGetStr(&Iop1));
            break;
        }
        break;
    /* *********************** I_READ *********************** */
    case I_READ:

        SearchRamec(&Aresult, &Iresult);
        if (Aresult->typ == TP_STRING)  /* Ošetření zda je řětězec */
        {
            char c;
                while ((c = getchar()))
                {
                    if ((c != 10)&&(c != 13)){  /* Načítání řetězce dokud není konec */
                        strAddChar(&PomString,c);
                    }else{
                        PridatPom(poma, &Iresult, TP_STRING, PomDouble, &PomString);
                        break;
                    }
                }
        }
        else if (Aresult->typ == TP_DOUBLE) /* Ošetření zda je číslo */
        {
            if (scanf("%lf",&PomDouble) == 1)   /* Načtení čísla ze vstupu */
            {
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
            }else
            {
            error(NULL,RUNN_IN_ERR,NULL);
            }
        }else{
            error(NULL,OTHER_ERR,NULL);
        }
        break;

    /* Skoky */
    /* *********************** I_LABEL *********************** */
    case I_LABEL:
        break;
    /* *********************** I_FJUMP *********************** */
    case I_FJUMP:

        SearchRamec(&Aop2, &Iop2);
        if (Aop2->hodnota.def == 0) /* Ošetření zda je definovaná */
        {
            error(NULL,RUNN_NOIN_ERR,NULL);
        }
        if(Aop2->typ == TP_DOUBLE){     /* Ošetření zda je číslo */
            if(Aop2->hodnota.cisloh == 0){
                *Ipoz = trojfindlab(Iop1);  /* Hledání pozice kam skočit */
            }
        }else{
            error(NULL,OTHER_ERR,NULL);
        }
        break;
    /* *********************** I_JUMP *********************** */
    case I_JUMP:
        *Ipoz = trojfindlab(Iop1);  /* Hledání pozice kam skočit */
        break;
    /* *********************** I_JUMP_FCE *********************** */
     case I_JUMP_FCE:

        if(vestav==0){
            if (poma!=NULL){    /* Pokud je voláná hlavní fce */
                poma=Rfirst->Ritem;
                PushRamec();
                vrch=1;
            }
        *Ipoz = (trojfindfce(Iop2)-1);  /* Hledání pozice kam skočit */
        }
        break;
    /* *********************** I_FCE_BEGIN *********************** */
    case I_FCE_BEGIN:

        if(strCmpConstStr(&Iop1,"find")==0) vestav=1;   /* Nastavení hodnoty podle vestavěné fce */
        else if (strCmpConstStr(&Iop1,"sort")==0) vestav=2;
        else if (strCmpConstStr(&Iop1,"length")==0) vestav=3;
        else if (strCmpConstStr(&Iop1,"copy")==0) {vestav=4;}
        else{
            sGlobTableItem *pomg;
            sLokTableItem *poml;

            pomg=ST->first;
            if (!tableSearchGlob(NULL,&pomg,&Iop1));
            poml=pomg->link;
            VytvorRamec(poml,RamecInit());  /* Vytvoření lokálního rámce */
        }
        break;
     /* *********************** I_FCE_END *********************** */
    case I_FCE_END:

            if (vrch==1){
                PopTopRamec();
                vrch=0;
            }
            SearchRamec(&poma,&Iop1);
            if (poma->hodnota.def == 0) /* Ošetření zda je definovaná */
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            double ret=poma->hodnota.cisloh;
            PopTopR(&poma);     /* Výběr ze zásobníku rámců */
            PopTopRamec();      /* Výběr ze zásobníku */
            PushRamec();        /* Uložení do zásobníku */

            SearchRamec(&poma,&Iop1);   /* předání návratové hodnoty */
            PridatPom(poma, &Iop1, TP_DOUBLE, ret, &PomString);
            PopTopRamec();
            if (poma==GlobRamec){
                strAddChar(&Iop2,'M');
                *Ipoz = (trojfindfce(Iop2));    /* Hledání pozice kam skočit */
            }else
                *Ipoz = (trojfindfce(Iop2));    /* Hledání pozice kam skočit */

        break;
    /* *********************** I_MAIN_BEGIN *********************** */
    case I_MAIN_BEGIN:

        if(vestav == 0){
            sGlobTableItem *pomgm;

            pomgm=ST->first;
            VytvorRamecGlob(pomgm,GlobRamecInit()); /* Vytvoření globálního rámce */
            poma = GlobRamec;
            PushRamec();    /* Uložení rámce */
        }
        break;
    /* *********************** I_ARG_VOL *********************** */
    case ARG_VOL:

        if(vestav == 0){
            if((strGetLength(&Iop1) != 0)&&(pomchyba3==1)){ /* Pokud je první operand a poslední číslo */
                pomafce = Rfirst->Ritem;
                PopTopRamec();
                PushRamec();
                SearchRamecPoradi(pomafce,&poma,PomResult);
                switch (Iop2.str[0])    /* Zjištění hodnoty */
                {
                case 's':   /* Řetězec */
                    strAddStr(&poma->hodnota.stringh,strGetStr(&Iop1));
                    break;
                case 'p':   /* Proměnná */
                    SearchRamec(&Aop1, &Iop1);
                    if (Aop1->hodnota.def == 0) /* Ošetření pokud není definovaná */
                    {
                        error(NULL,RUNN_NOIN_ERR,NULL);
                    }
                    if (Aop1->typ == TP_DOUBLE){    /* Číslo */
                        poma->hodnota.cisloh = Aop1->hodnota.cisloh;
                    }
                    else if (Aop1->typ == TP_STRING){   /* Řetězec */
                        strAddStr(&poma->hodnota.stringh,strGetStr(&Aop1->hodnota.stringh));
                    }
                    else
                    {
                        error(NULL,OTHER_ERR,NULL);
                    }
                    break;
                default:    /* Ostatní */
                if (pomchyba1==1){
                    poma->hodnota.cisloh = PomIop1;
                    }else{
                        SearchRamec(&Aop1, &Iop1);
                        if (Aop1->hodnota.def == 0) /* Ošetření pokud není definovaná */
                        {
                            error(NULL,RUNN_NOIN_ERR,NULL);
                        }
                        poma->hodnota.cisloh = Aop1->hodnota.cisloh;
                    }
                    break;
                }
                poma->hodnota.def = 1;
            }
        }else if ((vestav>0)&&(vestav<5)){  /* Ošetření pokud jsou vestavěné funkce */
            argum++;
            switch(vestav){
/* *********************** I_FIND *********************** */
            case 1:
                if(argum==1){ /* Načtní operandu 1 typu řetězec */
                    printf("I_FIND\n");
                    if (Iop2.str[0]=='p'){
                        SearchRamec(&Aop1, &Iop1);
                        if (Aop1->hodnota.def == 0)
                        {
                            error(NULL,RUNN_NOIN_ERR,NULL);
                        }

                        if (Aop1->typ == TP_STRING){
                            strInit(&vesstr);
                            vesstr=Aop1->hodnota.stringh;
                        }else
                        {
                            error(NULL,OTHER_ERR,NULL);
                        }
                    }else{
                        strInit(&vesstr);
                        vesstr=Iop1;
                    }
                }
                if(argum==2){   /* Načtní operandu 2 typu řetězec */
                    if (Iop2.str[0]=='p'){
                        SearchRamec(&Aop1, &Iop1);
                        if (Aop1->hodnota.def == 0)
                        {
                            error(NULL,RUNN_NOIN_ERR,NULL);
                        }
                        if (Aop1->typ == TP_STRING)
                        {
                            strInit(&vesstr2);
                            vesstr2=Aop1->hodnota.stringh;
                        }
                        else
                        {
                            error(NULL,OTHER_ERR,NULL);
                        }
                    }else{
                        strInit(&vesstr2);
                        vesstr2=Iop1;
                    }
                }
                break;
   /* *********************** I_SORT *********************** */
            case 2:
                if(argum==1){   /* Načtní operandu 1 typu řetězec */
                    printf("I_SORT\n");
                    if (Iop2.str[0]=='p'){
                        SearchRamec(&Aop1, &Iop1);
                        if (Aop1->hodnota.def == 0)
                        {
                            error(NULL,RUNN_NOIN_ERR,NULL);
                        }
                        if (Aop1->typ == TP_STRING)
                        {
                            strInit(&vesstr);

                            vesstr=Aop1->hodnota.stringh;
                        }
                        else
                        {
                            error(NULL,OTHER_ERR,NULL);
                        }
                    }else{
                        strInit(&vesstr);
                        vesstr=Iop1;
                    }
                }
                break;
   /* *********************** I_LENGTH *********************** */
            case 3:
                if(argum==1){   /* Načtní operandu 1 typu řetězec */
                    printf("I_LENGTH\n");
                    if (Iop2.str[0]=='p'){
                        SearchRamec(&Aop1, &Iop1);
                        if (Aop1->hodnota.def == 0)
                        {
                            error(NULL,RUNN_NOIN_ERR,NULL);
                        }
                        if (Aop1->typ == TP_STRING){
                            strInit(&vesstr);
                            vesstr=Aop1->hodnota.stringh;
                        }
                        else
                        {
                            error(NULL,OTHER_ERR,NULL);
                        }
                    }else{
                        strInit(&vesstr);
                        vesstr=Iop1;
                    }
                }
                break;
    /* *********************** I_COPY *********************** */
            case 4:
                if(argum==1){   /* Načtní operandu 1 typu řetězec */
                    printf("I_COPY\n");
                    if (Iop2.str[0]=='p'){
                        SearchRamec(&Aop1, &Iop1);
                        if (Aop1->hodnota.def == 0)
                        {
                            error(NULL,RUNN_NOIN_ERR,NULL);
                        }
                        if (Aop1->typ == TP_STRING){
                            strInit(&vesstr);
                            vesstr=Aop1->hodnota.stringh;
                        }
                        else
                        {
                            error(NULL,OTHER_ERR,NULL);
                        }
                    }else{
                        strInit(&vesstr);
                        vesstr=Iop1;
                    }
                }
                if(argum==2){   /* Načtní operandu 2 typu číslo */
                    if (pomchyba1==0){
                        if (Iop2.str[0]=='p'){
                            SearchRamec(&Aop1, &Iop1);
                            if (Aop1->hodnota.def == 0)
                            {
                                error(NULL,RUNN_NOIN_ERR,NULL);
                            }
                            if (Aop1->typ == TP_DOUBLE){
                                vescis = Aop1->hodnota.cisloh;
                            }
                        }else
                        {
                            error(NULL,OTHER_ERR,NULL);
                        }
                    }else{
                    vescis = PomIop1;
                    }
                }
                if(argum==3){   /* Načtní operandu 2 typu číslo */
                    if (pomchyba1==0){
                        if (Iop2.str[0]=='p'){
                            SearchRamec(&Aop1, &Iop1);
                            if (Aop1->hodnota.def == 0)
                            {
                                error(NULL,RUNN_NOIN_ERR,NULL);
                            }
                            if (Aop1->typ == TP_DOUBLE){
                                vescis2 = Aop1->hodnota.cisloh;
                            }
                        }else
                        {
                            error(NULL,OTHER_ERR,NULL);
                        }
                    }else{
                    vescis2 = PomIop1;
                    }
                }

                break;
            }

        }
        else {error(NULL,OTHER_ERR,NULL);}
        break;
     /* *********************** CHYBA *********************** */
    default:
        error(NULL,OTHER_ERR,NULL);
        break;
    }

}

void PushRamec(){
    ZASOBNIK *pom;  /* Ukazatel na zásobník */
    pom=(ZASOBNIK*) malloc(sizeof(ZASOBNIK));   /* Alokace pro novou promìnnou */
    pom->Pomramec=poma;     /* Uložení hodnot do zásobníku */
    pom->next=Zfirst;
    Zfirst=pom;
}

void PopTopRamec(){
    ZASOBNIK *pom;  /* Ukazatel na zásobník */

    if (Zfirst!=NULL){
        pom=Zfirst;
        Zfirst=Zfirst->next;
        poma=pom->Pomramec; /* Výběr hodnot ze zásobníku */
        free(pom);     /* Uvolnìní promìnné */
    }
}

