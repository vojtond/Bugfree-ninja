#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Interpret.h"
#include "ial.h"


int main()
{
    Interpret();
    return 0;
}


void Interpret()
{
tOperation oper;
int *result = 1;

tOperator op1, op2, resul;

op1.Typ = T_String;
//op1.value.d = 3;
strInit(&op1.value.s);
strAddChar(&op1.value.s,'m');
strAddChar(&op1.value.s,'a');
strAddChar(&op1.value.s,'m');
strAddChar(&op1.value.s,' ');
//op1.value.s.str = "ma";
//op1.value.s.length = 2;

op2.Typ = T_String;
//op2.value.d = 3;
strInit(&op2.value.s);
strAddChar(&op2.value.s,'e');
strAddChar(&op2.value.s,'r');
strAddChar(&op2.value.s,10);
strAddChar(&op2.value.s,'n');
//op2.value.s.str = "a";
//op2.value.s.length = 1;

resul.Typ = T_String;
//resul.value.s.str = "KOLOTOC";
//resul.value.s.length = 7;

char c;
oper = I_ADD;

    switch(oper)
    {
    /* Aritmetické operace */
    case I_ADD:
        printf("I_ADD\n");
        if(result == NULL)
        {
            break;
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
                //error=x;
                return;
            }

        }
        else
        {
            //error=4
            return;
        }
        break;

    case I_SUB:
        printf("I_SUB\n");
        if(result == NULL)
        {
            break;
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
            //error=4
            return;
        }
        break;

    case I_MUL:
        printf("I_MUL\n");
        if(result == NULL)
        {
            break;
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
            //error=4
            return;
        }
        break;

    case I_DIV:
        printf("I_DIV\n");
        if(result == NULL)
        {
            break;
        }
        if ((op1.Typ == T_Double)&&(op2.Typ == T_Double))
        {
            resul.value.d = op1.value.d / op2.value.d;
            resul.Typ = T_Double;
            printf("T_Double\n");
            printf("%g\n",resul.value.d);
        }
        else
        {
            //error=4
            return;
        }
        break;

    case I_POW:
        printf("I_POW\n");
        if(result == NULL)
        {
            break;
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
            //error=4
            return;
        }
        break;

    case I_ASSIGN:
        printf("I_ASSIGN\n");
        if(result == NULL)
        {
            break;
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
            //error=4
            return;
        }
        break;

    /* Logické operace */
    case I_MORE:
        printf("I_MORE\n");
        if(result == NULL)
        {
            break;
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
            //error=
            return;
        }
        break;

    case I_LESS:
        printf("T_LESS\n");
        if(result == NULL)
        {
            break;
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
            //error=
            return;
        }
        break;

    case I_MORE_EQUAL:
        printf("T_MORE_EQUAL\n");
        if(result == NULL)
        {
            break;
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
            //error=
            return;
        }
        break;

    case I_LESS_EQUAL:
        printf("T_LESS_EQUAL\n");
        if(result == NULL)
        {
            break;
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
            //error=
            return;
        }
        break;

    case I_EQUAL:
        printf("T_EQUAL\n");
        if(result == NULL)
        {
            break;
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
            //error=
            return;
        }
        break;

    case I_NOT_EQUAL:
        printf("T_NOT_EQUAL\n");
        if(result == NULL)
        {
            break;
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
            //error=
            return;
        }
        break;

    /* Vestavìné funkce */
    case I_FIND:
        printf("I_FIND\n");
        if(result == NULL)
        {
            break;
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
            //error=
            return;
        }
        break;

    case I_SORT:
        printf("I_SORT\n");
        if(result == NULL)
        {
            break;
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
            //error=
            return;
        }
        break;

    case I_LENGTH:
        printf("I_LENGTH\n");
        if(result == NULL)
        {
            break;
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
            //error=
            return;
        }
        break;

    case I_COPY:
         printf("I_COPY\n");
        if(result == NULL)
        {
            break;
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
            //error=
            return;
        }
        break;

        case I_WRITE:
        printf("I_Write\n");
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
            //error=4
            return;
        }
        break;

        case I_READ:
        printf("I_Read\n");
        if(result == NULL)
        {
            break;
        }
        if (resul.Typ == T_String)
        {
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
                //error = 6
                return;
            }
        }
        else
        {
            //error=4
            return;
        }
        break;

    /* Skoky */
    case I_LABEL:
        printf("I_Label\n");
        break;

    case I_GOTO:
        printf("I_Goto\n");
        break;

    case I_JUMP:
            printf("I_Jump\n");
            //pozice(xxx);
        break;

    case I_FJUMP:
        printf("I_Fjump\n");
        if((op1.Typ == T_Bool)&&(op1.value.b == false))
            printf("T_Bool\n");
            //pozice(xxx);
        else if ((op1.Typ == T_Double)&&(op1.value.d == 0))
            printf("T_Double\n");
            //pozice(xxx);
        break;

    case I_TJUMP:
        printf("I_Tjump\n");
        if((op1.Typ == T_Bool)&&(op1.value.b == true))
            printf("T_Bool\n");
            //pozice(xxx);
        else if ((op1.Typ == T_Double)&&(op1.value.d == 1))
            printf("T_Double\n");
            //pozice(xxx);
        break;
    }
    //error=9
}
