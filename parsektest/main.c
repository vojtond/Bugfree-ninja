/*!!prosim komenty bez diakritiky, blbne kodovani*/

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
string attr;
FILE *soubor;
  int token;
  double hodnota;
  int error;
void gtoken(){
    if ((strInit(&attr))==1)
        {
            printf("nepovedlo se vytvorit retezec\n");
        }
      token=get_token(soubor,&hodnota,&attr,&error);
     printf("String je: %s\n",strGetStr(&attr));
      printf("\nJe to typ: %i\n",token);
      strFree(&attr);
}
int main()
{
    strInit(&attr);
    soubor = fopen("text.txt", "r");
    if (START()) {
        printf("i tyhle hovadiny jsou spravne");

    }
    else{
        printf("to si prehnal kamo! na radku %i mas peknou hovadinu",get_line() );
    }

    fclose(soubor);
    strFree(&attr);
    return 4;
}
int START (){
    gtoken();
    if ((token == KEY_BEGIN) || (token ==KEY_VAR ) || (token == KEY_FUNCTION)) {
      printf("****start1****\n");
      if ((GLOBDEK()) && (FUNC()) && (SLOZ())) {
           printf("****start2****\n");
            if (token==TP_DOT){
                printf("****start3****\n");
                 gtoken();
                return 1;
            }
        }
    }
return 0;
}

