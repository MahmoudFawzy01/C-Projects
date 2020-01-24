

#include"file_manger.h"

static FILE *fp;


char * CreateFile (void)
{
    fp = fopen("program.c", "rb");

     if (fp == NULL)
     {
         printf("FILE NOT FOUND.");
         exit(-10);
     }

     fseek(fp, 0, SEEK_END);
     long fsize = ftell(fp);
     fseek(fp, 0, SEEK_SET);

     char *string = malloc(fsize + 2);
     fread(string, 1, fsize, fp);
     //printf(" %s",string);
     *(string+fsize)='\0';
     //printf(" %d",*(string+fsize));

     fclose(fp);

     return string;
}

int countLinesExists(void)
{
	int linesCount = 0;
	char currecntChar;
	
	fp = fopen("program.c", "r");
	 // Extract characters from file and store in character currecntChar 
    for (currecntChar = getc(fp); currecntChar != EOF; currecntChar = getc(fp)) 
        if (currecntChar == '\n') // Increment count if this character is newline 
            linesCount = linesCount + 1; 

	return linesCount;
}
void GetLine (char * Buffer,int size_)
{
    int i=0;
	char tmpArr[255];
	
	
    fp = fopen("program.c", "r");

    static int curser =1;
    for(i=0;i<curser;i++)
    {
		fgets(Buffer,sizeof(Buffer)*size_,fp) ;
    }

	i=0;
	memset(tmpArr,0,strlen(tmpArr));
	while ((i < 255)&&(Buffer[i] != '\n'))
	{
		if (Buffer[i] != '\t')
		// add the current char to the tmpWord arr as a string
		strncat(tmpArr, &Buffer[i], 1);
		i++;
	}
	//memset(Buffer,0,strlen(Buffer));
	strcpy(Buffer,tmpArr);
	
    curser++;

    fclose(fp);
}

void CloseFile(char * FileAddress)
{
    free(FileAddress);
}
