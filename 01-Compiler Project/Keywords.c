#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StanderedTypes.h"
#include "STACK_\LBTY.h"
#include "STACK_\STACK_int.h"





// make an object
struct Line LineClass = {
	.keywords = {
		{.index =0,.name = "auto",.dataType = 1},
		{.index =1,.name = "double",.dataType = 1},
		{.index =2,.name = "int",.dataType = 1},
		{.index =3,.name = "struct",.dataType = 1},
		{.index =4,.name = "break"},
		{.index =5,.name = "else"},
		{.index =6,.name = "long",.dataType = 1},
		{.index =7,.name = "switch"},
		{.index =8,.name = "case"},
		{.index =9,.name = "enum",.dataType = 1},
		{.index =10,.name = "register",.dataType = 1},
		{.index =11,.name = "typedef"},
		{.index =12,.name = "char",.dataType = 1},
		{.index =13,.name = "extern",.dataType = 1},
		{.index =14,.name = "return"},
		{.index =15,.name = "union",.dataType = 1},
		{.index =16,.name = "continue"},
		{.index =17,.name = "for"},
		{.index =18,.name = "signed",.dataType = 1},
		{.index =19,.name = "void",.dataType = 1},
		{.index =20,.name = "do"},
		{.index =21,.name = "if"},
		{.index =22,.name = "static",.dataType = 1},
		{.index =23,.name = "while"},
		{.index =24,.name = "default"},
		{.index =25,.name = "goto"},
		{.index =26,.name = "sizeof"},
		{.index =27,.name = "volatile"},
		{.index =28,.name = "const",.dataType = 1},
		{.index =29,.name = "float",.dataType = 1},
		{.index =30,.name = "short",.dataType = 1},
		{.index =31,.name = "unsigned",.dataType = 1},
		{.index =32,.name = "printf"},
		{.index =33,.name = "scanf"},
		{.index =34,.name = "main"}
	},
	.allowKeyword = 1,
	.allowDataType = 1,
	.DefineVar = 0,
	.SkipVarDefinition = 0,
	.DefineVarEnableAssgin = 0
	
};


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// not used yet
char * variables[255];
char * lineWords[255];
static char varCount;
static char lineWordsCount;
//
Stack s;
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////


// check the word passed if it's a keyword or not.
int checkKeywords(char * word)
{
	int y = 0;
	// compare word to the keywords
	for (y = 0; y < 32; ++y) 
	{
		if (!strcmp(LineClass.keywords[y].name, word))
		{
			return y;
		}
	}
	
	return -1;
}

