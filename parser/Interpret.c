#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Interpret.h"

void MakeInstrucion(int Iinst, string Iop1, string Iop2, string Iresult, int *Ipoz,tGlobSymbolTable *ST);

void Interpret(tGlobSymbolTable *ST)
{
tTroj *seznam;
seznam=Trfirst;

int Iinst;
string Iop1;
string Iop2;
string Iresult;
int Ipoz;

 while ( seznam!=NULL ){
        Iinst = seznam->data.inst;
        Iop1 = seznam->data.op1;
        Iop2 = seznam->data.op2;
        Iresult = seznam->data.result;
        Ipoz = 0;
        MakeInstrucion(Iinst, Iop1, Iop2, Iresult, &Ipoz,ST);
        //printf("* %i ** %i * \n", Ipoz, seznam->data.pozice);
        if(Ipoz>0)
        {
            seznam=Trfirst;
            while (seznam!=NULL){
                if (seznam->data.pozice == Ipoz){
                break;
                }
                seznam=seznam->next;
            }
        }
        seznam=seznam->next;
    }
}

void MakeInstrucion(int Iinst, string Iop1, string Iop2, string Iresult, int *Ipoz,tGlobSymbolTable *ST)
{
    sRamec *poma;
    sRamec *Aop1 = NULL;
    sRamec *Aop2 = NULL;
    sRamec *Aresult = NULL;
    double PomDouble = 0;
    string PomString;
    strInit(&PomString);
    if (Iinst<I_FCE_BEGIN){
        SearchRamec(&poma, &Iop1);
        Aop1 = poma;
        if((Aop1->typ == TP_INT)||(Aop1->typ == TP_REAL)||(Aop1->typ == BOOLEAN))
            Aop1->typ=TP_DOUBLE;
        SearchRamec(&poma, &Iop2);
        Aop2 = poma;
        if((Aop2->typ == TP_INT)||(Aop2->typ == TP_REAL)||(Aop2->typ == BOOLEAN))
            Aop2->typ=TP_DOUBLE;
        SearchRamec(&poma, &Iresult);
        Aresult = poma;
        if((Aresult->typ == TP_INT)||(Aresult->typ == TP_REAL)||(Aresult->typ == BOOLEAN))
            Aresult->typ=TP_DOUBLE;
    }

    switch(Iinst)
    {
    /* Aritmetick� operace */
    /* *********************** I_ADD *********************** */
    case TP_PLUS:
        printf("I_ADD\n");
        if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
        {
            PomDouble = Aop1->hodnota.cisloh + Aop2->hodnota.cisloh;
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
            printf("T_Double\n");
            printf("%g\n",PomDouble);
        }
        else if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
        {
            if(strCntStr(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) == 0)
            {
                PomString = Aop1->hodnota.stringh;
                PridatPom(poma, &Iresult, TP_STRING, PomDouble, &PomString);
                printf("T_String\n");
                printf("%s\n",strGetStr(&(PomString)));
            }
            else
            {
                error(NULL,OTHER_ERR,NULL);
            }

        }
        else
        {
            error(NULL,OTHER_ERR,NULL);
        }
        break;
    /* *********************** I_SUB *********************** */
    case TP_MINUS:
        printf("I_SUB\n");
    if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
        {
            PomDouble = Aop1->hodnota.cisloh - Aop2->hodnota.cisloh;
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
            printf("T_Double\n");
            printf("%g\n",PomDouble);
        }
        else
        {
            error(NULL,OTHER_ERR,NULL);
        }
        break;
    /* *********************** I_MUL *********************** */
    case TP_MUL:
        printf("I_MUL\n");
        if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
        {
            PomDouble = Aop1->hodnota.cisloh * Aop2->hodnota.cisloh;
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
            printf("T_Double\n");
            printf("%g\n",PomDouble);
        }
        else
        {
            error(NULL,OTHER_ERR,NULL);
        }
        break;
    /* *********************** I_DIV *********************** */
    case TP_MOD:
        printf("I_DIV\n");
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
        break;
    /* *********************** I_ASSIGN *********************** */
    case ASSIGN:
        printf("I_ASSIGN\n");
        if (Aop1->typ == TP_DOUBLE)
        {
            PomDouble = Aop1->hodnota.cisloh;
            PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
            printf("T_Double\n");
            printf("%f\n",PomDouble);
        }else if (Aop1->typ == TP_STRING)
        {
            PomString = Aop1->hodnota.stringh;
            PridatPom(poma, &Iresult, TP_STRING, PomDouble, &PomString);
            printf("T_String\n");
            printf("%s\n",strGetStr(&PomString));
        }
        else
        {
            error(NULL,OTHER_ERR,NULL);
        }
        break;
    /* Logick� operace */
    /* *********************** I_MORE *********************** */
    case TP_MORE:
        printf("I_MORE\n");
        if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
        {
            if(Aop1->hodnota.cisloh > Aop2->hodnota.cisloh)
            {
                PomDouble = 1;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%f\n",PomDouble);
            }else
            {
                PomDouble = 0;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%f\n",PomDouble);
            }
        }
        else if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
        {
            if(strCmpString(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) > 0)
            {
                PomDouble = 1;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%f\n",PomDouble);
            }else
            {
                PomDouble = 0;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%f\n",PomDouble);
            }
        }
        else
        {
            error(NULL,OTHER_ERR,NULL);
        }
        break;
    /* *********************** I_LESS *********************** */
    case TP_LESS:
        printf("T_LESS\n");
        if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
        {
            if(Aop1->hodnota.cisloh < Aop2->hodnota.cisloh)
            {
                PomDouble = 1;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%f\n",PomDouble);
            }else
            {
                PomDouble = 0;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%f\n",PomDouble);
            }

        }
        else if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
        {
            if(strCmpString(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) < 0)
            {
                PomDouble = 1;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%f\n",PomDouble);
            }else
            {
                PomDouble = 0;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%f\n",PomDouble);
            }
        }
        else
        {
            error(NULL,OTHER_ERR,NULL);
        }
        break;
    /* *********************** I_MORE_EQUAL *********************** */
    case TP_MOREQ:
        printf("T_MORE_EQUAL\n");
        if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
        {
            if(Aop1->hodnota.cisloh >= Aop2->hodnota.cisloh)
            {
                PomDouble = 1;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%g\n",PomDouble);
            }else
            {
                PomDouble = 0;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%g\n",PomDouble);
            }

        }
        else if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
        {
            if(strCmpString(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) >= 0)
            {
                PomDouble = 1;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%g\n",PomDouble);
            }else
            {
                PomDouble = 0;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%g\n",PomDouble);
            }
        }
        else
        {
            error(NULL,OTHER_ERR,NULL);
        }
        break;
    /* *********************** I_LESS_EQUAL *********************** */
    case TP_LESSQ:
        printf("T_LESS_EQUAL\n");
        if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
        {
            if(Aop1->hodnota.cisloh <= Aop2->hodnota.cisloh)
            {
                PomDouble = 1;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%g\n",PomDouble);
            }else
            {
                PomDouble = 0;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%g\n",PomDouble);
            }

        }
        else if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
        {
            if(strCmpString(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) <= 0)
            {
                PomDouble = 1;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%g\n",PomDouble);
            }else
            {
                PomDouble = 0;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%g\n",PomDouble);
            }
        }
        else
        {
            error(NULL,OTHER_ERR,NULL);
        }
        break;
    /* *********************** I_EQUAL *********************** */
    case TP_EQU:
        printf("T_EQUAL\n");
        if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
        {
            if(Aop1->hodnota.cisloh == Aop2->hodnota.cisloh)
            {
                PomDouble = 1;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%g\n",PomDouble);
            }else
            {
                PomDouble = 0;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%g\n",PomDouble);
            }

        }
        else if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
        {
            if(strCmpString(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) == 0)
            {
                PomDouble = 1;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%g\n",PomDouble);
            }else
            {
                PomDouble = 0;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%g\n",PomDouble);
            }
        }
        else
        {
            error(NULL,OTHER_ERR,NULL);
        }
        break;
    /* *********************** I_NOT_EQUAL *********************** */
    case TP_NEQU:
        printf("T_NOT_EQUAL\n");
        if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE))
        {
            if(Aop1->hodnota.cisloh != Aop2->hodnota.cisloh)
            {
                PomDouble = 1;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%g\n",PomDouble);
            }else
            {
                PomDouble = 0;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%g\n",PomDouble);
            }
        }
        else if ((Aop1->typ == TP_STRING)&&(Aop2->typ == TP_STRING))
        {
            if(strCmpString(&Aop1->hodnota.stringh, &Aop2->hodnota.stringh) != 0)
            {
                PomDouble = 1;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%g\n",PomDouble);
            }else
            {
                PomDouble = 0;
                PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble, &PomString);
                printf("T_Bool\n");
                printf("%g\n",PomDouble);
            }
        }
        else
        {
            error(NULL,OTHER_ERR,NULL);
        }
        break;

    /* Vestav�n� funkce */
    /* *********************** I_FIND *********************** */
    case I_FIND:
        printf("I_FIND\n");
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
        if (Aop1->typ == TP_STRING)
        {
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
        if ((Aop1->typ == TP_DOUBLE)&&(Aop2->typ == TP_DOUBLE)&&(Aresult->typ == TP_STRING))
        {
            Aresult->hodnota.stringh = copy(&Aresult->hodnota.stringh, Aop1->hodnota.cisloh, Aop2->hodnota.cisloh);
            printf("T_String\n");
            printf("%s\n",strGetStr(&Aresult->hodnota.stringh));
        }
        else
        {
            error(NULL,OTHER_ERR,NULL);
        }
        break;
    /* *********************** I_WRITE *********************** */
    case I_WRITE:
        printf("I_WRITE\n");
        if (Aop1->typ == TP_STRING)
        {
            printf("%s",strGetStr(&Aop1->hodnota.stringh));
        }
        else if (Aop1->typ == TP_DOUBLE)
        {
            printf("%g",Aop1->hodnota.cisloh);
        }
        else
        {
            error(NULL,OTHER_ERR,NULL);
        }
        break;
    /* *********************** I_READ *********************** */
    case I_READ:
        printf("I_READ\n");
        if (Aresult->typ == TP_STRING)
        {
            char c;
                while ((c = getchar()))
                {
                if ((c != 10)&&(c != 13))
                    strAddChar(&Aresult->hodnota.stringh,c);
                else
                    break;
                }
                //PridatPom(poma, &Iresult, TP_STRING, PomDouble , &PomString);
                printf("T_String\n");
                printf("%s\n",strGetStr(&Aresult->hodnota.stringh));

        }
        else if (Aresult->typ == TP_DOUBLE)
        {
            if (scanf("%lf",&Aresult->hodnota.cisloh) == 1)
            {
                //PridatPom(poma, &Iresult, TP_DOUBLE, PomDouble , &PomString);
                printf("T_Double\n");
                printf("%g",Aresult->hodnota.cisloh);
            }
            else
            {
            error(NULL,RUNN_IN_ERR,NULL);
            }
        }
        else
        {
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
        if(Aop1->typ == TP_DOUBLE){
            if(Aop1->hodnota.cisloh == 0)
            {
                printf("T_Bool\n");
                *Ipoz = trojfindlab(Iop1);
            }
        }
        else
        {
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
         *Ipoz = trojfindfce(Iop1);
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
        break;
     /* *********************** CHYBA *********************** */
    default:
        printf("CHYBA\n");
        error(NULL,OTHER_ERR,NULL);
        break;
    }
}
