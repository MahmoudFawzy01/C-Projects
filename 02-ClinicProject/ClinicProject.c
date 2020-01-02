#include <stdio.h>
#include <stdlib.h>
#include "StanderedTypes.h"

#define MAX_PW_TRYING 3
#define ADMIN 1
#define USER 2
#define ADD_PRECORD 1 
#define EDIT_PRECORD 2
#define RESERVE 3
#define CANCEL 4 
#define PRINT_NODE 1 
#define RESERVATION_LIST 2 
#define FAILD 0
#define APPOINTS_NUM 6
#define PM_2	0
#define PM_2_30	1
#define PM_3	2
#define PM_3_30	3
#define PM_4	4
#define PM_4_30	5
#define RESERVED 0
#define FREE	 1

////////////////////////////////// Patient records (linked List lib)/////////////

typedef struct NodeStructure node;
struct NodeStructure{
	u8 Name[50];
	u8 uNID;
	u8 Age;
	u8 gender;
	node * Next;
};

// Global var
node * Head = NULL;
node *Current = NULL;

u8 new_node(void);

u8 update_node_ByID();

void print_LinkedList(void);

void print_node();

void free_LinkedList(void);

void delete_last_node(void);

node * search_node_ByID(u8 NID);

u8 node_exist_ByID(u8 NID);

void search_node_ByID_and_destroy(u8 NID);

///////////////////////////////////////// Login/mode functions ////////////////////

u32 Password = 1234;

u8 check_Password(u32 _PW);

u8 login_mode(void);

u8 select_admin_features(void);

u8 select_user_features(void);

u8 login_auth(void);

/////////////////////////////////Appointment Functions ////////////////////////////

typedef struct Appointment reserve;
struct Appointment{
	u8 status;
	u8 PID;
}Appointment_default = {FREE,0};

reserve Appoint[6];

void Appointments_List(void);

void Appointment_Reserve(void);

void Free_Appointments(void);

void Cancel_Appointment(void);


u16 main(void){
	u8 Mode,login,PID,Feature = 0,AddPatient,EditPatient;
	
	
	printf("****************************************************\n");
	printf("***	       Welcome to MF Clinic App          ***\n");
	printf("****************************************************\n\n\n");
	Free_Appointments();  // configueration
	while(1)
	{
		while((Mode%1 == 0)&&((Mode!= ADMIN)&&(Mode!=USER)))
		{
			Mode = login_mode();
		}
		if (Mode == ADMIN)
		{
			login =login_auth();
			if (login == FAILD)
				return 0;
		
			Feature = select_admin_features();
			printf("****************************************************\n");
			switch (Feature)
			{
			case ADD_PRECORD:
				AddPatient = new_node();
				if (AddPatient)
					printf("Added Successfully. \n");
				else
					printf("Error, while adding new patient. \n");
			break;
	
			case EDIT_PRECORD:
				EditPatient = update_node_ByID();


				if (EditPatient)
					printf("Updated Successfully. \n");
				else
					printf("Error, while update the patient. \n");
			break;
			
			case RESERVE:
				Appointment_Reserve();
			break;
			
			case CANCEL:	
				Cancel_Appointment();
			break;
			
			default:
			break;
			}
			printf("****************************************************\n");
		}
		else if (Mode == USER)
		{
			Feature = select_user_features();
			printf("****************************************************\n");
			switch (Feature)
			{
			case PRINT_NODE:
				print_node();
			break;
	
			case RESERVATION_LIST:
				Appointments_List();
			break;
			}
		}		
		else
		{
			
		}
		printf("****************************************************\n");
		Mode = 0;
		Feature = 0;
	}
return 0;	
}



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
			scanf(" %[^\n]%*c", Head -> Name); 
			
			printf("Enter Age:");
			scanf("%d",&(Head -> Age));
			
			printf("Enter Gender (M/F):");
			scanf(" %c",&(Head -> gender));	
			while(Head -> gender != 'M' && Head -> gender != 'F')
			{
				printf("Wrong input, please try again.");
				printf("Enter Gender (M/F):");
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
			scanf(" %[^\n]%*c",Current-> Next -> Name);
			
			printf("Enter Age:");
			scanf("%d",&(Current-> Next ->Age));
			
			printf("Enter Gender (M/F):");
			while(Current-> Next ->gender != 'M' && Current-> Next ->gender != 'F')
			{
				scanf(" %c",&(Current-> Next ->gender));	
			}
			
			Current -> Next ->Next = NULL;	
		}	
	}
	
	return 1;
}

u8 update_node_ByID()
{
	node * Tmp_ptr,*Tmp_ptr1;
	u8 NID,Exist,gender,Age,i =0,ID;
	u8 Name[50];
	
	printf("Enter Patient ID:");
	scanf("%d",&NID);
	
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
			Exist = node_exist_ByID(NID);
			if(Exist != FAILD)
			{
				printf("ID is exist.\n");
				return 0;
			}
			else
			{
				// if not -> go update
				printf("Enter Patient Name:");
				scanf(" %[^\n]%*c",Tmp_ptr -> Name);
			
				printf("Enter Age:");
				scanf("%d",&Age);
				
				printf("Enter Gender (M/F):");
				while(gender != 'M' && gender != 'F')
				{
					scanf(" %c",&gender);	
				}
				
				// Update all
				Tmp_ptr -> uNID = ID;
				printf("ID: %d",Tmp_ptr -> uNID);
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
			printf("Name: ");
			index = 0;
			/*while (Current -> Name[index] != '\0') {
			  printf("%c",Current -> Name[index]);
			  index++;
			}
			printf("\n"); */
			printf(" %s \n",Current -> Name);
			
			printf("Gender: %c \n",Current -> gender);
			
			printf("****************************************************\n");
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
			printf("No Patient with that id.\n**************************\n");
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
			printf("No Patient with that id.\n**************************\n");
		}
	}
}
void print_node()
{
	u8 ID;
	node * desired;
	if (Head != NULL)
	{
		printf("Enter your ID: ");
		scanf("%d",&ID);
		desired = search_node_ByID(ID);
		if (desired != NULL)
		{
			printf("Patient ID:%d \n",desired -> uNID);
			printf("Patient Name: %s \n",desired -> Name);
			printf("Patient gender: %c \n",desired -> gender);
			printf("Patient Age: %d \n",(desired -> Age));	
		}
	}
	else
		printf("No patient records yet.\n");
}


