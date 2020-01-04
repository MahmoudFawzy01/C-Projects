#include <stdio.h>
#include <stdlib.h>
#include "StanderedTypes.h"
#include <string.h>
#include "Clinic_interface.h"


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
				if (!isLinkedListImpty)
				{
					EditPatient = update_node_ByID();
					if (EditPatient)
						printf("Updated Successfully. \n");
					else
						printf("Error, while update the patient. \n");
				}
				else 
				{
					printf("Patient list is empty.\n");// as that means there is nothing in the list
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



