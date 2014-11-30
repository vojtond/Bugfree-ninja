#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Interpret.h"

int main()
{
    Interpret();
    return 0;
}


void Interpret()
{
tOperation oper;
int *result;

tOperator op1, op2, resul;

op1.Typ = T_String;
op2.Typ = T_String;
op1.value.s = "AB";
op2.value.s = "BA";

oper = I_EQUAL;
result = 1;

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
            printf("%f\n",resul.value.d);
        }
        else
        {
            //error=
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
            printf("%f\n",resul.value.d);
        }
        else
        {
            //error=
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
            printf("%f\n",resul.value.d);
        }
        else
        {
            //error=
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
            printf("%f\n",resul.value.d);
        }
        else
        {
            //error=
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
            printf("%f\n",resul.value.d);
        }
        else
        {
            //error=
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
            resul.value.s = op1.value.s;
            resul.Typ = T_String;
            printf("T_String\n");
            printf("%s\n",resul.value.s);
        }
        else
        {
            //error=
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
                if(strcmp(op1.value.s, op2.value.s) > 0)
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
                if(strcmp(op1.value.s, op2.value.s) < 0)
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
                if(strcmp(op1.value.s, op2.value.s) >= 0)
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
                if(strcmp(op1.value.s, op2.value.s) <= 0)
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
                if(strcmp(op1.value.s, op2.value.s) == 0)
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
                if(strcmp(op1.value.s, op2.value.s) != 0)
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
            resul.value.d = find(op1.value.s, op2.value.s);
            resul.Typ = T_Double;
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
            resul.value.s = sort(op1.value.s);
            resul.Typ = T_String;
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
            resul.value.d = lenght(op1.value.s);
            resul.Typ = T_Double;
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
            resul.value.s = copy(resul.value.s, op1.value.d, op2.value.d);
            resul.Typ = T_String;
        }
        else
        {
            //error=
            return;
        }
        break;

    /* Skoky */
    case I_LABEL:
        break;

    case I_GOTO:
        break;

    case I_JUMP:
        break;

    case I_FJUMP:
        break;

    case I_TJUMP:
        break;
    }

}
