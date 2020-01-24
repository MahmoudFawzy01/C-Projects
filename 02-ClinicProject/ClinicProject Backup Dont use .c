#include <stdio.h>
#include <stdlib.h>
#include "StanderedTypes.h"
#include <string.h>

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
#define RESERVED 1
#define FREE	 0
#define ADMIN_TO_MAIN_MENU	 5
#define USER_TO_MAIN_MENU	 3

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

u8 update_node_ByID(void);

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

void Appointments_Admin_List(void);

void Appointments_User_List(void);

void Appointment_Reserve(void);

void Free_Appointments(void);

void Cancel_Appointment(void);

u8 isAppointmentFull(void);

void WelcomeMessae(void);

u16 main(void){
	u8 Mode,login,Feature = 0,AddPatient,EditPatient;
	
	
	WelcomeMessae(); // welcome
	Free_Appointments();  // configueration
	
	MainMenu: 
	Mode = 0;
	while(((Mode!= ADMIN)&&(Mode!=USER)))
	{
		Mode = login_mode();
		
		// lOGIN SYSTEM IF ADMIN
		if (Mode == ADMIN)
		{
			login =login_auth();
			if (login == FAILD)
				return 0;
		}
	}

	while(1)
	{		
		Feature = 0;

		if (Mode == ADMIN)
		{
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
				if (Head!=NULL)
				{
					EditPatient = update_node_ByID();
					if (EditPatient)
						printf("Updated Successfully. \n");
					else
						printf("Error, while update the patient. \n");
				}
				else 
				{
					printf("list is empty\n");// as that means there is nothing in the list
				}
			break;
			
			case RESERVE:
				if (isAppointmentFull())
				{
					printf("The appointment list is reserved.\n");// as that means there is nothing in the list
				}
				else
					Appointment_Reserve();
			break;
			
			case CANCEL:	
				Cancel_Appointment();
			break;
			
			case ADMIN_TO_MAIN_MENU:	
				goto MainMenu;
			break;
			
			default:
			break;
			}
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
				Appointments_User_List();
			break;
			
			case USER_TO_MAIN_MENU:
				goto MainMenu;
			break;
			}
		}
	}
return 0;	
}



u8 new_node(void)
{
	u8 strID[5],Exist,ID,strLength;
	u8 strAge[5],Age;
	
	
	// add new check for the size of linked list 
	// Add new check for the malloc
	printf("Enter Patient ID 1~255: ");
	scanf("%s",strID);
	
	strLength = strlen(strID);
	ID = atoi(strID);
	
	if (strLength <= 3 && ID > 0 && strLength <= 255)
	{
		// check if id exist.
		printf("ID is: %d \n",ID);
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
				
				
				
				insertAge1:
				
					printf("Enter Age 1~120:");
					scanf("%s",strAge);
					strLength = strlen(strAge);
					Age = atoi(strAge);
					
					if(strLength <= 3 && (Age > 0 && Age <= 120)) 
					{
						printf("Age is: %d \n",Age);
						Head -> Age = Age;
					}
					else
					{
						printf("Age is out of the range. \n");
						goto insertAge1;	
					}
				
				printf("Enter Gender (M/F):");
				scanf(" %c",&(Head -> gender));	
				while(Head -> gender != 'M' && Head -> gender != 'F'&& Head -> gender != 'm' && Head -> gender != 'f')
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

				insertAge2:
				
					printf("Enter Age 1~120:");
					scanf("%s",strAge);
					strLength = strlen(strAge);
					Age = atoi(strAge);
					
					if(strLength <= 3 && (Age > 0 && Age <= 120)) 
					{
						printf("Age is: %d \n",Age);
						Current-> Next ->Age = Age;
					}
					else
					{
						printf("Age is out of the range. \n");
						goto insertAge2;	
					}			
				
				printf("Enter Gender (M/F):");
				while( Current-> Next -> gender != 'M' && Current-> Next -> gender != 'F' && Current-> Next -> gender != 'm' && Current-> Next -> gender != 'f')
				{
					scanf(" %c",&(Current-> Next ->gender));	
				}
				
				Current -> Next ->Next = NULL;	
			}	
		}
	}
	else 
	{
		printf("ID is out of range.\n");
		return 0;
	}
	return 1;
}