/*<FUNC>		->	eps*/
/*<FUNC> 		->	function id  (<ARG>) : <TYPE> <FORWARD>*/
int FUNC (){

   if ((token == KEY_BEGIN)){
        return 1;
        printf("****func1****\n");
   }else {
   if ((token==KEY_FUNCTION)){
       printf("****func1.1****\n");
       gtoken();
       if (token==TP_IDENT){
           printf("****func2****\n");
            gtoken();
            if (token==TP_LBRA){
                printf("****func3****\n");
                gtoken();
                if (ARG()) {
                    printf("****func4****\n");
                    if (token==TP_RBRA){
                        printf("****func5****\n");
                        gtoken();
                        if (token==TP_COL){
                            printf("****func6****\n");
                            gtoken();

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

    if (token==TP_SEM){
        printf("****forward1****\n");
        gtoken();
        if ((DEK())&& (SLOZ())) {
             printf("****forward2****\n");
            if (token==TP_SEM){
                 printf("****forward3****\n");
                gtoken();
                return FUNC();
            }
        }
    }else{
        if (token==KEY_FORWARD){
             printf("****forward1.1****\n");
            gtoken();
            if (token==TP_SEM){
                 printf("****forward2.1****\n");
                gtoken();
                return FUNC();
            }
        }
    }
return 0;
}

/*<ARG> 		-> 	eps*/
/*<ARG> 		-> 	id : <TYPE> <ARGDAL>*/

int ARG (){
    if (token==TP_RBRA){
         printf("****arg0****\n");
        return 1;
    }else{
        if (token==TP_IDENT){
             printf("****arg1.1****\n");
            gtoken();
            if (token==TP_COL){
                 printf("****arg2.1****\n");
                gtoken();
                return TYPE () && ARGDAL();
            }
        }
    }
    return 0;
}

/*<ARGDAL> 	-> 	; id : <TYPE> <ARGDAL>*/
/*<ARGDAL> 	-> 	eps*/
int ARGDAL (){
     if (token==TP_RBRA){
         printf("****argd0****\n");
        return 1;
    }else{
        if (token==TP_SEM){
             printf("****argd2.1****\n");
            gtoken();
            if (token==TP_IDENT){
                 printf("****argd3.1****\n");
                gtoken();
                if (token==TP_COL){
                     printf("****argd3.1****\n");
                    gtoken();
                    return TYPE() && ARGDAL();
                }
            }
        }
    }
    return 0;
}

/*<CYKLUS>	->	while <VYRAZ> do  <SLOZ>   */
int CYKLUS (){
    if (token==KEY_WHILE){
        gtoken();
        if(VYRAZ()){
            if (token==KEY_DO)
                gtoken();
                return SLOZ();
        }

    }

return 0;
}

/*<KDYZ>		->  	if <VYRAZ> then  <SLOZ> <ELSE> */
int KDYZ (){

    if (token==52/*KEY_IF*/){
        printf("****if1***\n");
        gtoken();
        if(VYRAZ()){
            printf("****if2***\n");
            if (token==KEY_THEN){
                printf("****if3***\n");
                gtoken();
                if (SLOZ()){
                    printf("****if4***\n");
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
    if ((token==TP_IDENT)||(token==KEY_WHILE)|| (token==KEY_IF)||(token==ST_SEM)
    ||(token==KEY_READLN)||(token==KEY_WRITE)||(token==KEY_BEGIN)||(token==KEY_END)){
        printf("****else0****\n");
       return 1;
    }else {

        if (token==KEY_ELSE){
             printf("****else2****\n");
            gtoken();
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
 printf("****pokyn0****\n");
  switch (token ){
    case TP_IDENT:
        printf("****pokyn1****\n");
        return PRIKAZ();
    break;
    case KEY_WHILE:
        printf("****pokyn2****\n");
        return CYKLUS();
    break;
    case KEY_IF:
        printf("****pokyn3****\n");
        return KDYZ();
    break;
    case KEY_READLN:
        gtoken();
        if (token==TP_LBRA){
          gtoken();
          if (token==TP_IDENT){
            gtoken();
            if (token==TP_RBRA){
                gtoken();
                return 1;
            }
          }
        }
    break;
    case KEY_WRITE:
        gtoken();
        if (token==TP_LBRA){
            gtoken();
            if (VYPIS()){
                if (token==TP_RBRA){
                    gtoken();
                    return 1;
                }
            }
        }
    break;
    case KEY_BEGIN:
        printf("****pokyn4****\n");
        return SLOZ();
    break;


  }

return 0;
}

/*<SLOZ>		->	begin	<PRVNI> end*/
int SLOZ (){
     if (token == KEY_BEGIN){
         printf("****SLOZ1****\n");
       gtoken();;
       if (PRVNI()){
            printf("****SLOZ2****\n");
            if (token== KEY_END){
                printf("****SLOZ3****\n");
                gtoken();
                return 1;
            }
       }
     }
return 0;
}

/*<PRVNI>		->	eps*/
/*<PRVNI>		-> 	<POKYN> <DALSI>*/
int PRVNI (){

    if (token==KEY_END){
        printf("****PRVNI0****\n");
        return 1;

    }else {
        if ((token==TP_IDENT)||(token==KEY_WHILE)|| (token==KEY_IF)
        ||(token==KEY_READLN)||(token==KEY_WRITE)||(token==KEY_BEGIN)){
            printf("****PRVNI1****\n");
            return POKYN() && DALSI();

        }
    }



return 0;
}

/*<DALSI>		->	eps*/
/*<DALSI>		->	; <POKYN> <PRVNI>*/
int DALSI (){
	if (token==KEY_END){
        printf("****dalsi0****\n");
		return 1;
	}else {
		if (token==TP_SEM){
            printf("****dalsi1****\n");
			gtoken();
			return POKYN() && DALSI();
		}

	}

return 0;
}
/*<PRIKAZ>	-> 	id := <VYRAZ>*/
int PRIKAZ (){
	if (token==TP_IDENT) {
        printf("****prikaz1****\n");
		gtoken();
		if (token==TP_SGNMNT){
		    printf("****prikaz2****\n");
			gtoken();
			return VYRAZ();
		}
	}
return 0;
}

/*<GLOBDEK>		->	var id : <TYPE> ; <GLOBDEKDAL>*/
/*<GLOBDEK>		->	eps*/
int GLOBDEK (){

	if ((token==KEY_FUNCTION)|| (token==KEY_BEGIN)){
        printf("****GLOBDEK0****\n\n");
		return 1;
	}else {
		if ((token==KEY_VAR)){
             printf("****GLOBDEK1****\n\n");
			gtoken();
			if ((token==TP_IDENT)){
				gtoken();
				if (token==TP_COL){
					gtoken();
					if (TYPE()){
						if (token==TP_SEM){
							gtoken();
							return GLOBDEKDAL();
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
	if ((token==KEY_FUNCTION)|| (token==KEY_BEGIN)){
		 printf("****GLOBDEKd0****\n\n");
		return 1;

	}else {
		if ((token==TP_IDENT)){
             printf("****GLOBDEKd1****\n\n");
			gtoken();
			if (token==TP_COL){
				gtoken();
				if (TYPE()){
					if (token==TP_SEM){
						gtoken();
						return GLOBDEKDAL();
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
	switch(token){
		case KEY_REAL:
		    printf("****type1****\n\n");
			gtoken();
			return 1;
		break;
		case KEY_STRING:
		    printf("****type2****\n\n");
			gtoken();
			return 1;
		break;
		case KEY_INTEGER:
		    printf("****type3****\n\n");
			gtoken();
			return 1;
		break;
		case KEY_BOOLEAN:
		    printf("****type4****\n\n");
			gtoken();
			return 1;
		break;
	}
return 0;
}

/*<VYPIS>		->	id <DVYPIS>*/
int VYPIS (){
	if ((token==TP_IDENT)||(token==TP_STRING)||(token==TP_CHAR)||(token==TP_REAL)||(token==TP_REAL_EXP)||(token==TP_INT)){
			gtoken();
			return DVYPIS();
	}
return 0;
}

/*<DVYPIS>	->	, <VYPIS>*/
/*<DVYPIS>	->	eps*/

int DVYPIS (){
	if (token==TP_RBRA){
		return 1;
	}else {
		if (token==TP_COMMA){
            gtoken();
			return VYPIS();
		}
	}
return 0;
}
/*<DEK>		->	var id : <TYPE> ; <DEKDAL>*/
/*<DEK>		->	eps*/
int DEK (){
	if ( (token==KEY_BEGIN)){
         printf("****DEK0****\n\n");
		return 1;
	}else {
		if ((token==KEY_VAR)){
		     printf("****DEK1****\n\n");
			gtoken();
			if ((token==TP_IDENT)){
				gtoken();
				if (token==TP_COL){
					gtoken();
					if (TYPE()){
						if (token==TP_SEM){
							gtoken();
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
	if ( (token==KEY_BEGIN)){
         printf("****DEKd0****\n\n");
		return 1;
	}else {
		if ((token==TP_IDENT)){
		    printf("****DEKd1****\n\n");
			gtoken();
			if (token==TP_COL){
				gtoken();
				if (TYPE()){
					if (token==TP_SEM){
						gtoken();
						return DEKDAL();
					}
				}

			}
		}
	}
return 0;
}

int VYRAZ(){
 if (token==TP_IDENT){
    printf("****vyr1****\n\n");
    gtoken();
    return 1;

 }
 return 0;
}
 /*PRO HUBLIKA*/
int ARGVOL(){
    if (token==TP_RBRA){
        return 1;

    }else {
        if (VYRAZ()){
            return ARGVOLDAL();
        }

    }
return 0;
}

int ARGVOLDAL(){
    if (token==TP_RBRA){
        return 1;

    }else {
        if(token==TP_COMMA){
            gtoken();
            if (VYRAZ()){
                return ARGVOLDAL();
            }
        }

    }

return 0;
}/*
ZADANE FCE LENGTH COPY FIND SORT
jak rozlisit identifikator od zadanych fci? mara vraci ve string....asi se ptat na string

*/






