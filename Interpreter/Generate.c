#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>
#include "Generate.h"

/*tData *tData_new ()
{
  tData *d = malloc (sizeof (tData));
  d->inst = 0;
  d->op1.str = "";
  d->op1.str = "";
  d->op1.str = "";
  return d;
}*/

int main()
{
    trojinit();
    int inst = 1;
    string op1 ;
    strInit(&op1);
    string op2 ;
    strInit(&op2);
    string result ;
    strInit(&result);

    op1.str = "a";
    op2.str = "b";
    result.str = "c";
    Generate(inst, op1, op2, result);

    inst=21;
    op1.str = "c";
    op2.str = "b";
    result.str = "d";
    Generate(inst, op1, op2, result);

    inst=5;
    op1.str = "";
    op2.str = "";
    result.str = "";
    Generate(inst, op1, op2, result);

    inst=21;
    op1.str = "e";
    op2.str = "d";
    result.str = "x";
    Generate(inst, op1, op2, result);

    inst=20;
    op1.str = "jff";
    op2.str = "dgd";
    result.str = "yjj";
    Generate(inst, op1, op2, result);

    inst=5;
    op1.str = "ghf";
    op2.str = "mn";
    result.str = "rt";
    Generate(inst, op1, op2, result);

    inst=20;
    op1.str = "";
    op2.str = "";
    result.str = "";
    Generate(inst, op1, op2, result);


    string o;
    strInit(&o);
    o.str="L9";


    trojvypis();

    //trojfind(o);

    return 0;
}

void Generate(int Ginst, string Gop1, string Gop2, string Gresult)
{
    if ((Ginst > 0)&&(Ginst < 10))
    {
        trojinsert(Ginst, Gop1, Gop2, Gresult);
        //printf("tady %i\n",Ginst);
    }
    else
    {
        trojinsert(Ginst, Gop1, Gop2, Gresult);
        //printf("tam %i\n",Ginst);
    }

}