///////////////////////////////////////////////////////////////////////////

u8 check_Password(u32 _PW)
{
	u32 tmp_PW,bitNum = 1;
	u8 PW_length = 0,MPW_length = 0;
	
	//tmp_PW = _PW;
	while(_PW/bitNum!=0)
	{
		PW_length++;
		bitNum*=10;
	}
	bitNum = 1;
	while(Password/bitNum!=0)
	{
		MPW_length++;
		bitNum*=10;	
	}
	if(MPW_length!=PW_length)
	{
		return 0;
	}
	else
	{
		bitNum = 10;
		while(_PW/bitNum!=0)
		{
			if(_PW%bitNum!=Password%bitNum)
			{
				printf("_PW%bitNum =%d \n",_PW%bitNum);
				printf("Password%bitNum =%d \n",Password%bitNum);
				return 0;
			}
			bitNum*=10;	
		}
	}
	return 1;
}
u8 login_mode(void)
{
	u8 mode;
	while ((mode != 1) && (mode!=2))
	{
		printf(" 1- Admin Mode.\n 2- User Mode.\n");
		printf(" Choose login mode: ");
		scanf("%d",&mode);
	}
	return mode;
}
u8 select_admin_features(void)
{
	u8 feature = 0;
	while (feature!=1 && feature != 2 && feature != 3 && feature != 4)
	{
		printf("****************************************************\n");
		printf(" 1- Add new patient record.\n 2- Edit patient record.\n 3- Reserve a slot with the doctor.\n 4- Cancel reservation.\n");
		printf(" Select the desird feature: ");
		scanf("%d",&feature);
	}
		return feature;
}

u8 select_user_features(void)
{
	u8 feature = 0;
	while (feature != 1 && feature != 2)
	{	
		printf("****************************************************\n");
		printf(" 1- View patient record.\n 2- View today's reservation.\n");
		printf(" Select the desird feature: ");
		scanf("%d",&feature);	
	}
	return feature;
}
u8 login_auth(void)
{
	u32 _PW,chkPW;
	u8 i;
	
	printf("****************************************************\n");
	printf("You are trying to access admin mode.\n");
	for (i = 0; i < MAX_PW_TRYING;i++)
	{
		printf("Please enter password: ");
		scanf("%d",&_PW);
		chkPW = check_Password(_PW);
		if (chkPW)
		{
			printf("successful login. \n");
			return (chkPW);	
		}
		else 
		{
			printf("faild login. \n");
		}
	}
	printf("****************************************************\n\n\n");
	return 0;
}
//////////////////////////////////////////////////////////////////////////
void Appointments_List(void)
{
	u8 i;
	
	printf("The appointments list is :\n");
	for(i=0;i<APPOINTS_NUM;i++)
	{
		switch(i)
		{
			case PM_2:
			printf("1- 02:00 PM to 02:30 PM: ");
			break;
			case PM_2_30:
			printf("2- 02:30 PM to 03:00 PM: ");
			break;
			case PM_3:
			printf("3- 03:00 PM to 03:30 PM: ");
			break;
			case PM_3_30:
			printf("4- 03:30 PM to 04:00 PM: ");
			break;
			case PM_4:
			printf("5- 04:00 PM to 04:30 PM: ");
			break;
			case PM_4_30:
			printf("6- 04:30 PM to 05:00 PM: ");
			break;
		}
		if (Appoint[i].status == FREE)
		{
			printf("Free.\n");
		}
		else if (Appoint[i].status == RESERVED)
		{
			printf("Reserved.\n");
		}
		else
		{
		}
	}	
}

void Appointment_Reserve(void)
{
	u8 time,ID;
	
	if (Head != NULL)
	{
		Appointments_List();
		printf("Enter the desird appointment time: ");
		scanf("%d",&time);
		while(Appoint[time-1].status != FREE)
		{
			printf("This appointment is reserved for patient id: %d .\n",Appoint[time - 1].PID);
			printf("Enter the desird appointment time: ");
			scanf("%d",&time);	
		}
		printf("Enter Patient ID: ");
		scanf(" %c",&ID);
		Appoint[time-1].PID = ID - 48;
		if(node_exist_ByID(ID-48))
			Appoint[time-1].status = RESERVED;
	}
	else 
		printf("No patient records exist.\n");
}


void Free_Appointments(void)
{
	u8 i=0;
	for(i=0;i<APPOINTS_NUM;i++)
	{
		Appoint[i] = Appointment_default;
	}
}

void Cancel_Appointment(void)
{
	u8 time,i,Reserved = 0;

	for (i=0 ; i < APPOINTS_NUM ; i++)
	{
		if (Appoint[i-1].status != FREE)
		{
			Reserved++;
		}	
	}
	if(Reserved > 1)
	{
		Appointments_List();
		printf("Enter the appointment number: ");
		scanf("%d",&time);
		while(Appoint[time-1].status != RESERVED)
		{
			printf("This appointment is free.\n");
			printf("Enter the appointment number: ");
			scanf("%d",&time);
		}
		Appoint[time-1] = Appointment_default;
	}
	else
		printf("The appointments list is already free.\n");
}

