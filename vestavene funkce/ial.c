#include <stdio.h>
#include <stdlib.h>
#include "str.h"
//#include "parser.h"

int lenght(string *str)
{
    return str->length;
}

int copy(string *str, int i, int j, string *strback)
{
    if ((i < 1) || ((i+j-1) > str->length))
    {
        return 0;
    }
    int p;
    strInit(strback);
    for (p = 0; p < j; p++)
    {
        strAddChar(strback,str->str[i+p-1]);
    }
    return 0;
}

int find(string *str, string *vzorek, int *ind)
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
        //printf("%i\n",Fail[k]);
    }



    while ((TInd < str->length) && (PInd < vzorek->length))
    {
        if ((PInd == -1) || (str->str[TInd] == vzorek->str[PInd]))
        {

            TInd++;
            PInd++;
            printf("%i\n",PInd);
        }
        else
        {
            PInd = Fail[PInd];

        }
    }
        if (PInd > vzorek->length-1)
        {
            *ind = TInd-vzorek->length+1;
            return 1;
        }
        else
            return 0;


}




int main()
{
    int k;
    int ind = 0;
    string str;
    string vzorek;

    strInit(&str);
    strInit(&vzorek);

    strAddChar(&str,'a');
    strAddChar(&str,'a');
    strAddChar(&str,'a');
    strAddChar(&str,'a');
    strAddChar(&str,'b');
    strAddChar(&str,'b');
    strAddChar(&str,'a');
    strAddChar(&str,'a');

    strAddChar(&vzorek,'a');
    strAddChar(&vzorek,'b');
    k = find(&str,&vzorek,&ind);
    if (k>0)
        printf("nasel, pozice je %i\n",ind);
    else
        printf("nenasel\n");

    strFree(&str);
    strFree(&vzorek);
    return 0;
}




