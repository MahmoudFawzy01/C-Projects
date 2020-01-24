#include <stdio.h>
#include <stdlib.h>
#include "StanderedTypes.h"
//#include "PatientRecord.h"
#define ADD_PRECORD 1 
#define EDIT_PRECORD 2
#define RESERVE 3
#define CANCEL 4 
#define FAILD 0

typedef struct NodeStructure node;
struct NodeStructure{
	u8 uNID;
	u8 Age;
	u8 Name[50];
	u8 gender;
	node * Next;
};
u8 new_node(void);
u8 update_node_ByID(u8 NID);
void print_LinkedList(void);
void free_LinkedList(void);
void delete_last_node(void);
node * search_node_ByID(u8 NID);
u8 node_exist_ByID(u8 NID);
void search_node_ByID_and_destroy(u8 NID);


// Global var
node * Head = NULL;
node *Current = NULL;


u8 new_node(void)
{
	u8 ID,Exist;
	
	printf("Enter Patient ID:");
	scanf("%d",&ID);
	
	// check if id exist
	Exist = node_exist_ByID(ID);
	if(Exist != FAILD)
	{
		printf("ID is exist.\n");
		//new_node();  // option to make it a recusive function. and cancel the return.
		return 0;
	}
	else
	{
		// insert Age
		if (Head == NULL)
		{
			Head = (node*) malloc(sizeof(node));
			Head -> uNID = ID;
			
			printf("Enter Patient Name:");
			scanf("%s",Head -> Name);
			
			printf("Enter Age:");
			scanf("%d",&(Head -> Age));
			
			printf("Enter Gender (M/F):");
			while(Head -> gender != "M" || Head -> gender != "F")
			{
				scanf(" %c",&(Head -> gender));	
			}
			
			Head -> Next = NULL;		
		}
		else
		{
			Current = Head;
			while(Current -> Next != NULL)
			{
				Current = Current -> Next;
			}
			
			Current -> Next = (node*) malloc(sizeof(node));
			Current-> Next ->uNID = ID;
			
			printf("Enter Patient Name:");
			scanf("%s",Current-> Next -> Name);
			
			printf("Enter Age:");
			scanf("%d",&(Current-> Next ->Age));
			
			printf("Enter Gender (M/F):");
			while(Current-> Next ->gender != "M" || Current-> Next ->gender != "F")
			{
				scanf(" %c",&(Current-> Next ->gender));	
			}
			
			Current -> Next ->Next = NULL;	
		}	
	}
	
	return 1;
}

u8 update_node_ByID(u8 NID)
{
	node * Tmp_ptr,*Tmp_ptr1;
	u8 ID,Exist,gender,Age,Name[50];
	
	Tmp_ptr == NULL;
	if (Head==NULL)
	{
		printf("list is empty\n");// as that means there is nothing in the list
	} 
	else 
	{
		Tmp_ptr = search_node_ByID(NID);
		Tmp_ptr1 = Tmp_ptr -> Next; 
		if (Tmp_ptr == NULL)
		{
			printf("No Age with that id.\n**************************\n");
		}
		else
		{
			printf("Enter Patient ID:");
			scanf("%d",&ID);
			
			// check if id exist
			Exist = node_exist_ByID(ID);
			if(Exist != FAILD)
			{
				printf("ID is exist.\n");
				return 0;
			}
			else
			{
				// if not -> go update
				printf("Enter Patient Name:");
				scanf("%s",Name);
				printf("Enter Age:");
				scanf("%d",&Age);
				
				printf("Enter Gender (M/F):");
				while(gender != "M" || gender != "F")
				{
					scanf(" %c",&gender);	
				}
				
				// Update all
				Tmp_ptr -> uNID = ID;
				Tmp_ptr -> Name = Name;
				Tmp_ptr -> Age = Age;
				Tmp_ptr -> gender = gender;
				Tmp_ptr -> Next = Tmp_ptr1; 	
			}
		}
	}
	
	return 1;
}

void print_LinkedList(void)
{
	u8 index = 0;
	
	if (Head==NULL)
	{
		printf("list is empty\n");// as that means there is nothing in the list
	} 
	else 
	{
		Current = Head;
		while(Current != NULL)
		{
			printf("Patient ID: %d \n",Current -> uNID);
			printf("Age: %d \n",Current -> Age);
			printf("Gender: %c \n",Current -> gender);
			printf("Name: ");
			/*while (Current -> Name[index] != '\0') {
			  printf("%c",Current -> Name[index]);
			  index++;
			}
			printf("\n");*/ 
			printf(" %s \n",Current -> Name);
			printf("****************************************************\n\n\n");
			Current = Current -> Next;
		}
	}
}


void free_LinkedList(void)
{	
	if (Head==NULL)
	{
		printf("list is empty\n");// as that means there is nothing in the list
	} 
	else 
	{
		Current = Head;
		while(Current != NULL)
		{
			Current = Current -> Next;
			free(Head);
			Head = Current;
		}
	}
}

void delete_last_node(void)
{
	if (Head==NULL)
	{
		printf("list is empty\n");// as that means there is nothing in the list
	} 
	else 
	{
		Current = Head;
		while(Current-> Next -> Next != NULL)
		{
			Current = Current -> Next;
		}
		free(Current -> Next);
		Current -> Next = NULL;
	}
}

node * search_node_ByID(u8 NID)
{
	if (Head==NULL)
	{
		printf("list is empty\n");// as that means there is nothing in the list
	} 
	else 
	{
		Current = Head;
		while(Current != NULL)
		{
			if (Current -> uNID == NID)
			{
				return Current;
			}
			Current = Current -> Next;
		}
		if (Current == NULL)
		{
			printf("No Age with that id.\n**************************\n");
		}
	}
	return NULL;
}

u8 node_exist_ByID(u8 NID)
{
	if (Head==NULL)
	{
	} 
	else 
	{
		Current = Head;
		while(Current != NULL)
		{
			if (Current -> uNID == NID)
			{
				return 1;
			}
			Current = Current -> Next;
		}
		if (Current == NULL)
		{
		}
	}
	return 0;
}

void search_node_ByID_and_destroy(u8 NID)
{
	node * Tmp_ptr;
	
	if (Head==NULL)
	{
		printf("list is empty\n");// as that means there is nothing in the list
	} 
	else 
	{
		Current = Head;
		Tmp_ptr = Head;
		while(Current != NULL)
		{
			if (Current -> uNID == NID)
			{
				if(Current == Head)
				{
					Head = Head -> Next;
					free(Current);
					break;
				}
				else
				{
					Tmp_ptr -> Next = Current -> Next;
					free(Current);
					break;
				}				
			}
			if(Current != Head)
			{
				Tmp_ptr = Tmp_ptr -> Next;
			}
			Current = Current -> Next;
		}
		if (Current == NULL)
		{
			printf("No Age with that id.\n**************************\n");
		}
	}
}

