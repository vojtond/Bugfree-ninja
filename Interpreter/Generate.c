#include <stdio.h>
#include <stdlib.h>
#include "Generate.h"

void Generate(int Ginst, string Gop1, string Gop2, string Gresult)
{
    if ((Ginst >= 10)&&(Ginst <= 49))
    {
        trojinsert(Ginst, Gop1, Gop2, Gresult);
    }
    else
    {
        printf("Neznama instrukce %i\n",Ginst);
    }

}
