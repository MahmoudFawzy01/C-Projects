#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "file_manger.h"
#include "Brac_Checking.h"
#include "./LexicalAndParser/Compiler_LexicalAndParserPhases.h"


int main()
{
	char Buffer[255];
	int lineCounts,index;
	
	initLexicalAndParserPhases();
    char * p = CreateFile();
	
    Compiler_CheckBract(p);
	
	lineCounts = countLinesExists();
	
	// to remove the start of the file
	GetLine (Buffer,255);
	
	for (index = 1; index < lineCounts ; index++)
	{
		memset(Buffer,0,strlen(Buffer));
		GetLine (Buffer,255);
		checkWords(Buffer,index);		
		
	}	
    
    CloseFile(p);

}

