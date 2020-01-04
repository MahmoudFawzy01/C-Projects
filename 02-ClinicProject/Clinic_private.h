#ifndef CLINIC_PRIVATE_H_
#define CLINIC_PRIVATE_H_

//////////////////////////////////
//////MACROS/////////////////////
////////////////////////////////
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
///////////////////////////////

////////////////////////////////// Patient records (linked List lib)/////////////

typedef struct NodeStructure node;
struct NodeStructure{
	u8 Name[50];
	u8 uNID;
	u8 Age;
	u8 gender;
	node * Next;
};

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////Appointment records ////////////////////////////

typedef struct Appointment reserve;
struct Appointment{
	u8 status;
	u8 PID;
};
//////////////////////////////////////////////////////////////////////////////////



#endif /*CLINIC_INTERFACE_H_*/