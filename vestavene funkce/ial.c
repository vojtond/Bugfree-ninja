#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int lenght(string *str)														//Funkce, která vrací délu řetězce.
{
    return str->length;														//Vracíme délku řetězce ze struktury string.
}

string copy(string *str, int i, int j)										//Funkce vrací podřetězec z řetězce str od i o délce j.
{
    string strback;															//Pomocná proměnná typu string.
	int p;																	//Řídící proměnná for cyklu.
	
    if (i < 1)																//Pokud je i menší než 1, přiřadíme mu hodnotu 1, aby jsme nepřistupovali mimo string.
    {
        i=1;
    }
    if ((i+j-1) > str->length)												//Pokud je j větší než délka řetězce, upravíme jej, aby jsme nekopírovali prvky za rozsahem stringu.												
    {
        j=str->length-i+1;
    }
    																	
    strInit(&strback);														//Inicializace stringu.
    for (p = 0; p < j; p++)													//For cyklus o j opakováních.
    {
        strAddChar(&strback,str->str[i+p-1]);								//Jednotlivé znaky přidáváme do strback.
    }
    return strback;															//Vracíme string.
}

int find(string *str, string *vzorek)										//Funkce která najde vzorek v str.
{
    int Fail[str->length];													//Pole Fail o délce str->lenght.
    int TInd = 0;															//Index prvku v str.
    int PInd = 0;															//Index prvku ve vzorku.
    int k,r;																//Pomocné proměnné.
	
    Fail[0] = -1;															//Do prvního prvku pole si přiřadíme -1.
    for (k = 1; k <= vzorek->length; k++)															
    {
        r = Fail[k-1];														//Do r si přiřadíme hodnotu z prvku k-1.
        while ((r > -1) && (vzorek->str[r] != vzorek->str[k-1]))			//Procházíme vzorek a zjišťujeme na kterou pozici se můžeme vrátit při neshodě na každé pozici.
        {
            r = Fail[r];
        }
        Fail[k] = r+1;
    }



    while ((TInd < str->length) && (PInd < vzorek->length))					//Samotné vyhledávání podřetězce.
    {
        if ((PInd == -1) || (str->str[TInd] == vzorek->str[PInd]))			//Pokud se str na indexu TInd rovná vzorku na indexu PInd.. 
        {

            TInd++;															//Inkrementujeme obě počítadla.
            PInd++;
        }
        else
        {
            PInd = Fail[PInd];												//Pokud se nerovná, vracíme se na index, který je uložem v poli Fail.

        }
    }
        if (PInd > vzorek->length-1)										//Ppokud je PInd větší než délka vzorku -1, prošli jsme vzorek až na konec a mám eshodu.
        {
            return TInd-vzorek->length+1;									//Vracíme index, na kterém jsme našli podřetězec.
        }
        else
            return 0;														//Nenašli jsme podřetězec, vracíme 0.


}


string sort(string *str)
{
    int step = str->length / 2;												//Proměnná v které máme uložený krok, pro procházení řetězce.
    int i, j;																//Pomocné proměnné pro průchod.
    char c;

    while (step > 0)														//Procházíme, dokud je krok větší než 0.
    {
        for (i = step; i < str->length; i++)								
        {
            j = i-step;														//Posun na další prvek.
            while ((j >= 0) && (str->str[j] > str->str[j+step]))			//Bubble sort pro prvky vzdálené o step.
            {
                c=str->str[j];												//Výměna dvou prvku.
                str->str[j] = str->str[j+step];
                str->str[j+step] = c;
                j=j-step;													//Snížení indexu o krok.
            }
        }
        step = step / 2;													//Po všech průchodech vždy rozpůlíme krok.
    }
    return *str;															//Vracíme seřazený string.
}






