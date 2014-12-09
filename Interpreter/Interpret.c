#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Interpret.h"

void MakeInstrucion(int Iinst, string Iop1, string Iop2, string Iresult, int *Ipoz);

int f=1;

void Interpret()
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
        //printf("%i %s %s %s %i %i\n",seznam->data.inst, seznam->data.op1.str, seznam->data.op2.str, seznam->data.result.str, seznam->data.pozice, seznam->data.label);
        Ipoz = 0;
        MakeInstrucion(Iinst, Iop1, Iop2, Iresult, &Ipoz);
        printf("* %i ** %i * \n", Ipoz, seznam->data.pozice);
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

void MakeInstrucion(int Iinst, string Iop1, string Iop2, string Iresult, int *Ipoz)
{
    switch(Iinst)
    {
    /* Aritmetické operace */
    /* *********************** I_ADD *********************** */
    case 10:
        printf("I_ADD\n");
        /*if((Iop1.str=='\0')||(Iop2.str=='\0')||(Iresult.str=='\0'))
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
        if ((op1.Typ == T_Double)&&(op2.Typ == T_Double))
        {
            resul.value.d = op1.value.d + op2.value.d;
            resul.Typ = T_Double;
            printf("T_Double\n");
            printf("%g\n",resul.value.d);
        }
        else if ((op1.Typ == T_String)&&(op2.Typ == T_String))
        {
            if(strCntStr(&op1.value.s, &op2.value.s) == 0)
            {
                resul.value.s = op1.value.s;
                resul.Typ = T_String;
                printf("T_String\n");
                printf("%s\n",resul.value.s.str);
            }
            else
            {
                error(x,OTHER_ERR,xx);
            }

        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        break;
    /* *********************** I_SUB *********************** */
    case 11:
        printf("I_SUB\n");
        /*if((Iop1.str=='\0')||(Iop2.str=='\0')||(Iresult.str=='\0'))
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
    if ((op1.Typ == T_Double)&&(op2.Typ == T_Double))
        {
            resul.value.d = op1.value.d - op2.value.d;
            resul.Typ = T_Double;
            printf("T_Double\n");
            printf("%g\n",resul.value.d);
        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        break;
    /* *********************** I_MUL *********************** */
    case 12:
        printf("I_MUL\n");
        /*if((Iop1.str=='\0')||(Iop2.str=='\0')||(Iresult.str=='\0'))
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
        if ((op1.Typ == T_Double)&&(op2.Typ == T_Double))
        {
            resul.value.d = op1.value.d * op2.value.d;
            resul.Typ = T_Double;
            printf("T_Double\n");
            printf("%g\n",resul.value.d);
        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        break;
    /* *********************** I_DIV *********************** */
    case 13:
        printf("I_DIV\n");
        /*if((Iop1.str=='\0')||(Iop2.str=='\0')||(Iresult.str=='\0'))
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
        if ((op1.Typ == T_Double)&&(op2.Typ == T_Double))
        {
            if (op2.VALUE.D == 0)
            {
                    error(xx,RUNN_ZERODI_ERR,xx);
            }
            resul.value.d = op1.value.d / op2.value.d;
            resul.Typ = T_Double;
            printf("T_Double\n");
            printf("%g\n",resul.value.d);
        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        break;
    /* *********************** I_POW *********************** */
    case 14:
        printf("I_POW\n");
        /*if((Iop1.str=='\0')||(Iop2.str=='\0')||(Iresult.str=='\0'))
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
        if ((op1.Typ == T_Double)&&(op2.Typ == T_Double))
        {
            resul.value.d = pow(op1.value.d, op2.value.d);
            resul.Typ = T_Double;
            printf("T_Double\n");
            printf("%g\n",resul.value.d);
        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        break;
    /* *********************** I_ASSIGN *********************** */
    case 15:
        printf("I_ASSIGN\n");
        /*if((Iop1.str=='\0')||(Iop2.str=='\0')||(Iresult.str=='\0'))
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
        if (op1.Typ == T_Double)
        {
            resul.value.d = op1.value.d;
            resul.Typ = T_Double;
            printf("T_Double\n");
            printf("%f\n",resul.value.d);
        }else if (op1.Typ == T_Bool)
        {
            resul.value.b = op1.value.b;
            resul.Typ = T_Bool;
            printf("T_Bool\n");
            printf("%i\n",resul.value.b);
        }else if (op1.Typ == T_String)
        {
            resul.value.s.str = op1.value.s.str;
            resul.Typ = T_String;
            printf("T_String\n");
            printf("%s\n",resul.value.s.str);
        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        break;
    /* Logické operace */
    /* *********************** I_MORE *********************** */
    case 20:
        printf("I_MORE\n");
       /*if((Iop1.str=='\0')||(Iop2.str=='\0')||(Iresult.str=='\0'))
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
        if ((op1.Typ == T_Double)&&(op2.Typ == T_Double))
        {
                if(op1.value.d > op2.value.d)
                {
                    resul.value.b = true;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }else
                {
                    resul.value.b = false;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }
        }
        else if ((op1.Typ == T_String)&&(op2.Typ == T_String))
        {
                if(strCmpString(&op1.value.s, &op2.value.s) > 0)
                {
                    resul.value.b = true;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }else
                {
                    resul.value.b = false;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }
        }
        else if ((op1.Typ == T_Bool)&&(op2.Typ == T_Bool))
        {
                if(op1.value.b > op2.value.b)
                {
                    resul.value.b = true;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }else
                {
                    resul.value.b = false;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }
        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        break;
    /* *********************** I_LESS *********************** */
    case 21:
        printf("T_LESS\n");
        /*if((Iop1.str=='\0')||(Iop2.str=='\0')||(Iresult.str=='\0'))
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
        if ((op1.Typ == T_Double)&&(op2.Typ == T_Double))
        {
                if(op1.value.d < op2.value.d)
                {
                    resul.value.b = true;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }else
                {
                    resul.value.b = false;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }

        }
        else if ((op1.Typ == T_String)&&(op2.Typ == T_String))
        {
                if(strCmpString(&op1.value.s, &op2.value.s) < 0)
                {
                    resul.value.b = true;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }else
                {
                    resul.value.b = false;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }
        }
        else if ((op1.Typ == T_Bool)&&(op2.Typ == T_Bool))
        {
                if(op1.value.b < op2.value.b)
                {
                    resul.value.b = true;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }else
                {
                    resul.value.b = false;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }
        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        break;
    /* *********************** I_MORE_EQUAL *********************** */
    case 22:
        printf("T_MORE_EQUAL\n");
        /*if((Iop1.str=='\0')||(Iop2.str=='\0')||(Iresult.str=='\0'))
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
        if ((op1.Typ == T_Double)&&(op2.Typ == T_Double))
        {
                if(op1.value.d >= op2.value.d)
                {
                    resul.value.b = true;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }else
                {
                    resul.value.b = false;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }

        }
        else if ((op1.Typ == T_String)&&(op2.Typ == T_String))
        {
                if(strCmpString(&op1.value.s, &op2.value.s) >= 0)
                {
                    resul.value.b = true;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }else
                {
                    resul.value.b = false;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }
        }
        else if ((op1.Typ == T_Bool)&&(op2.Typ == T_Bool))
        {
                if(op1.value.b >= op2.value.b)
                {
                    resul.value.b = true;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }else
                {
                    resul.value.b = false;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }
        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        break;
    /* *********************** I_LESS_EQUAL *********************** */
    case 23:
        printf("T_LESS_EQUAL\n");
       /*if((Iop1.str=='\0')||(Iop2.str=='\0')||(Iresult.str=='\0'))
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
        if ((op1.Typ == T_Double)&&(op2.Typ == T_Double))
        {
                if(op1.value.d <= op2.value.d)
                {
                    resul.value.b = true;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }else
                {
                    resul.value.b = false;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }

        }
        else if ((op1.Typ == T_String)&&(op2.Typ == T_String))
        {
                if(strCmpString(&op1.value.s, &op2.value.s) <= 0)
                {
                    resul.value.b = true;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }else
                {
                    resul.value.b = false;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }
        }
        else if ((op1.Typ == T_Bool)&&(op2.Typ == T_Bool))
        {
                if(op1.value.b <= op2.value.b)
                {
                    resul.value.b = true;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }else
                {
                    resul.value.b = false;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }
        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        break;
    /* *********************** I_EQUAL *********************** */
    case 24:
        printf("T_EQUAL\n");
        /*if((Iop1.str=='\0')||(Iop2.str=='\0')||(Iresult.str=='\0'))
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
        if ((op1.Typ == T_Double)&&(op2.Typ == T_Double))
        {
                if(op1.value.d == op2.value.d)
                {
                    resul.value.b = true;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }else
                {
                    resul.value.b = false;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }

        }
        else if ((op1.Typ == T_String)&&(op2.Typ == T_String))
        {
                if(strCmpString(&op1.value.s, &op2.value.s) == 0)
                {
                    resul.value.b = true;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }else
                {
                    resul.value.b = false;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }
        }
        else if ((op1.Typ == T_Bool)&&(op2.Typ == T_Bool))
        {
                if(op1.value.b == op2.value.b)
                {
                    resul.value.b = true;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }else
                {
                    resul.value.b = false;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }
        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        break;
    /* *********************** I_NOT_EQUAL *********************** */
    case 25:
        printf("T_NOT_EQUAL\n");
        /*if((Iop1.str=='\0')||(Iop2.str=='\0')||(Iresult.str=='\0'))
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
        if ((op1.Typ == T_Double)&&(op2.Typ == T_Double))
        {
                if(op1.value.d != op2.value.d)
                {
                    resul.value.b = true;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }else
                {
                    resul.value.b = false;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }

        }
        else if ((op1.Typ == T_String)&&(op2.Typ == T_String))
        {
                if(strCmpString(&op1.value.s, &op2.value.s) != 0)
                {
                    resul.value.b = true;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }else
                {
                    resul.value.b = false;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }
        }
        else if ((op1.Typ == T_Bool)&&(op2.Typ == T_Bool))
        {
                if(op1.value.b != op2.value.b)
                {
                    resul.value.b = true;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }else
                {
                    resul.value.b = false;
                    resul.Typ = T_Bool;
                    printf("T_Bool\n");
                    printf("%i\n",resul.value.b);
                }
        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        break;

    /* Vestavìné funkce */
    /* *********************** I_FIND *********************** */
    case 30:
        printf("I_FIND\n");
        /*if((Iop1.str=='\0')||(Iop2.str=='\0')||(Iresult.str=='\0'))
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
        if ((op1.Typ == T_String)&&(op2.Typ == T_String))
        {
            resul.value.d = find(&op1.value.s, &op2.value.s);
            resul.Typ = T_Double;
            printf("T_Double\n");
            printf("%g\n",resul.value.d);
        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        break;
    /* *********************** I_SORT *********************** */
    case 31:
        printf("I_SORT\n");
        /*if((Iop1.str=='\0')||(Iresult.str=='\0'))
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
        if (op1.Typ == T_String)
        {
            resul.value.s = sort(&op1.value.s);
            resul.Typ = T_String;
            printf("T_String\n");
            printf("%s\n",resul.value.s.str);
        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        break;
    /* *********************** I_LENGTH *********************** */
    case 32:
        printf("I_LENGTH\n");
        /*if((Iop1.str=='\0')||(Iresult.str=='\0'))
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
        if (op1.Typ == T_String)
        {
            resul.value.d = lenght(&op1.value.s);
            resul.Typ = T_Double;
            printf("T_Double\n");
            printf("%g\n",resul.value.d);
        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        break;
    /* *********************** I_COPY *********************** */
    case 33:
         printf("I_COPY\n");
       /*if((Iop1.str=='\0')||(Iop2.str=='\0')||(Iresult.str=='\0'))
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
        if ((op1.Typ == T_Double)&&(op2.Typ == T_Double)&&(resul.Typ == T_String))
        {
            resul.value.s = copy(&resul.value.s, op1.value.d, op2.value.d);
            resul.Typ = T_String;
            printf("T_String\n");
            printf("%s\n",resul.value.s.str);
        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        break;
    /* *********************** I_WRITE *********************** */
    case 34:
        printf("I_WRITE\n");
        /*if(Iop1.str=='\0')
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
        if (op1.Typ == T_String)
        {
            printf("%s",op1.value.s.str);
        }
        else if (op1.Typ == T_Double)
        {
            printf("%g",op1.value.d);
        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        break;
    /* *********************** I_READ *********************** */
    case 35:
        printf("I_READ\n");
        /*if(Iresult.str=='\0')
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
        if (resul.Typ == T_String)
        {
            char c;
                while ((c = getchar()))
                {
                if ((c != 10)&&(c != 13))
                    strAddChar(&resul.value.s,c);
                else
                    break;
                }
                resul.Typ = T_String;
                printf("T_String\n");
                printf("%s\n",resul.value.s.str);

        }
        else if (resul.Typ == T_Double)
        {
            if (scanf("%lf",&resul.value.d) == 1)
            {
                resul.Typ = T_Double;
                printf("T_Double\n");
                printf("%g",resul.value.d);
            }
            else
            {
            error(x,RUNN_IN_ERR,xx);
            }
        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        break;

    /* Skoky */
    /* *********************** I_LABEL *********************** */
    case 40:
        printf("I_LABEL\n");
        break;
    /* *********************** I_FJUMP *********************** */
    case 41:
        printf("I_FJUMP\n");
        /*if((Iop1.str=='\0')||(Iop2.str=='\0'))
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
        if((op1.Typ == T_Bool)&&(op1.value.b == false))
        {
            printf("T_Bool\n");
            *Ipoz = trojfindlab(Iop1);
        }
        else if ((op1.Typ == T_Double)&&(op1.value.d == 0))
        {
            printf("T_Double\n");
            *Ipoz = trojfindlab(Iop1);
        //else if((op2.Typ != null )...
        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        //if (Iop2.str = "false");
        if (f == 0){
                *Ipoz = trojfindlab(Iop1);
        f = 1;
        }else{
                *Ipoz = 0;
        f = 0;
        }

        break;
    /* *********************** I_JUMP *********************** */
    case 42:
        printf("I_JUMP\n");
        /*if(Iop1.str=='\0')
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
        if (op1.Typ == T_Double)
        {
            printf("I_Jump\n");
            *Ipoz = trojfindlab(Iop1);
        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        if (f == 0){
                *Ipoz = trojfindlab(Iop1);
        f = 1;
        }else{
                *Ipoz = 0;
        f = 0;
        }
        break;
    /* *********************** I_JUMP_FCE *********************** */
     case 43:
         printf("I_JUMP_FCE\n");
        /*if(Iop1.str=='\0')
        {
            error(st,RUNN_NOIN_ERR,kk);
        }
        if (op1.Typ == T_Double)
        {
            printf("I_Jump\n");
            *Ipoz = trojfindfce(Iop1);
        }
        else
        {
            error(x,OTHER_ERR,xx);
        }*/
        *Ipoz = trojfindfce(Iop1);
        break;
    /* *********************** I_FCE_BEGIN *********************** */
    case 44:
        printf("I_FCE_BEGIN\n");
        // vytvorit ramec
        break;
     /* *********************** I_FCE_END *********************** */
    case 45:
        printf("I_FCE_END\n");
        // zrusit ramec
        break;
    }
    //else
    //error(x,OTHER_ERR,xx);
}
