/*!!prosim komenty bez diakritiky, blbne kodovani*/
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
string attr;
FILE *soubor;
  SToken *token;
int gtoken(FILE *F, SToken *token ){


    strFree(token->stri);

     if ((strInit(token->stri))==1)
        {
            printf("nepovedlo se vytvorit retezec\n");
        }


     get_token(soubor,token);

     printf("\nJe to typ: %i\n",token->type);
     printf("String je: %s\n",strGetStr(token->stri));
}
int main()
{

    token=malloc(sizeof(SToken));
    token->stri=malloc(sizeof(string));
    token->type=-1;
    strInit(&attr);
/* soubor = fopen("text.txt", "r");

    while (token->type != 3)
    {
        if ((strInit(token->stri))==1)
        {
            printf("nepovedlo se vytvorit retezec\n");
        }

        gtoken(soubor,token);
        printf("\nJe to typ: %i\n",token->type);
        printf("Charnum je: %f\n",token->charnum);
        printf("String je: %s\n",strGetStr(token->stri));
        printf("**************************************\n");
        strFree(token->stri);
        //printf("String je: %s\n",token->stri);
    }

    fclose(soubor);*/
     soubor = fopen("text.txt", "r");





    printf ("%i",START());
    free(token);
    fclose(soubor);

    return 4;
}
int START (){





    if ((token->type == KEY_BEGIN) || (token->type ==KEY_VAR ) || (token->type == KEY_FUNCTION)) {
      printf("start2\n");

      if ((GLOBDEK()) && (FUNC()) && (SLOZ())) {
            printf("start3\n");

            if (token->type==TP_DOT){
                 gtoken(soubor,token);
                return 1;
            }
        }
    }
return 0;
}

/*<FUNC>		->	eps*/
/*<FUNC> 		->	function id  (<ARG>) : <TYPE> <FORWARD>*/
int FUNC (){

   if ((token->type == KEY_BEGIN)){
        printf("FUNC2\n");
        return 1;

   }else {
   if ((token->type==KEY_FUNCTION)){
        printf("FUNC3\n");
       gtoken(soubor,token);
       if (token->type==TP_IDENT){
            gtoken(soubor,token);
            if (token->type==TP_LBRA){
                gtoken(soubor,token);
                if (ARG()) {
                    if (token->type==TP_RBRA){
                        gtoken(soubor,token);
                        if (token->type==TP_COL){
                            gtoken(soubor,token);

                                    return TYPE() && FORWAR();
                        }
                    }

                }
            }
        }
    }
   }
           printf("FUNC3\n");

    return 0;
}


