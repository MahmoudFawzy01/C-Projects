#ifndef _COMPILER_LEXICAL_AND_PARSER_PHASES_H_
#define _COMPILER_LEXICAL_AND_PARSER_PHASES_H_

/************************************************************************/
/*	Function:		checkKeywords
	Description:	check the word passed if it's a keyword or not.
	Parameters:		word	 -> char pointer to the start of the word passed
	returns:		int (1/0)  1- means that the word is existed at the keywords
					0- means that the word is not existed 				*/
/************************************************************************/
int checkKeywords(char * word);


/************************************************************************/
/*	Function:		addVar
	Description:	add new var to the stack
	Parameters:		varName	 -> char pointer to the start of the varName passed
	returns:		int (1/0)  1- means that the var added successfully
					0- means that the var is not added successfully		*/
/************************************************************************/
char addVar( char * varName );


/************************************************************************/
/*	Function:		checkWords
	Description:	extract the tokens from the line and parse (analyse) each word.
					first phase of the compiler.
	Parameters:		line	 -> char pointer to the start of the varName passed
					lineIndex-> int var provide the functio the index of the line passed
	returns:		int (1/0)  1- means that the var added successfully
					0- means that the var is not added successfully		*/
/************************************************************************/ 
char checkWords(char * line,int lineIndex);


/************************************************************************/
/*	Function:		initLexicalAndParserPhases
	Description:	Init the phase.
	Parameters:		void
	returns:		void												*/
/************************************************************************/ 
void initLexicalAndParserPhases(void);




#endif /*_COMPILER_LEXICAL_AND_PARSER_PHASES_H_*/