u8 update_node_ByID(void)
{
	node * Tmp_ptr;
	u8 NID,strNID[5],Exist,gender,Age,strAge[5],i =0,ID,strID[5],strLength;
	u8 Name[50];
	
	// add new check for the size of linked list 
	printf("Enter Patient ID 1~255: ");
	scanf("%s",strNID);
	strLength = strlen(strNID);
	NID = atoi(strNID);
	
	if (NID > 0 && NID <= 255 && strLength <= 3)
	{
		printf("You entered: %d \n",NID);
		Tmp_ptr == NULL;
		if (Head==NULL)
		{
			printf("list is empty\n");// as that means there is nothing in the list
		} 
		else 
		{
			Tmp_ptr = search_node_ByID(NID);
			if (Tmp_ptr == NULL)
			{
				return 0;
			}
			else
			{	

				// if not -> go update
				updateID:
				
				printf("Enter new patient ID 1~255: ");
				scanf("%s",strID);
				strLength = strlen(strID);
				ID = atoi(strID);
				if (ID > 0 && ID <= 255 && strLength <= 3)
				{
					// Update ID
					printf("The new ID is: %d \n",ID);
					Tmp_ptr -> uNID = ID;
				}
				else
				{	
					printf("ID is out of range. \n");
					goto updateID;	
				}
				
				// Update Name
				printf("Enter Patient Name:");
				scanf(" %[^\n]%*c",Tmp_ptr -> Name);
				
				updateAge:
				
				printf("Enter Age 1~120:");
				scanf("%s",strAge);
				strLength = strlen(strAge);
				Age = atoi(strAge);
				if(strLength <= 3 && (Age > 0 && Age <= 120)) 
				{
					// Update Age
					printf("The new age is: %d \n",Age);
					Tmp_ptr -> Age = Age;
				}
				else
				{
					printf("Age is out of the range. \n");
					goto updateAge;	
				}
				
				printf("Enter Gender (M/F):");
				while(gender != 'M' && gender != 'F' && gender != 'm' && gender != 'f')
				{
					scanf(" %c",&gender);	
				}
				// Update gender
				Tmp_ptr -> gender = gender;					
			}
		}		
	}
	else
	{
		printf("ID is out of range. \n");
		return 0;
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
			printf("No Patient with that id.\n");
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
	static u8 mode;
	mode = 0;
	while ((mode != 1) && (mode!=2))
	{
		printf(" 1- Admin Mode.\n 2- User Mode.\n");
		printf(" Choose login mode: ");
		scanf("%d",&mode);
		if ((mode != 1) && (mode!=2))
		{
			printf("\n Invalid mode number. \n ****************************************************\n");
			
		}
	}
	return mode;
}
u8 select_admin_features(void)
{
	static u8 feature;
	
	feature = 0;
	while (feature!=1 && feature != 2 && feature != 3 && feature != 4 && feature != 5)
	{
		printf("****************************************************\n");
		printf(" 1- Add new patient record.\n 2- Edit patient record.\n 3- Reserve a slot with the doctor.\n 4- Cancel reservation.\n 5- Back to main menu.\n");
		printf(" Select the desird feature: ");
		scanf("%d",&feature);
	}
		return feature;
}

u8 select_user_features(void)
{
	static u8 feature;
	
	feature = 0;
	while (feature != 1 && feature != 2&& feature != 3)
	{	
		printf("****************************************************\n");
		printf(" 1- View patient record.\n 2- View today's reservation.\n 3- Back to main menu.\n");
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

void Appointments_Admin_List(void)
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
			printf("Reserved.        -> Patient ID: %d\n",Appoint[i].PID);
		}
		else
		{
		}
	}	
}

