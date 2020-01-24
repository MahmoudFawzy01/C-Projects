#ifndef FILE_MANGER_H_INCLUDED
#define FILE_MANGER_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/************************************************************************/
/*	Function:		countLinesExists
	Description:	count the lines exist at the file.
	Parameters:		void                
	returns:		lineCounts											*/
/************************************************************************/
int countLinesExists(void);



/************************************************************************/
/*	Function:		CreateFile
	Description:	load the data of the file to a malloc and return its address so it can be accessed
	Parameters:		void                
	returns:		pointer of type char pointing to the first element in the malloc                                                                 */
/************************************************************************/

char * CreateFile (void);





/************************************************************************/
/*	Function:		GetLine
	Description:	load the data line by line each time the function is called
	Parameters:		Buffer	 -> char pointer to the buffer used to load the line
					size_    -> size of the buffer               
	returns:		void                                                                 */
/************************************************************************/

void GetLine (char * Buffer,int size_);




/************************************************************************/
/*	Function:		CloseFile
	Description:	free the memory of the given pointer 
	Parameters:		FileAddress  -> char pointer to the malloc containing the file data                
	returns:		void                                                                 */
/************************************************************************/
void CloseFile(char * FileAddress);

#endif // FILE_MANGER_H_INCLUDED
