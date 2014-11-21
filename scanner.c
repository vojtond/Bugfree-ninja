#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "scanner.h"



#define TEXT "text.txt"
int line=1;

char *KeyWord[20]={"do","if","end","var","else","find","real","sort","then","true","begin","false","while","write","readln","string","boolean","forward","integer","function"};


int get_token(FILE *F, double *num, string *stri, int *error )
{
    int pom;
    int cha=0;
    int err_char=0;
    int next_state=ST_START;
    char c;
    char *chyba;
    char min;

    *num=0;
    c=fgetc(F);

    while (c != EOF)
    {

        switch(next_state)
        {
            case ST_START:
                            if (c == '\n')
                            {
                                line++;
                                next_state=ST_START;
                            }
                            if (isspace(c))
                            {
                                break;              //Tohle jsem přidával !!!!!!!!
                            }
                            else if (c == ';')
                            {
                                return TP_SEM;
                            }
                            else if (c == '/')
                            {
                                return TP_MOD;
                            }
                            else if (c == '.')
                            {
                                return TP_DOT;
                            }
                            else if (c == '(')
                            {
                                return TP_LBRA;
                            }
                            else if (c == '+')
                            {
                                return TP_PLUS;
                            }
                            else if (c == '-')
                            {
                                return TP_MINUS;
                            }
                            else if (c == ')')
                            {
                                return TP_RBRA;
                            }
                            else if (c == '*')
                            {
                                return TP_MUL;
                            }
                            else if (isdigit(c))
                            {
                                next_state=ST_NUMBER;
                                strAddChar(stri,c);

                            }
                            else if (isalpha(c))
                            {
                                pom=0;
                                next_state=ST_IDENT_KEY;
                                strAddChar(stri,c);
                            }
                            else if (c == '{')
                            {
                                next_state=ST_KOMENT;
                            }
                            else if (c == 39)
                            {
                                next_state=ST_STRING;
                            }
                            else if (c == ':')
                            {
                                next_state=ST_COLONS;
                                strAddChar(stri,c);
                            }
                            else if (c == '<')
                            {
                                next_state=ST_LESS;
                            }
                            else if (c == '>')
                            {
                                next_state=ST_MORE;
                            }
                            else if (c == ',')
                            {
                                return TP_COMMA;
                            }
                            else
                            {
                                *error=1;                       //nastala chyba.
                            }
            break;

            case ST_KOMENT:
                            if (c == '}')
                            {
                                next_state=ST_START;
                            }
            break;

            case ST_IDENT_KEY:

                            if  ((!(isdigit(c))) && (!(isalpha(c))))
                            {
                                ungetc(c,F);
                                return TP_IDENT;
                            }
                            else
                            {
                                strAddChar(stri,c);
                            }


                            for (pom=0;pom<20;pom++)
                            {
                                if ((strCmpConstStr(stri,KeyWord[pom]))==0)
                                {

                                    c=fgetc(F);
                                    if ((!(isdigit(c))) && (!(isalpha(c))))
                                    {
                                        ungetc(c,F);
                                        return pom+51;
                                    }
                                    else
                                    {
                                        ungetc(c,F);
                                    }

                                }

                            }



            break;

            case ST_NUMBER:

                            if(!(isdigit(c)))
                            {
                                if(c == '.')
                                {
                                    next_state=ST_REAL;
                                    strAddChar(stri,c);
                                }
                                else if ((c == 'E') || (c == 'e'))
                                {
                                    next_state=ST_REAL_EXP;
                                    strAddChar(stri,c);
                                }
                                else if ((c == '+') || (c == '-'))
                                {
                                    if (c == '-')
                                    {
                                        min='-';
                                    }
                                    c=fgetc(F);
                                    if ((c == 'E') || (c == 'e'))
                                    {
                                        next_state=ST_REAL_EXP;
                                        strAddChar(stri,c);
                                        if (min == '-')
                                        {
                                            strAddChar(stri,'-');
                                        }
                                    }
                                    else
                                    {
                                        *error=1;
                                        next_state=ST_START;
                                    }
                                }
                                else if ((isspace(c)) || (c == ';') || (c == '\n'))
                                {
                                    *num = strtod(strGetStr(stri),&chyba);
                                    return TP_INT;
                                }
                                else
                                {
                                    *error=1;
                                    next_state=ST_START;
                                }

                            }
                            else
                            {
                                    strAddChar(stri,c);
                            }
            break;

            case ST_LESS:
                            if (c == '>')
                            {
                                return TP_NEQU;
                            }
                            else if (c == '=')
                            {
                                return TP_LESSEQ;
                            }
                            else
                            {
                                ungetc(c,F);
                                return TP_LESS;
                            }
            break;

            case ST_MORE:
                            if (c == '=')
                            {
                                return TP_MOREEQ;
                            }
                            else
                            {
                                ungetc(c,F);
                                return TP_MORE;
                            }
            break;

            case ST_COLONS:
                            if (c == '=')
                            {
                                return TP_SGNMNT;
                            }
                            else
                            {
                                ungetc(c,F);
                                return TP_COL;
                            }
            break;

            case ST_CHAR:
                            if (c == 39)
                            {
                                if (err_char == 0)
                                {
                                    strAddChar(stri,cha);
                                }
                                err_char=0;
                                next_state=ST_STRING;
                                break;
                            }
                            if ((!(isdigit(c)) && (c != 39)) || (err_char==1))
                            {
                                printf("chyba\n");

                            }
                            else
                            {
                                cha=cha*10+(c-48);
                                if ((cha <1) && (cha >255))
                                {
                                    printf("chyba\n");
                                    err_char=1;
                                }
                            }

            break;

            case ST_STRING:
                            if (c == 39)
                            {
                                c=fgetc(F);
                                if (c == '#')
                                {
                                    next_state=ST_CHAR;
                                    break;
                                }
                                else
                                {
                                    ungetc(c,F);
                                    return TP_STRING;
                                }

                            }
                            else
                            {
                                strAddChar(stri,c);
                            }
            break;

            case ST_REAL:
                            if(!(isdigit(c)))
                            {

                                if ((c == 'E') || (c == 'e'))
                                {
                                    next_state=ST_REAL_EXP;
                                    strAddChar(stri,c);
                                }
                                else if ((c == '+') || (c == '-'))
                                {
                                    if (c == '-')
                                    {
                                        min='-';
                                    }
                                    c=fgetc(F);
                                    if ((c == 'E') || (c == 'e'))
                                    {
                                        next_state=ST_REAL_EXP;
                                        strAddChar(stri,c);
                                        if (min == '-')
                                        {
                                            strAddChar(stri,'-');
                                        }
                                    }
                                    else
                                    {
                                        *error=1;
                                        next_state=ST_START;
                                    }
                                }
                                else if ((isspace(c)) || (c == ';') || (c == '\n'))
                                {
                                    *num = strtod(strGetStr(stri),&chyba);
                                    return TP_REAL;
                                }
                                else
                                {
                                    *error=1;
                                    next_state=ST_START;
                                }

                            }
                            else
                            {
                                    strAddChar(stri,c);
                            }
            break;

            case ST_REAL_EXP:

                            if(!(isdigit(c)))
                            {


                                if ((isspace(c)) || (c == ';') || (c == '\n'))
                                {
                                    *num = strtod(strGetStr(stri),&chyba);
                                    return TP_REAL_EXP;
                                }
                                else
                                {
                                    *error=1;
                                    next_state=ST_START;
                                }

                            }
                            else
                            {
                                    strAddChar(stri,c);
                            }
            break;
        }


    c=fgetc(F);
    }

    return TP_EOF;



}








int main()

{
    string stri;
    int type;
    double num;
    int error;


    type=-1;
    //*num=0;
    //*line=1;

    FILE *soubor;


    //stri=malloc(sizeof(string));

    printf("*******************\n");




    soubor = fopen(TEXT, "r");

    while (type != 3)
    {
        if ((strInit(&stri))==1)
        {
            printf("nepovedlo se vytvořit řetězec\n");
        }
//int get_token(FILE *F, double *num, int *line, string *stri, int *error )
        type=get_token(soubor,&num,&stri,&error);
        printf("\nJe to typ: %i\n",type);
        printf("Charnum je: %f a radek je:%i\n",num,line);
        printf("String je: %s\n",strGetStr(&stri));
        printf("**************************************\n");
        strFree(&stri);

    }
    fclose(soubor);
}
