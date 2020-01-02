/****************************************************************/
/*   Author             :    								    */
/*	 Date 				:    10 March 2019 						*/
/*	 Version 			:    1.0V 							 	*/
/*	 Description 		:    Stack priv [priv.h] contain stack  */
/*                           definition                 		*/
/****************************************************************/


/****************************************************************/
/* Description   : Guard to protect this File from include more */
/*                 than one time .                              */
/****************************************************************/

#ifndef _STACK_PRIV_H_
#define _STACK_PRIV_H_


typedef struct cKeywords cWord;
struct cKeywords {
	// word properties
	char index;
	char name[255];
	char dataTypeUsed;
	char linePos;
	
	char dataTypeCount;
	char dataType;
	char var;
	//..
	//..
};


struct Line{
	// line properties
	struct cKeywords keywords[35];
	char allowKeyword;
	char allowDataType;
	char DefineVar;
	char SkipVarDefinition;
	char DefineVarEnableAssgin;
	//..
	//..
};

/***************************************************************/
/** !comment : redefine new aliase Datatype for data stored in */
/**            Stack                                           */
/***************************************************************/

typedef TYPE_OF_DATA_STORED_ON_STACK StackEntry ;

/*****************************************************************/
/*!comment :Define Encabsulated Data type [ Stack ] it is Struct**/
/*          contain u8 for stack pointer (index) and array for  **/
/*          generic type of data user defined in configuration  **/
/*			file 												**/
/*****************************************************************/

typedef struct stack 
{
   /** top simulate stack pointer refer to first place will push  */
	u8 top ; 
	
   /** StackData is container for data which type generic for user */
	StackEntry StackData [ 255 ] ;
	
}Stack ; /** Stack  is new Data type */


#endif /** !comment  :  End of guard                            **/
