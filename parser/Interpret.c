#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Interpret.h"

void MakeInstrucion(int Iinst, string Iop1, string Iop2, string Iresult, int *Ipoz,tGlobSymbolTable *ST);

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
            while (seznam!=NULL){   /* Procházení seznamu  dokuk nedojdu na pozici */
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
    sRamec *poma;           /* Inicializace proměnných a jejich naplnění */
    sRamec *Aop1 = NULL;
    sRamec *Aop2 = NULL;
    sRamec *Aresult = NULL;

    double PomIop1=0;
    double PomIop2=0;
    int pomchyba1=0;
    int pomchyba2=0;

    double PomDouble = 0;
    string PomString;
    strInit(&PomString);    /* ****************************************** */

    //printf("%i",Iinst);
    if (Iinst<I_JUMP_FCE){

        PomIop1 = atof(Iop1.str);
        if (!PomIop1){
        if (Iop1.str[0]== '0'){
            PomIop1=0;
            pomchyba2=1;}
        }else pomchyba1=1;

        PomIop2 = atof(Iop2.str);
        if (!PomIop2){
        if (Iop2.str[0]== '0'){
            PomIop2=0;
            pomchyba2=1;}
        }else pomchyba2=1;

        if(Rfirst != NULL) Aop1 = Rfirst->Ritem;
        else Aop1 = GlobRamec;

        printf("\n\n -- HLEDA se: %s\n\n",strGetStr(&(Iop1)));
        if(SearchRamec(&Aop1, &Iop1)==1){
                printf("\n -- NASEL JSEM je: %s\n",strGetStr(&(Aop1->nazev)));
            //printf("**********************prvni search probehl*****************************");
            if((Aop1->typ == TP_INT)||(Aop1->typ == TP_REAL)||(Aop1->typ == BOOLEAN))
                Aop1->typ=TP_DOUBLE;
        }

        if(Rfirst != NULL) Aop2 = Rfirst->Ritem;
        else Aop2 = GlobRamec;

        printf("\n -- HLEDA se (2.op): %s\n",strGetStr(&(Iop2)));

        if(SearchRamec(&Aop2, &Iop2)==1){
            printf("\n -- NASEL JSEM je: %s\n",strGetStr(&(Aop2->nazev)));
            if((Aop2->typ == TP_INT)||(Aop2->typ == TP_REAL)||(Aop2->typ == BOOLEAN))
                Aop2->typ=TP_DOUBLE;
        }

        if(Rfirst != NULL) Aresult = Rfirst->Ritem;
        else Aresult = GlobRamec;

        printf("\n -- HLEDA se (vysledek): %s\n",strGetStr(&(Iresult)));

        if(SearchRamec(&Aresult, &Iresult)==1){
            printf("\n -- NASEL JSEM je: %s\n",strGetStr(&(Aresult->nazev)));
            if((Aresult->typ == TP_INT)||(Aresult->typ == TP_REAL)||(Aresult->typ == BOOLEAN))
                Aresult->typ=TP_DOUBLE;
        }
    }

    switch(Iinst)
    {
    /* Aritmetické operace */
    /* *********************** I_ADD *********************** */
    case TP_PLUS:
        printf("I_ADD\n");

        if ((pomchyba1==1)&&(pomchyba2==0)){
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            PomDouble = PomIop1 + Aop2->hodnota.cisloh;
            printf("*%g\n",PomDouble);
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            PomDouble = Aop1->hodnota.cisloh + PomIop2;
            printf("**%g\n",PomDouble);
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            PomDouble = PomIop1 + PomIop2;
            printf("***%g\n",PomDouble);
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }else{
            if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
            {
                PomDouble = Aop1->hodnota.cisloh + Aop2->hodnota.cisloh;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);

                printf("T_Double\n");
                printf("****%g\n",PomDouble);
            }
            else if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING)){
                if(strCntStr(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) == 0){
                    PomString = Aop1->hodnota.stringh;
                    PridatPom(poma, &Iresult, TP_STRING, PomDouble, &PomString);
                    printf("T_String\n");
                    printf("%s\n",strGetStr(&(PomString)));
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
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            PomDouble = PomIop1 - Aop2->hodnota.cisloh;
            printf("*%g\n",PomDouble);
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            PomDouble = Aop1->hodnota.cisloh - PomIop2;
            printf("**%g\n",PomDouble);
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            PomDouble = PomIop1 - PomIop2;
            printf("***%g\n",PomDouble);
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }else{
            if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE)){
                PomDouble = Aop1->hodnota.cisloh - Aop2->hodnota.cisloh;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Double\n");
                printf("%g\n",PomDouble);
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }
        break;
    /* *********************** I_MUL *********************** */
    case TP_MUL:
        printf("I_MUL\n");
        if ((pomchyba1==1)&&(pomchyba2==0)){
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            PomDouble = PomIop1 * Aop2->hodnota.cisloh;
            printf("*%g\n",PomDouble);
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            PomDouble = Aop1->hodnota.cisloh * PomIop2;
            printf("**%g\n",PomDouble);
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            PomDouble = PomIop1 * PomIop2;
            printf("***%g\n",PomDouble);
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }else{
            if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE)){
                PomDouble = Aop1->hodnota.cisloh * Aop2->hodnota.cisloh;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Double\n");
                printf("%g\n",PomDouble);
            }else{
                error(NULL,OTHER_ERR,NULL);
            }
        }
        break;
    /* *********************** I_DIV *********************** */
    case TP_MOD:
        printf("I_DIV\n");

        if ((pomchyba1==1)&&(pomchyba2==0)){
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (Aop2->hodnota.cisloh == 0)
            {
                error(NULL,RUNN_ZERODI_ERR,NULL);
            }
            PomDouble = PomIop1 / Aop2->hodnota.cisloh;
            printf("*%g\n",PomDouble);
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if (PomIop2 == 0)
            {
                error(NULL,RUNN_ZERODI_ERR,NULL);
            }
            PomDouble = Aop1->hodnota.cisloh / PomIop2;
            printf("**%g\n",PomDouble);
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            if (PomIop2 == 0)
            {
                error(NULL,RUNN_ZERODI_ERR,NULL);
            }
            PomDouble = PomIop1 / PomIop2;
            printf("***%g\n",PomDouble);
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }else{
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
                printf("T_Double\n");
                printf("%g\n",PomDouble);
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

        if (pomchyba1==1){
                PridatPom(poma, &Iresult, TP_DOUBLE, PomIop1, &PomString);
        }else{
            if (Aresult->typ == TP_DOUBLE)
            {
                PomDouble = Aop1->hodnota.cisloh;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Double\n");
                printf("%g\n",PomDouble);
            }else if (Aresult->typ == TP_STRING)
            {
                PomString = Iop1;
                printf("%s\n",strGetStr(&PomString));
                PridatPom(poma, &Iresult, TP_STRING, PomDouble, &PomString);
                printf("T_String\n");
                printf("%s\n",strGetStr(&PomString));
            }
            else
            {
                error(NULL,OTHER_ERR,NULL);
            }
        }
        break;
    /* Logické operace */
    /* *********************** I_MORE *********************** */
    case TP_MORE:
        printf("I_MORE\n");

        if ((pomchyba1==1)&&(pomchyba2==0)){
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if(PomIop1 > Aop2->hodnota.cisloh){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if(Aop1->hodnota.cisloh > PomIop2){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            if(PomIop1 > PomIop2){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else{
            if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
            {
                if(Aop1->hodnota.cisloh > Aop2->hodnota.cisloh){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }
            else if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
            {
                if(strCmpString(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) > 0){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }
            else{
                error(NULL,OTHER_ERR,NULL);
            }
        }
        printf("%g\n",PomDouble);
        PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        break;
    /* *********************** I_LESS *********************** */
    case TP_LESS:
        printf("T_LESS\n");
        if ((pomchyba1==1)&&(pomchyba2==0)){
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if(PomIop1 < Aop2->hodnota.cisloh){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if(Aop1->hodnota.cisloh < PomIop2){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            if(PomIop1 < PomIop2){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else{
            if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
            {
                if(Aop1->hodnota.cisloh < Aop2->hodnota.cisloh){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }
            else if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
            {
                if(strCmpString(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) < 0){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }
            else{
                error(NULL,OTHER_ERR,NULL);
            }
        }
        printf("%g\n",PomDouble);
        PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        break;
    /* *********************** I_MORE_EQUAL *********************** */
    case TP_MOREQ:
        printf("T_MORE_EQUAL\n");
        if ((pomchyba1==1)&&(pomchyba2==0)){
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if(PomIop1 >= Aop2->hodnota.cisloh){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if(Aop1->hodnota.cisloh >= PomIop2){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            if(PomIop1 >= PomIop2){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else{
            if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
            {
                if(Aop1->hodnota.cisloh >= Aop2->hodnota.cisloh){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }
            else if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
            {
                if(strCmpString(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) >= 0){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }
            else{
                error(NULL,OTHER_ERR,NULL);
            }
        }
        printf("%g\n",PomDouble);
        PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        break;
    /* *********************** I_LESS_EQUAL *********************** */
    case TP_LESSQ:
        printf("T_LESS_EQUAL\n");
        if ((pomchyba1==1)&&(pomchyba2==0)){
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if(PomIop1 <= Aop2->hodnota.cisloh){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if(Aop1->hodnota.cisloh <= PomIop2){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            if(PomIop1 <= PomIop2){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else{
            if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
            {
                if(Aop1->hodnota.cisloh <= Aop2->hodnota.cisloh){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }
            else if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
            {
                if(strCmpString(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) <= 0){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }
            else{
                error(NULL,OTHER_ERR,NULL);
            }
        }
        printf("%g\n",PomDouble);
        PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        break;
    /* *********************** I_EQUAL *********************** */
    case TP_EQU:
        printf("T_EQUAL\n");
        if ((pomchyba1==1)&&(pomchyba2==0)){
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if(PomIop1 == Aop2->hodnota.cisloh){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if(Aop1->hodnota.cisloh == PomIop2){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            if(PomIop1 == PomIop2){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else{
            if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
            {
                if(Aop1->hodnota.cisloh == Aop2->hodnota.cisloh){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }
            else if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
            {
                if(strCmpString(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) == 0){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }
            else{
                error(NULL,OTHER_ERR,NULL);
            }
        }
        printf("%g\n",PomDouble);
        PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        break;
    /* *********************** I_NOT_EQUAL *********************** */
    case TP_NEQU:
        printf("T_NOT_EQUAL\n");
        if ((pomchyba1==1)&&(pomchyba2==0)){
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if(PomIop1 != Aop2->hodnota.cisloh){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if(Aop1->hodnota.cisloh != PomIop2){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            if(PomIop1 != PomIop2){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else{
            if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
            {
                if(Aop1->hodnota.cisloh != Aop2->hodnota.cisloh){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }
            else if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
            {
                if(strCmpString(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) != 0){
                    PomDouble = 1;
                }else{
                    PomDouble = 0;
                }
            }
            else{
                error(NULL,OTHER_ERR,NULL);
            }
        }
        printf("%g\n",PomDouble);
        PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        break;

    /* Vestavìné funkce */
    /* *********************** I_FIND *********************** */
    case I_FIND:
        printf("I_FIND\n");
        if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
        {
            error(NULL,RUNN_NOIN_ERR,NULL);
        }
        if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
        {
            PomDouble = find(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh);
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
            printf("T_Double\n");
            printf("%g\n",PomDouble);
        }
        else
        {
            error(NULL,OTHER_ERR,NULL);
        }
        break;
    /* *********************** I_SORT *********************** */
    case I_SORT:
        printf("I_SORT\n");
        if (Aop1->hodnota.def == 0)
        {
            error(NULL,RUNN_NOIN_ERR,NULL);
        }
        if (Aop1->typ == TP_STRING)
        {
            PomString = sort(&Aop1->hodnota.stringh);
            PridatPom(poma, &Iresult, TP_STRING, PomDouble, &PomString);
            printf("T_String\n");
            printf("%s\n",strGetStr(&PomString));
        }
        else
        {
            error(NULL,OTHER_ERR,NULL);
        }
        break;
    /* *********************** I_LENGTH *********************** */
    case I_LENGTH:
        printf("I_LENGTH\n");
        if (Aop1->hodnota.def == 0)
        {
            error(NULL,RUNN_NOIN_ERR,NULL);
        }
        if (Aop1->typ == TP_STRING){
            PomDouble = lenght(&Aop1->hodnota.stringh);
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
            printf("T_Double\n");
            printf("%g\n",PomDouble);
        }
        else
        {
            error(NULL,OTHER_ERR,NULL);
        }
        break;
    /* *********************** I_COPY *********************** */
    case I_COPY:
         printf("I_COPY\n");
        if (Aresult->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
        if ((pomchyba1==1)&&(pomchyba2==0)){
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            Aresult->hodnota.stringh = copy(&Aresult->hodnota.stringh, PomIop1, Aop2->hodnota.cisloh);
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            Aresult->hodnota.stringh = copy(&Aresult->hodnota.stringh, Aop1->hodnota.cisloh, PomIop2);
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            Aresult->hodnota.stringh = copy(&Aresult->hodnota.stringh, PomIop1, PomIop2);
        }else{
            if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE)&&(Aresult->typ == TP_STRING))
            {
                Aresult->hodnota.stringh = copy(&Aresult->hodnota.stringh, Aop1->hodnota.cisloh, Aop2->hodnota.cisloh);
                printf("T_String\n");
                printf("%s\n",strGetStr(&Aresult->hodnota.stringh));
            }else
            {
                error(NULL,OTHER_ERR,NULL);
            }
        }
        break;
    /* *********************** I_WRITE *********************** */
    case I_WRITE:
        printf("I_WRITE\n");
        int op = 0;
        if(Iop2.str[0] == 'p') op = 1;
        switch (op)
        {
        case 1:
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
        if (Aresult->hodnota.def == 0)
        {
            error(NULL,RUNN_NOIN_ERR,NULL);
        }
        if (Aresult->typ == TP_STRING)
        {
            char c;
                while ((c = getchar()))
                {
                if ((c != 10)&&(c != 13))
                    strAddChar(&Aresult->hodnota.stringh,c);
                else
                    Aresult->hodnota.def = 1;
                    break;
                }
                printf("T_String\n");
                printf("%s\n",strGetStr(&Aresult->hodnota.stringh));

        }
        else if (Aresult->typ == TP_DOUBLE)
        {
            if (scanf("%lf",&Aresult->hodnota.cisloh) == 1)
            {
                Aresult->hodnota.def = 1;
                printf("T_Double\n");
                printf("%g",Aresult->hodnota.cisloh);
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
        if (Aop2->hodnota.def == 0)
        {
            error(NULL,RUNN_NOIN_ERR,NULL);
        }
        if(Aop2->typ == TP_DOUBLE){
            if(Aop2->hodnota.cisloh == 0){
                printf("T_Bool\n");
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
         *Ipoz = (trojfindfce(Iop2)-1);
         //printf("%i",*Ipoz);
        break;
    /* *********************** I_FCE_BEGIN *********************** */
    case I_FCE_BEGIN:
        printf("I_FCE_BEGIN\n");
        sGlobTableItem *pomg;
        sLokTableItem *poml;

        pomg=ST->first;
        if (!tableSearchGlob(NULL,&pomg,&Iop1));
        poml=pomg->link;
        VytvorRamec(poml,RamecInit());

        poma = Rfirst->Ritem;
        //VypisRamce(poma);
        break;
     /* *********************** I_FCE_END *********************** */
    case I_FCE_END:
        printf("I_FCE_END\n");
        PopTopR(&poma);
        //*Ipoz = (trojfindfce(Iop2));
        break;
    /* *********************** I_MAIN_BEGIN *********************** */
    case I_MAIN_BEGIN:
        printf("I_MAIN_BEGIN\n");
        sGlobTableItem *pomgm;

        pomgm=ST->first;

        VytvorRamecGlob(pomgm,GlobRamecInit());

        poma = GlobRamec;
        //VypisRamce(poma);
        break;
     /* *********************** CHYBA *********************** */
    default:
        printf("CHYBA\n");
        error(NULL,OTHER_ERR,NULL);
        break;
    }
}
