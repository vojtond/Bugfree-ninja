#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "scanner.h"
FILE *soubor;
  SToken *token;

int main()
{

    token=malloc(sizeof(SToken));
    token->stri=malloc(sizeof(string));
    token->type=-1;


  /*  while (token->type != 3)
    {
        if ((strInit(token->stri))==1)
        {
            printf("nepovedlo se vytvoøit øetìzec\n");
        }

        get_token(soubor,token);
        printf("\nJe to typ: %i\n",token->type);
        printf("Charnum je: %f\n",token->charnum);
        printf("String je: %s\n",strGetStr(token->stri));
        printf("**************************************\n");
        strFree(token->stri);
        //printf("String je: %s\n",token->stri);
    }

    fclose(soubor);*/
    soubor = fopen("text.txt", "r");
    if ((strInit(token->stri))==1)
        {
            printf("nepovedlo se vytvoøit øetìzec\n");
        }
          if (TYPE())
    printf ("%i",START());
    free(token);
    fclose(soubor);

    return 4;
}
int START (){
    get_token(soubor,token);
    if (1/*(token->type == KEY_BEGIN) || (token->type ==KEY_VAR ) || (token->type == KEY_FUNCTION)*/) {
      if ((DEK()) && (FUNC()) && (SLOZ())) {
            get_token(soubor,token);
            token->type==TP_DOT;
            return 1;
        }
    }
return 0;
}

/*<FUNC>		->	eps*/
/*<FUNC> 		->	function id  (<ARG>) : <TYPE> <FORWARD>*/
int FUNC (){

   if ((1/*token->type == kbegin*/)){

        return 1;

   }else {
   if (1/*(token->type==KEY_FUNCTION)*/){
       get_token(soubor,token);
       if (token->type==TP_IDENT){
            get_token(soubor,token);
            if (token->type==TP_LBRA){
                get_token(soubor,token);
                if (ARG()) {
                    if (token->type==TP_RBRA){
                        get_token(soubor,token);
                        if (token->type==TP_COL){
                            get_token(soubor,token);

                                    return TYPE() && FORWAR();
                        }
                    }

                }
            }
        }
    }
   }
    return 0;
}


/*<FORWARD> 	->	; <DEK> <SLOZ> ; <FUNC>*/
/*<FORWARD>	->	forward ; <FUNC>*/
int FORWAR (){
    if (token->type==ST_SEM){
        get_token(soubor,token);
        if ((DEK())&& (SLOZ)) {
            if (token->type==ST_SEM){
                get_token(soubor,token);
                return FUNC();
            }
        }
    }else{
        if (1/*token->type==KEY_FORWARD*/){
            get_token(soubor,token);
            if (token->type==ST_SEM){
                get_token(soubor,token);
                return FUNC;
            }
        }
    }
return 0;
}

/*<ARG> 		-> 	eps*/
/*<ARG> 		-> 	id : <TYPE> <ARGDAL>*/

int ARG (){
    if (token->type==TP_RBRA){
        return 1;
    }else{
        if (token->type==TP_IDENT){
            get_token(soubor,token);
            if (token->type==TP_COL){
                get_token(soubor,token);
                return TYPE () && ARGDAL();
            }
        }
    }
}

/*<ARGDAL> 	-> 	; id : <TYPE> <ARGDAL>*/
/*<ARGDAL> 	-> 	eps*/
int ARGDAL (){
     if (token->type==TP_RBRA){
        return 1;
    }else{
        if (token->type==ST_SEM){
            get_token(soubor,token);
            if (token-> type==TP_IDENT){
                get_token(soubor,token);
                if (token->type==TP_COL){
                    get_token(soubor,token);
                    return TYPE() && ARGDAL();
                }
            }
        }
    }
}

/*<CYKLUS>	->	while <VYRAZ> do  <SLOZ>   */
int CYKLUS (){
return 0;
}

/*<KDYZ>		->  	if <VYRAZ> then  <SLOZ> <ELSE> */
int KDYZ (){
return 0;
}

/*<ELSE>		->  	else  <SLOZ>*/
/*<ELSE>		-> 	eps*/
int ELSEP (){
return 0;
}

/*<SEKVENCE>	-> 	<POKYN> <SEKVENCE>*/
/*<SEKVENCE>	->	eps*/
int SEKVENCE (){
return 0;
}

/*<POKYN>		->	<CYKLUS>*/
/*<POKYN>		->	<KDYZ>*/
/*<POKYN>		->	<PRIKAZ>*/
/*<POKYN>		->	READLN(id) */
/*<POKYN>		->	WRITE( <VYPIS>)	*/
/*<POKYN>		->	<SLOZ> */
int POKYN (){
return 0;
}

/*<SLOZ>		->	begin	<PRVNI> end*/
int SLOZ (){

    printf("\nsd3\n");
     if (token->charnum == BEGIN){


       get_token(soubor,token);


       if (token->charnum == 53.0){
        printf("\nsd2\n");
        return 1;
       }

     }
return 0;
}

/*<PRVNI>		->	eps*/
/*<PRVNI>		-> 	<POKYN> <DALSI>*/
int PRVNI (){
return 0;
}

/*<DALSI>		->	eps*/
/*<DALSI>		->	; <POKYN> <PRVNI>*/
int DALSI (){
return 0;
}
/*<PRIKAZ>	-> 	id := <VYRAZ>*/
int PRIKAZ (){
return 0;
}

/*<DEK>		->	var id : <TYPE> ; <DEKDAL>*/
/*<DEK>		->	eps*/
int DEK (){
return 0;
}

/*<DEKDAL>	->	id : <TYPE> ;  <DEKDAL>*/
/*<DEKDAL>	->	eps*/
int DEKDAL (){
return 0;
}

/*<TYPE>		->	real*/
/*<TYPE>		->	string*/
/*<TYPE>		->	integer*/
/*<TYPE>		->	boolean*/
int TYPE (){
return 0;
}

/*<BOOLEAN>	->	true*/
/*<BOOLEAN>	->	false*/
int BOOLEANP (){
return 0;
}

/*<VYPIS>		->	id <DVYPIS>*/
int VYPIS (){
return 0;
}

/*<DVYPIS>	->	, <VYPIS>*/
/*<DVYPIS>	->	eps*/
int DVYPIS (){
return 0;
}










