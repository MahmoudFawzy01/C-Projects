#include "Brac_Checking.h"
#include <stdint.h>

static char stack[1000];
static char * Sp = stack;
static uint16_t  i =0 ;

static void Stack_AddElement(void);
static void Stack_RemoveElement(void);
static int MiniCompiler_CheckError(void);
static uint8_t MiniCompiler_MutualMatch(void);


void Compiler_CheckBract(char * p_firstLine)
{
    do
    {
        *Sp = *p_firstLine;

        p_firstLine++;
        Stack_AddElement();
        if (MiniCompiler_MutualMatch() == 1)
        {
            Stack_RemoveElement();
            Stack_RemoveElement();
        }
        else if (MiniCompiler_MutualMatch() == 2)
        {
            i++;
            printf("Exit from Mutual Match \n");
            break;
        }

    }while(*(Sp-1) != '\0');
    MiniCompiler_CheckError();
}


void Stack_AddElement(void)
{

    i++;
    switch(*Sp)
    {
    case '(':
    case ')':
    case '{':
    case '}':
    case '[':
    case ']':
                Sp++;
    break;
    default:
    break;
    }
}
void Stack_RemoveElement(void)
{
    if  (stack == Sp)
    {
        printf("Error !!!! Stack is Empty ! \n");
        exit(-1);
    }
    printf("Removing %c to stack \n",*Sp);
    Sp--;
}

int MiniCompiler_CheckError(void)
{
    if (stack != Sp)
    {
        printf("!!! Error Found At  %hi !!!\n",i-1);
        printf("Number %hi \n",Sp-stack);
        exit(-9);
    }
    return 0;
}
uint8_t MiniCompiler_MutualMatch(void)
{
    uint8_t Match = 0;


    if (Sp - stack < 2)
    {
        return Match;
    }

    switch(*(Sp-1))
    {
    case ')':
             if (*(Sp-2) == '(')
             {
                 Match = 1;
             }
             else
             {
                 Match = 2;
             }
    break;
    case '}':
            if (*(Sp-2) == '{')
             {
                 Match = 1;
             }
             else
             {
                 Match = 2;
             }
    break;
    case ']':
            if (*(Sp-2) == '[')
             {
                 Match = 1;
             }
             else
             {
                 Match = 2;
             }
    break;

    break;
    default:
    break;
    }

    return Match;
}
