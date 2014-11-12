#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

#include <ctype.h>
#include <string.h>
#define TEXT "text.txt"

char *KeyWord[20]={"do","if","end","var","else","find","real","sort","then","true","begin","false","while","write","readln","string","boolean","forward","integer","function"};


int get_token(FILE *F, SToken *token )
{
    int pom;
    char c;
    char *chyba;
    char min;
    token->next_state=ST_START;
    c=fgetc(F);

    while (c != EOF)
    {

        switch(token->next_state)
        {
            case ST_START:
                            if (c == '\n')
                            {
                                token->line++;
                                token->type=TP_EOL;
                                return 0;
                            }
                            if (isspace(c))
                            {

                            }
                            else if (c == ';')
                            {
                                token->type=TP_SEM;
                                return 0;
                            }
                            else if (c == '/')
                            {
                                token->type=TP_MOD;
                                return 0;
                            }
                            else if (c == '.')
                            {
                                token->type=TP_DOT;
                                return 0;
                            }
                            else if (c == '(')
                            {
                                token->type=TP_LBRA;
                                return 0;
                            }
                            else if (c == '+')
                            {
                                token->type=TP_PLUS;
                                return 0;
                            }
                            else if (c == '-')
                            {
                                token->type=TP_MINUS;
                                return 0;
                            }
                            else if (c == ')')
                            {
                                token->type=TP_RBRA;
                                return 0;
                            }
                            else if (c == '*')
                            {
                                token->type=TP_MUL;
                                return 0;
                            }
                            else if (isdigit(c))
                            {
                                token->next_state=ST_NUMBER;
                                strAddChar(token->stri,c);

                            }
                            else if (isalpha(c))
                            {
                                pom=0;
                                token->next_state=ST_IDENT_KEY;
                                strAddChar(token->stri,c);
                            }
                            else if (c == '{')
                            {
                                token->next_state=ST_KOMENT;
                            }
                            else if (c == 39)
                            {
                                token->next_state=ST_STRING;
                            }
                            else if (c == '#')
                            {
                                token->next_state=ST_CHAR;
                            }
                            else if (c == ':')
                            {
                                token->next_state=ST_COLONS;
                                strAddChar(token->stri,c);
                            }
                            else if (c == '<')
                            {
                                token->next_state=ST_LESS;
                            }
                            else if (c == '>')
                            {
                                token->next_state=ST_MORE;
                            }
                            else
                            {
                                token->error=1;                       //nastala chyba.
                            }
            break;

            case ST_KOMENT:
                            if (c == '}')
                            {
                                token->next_state=ST_START;
                            }
            break;

            case ST_IDENT_KEY:

                            if  ((!(isdigit(c))) && (!(isalpha(c))))
                            {
                                token->type=TP_IDENT;
                                ungetc(c,F);
                                return 0;
                            }
                            else
                            {
                                strAddChar(token->stri,c);
                            }


                            for (pom=0;pom<20;pom++)
                            {
                                if ((strCmpConstStr(token->stri,KeyWord[pom]))==0)
                                {

                                    c=fgetc(F);
                                    if ((!(isdigit(c))) && (!(isalpha(c))))
                                    {
                                        ungetc(c,F);
                                        token->type=TP_KEY;
                                        token->charnum=pom+51;
                                        return 0;
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
                                    token->next_state=ST_REAL;
                                    strAddChar(token->stri,c);
                                }
                                else if ((c == 'E') || (c == 'e'))
                                {
                                    token->next_state=ST_REAL_EXP;
                                    strAddChar(token->stri,c);
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
                                        token->next_state=ST_REAL_EXP;
                                        strAddChar(token->stri,c);
                                        if (min == '-')
                                        {
                                            strAddChar(token->stri,'-');
                                        }
                                    }
                                    else
                                    {
                                        token->error=1;
                                        token->next_state=ST_START;
                                    }
                                }
                                else if ((isspace(c)) || (c == ';') || (c == '\n'))
                                {
                                    token->charnum = strtod(strGetStr(token->stri),&chyba);
                                    //free(token->stri);
                                    //token->stri=NULL;
                                    token->type=TP_INT;
                                    return 0;
                                }
                                else
                                {
                                    token->error=1;
                                    token->next_state=ST_START;
                                }

                            }
                            else
                            {
                                    strAddChar(token->stri,c);
                            }
            break;

            case ST_LESS:
                            if (c == '>')
                            {
                                token->type=TP_NEQU;
                                return 0;
                            }
                            else if (c == '=')
                            {
                                token->type=TP_LESSEQ;
                                return 0;
                            }
                            else
                            {
                                token->type=TP_LESS;
                                ungetc(c,F);
                                return 0;
                            }
            break;

            case ST_MORE:
                            if (c == '=')
                            {
                                token->type=TP_MOREEQ;
                                return 0;
                            }
                            else
                            {
                                token->type=TP_MORE;
                                ungetc(c,F);
                                return 0;
                            }
            break;

            case ST_COLONS:
                            if (c == '=')
                            {
                                token->type=TP_SGNMNT;
                                return 0;
                            }
                            else
                            {
                                token->type=TP_COL;
                                ungetc(c,F);
                                return 0;
                            }
            break;

            case ST_CHAR:
                            if (!(isdigit(c)))
                            {
                                token->type=TP_CHAR;
                                ungetc(c,F);
                                return 0;
                            }
                            else
                            {
                                token->charnum=token->charnum*10+(c-48);
                                if (token->charnum >255)
                                {
                                    printf("chyba\n");
                                }
                            }
            break;

            case ST_STRING:
                            if (c == 39)
                            {
                                token->type=TP_STRING;
                                return 0;
                            }
                            else
                            {
                                strAddChar(token->stri,c);
                            }
            break;

            case ST_REAL:
                            if(!(isdigit(c)))
                            {

                                if ((c == 'E') || (c == 'e'))
                                {
                                    token->next_state=ST_REAL_EXP;
                                    strAddChar(token->stri,c);
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
                                        token->next_state=ST_REAL_EXP;
                                        strAddChar(token->stri,c);
                                        if (min == '-')
                                        {
                                            strAddChar(token->stri,'-');
                                        }
                                    }
                                    else
                                    {
                                        token->error=1;
                                        token->next_state=ST_START;
                                    }
                                }
                                else if ((isspace(c)) || (c == ';') || (c == '\n'))
                                {
                                    token->charnum = strtod(strGetStr(token->stri),&chyba);
                                    //free(token->stri);
                                    //token->stri=NULL;
                                    token->type=TP_REAL;
                                    return 0;
                                }
                                else
                                {
                                    token->error=1;
                                    token->next_state=ST_START;
                                }

                            }
                            else
                            {
                                    strAddChar(token->stri,c);
                            }
            break;

            case ST_REAL_EXP:

                            if(!(isdigit(c)))
                            {


                                if ((isspace(c)) || (c == ';') || (c == '\n'))
                                {
                                    token->charnum = strtod(strGetStr(token->stri),&chyba);
                                    //free(token->stri);
                                    //token->stri=NULL;
                                    token->type=TP_REAL_EXP;
                                    return 0;
                                }
                                else
                                {
                                    token->error=1;
                                    token->next_state=ST_START;
                                }

                            }
                            else
                            {
                                    strAddChar(token->stri,c);
                            }
            break;
        }


    c=fgetc(F);
    }
    token->type=TP_EOF;
    return 0;



}








int main()

{

    SToken *token;
    token=malloc(sizeof(SToken));
    FILE *soubor;

    token->stri=malloc(sizeof(string));

    printf("*******************\n");
    //return 0;

    token->type=-1;

    soubor = fopen(TEXT, "r");

    while (token->type != 3)
    {
        if ((strInit(token->stri))==1)
        {
            printf("nepovedlo se vytvořit řetězec\n");
        }

        get_token(soubor,token);
        printf("\nJe to typ: %i\n",token->type);
        printf("Charnum je: %f\n",token->charnum);
        printf("String je: %s\n",strGetStr(token->stri));
        printf("**************************************\n");
        strFree(token->stri);
        //printf("String je: %s\n",token->stri);
    }
    free(token);
    fclose(soubor);
}
