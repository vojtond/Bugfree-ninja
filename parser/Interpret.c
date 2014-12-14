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
            pomchyba2=1;}
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
        printf("I_ADD\n");

        if ((pomchyba1==1)&&(pomchyba2==0)){    /* Provede se když je první operand číslo a druhý proměnná */
            SearchRamec(&Aop2, &Iop2);  /* Hledání proměnné v rámci */
            if (Aop2->hodnota.def == 0) /* Ošetření jestli je proměnná definovaná */
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop2->typ == TP_DOUBLE)
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
                if(strCntStr(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) == 0){ /* Ošetření zřeztězení */
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
        printf("I_SUB\n");

        if ((pomchyba1==1)&&(pomchyba2==0)){
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
        printf("I_MUL\n");
        if ((pomchyba1==1)&&(pomchyba2==0)){
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
        printf("I_DIV\n");

        if ((pomchyba1==1)&&(pomchyba2==0)){
            SearchRamec(&Aop2, &Iop2);
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop2->hodnota.cisloh == 0)
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
            if (Aop1->hodnota.def == 0)
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
            if (PomIop2 == 0)
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
                if (Aop2->hodnota.cisloh == 0)
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
        printf("I_ASSIGN\n");

       if (vestav == 0){
            switch(Iop2.str[0]){

            case 's':
                PomString=Iop1;
                PridatPom(poma, &Iresult, TP_STRING,PomDouble, &PomString);
                break;
            case 'p':
                SearchRamec(&Aop1, &Iop1);
                if (Aop1->hodnota.def == 0)
                {
                    error(NULL,RUNN_NOIN_ERR,NULL);
                }
                if (Aop1->typ == TP_DOUBLE){
                    PomDouble=Aop1->hodnota.cisloh;
                    PridatPom(poma, &Iresult, TP_DOUBLE,PomDouble, &PomString);
                }
                else if (Aop1->typ == TP_STRING){
                PomString=Aop1->hodnota.stringh;
                PridatPom(poma, &Iresult, TP_DOUBLE,PomDouble, &PomString);
                }else
                {
                    error(NULL,OTHER_ERR,NULL);
                }
                break;
            default:
                if (pomchyba1==1){
                    PridatPom(poma, &Iresult, TP_DOUBLE, PomIop1, &PomString);
                }else{
                    SearchRamec(&Aop1, &Iop1);
                    if (Aop1->hodnota.def == 0)
                    {
                        error(NULL,RUNN_NOIN_ERR,NULL);
                    }
                    PridatPom(poma, &Iresult, TP_DOUBLE, Aop1->hodnota.cisloh, &PomString);

                }
                break;
            }

        }else if ((vestav>0)&&(vestav<5)){
            switch(vestav){
            case 1:
                PomDouble = find(&vesstr, &vesstr2);
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                break;
            case 2:
                PomString = sort(&vesstr);
                PridatPom(poma, &Iresult, TP_STRING, PomDouble, &PomString);
                break;
            case 3:
                PomDouble = lenght(&vesstr);
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                break;
            case 4:
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
        printf("I_MORE\n");

        if ((pomchyba1==1)&&(pomchyba2==0)){
            SearchRamec(&Aop2, &Iop2);
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop2->typ == TP_DOUBLE)
            {
                if(PomIop1 > Aop2->hodnota.cisloh){
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
                if(Aop1->hodnota.cisloh > PomIop2){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            if(PomIop1 > PomIop2){
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
                    if(strCmpString(&Aop1->hodnota.stringh, &Iop2) > 0){
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
                if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
                {
                    if(strCmpString(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) > 0){
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
    /* *********************** I_LESS *********************** */
    case TP_LESS:
        printf("T_LESS\n");
        if ((pomchyba1==1)&&(pomchyba2==0)){
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
        printf("T_MORE_EQUAL\n");
        if ((pomchyba1==1)&&(pomchyba2==0)){
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
        printf("T_LESS_EQUAL\n");
        if ((pomchyba1==1)&&(pomchyba2==0)){
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
        printf("T_EQUAL\n");
        if ((pomchyba1==1)&&(pomchyba2==0)){
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
        printf("T_NOT_EQUAL\n");
        if ((pomchyba1==1)&&(pomchyba2==0)){
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
        printf("I_WRITE\n");

        switch (Iop2.str[0])
        {
        case 'p':
            SearchRamec(&Aop1, &Iop1);
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop1->typ == TP_STRING){
                printf("%s",strGetStr(&Aop1->hodnota.stringh));
            }
            else if (Aop1->typ == TP_DOUBLE){
                printf("%g",Aop1->hodnota.cisloh);
            }else
            {
                error(NULL,OTHER_ERR,NULL);
            }
            break;
        default:
            printf("%s",strGetStr(&Iop1));
            break;
        }
        break;
    /* *********************** I_READ *********************** */
    case I_READ:
        printf("I_READ\n");
        SearchRamec(&Aresult, &Iresult);
        if (Aresult->typ == TP_STRING)
        {
            char c;
                while ((c = getchar()))
                {
                    if ((c != 10)&&(c != 13)){
                        strAddChar(&PomString,c);
                    }else{
                        PridatPom(poma, &Iresult, TP_STRING, PomDouble, &PomString);
                        break;
                    }
                }
        }
        else if (Aresult->typ == TP_DOUBLE)
        {
            if (scanf("%lf",&PomDouble) == 1)
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
        printf("I_LABEL\n");
        break;
    /* *********************** I_FJUMP *********************** */
    case I_FJUMP:
        printf("I_FJUMP\n");
        SearchRamec(&Aop2, &Iop2);
        if (Aop2->hodnota.def == 0)
        {
            error(NULL,RUNN_NOIN_ERR,NULL);
        }
        if(Aop2->typ == TP_DOUBLE){
            if(Aop2->hodnota.cisloh == 0){
                *Ipoz = trojfindlab(Iop1);
            }
        }else{
            error(NULL,OTHER_ERR,NULL);
        }
        break;
    /* *********************** I_JUMP *********************** */
    case I_JUMP:
        printf("I_JUMP\n");
        *Ipoz = trojfindlab(Iop1);
        break;
    /* *********************** I_JUMP_FCE *********************** */
     case I_JUMP_FCE:
        printf("I_JUMP_FCE\n");
        if(vestav==0){
            if (poma!=NULL){
                poma=Rfirst->Ritem;
                PushRamec();
                vrch=1;
            }
        *Ipoz = (trojfindfce(Iop2)-1);
        }
        break;
    /* *********************** I_FCE_BEGIN *********************** */
    case I_FCE_BEGIN:
        printf("I_FCE_BEGIN\n");
        if(strCmpConstStr(&Iop1,"find")==0) vestav=1;
        else if (strCmpConstStr(&Iop1,"sort")==0) vestav=2;
        else if (strCmpConstStr(&Iop1,"length")==0) vestav=3;
        else if (strCmpConstStr(&Iop1,"copy")==0) {vestav=4;}
        else{
            sGlobTableItem *pomg;
            sLokTableItem *poml;

            pomg=ST->first;
            if (!tableSearchGlob(NULL,&pomg,&Iop1));
            poml=pomg->link;
            VytvorRamec(poml,RamecInit());
        }
        break;
     /* *********************** I_FCE_END *********************** */
    case I_FCE_END:
        printf("I_FCE_END\n");

            if (vrch==1){
                PopTopRamec();
                vrch=0;
            }
            SearchRamec(&poma,&Iop1);
            if (poma->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            double ret=poma->hodnota.cisloh;
            PopTopR(&poma);
            PopTopRamec();
            PushRamec();

            SearchRamec(&poma,&Iop1);
            PridatPom(poma, &Iop1, TP_DOUBLE, ret, &PomString);
            PopTopRamec();
            if (poma==GlobRamec){
                strAddChar(&Iop2,'M');
                *Ipoz = (trojfindfce(Iop2));
            }else
                *Ipoz = (trojfindfce(Iop2));

        break;
    /* *********************** I_MAIN_BEGIN *********************** */
    case I_MAIN_BEGIN:
        printf("I_MAIN_BEGIN\n");
        if(vestav == 0){
            sGlobTableItem *pomgm;

            pomgm=ST->first;
            VytvorRamecGlob(pomgm,GlobRamecInit());
            poma = GlobRamec;
            PushRamec();
        }
        break;
    /* *********************** I_ARG_VOL *********************** */
    case ARG_VOL:
        printf("I_ARG_VOL\n");
        if(vestav == 0){
            if((strGetLength(&Iop1) != 0)&&(pomchyba3==1)){
                pomafce = Rfirst->Ritem;
                PopTopRamec();
                PushRamec();
                SearchRamecPoradi(pomafce,&poma,PomResult);
                switch (Iop2.str[0])
                {
                case 's':
                    strAddStr(&poma->hodnota.stringh,strGetStr(&Iop1));
                    break;
                case 'p':
                    SearchRamec(&Aop1, &Iop1);
                    if (Aop1->hodnota.def == 0)
                    {
                        error(NULL,RUNN_NOIN_ERR,NULL);
                    }
                    if (Aop1->typ == TP_DOUBLE){
                        poma->hodnota.cisloh = Aop1->hodnota.cisloh;
                    }
                    else if (Aop1->typ == TP_STRING){
                        strAddStr(&poma->hodnota.stringh,strGetStr(&Aop1->hodnota.stringh));
                    }
                    else
                    {
                        error(NULL,OTHER_ERR,NULL);
                    }
                    break;
                default:
                if (pomchyba1==1){
                    poma->hodnota.cisloh = PomIop1;
                    }else{
                        SearchRamec(&Aop1, &Iop1);
                        if (Aop1->hodnota.def == 0)
                        {
                            error(NULL,RUNN_NOIN_ERR,NULL);
                        }
                        poma->hodnota.cisloh = Aop1->hodnota.cisloh;
                    }
                    break;
                }
                poma->hodnota.def = 1;
            }
        }else if ((vestav>0)&&(vestav<5)){
            argum++;
            switch(vestav){
/* *********************** I_FIND *********************** */
            case 1:
                if(argum==1){
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
                if(argum==2){
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
                if(argum==1){
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
                if(argum==1){
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
                if(argum==1){
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
                if(argum==2){
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
                if(argum==3){
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
    printf("+++++\n");
}

void PopTopRamec(){
    ZASOBNIK *pom;  /* Ukazatel na zásobník */

    if (Zfirst!=NULL){
        pom=Zfirst;
        Zfirst=Zfirst->next;
        poma=pom->Pomramec; /* Výběr hodnot ze zásobníku */
        free(pom);     /* Uvolnìní promìnné */
        printf("-----\n");
    }
}