/*<FORWARD> 	->	; <DEK> <SLOZ> ; <FUNC>*/
/*<FORWARD>	->	forward ; <FUNC>*/
int FORWAR (){
    if (token->type==ST_SEM){
        gtoken(soubor,token);
        if ((DEK())&& (SLOZ())) {
            if (token->type==ST_SEM){
                gtoken(soubor,token);
                return FUNC();
            }
        }
    }else{
        if (token->type==KEY_FORWARD){
            gtoken(soubor,token);
            if (token->type==ST_SEM){
                gtoken(soubor,token);
                return FUNC();
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
            gtoken(soubor,token);
            if (token->type==TP_COL){
                gtoken(soubor,token);
                return TYPE () && ARGDAL();
            }
        }
    }
    return 0;
}

/*<ARGDAL> 	-> 	; id : <TYPE> <ARGDAL>*/
/*<ARGDAL> 	-> 	eps*/
int ARGDAL (){
     if (token->type==TP_RBRA){
        return 1;
    }else{
        if (token->type==ST_SEM){
            gtoken(soubor,token);
            if (token-> type==TP_IDENT){
                gtoken(soubor,token);
                if (token->type==TP_COL){
                    gtoken(soubor,token);
                    return TYPE() && ARGDAL();
                }
            }
        }
    }
    return 0;
}

/*<CYKLUS>	->	while <VYRAZ> do  <SLOZ>   */
int CYKLUS (){
    if (token->type==KEY_WHILE){
        gtoken(soubor,token);
        if(VYRAZ()){
            if (token->type==KEY_DO)
                gtoken(soubor,token);
                return SLOZ();
        }

    }

return 0;
}

/*<KDYZ>		->  	if <VYRAZ> then  <SLOZ> <ELSE> */
int KDYZ (){
    if (token->type==KEY_IF){
        gtoken(soubor,token);
        if(VYRAZ()){
            if (token->type==KEY_THEN){
                gtoken(soubor,token);
                if (SLOZ()){
                    return ELSEP();
                }
            }
        }
    }
return 0;
}

/*<ELSE>		->  	else  <SLOZ>*/
/*<ELSE>		-> 	eps*/
int ELSEP (){
    if ((token->type==TP_IDENT)||(token->type==KEY_WHILE)|| (token->type==KEY_IF)||(token->type==ST_SEM)
    ||(token->type==KEY_READLN)||(token->type==KEY_WRITE)||(token->type==KEY_BEGIN)||(token->type==KEY_END)){

       return 1;
    }else {
        if (token->type==KEY_ELSE){
            gtoken(soubor,token);
            return SLOZ();
        }
    }
return 0;
}

//<SEKVENCE>	-> 	<POKYN> <SEKVENCE>
//sEKVENCE>	->	eps
//int SEKVENCE (){
//return 0;
//}

/*<POKYN>		->	<CYKLUS>*/
/*<POKYN>		->	<KDYZ>*/
/*<POKYN>		->	<PRIKAZ>*/
/*<POKYN>		->	READLN(id) */
/*<POKYN>		->	WRITE( <VYPIS>)	*/
/*<POKYN>		->	<SLOZ> */
int POKYN (){
  switch (token->type ){
    case TP_IDENT:
        gtoken(soubor,token);
        return PRIKAZ();
    break;
    case KEY_WHILE:
        gtoken(soubor,token);
        return CYKLUS();
    break;
    case KEY_IF:
        gtoken(soubor,token);
        return KDYZ();
    break;
    case KEY_READLN:
        gtoken(soubor,token);
        if (token->type==TP_LBRA){
          gtoken(soubor,token);
          if (token->type==TP_IDENT){
            gtoken(soubor,token);
            if (token->type==TP_RBRA){
                return 1;
            }
          }
        }
    break;
    case KEY_WRITE:
        gtoken(soubor,token);
        if (token->type==TP_LBRA){
            gtoken(soubor,token);
            if (VYPIS()){
                if (token->type==TP_RBRA){
                    gtoken(soubor,token);
                    return 1;
                }
            }
        }
    break;
    case KEY_BEGIN:
        gtoken(soubor,token);
        return SLOZ();
    break;


  }

return 0;
}

/*<SLOZ>		->	begin	<PRVNI> end*/
int SLOZ (){
     if (token->type == KEY_BEGIN){
        printf("SLOZ\n");
                printf("String je: %s\n",strGetStr(token->stri));

                       printf("\nJe to typ: %i\n",token->type);

       gtoken(soubor,token);
               printf("String je: %s\n",strGetStr(token->stri));

               printf("\nJe to typ: %i\n",token->type);

       if (PRVNI()){
            printf("SLOZ2\n");
            if (token->type== KEY_END){
                gtoken(soubor,token);
                return 1;
            }
       }
     }
return 0;
}

/*<PRVNI>		->	eps*/
/*<PRVNI>		-> 	<POKYN> <DALSI>*/
int PRVNI (){
    printf("PRVNI0\n");
   // printf("\nJe to typ: %i\n",token->type);
    if (token->type==KEY_END){
        printf("PRVNI\n");
        return 1;

    }else {
        if ((token->type==TP_IDENT)||(token->type==KEY_WHILE)|| (token->type==KEY_IF)
        ||(token->type==KEY_READLN)||(token->type==KEY_WRITE)||(token->type==KEY_BEGIN)){
            gtoken(soubor,token);
            return POKYN() && DALSI();

        }
    }



return 0;
}

/*<DALSI>		->	eps*/
/*<DALSI>		->	; <POKYN> <PRVNI>*/
int DALSI (){
	if (token->type==KEY_END){

		return 1;
	}else {
		if (token->type==TP_SEM){
			gtoken(soubor,token);
			return POKYN() && PRVNI();
		}

	}

return 0;
}
/*<PRIKAZ>	-> 	id := <VYRAZ>*/
int PRIKAZ (){
	if (token->type==TP_IDENT) {
		gtoken(soubor,token);
		if (token->type==TP_SGNMNT){
			gtoken(soubor,token);
			return VYRAZ();
		}
	}
return 0;
}

/*<GLOBDEK>		->	var id : <TYPE> ; <GLOBDEKDAL>*/
/*<GLOBDEK>		->	eps*/
/*----asi vyreseno---asi pouze na deklaraci globalnich prom.*/
/*----asi vyreseno---prusvih c. 1 pokud bude deklarace lokalnich promennych, pak eps nemuze zacinat na function, ale pouze na begin, vypada to na dalsi 4 pravidla*/
int GLOBDEK (){
	if ((token->type==KEY_FUNCTION)|| (token->type==KEY_BEGIN)){
        printf("GLOBDEK\n\n");
		return 1;
	}else {
		if ((token->type==KEY_VAR)){
			gtoken(soubor,token);
			if ((token->type==TP_IDENT)){
				gtoken(soubor,token);
				if (token->type==TP_COL){
					gtoken(soubor,token);
					if (TYPE()){
						if (token->type==TP_SEM){
							gtoken(soubor,token);
							return DEKDAL();
						}
					}

				}
			}
		}
	}


return 0;
}

/*<GLOBDEKDAL>	->	id : <TYPE> ;  <GLOBDEKDAL>*/
/*<GLOBDEKDAL>	->	eps*/
int GLOBDEKDAL (){
	if ((token->type==KEY_FUNCTION)|| (token->type==KEY_BEGIN)){
		return 1;
	}else {
		if ((token->type==TP_IDENT)){
			gtoken(soubor,token);
			if (token->type==TP_COL){
				gtoken(soubor,token);
				if (TYPE()){
					if (token->type==TP_SEM){
						gtoken(soubor,token);
						return DEKDAL();
					}
				}

			}
		}
	}
return 0;
}

/*<TYPE>		->	real*/
/*<TYPE>		->	string*/
/*<TYPE>		->	integer*/
/*<TYPE>		->	boolean*/
int TYPE (){
	switch(token->type){
		case KEY_REAL:
			gtoken(soubor,token);
			return 1;
		break;
		case KEY_STRING:
			gtoken(soubor,token);
			return 1;
		break;
		case KEY_INTEGER:
			gtoken(soubor,token);
			return 1;
		break;
		case KEY_BOOLEAN:
			gtoken(soubor,token);
			return 1;
		break;
	}
return 0;
}
/*prusvih c.2 co  s termama? bud cast v závorce resit jako vyraz nebo docasne promenne, konzultace Hublik*/
/*<VYPIS>		->	id <DVYPIS>*/
int VYPIS (){
	if (token->type==TP_IDENT){
			gtoken(soubor,token);
			return DVYPIS();
	}
return 0;
}

/*<DVYPIS>	->	, <VYPIS>*/
/*<DVYPIS>	->	eps*/
/*mara asi nema nadefinovanou carku, zeptat se*/
int DVYPIS (){
	if (token->type==TP_RBRA){
		return 1;
	}else {
		if (token->type==TP_COMMA){
			return VYPIS();
		}
	}
return 0;
}
/*<DEK>		->	var id : <TYPE> ; <DEKDAL>*/
/*<DEK>		->	eps*/
int DEK (){
	if ( (token->type==KEY_BEGIN)){
		return 1;
	}else {
		if ((token->type==KEY_VAR)){
			gtoken(soubor,token);
			if ((token->type==TP_IDENT)){
				gtoken(soubor,token);
				if (token->type==TP_COL){
					gtoken(soubor,token);
					if (TYPE()){
						if (token->type==TP_SEM){
							gtoken(soubor,token);
							return DEKDAL();
						}
					}

				}
			}
		}
	}


return 0;
}
/*<DEKDAL>	->	id : <TYPE> ;  <DEKDAL>*/
/*<DEKDAL>	->	eps*/
int DEKDAL (){
	if ( (token->type==KEY_BEGIN)){
		return 1;
	}else {
		if ((token->type==TP_IDENT)){
			gtoken(soubor,token);
			if (token->type==TP_COL){
				gtoken(soubor,token);
				if (TYPE()){
					if (token->type==TP_SEM){
						gtoken(soubor,token);
						return DEKDAL();
					}
				}

			}
		}
	}
return 0;
}

int VYRAZ(){
return 1;/*simulace eps pravidla pro vyraz, jakmile, hubli, zacnes pravidlo rozvijet, zmen na 0*/
}









