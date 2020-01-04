#ifndef CLINIC_INTERFACE_H_
#define CLINIC_INTERFACE_H_

//////////////////////////////////
//////PROTOTYPES/////////////////
////////////////////////////////

#include "Clinic_private.h"

////////////////////////////////// Patient records (linked List lib)/////////////

u8 new_node(void);

u8 update_node_ByID(void);

void print_LinkedList(void);

void print_node();

void free_LinkedList(void);

u8 isLinkedListImpty(void);

void delete_last_node(void);

node * search_node_ByID(u8 NID);

u8 node_exist_ByID(u8 NID);

void search_node_ByID_and_destroy(u8 NID);

///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////// Login/mode functions ////////////////////

u8 check_Password(u32 _PW);

u8 login_mode(void);

u8 select_admin_features(void);

u8 select_user_features(void);

u8 login_auth(void);

///////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////Appointment Functions ////////////////////////////

void Appointments_List(void);

void Appointments_Admin_List(void);

void Appointments_User_List(void);

void Appointment_Reserve(void);

void Free_Appointments(void);

void Cancel_Appointment(void);

u8 isAppointmentFull(void);

void WelcomeMessae(void);



#endif /*CLINIC_INTERFACE_H_*/