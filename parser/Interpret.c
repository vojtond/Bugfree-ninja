#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Interpret.h"

void PushRamec();
void PopTopRamec();
void MakeInstrucion(int Iinst, string Iop1, string Iop2, string Iresult, int *Ipoz,tGlobSymbolTable *ST);

sRamec *poma=NULL;
int vrch=0;

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
              /* Inicializace proměnných a jejich naplnění */
    sRamec *pomafce;
    sRamec *Aop1 = poma;
    sRamec *Aop2 = poma;
    sRamec *Aresult = poma;

    double PomIop1=0;
    double PomIop2=0;
    double PomResult=0;
    int pomchyba1=0;
    int pomchyba2=0;
    int pomchyba3=0;

    double PomDouble = 0;
    string PomString;
    strInit(&PomString);    /* ****************************************** */



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

    PomResult = atof(Iresult.str);
        if (!PomResult){
        if (Iresult.str[0]== '0'){
            PomResult=0;
            pomchyba3=1;}
        }else pomchyba3=1;

        /*if (Iinst != ARG_VOL){
            if(Rfirst != NULL) poma = Rfirst->Ritem;
            else poma = GlobRamec;
        }*/

       /* if ((strGetLength(&Iop1) != 0)&&(pomchyba1 == 0)){
            if(Rfirst != NULL) Aop1 = Rfirst->Ritem;
            else Aop1 = GlobRamec;
        }

        if ((strGetLength(&Iop2) != 0)&&(pomchyba2 == 0)){
            if(Rfirst != NULL) Aop2 = Rfirst->Ritem;
            else Aop2 = GlobRamec;
        }

        if ((strGetLength(&Iresult) != 0)&&(pomchyba3 == 0)){
            if(Rfirst != NULL) Aresult = Rfirst->Ritem;
            else Aresult = GlobRamec;
        }*/
    }

    switch(Iinst)
    {
    /* Aritmetické operace */
    /* *********************** I_ADD *********************** */
    case TP_PLUS:
        printf("I_ADD\n");

        if ((pomchyba1==1)&&(pomchyba2==0)){
            SearchRamec(&Aop2, &Iop2);
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            PomDouble = PomIop1 + Aop2->hodnota.cisloh;
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            SearchRamec(&Aop1, &Iop1);
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            PomDouble = Aop1->hodnota.cisloh + PomIop2;
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            PomDouble = PomIop1 + PomIop2;
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
                PomDouble = Aop1->hodnota.cisloh + Aop2->hodnota.cisloh;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
            }
            else if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING)){
                if(strCntStr(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) == 0){
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
            PomDouble = PomIop1 - Aop2->hodnota.cisloh;
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            SearchRamec(&Aop1, &Iop1);
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            PomDouble = Aop1->hodnota.cisloh - PomIop2;
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
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
            PomDouble = PomIop1 * Aop2->hodnota.cisloh;
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            SearchRamec(&Aop1, &Iop1);
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            PomDouble = Aop1->hodnota.cisloh * PomIop2;
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
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
            PomDouble = PomIop1 / Aop2->hodnota.cisloh;
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
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
            PomDouble = Aop1->hodnota.cisloh / PomIop2;
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
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
    switch(Iop2.str[0]){

        case 's':
            PomString=Iop1;
            PridatPom(poma, &Iresult, TP_DOUBLE,PomDouble, &PomString);
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
            if(PomIop1 > Aop2->hodnota.cisloh){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            SearchRamec(&Aop1, &Iop1);
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
            SearchRamec(&Aop1, &Iop1);
            SearchRamec(&Aop2, &Iop2);
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
            if(PomIop1 < Aop2->hodnota.cisloh){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            SearchRamec(&Aop1, &Iop1);
            //printf("op %s val %g\n",Aop1->nazev.str,Aop1->hodnota.cisloh);
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
            SearchRamec(&Aop1, &Iop1);
            SearchRamec(&Aop2, &Iop2);
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
        //printf("pomoc %g",PomDouble);
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
            if(PomIop1 >= Aop2->hodnota.cisloh){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            SearchRamec(&Aop1, &Iop1);
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
            SearchRamec(&Aop1, &Iop1);
            SearchRamec(&Aop2, &Iop2);
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
            if(PomIop1 <= Aop2->hodnota.cisloh){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            SearchRamec(&Aop1, &Iop1);
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
            SearchRamec(&Aop1, &Iop1);
            SearchRamec(&Aop2, &Iop2);
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
            if(PomIop1 == Aop2->hodnota.cisloh){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            SearchRamec(&Aop1, &Iop1);
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
            SearchRamec(&Aop1, &Iop1);
            SearchRamec(&Aop2, &Iop2);
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
            if(PomIop1 != Aop2->hodnota.cisloh){
                PomDouble = 1;
            }else{
                PomDouble = 0;
            }
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            SearchRamec(&Aop1, &Iop1);
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
            SearchRamec(&Aop1, &Iop1);
            SearchRamec(&Aop2, &Iop2);
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
        PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        break;

    /* Vestavìné funkce */
    /* *********************** I_FIND *********************** */
    case I_FIND:
        printf("I_FIND\n");
        SearchRamec(&Aop1, &Iop1);
        SearchRamec(&Aop2, &Iop2);
        if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
        {
            error(NULL,RUNN_NOIN_ERR,NULL);
        }
        if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
        {
            PomDouble = find(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh);
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }
        else
        {
            error(NULL,OTHER_ERR,NULL);
        }
        break;
    /* *********************** I_SORT *********************** */
    case I_SORT:
        printf("I_SORT\n");
        SearchRamec(&Aop1, &Iop1);
        if (Aop1->hodnota.def == 0)
        {
            error(NULL,RUNN_NOIN_ERR,NULL);
        }
        if (Aop1->typ == TP_STRING)
        {
            PomString = sort(&Aop1->hodnota.stringh);
            PridatPom(poma, &Iresult, TP_STRING, PomDouble, &PomString);
        }
        else
        {
            error(NULL,OTHER_ERR,NULL);
        }
        break;
    /* *********************** I_LENGTH *********************** */
    case I_LENGTH:
        printf("I_LENGTH\n");
        SearchRamec(&Aop1, &Iop1);
        if (Aop1->hodnota.def == 0)
        {
            error(NULL,RUNN_NOIN_ERR,NULL);
        }
        if (Aop1->typ == TP_STRING){
            PomDouble = lenght(&Aop1->hodnota.stringh);
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
        }
        else
        {
            error(NULL,OTHER_ERR,NULL);
        }
        break;
    /* *********************** I_COPY *********************** */
    case I_COPY:
         printf("I_COPY\n");
         SearchRamec(&Aresult, &Iresult);
        if (Aresult->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
        if ((pomchyba1==1)&&(pomchyba2==0)){
            SearchRamec(&Aop2, &Iop2);
            if (Aop2->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            Aresult->hodnota.stringh = copy(&Aresult->hodnota.stringh, PomIop1, Aop2->hodnota.cisloh);
        }else if ((pomchyba1==0)&&(pomchyba2==1)){
            SearchRamec(&Aop1, &Iop1);
            if (Aop1->hodnota.def == 0)
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            Aresult->hodnota.stringh = copy(&Aresult->hodnota.stringh, Aop1->hodnota.cisloh, PomIop2);
        }else if ((pomchyba1==1)&&(pomchyba2==1)){
            Aresult->hodnota.stringh = copy(&Aresult->hodnota.stringh, PomIop1, PomIop2);
        }else{
            SearchRamec(&Aop1, &Iop1);
            SearchRamec(&Aop2, &Iop2);
            if ((Aop1->hodnota.def == 0)||(Aop2->hodnota.def == 0))
            {
                error(NULL,RUNN_NOIN_ERR,NULL);
            }
            if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE)&&(Aresult->typ == TP_STRING))
            {
                Aresult->hodnota.stringh = copy(&Aresult->hodnota.stringh, Aop1->hodnota.cisloh, Aop2->hodnota.cisloh);
            }else
            {
                error(NULL,OTHER_ERR,NULL);
            }
        }
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
                if ((c != 10)&&(c != 13))
                    strAddChar(&Aresult->hodnota.stringh,c);
                else
                    Aresult->hodnota.def = 1;
                    break;
                }
        }
        else if (Aresult->typ == TP_DOUBLE)
        {
            if (scanf("%lf",&Aresult->hodnota.cisloh) == 1)
            {
                Aresult->hodnota.def = 1;
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
         if (poma!=NULL){
            poma=Rfirst->Ritem;
            PushRamec();
            vrch=1;
            printf("Ukladam dobre");
            if (poma==GlobRamec) printf("OKOKOKOKOKOK\n");
         }
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


        //VypisRamce(pomafce);
        break;
     /* *********************** I_FCE_END *********************** */
    case I_FCE_END:
        printf("I_FCE_END\n");
        double ret;
        if (vrch==1){
            PopTopRamec();
            vrch=0;
        }
        SearchRamec(&poma,&Iop1);
        printf("POMAAAAAAA %g\n",poma->hodnota.cisloh);
        if (poma->hodnota.def == 0)
        {
            error(NULL,RUNN_NOIN_ERR,NULL);
        }
        ret=poma->hodnota.cisloh;
        PopTopR(&poma);
        PopTopRamec();
        PushRamec();

        SearchRamec(&poma,&Iop1);
        PridatPom(poma, &Iop1, TP_DOUBLE, ret, &PomString);
        printf("POMAAAAAAA %g\n",poma->hodnota.cisloh);
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
        sGlobTableItem *pomgm;

        pomgm=ST->first;

        VytvorRamecGlob(pomgm,GlobRamecInit());

        poma = GlobRamec;
        PushRamec();
        if (poma==GlobRamec) printf("OKOKOKOKOKOK\n");
        //VypisRamce(poma);
        break;
    /* *********************** I_ARG_VOL *********************** */
    case ARG_VOL:
        printf("I_ARG_VOL\n");

        if((strGetLength(&Iop1) != 0)&&(pomchyba3==1)){
            pomafce = Rfirst->Ritem;
            PopTopRamec();
            PushRamec();
            if (poma==GlobRamec) printf("OKOKOKOKOKOK\n");
            //printf("Hladam poradi > %g\n",PomResult);
            SearchRamecPoradi(pomafce,&poma,PomResult);
            //printf("***%s***",strGetStr(&pomafcea->nazev));
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
                printf("****%g*****\n",poma->hodnota.cisloh);
                }else{
                    SearchRamec(&Aop1, &Iop1);
                    if (Aop1->hodnota.def == 0)
                    {
                        error(NULL,RUNN_NOIN_ERR,NULL);
                    }
                    poma->hodnota.cisloh = Aop1->hodnota.cisloh;
                    printf("****%g*****\n",poma->hodnota.cisloh);
                }
                break;
            }
            poma->hodnota.def = 1;
        }
        else {error(NULL,OTHER_ERR,NULL);}
        break;
     /* *********************** CHYBA *********************** */
    default:
        //printf("CHYBA\n");
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
        poma=pom->Pomramec; /* Výbìr hodnot ze zásobníku */
        free(pom);     /* Uvolnìní promìnné */
        printf("-----\n");
    }
}