void Appointments_User_List(void)
{
	u8 i,ID,strID[5],strLength,tryCount = 0,Exist;
	
	appointmentUserID:
	printf("Enter Patient ID 1~255: ");
	scanf("%s",strID);
	
	strLength = strlen(strID);
	ID = atoi(strID);
	
	if (strLength <= 3 && ID > 0 && strLength <= 255)
	{
		Exist = node_exist_ByID(ID);
		if(Exist == FAILD)
		{
			printf("This id is not exist.\n");
			goto appointmentUserListEnd;
		}
		else
		{
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
					if (ID == Appoint[i].PID)
					{
						printf("Reserved by your id.    -> Patient ID: %d\n",Appoint[i].PID);
						continue;
					}
					printf("Reserved.\n");
				}
			}		
		}
	}
	else
	{
		if (tryCount < 3)
		{
			printf("Out of range id.");
			goto appointmentUserID;
		}
		else
		{
			goto appointmentUserListEnd;
		}
	}	
	appointmentUserListEnd:
	printf("");
}


void Appointment_Reserve(void)
{
	static u8 time,ID,exist;
	u8 appointmentTry,idTry;
	
	appointmentTry = 0;
	idTry = 0;
	
	if (Head != NULL)
	{
		Appointments_Admin_List();
		appointmentTime:
		printf("Enter the desird appointment time: ");
		scanf("%d",&time);
		
		if (time >= 1 && time <= 6)
		{
			if (Appoint[time-1].status != FREE)
			{
				printf("This appointment is reserved for patient id: %d .\n",Appoint[time - 1].PID);
				if (appointmentTry < 3)
				{
					goto appointmentTime;	
					appointmentTry++;
				}
				
			}
			
			userAppointmentID:
			printf("Enter Patient ID: ");
			scanf("%d",&ID);
			
			exist = node_exist_ByID(ID);
			if(exist != FAILD)
			{
				Appoint[time-1].PID = ID;
				Appoint[time-1].status = RESERVED;
				printf("Reserved Successfully. \n");
			}
			else
			{
				printf("Patient record is not exist. \n");
				if (idTry < 3)
				{
					goto userAppointmentID;
					idTry++;
				}
			}
		}
		else
		{
			printf("Invalid appointment,try again.\n");
			goto appointmentTime;
		}		
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
	static u8 time,i,Reserved;
	u8 ID,strID[5],strLength,Exist;
	
	Reserved = 0;
	
	for (i=0 ; i < APPOINTS_NUM ; i++)
	{
		if (Appoint[i].status != FREE)
		{
			Reserved++;
		}	
	}
	if(Reserved >= 1)
	{
		cancelAppointmentUserID:
		printf("Enter Patient ID 1~255: ");
		scanf("%s",strID);
		
		strLength = strlen(strID);
		ID = atoi(strID);
		
		if (strLength <= 3 && ID > 0 && strLength <= 255)
		{
			Exist = node_exist_ByID(ID);
			if(Exist == FAILD)
			{
				printf("This id is not exist.\n");
				goto cancelUserAppointmentEnd;
			}
			else
			{
				Appointments_Admin_List();		
				cancelAppointmentGetTime:
				printf("Enter the appointment number: ");
				scanf("%d",&time);
				if(Appoint[time-1].status != RESERVED)
				{
					printf("This appointment is free.\n");
					goto cancelAppointmentGetTime;
				}
				else if ((Appoint[time-1].status == RESERVED)&&(Appoint[time-1].PID == ID))
				{
					Appoint[time-1] = Appointment_default;	
					printf("Canceled Successfully. \n");
				}
				else
				{
					printf("This appointment is not belong the entered id.\n");
					goto cancelAppointmentGetTime;
				}
			}
		}
		else
		{
			printf("Out of range id.\n");
			goto cancelAppointmentUserID;
		}			
	}
	else
	{
		printf("The appointments list is already free.\n");		
	}
	
	cancelUserAppointmentEnd:
		printf("");

}
u8 isAppointmentFull(void)
{
	u8 time,i,Reserved = 0;

	for (i=0 ; i < APPOINTS_NUM ; i++)
	{
		if (Appoint[i].status != FREE)
		{
			Reserved++;
		}	
	}
	
	if (Reserved == 6)
	{
		return 1;
	}
	
	return 0;
}
void WelcomeMessae(void)
{
	printf("****************************************************\n");
	printf("***	       Welcome to MF Clinic App          ***\n");
	printf("****************************************************\n\n\n");
}