// add new var to the stack
char addVar( char *varName )
{
	char status,search,Error = 0;
	cWord newVar ;
	
	// create new struct
	strcpy(newVar.name,varName);
	newVar.var = 1;
	// check if the stack is full
	STACK_enuIsFull(&s , &status );
	// check if the var is defined before
	STACK_enuSearch(&s,&newVar,&search);
	
	if ((search == 0)&&(status == 0))
	{
		// push to the stack
		STACK_enuPush( &newVar ,&s );
		Error = 1;
	} 
	else
	{
		Error = 0;
	}
	
	return Error;
}
// 
char checkWords(char * line,int lineIndex)
{
	int i = 0,y = -1,z=0, index = -1;
	char tmpWord[255],dataTypeUsed,tmpPreviousWord[255];
	struct Line currentLine;
	
	// get object from the Line struct
	currentLine = LineClass;
	// clear the word arr before use 
	memset(tmpWord,0,strlen(tmpWord));
	
	// while to move on the whole line.
	while ((line[y] != ';'))
	{
		y++;
		// while to move on the word.
		while ((line[y] != '=')&&(line[y] != ' ') && (line[y] != ',') && (line[y] != ';'))
		{
			// add the current char to the tmpWord arr as a string
			strncat(tmpWord, &line[y], 1);
			y++;
		}
		// get the index at the keywords
		index = checkKeywords(tmpWord);

		// case KeyWords
		if (index != -1)
		{	
			// case dataType
			if ((currentLine.keywords[index].dataType == 1))
			{
				// case dataType allowed to be writen 
				if (currentLine.allowDataType == 1)
				{ 
					// case used before at the same line
					if (currentLine.keywords[index].dataTypeUsed == 0)
					{
						
						currentLine.keywords[index].dataTypeUsed = 1;
						// Allow define var at next words
						currentLine.DefineVar = 1;
					}
					else if (currentLine.keywords[index].dataTypeUsed == 1)
					{
						printf("[Line %d] Syntax error, dublicated %s.\n",lineIndex,tmpWord);
						return 0;
					}		
				}
				else
				{
					printf("[Line %d] Syntax error, can't use %s after %s.\n",lineIndex,tmpWord,tmpPreviousWord);
					return 0;
				}	
			}
		}
		else
		{	
			//printf("1-  %s.\n",tmpWord);
			// disable adding data types
			currentLine.allowDataType = 0;
			// case qoumma after init at definition mode   (line[y] == ' ')&&
			if ((line[y] == ',')&&(currentLine.SkipVarDefinition == 1)&&(currentLine.DefineVar == 1))
			{
				//printf("2-  %s.\n",tmpWord);
				// remove skip next tmpWord 
				currentLine.SkipVarDefinition = 0;
				// clear the word arr before use
				memset(tmpPreviousWord,0,strlen(tmpPreviousWord));
				// cpy the word.
				strcpy(tmpPreviousWord,tmpWord);
				// clear the word arr before use
				memset(tmpWord,0,strlen(tmpWord));
				index = -1;
				continue;
			}
			else if ((tmpWord[0] != 0)&&(currentLine.SkipVarDefinition == 0)&&(currentLine.DefineVar == 1))
			{
				//printf("3-  %s.\n",tmpWord);
				char addingVarError;
				
				addingVarError = addVar(tmpWord);

				if (addingVarError == 0)
				{
					printf("[Line %d] Semantic error, redeclaration of %s.\n",lineIndex,tmpWord);
					return 0;
				}
			}
			else if (((tmpWord[0] > 'a')&&(tmpWord[0] < 'z')||(tmpWord[0] > 'A')&&(tmpWord[0] < 'Z'))&&(currentLine.DefineVarEnableAssgin == 1))//&&(currentLine.SkipVarDefinition = 1))
			{
				char search = 0;
				cWord newVar ;
				
				// create new struct
				strcpy(newVar.name,tmpWord);
				newVar.var = 1;
				// check if the var is defined before
				STACK_enuSearch(&s,&newVar,&search);
				
				if (search == 0)
				{
					printf("[Line %d] Semantic error, undeclared var %s.\n",lineIndex,newVar.name);
				}
				
				currentLine.DefineVarEnableAssgin = 0;
			}
			else if ((tmpWord[0] != 0)&&(currentLine.DefineVar == 0))
			{
				char search = 0;
				cWord newVar ;
				
				// create new struct
				strcpy(newVar.name,tmpWord);
				newVar.var = 1;
				// check if the var is defined before
				STACK_enuSearch(&s,&newVar,&search);
				
				if (search == 0)
				{
					printf("[Line %d] Semantic error, undeclared var %s.\n",lineIndex,newVar.name);
				}
			}
			// skip adding values as vars after assining 
			// next step is adjusting this case to handle var assignment to another var int x = y;
			// prefered to move this case to the adding var section during the previous adjustment.
			if ((line[y] == '=')&&(currentLine.SkipVarDefinition == 0))//&&(currentLine.DefineVar == 1))
			{
				if (currentLine.DefineVar == 1)
				{
					currentLine.SkipVarDefinition = 1;
					currentLine.DefineVarEnableAssgin = 1;
					
				}
				else
				{
					
					//currentLine.DefineVar = 0;
				}				
			}
			
		}
		
		// clear the word arr before use
		memset(tmpPreviousWord,0,strlen(tmpPreviousWord));
		// cpy the word.
		strcpy(tmpPreviousWord,tmpWord);
		// clear the word arr before use
		memset(tmpWord,0,strlen(tmpWord));
		index = -1;
		//printf("%s\n",tmpPreviousWord);
	}
	//reset all to next line
	y = 0;
	
	return 0;
}


void main(void)
{
	char test;
	STACK_enuInitialize (&s) ;
	
	checkWords("void main(void)",1);
	checkWords("float i=100,y = 1000.00;",2);
	checkWords("float i = 1000.00;",3);
	checkWords("float z = 1000.00;",4);
	checkWords("float test = y;",5);
	checkWords("h_= y;",6);
	checkWords("haha=int h_;",7);
}