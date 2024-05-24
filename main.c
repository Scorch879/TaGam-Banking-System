#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "logo.h"
#include "AcctManage.h"
#include "Transact.h"
#include "OtherServices.h"
int main()
{
    int loggedIn = 0; // No one is logged in yet
    char choice_1, choice_2, choice_term, choice_transact, choice_services; // Initialization of variables or declaration
    char username[MAX_USERNAME_LENGTH + 1]; // +1 for null terminator
    char password[MAX_PASSCODE_LENGTH + 1]; // +1 for null terminator
    float money = 0;
	logo();
	
    while (1) 
	{
		Main:
        // Selection
        setColor(14); //set color to yellow
        printf("\n\n\t\t\t\t\t        MAIN SCREEN\n\n");
        printf("\n\t\t\t\t\t1. Account Management");
        printf("\n\t\t\t\t\t2. Transaction Processing");
        printf("\n\t\t\t\t\t3. Other Services");
        printf("\n\t\t\t\t\t4. Exit");
        printf("\n\n\t\t\t\t\tSelection: ");
        scanf(" %c", &choice_1);
        	fflush(stdin);
        switch(choice_1) 
		{
            case '1':
            {
                system("cls"); // Clear Previous Screen
                logo(); // Logo "BANK" Printing function
                setColor(14); //set color to yellow
				 	printf("\n\n\t\t\t\t\t    Account Management\n\n");
			        printf("\n\t\t\t\t\t1. Account Creation");
			        printf("\n\t\t\t\t\t2. Login Account");
			        printf("\n\t\t\t\t\t3. Account Termination"); 
			        printf("\n\t\t\t\t\t4. Back");
			        printf("\n\t\t\t\t\t5. Logout");
			        printf("\n\n\t\t\t\t\tSelection: ");
			        scanf(" %c", &choice_2);
			        	fflush(stdin);
				switch(choice_2) //Another One 
				{
					case '1':
						{
							if (loggedIn == 0) 
							{
			                    accountCreation();
			                } 
							else 
							{
								setColor(12); //set color to red
			                    printf("\nAlready logged in!\nPress Enter to continue...");
			                    getchar();
			                    fflush(stdin);    
	                		}		
						break;	
						}
					case '2':
						{
							if (loggedIn == 0) // If no account is logged in
							{
								login(username, password, &loggedIn);
							}
							else
							{
								system("cls");
								logo();
								setColor(12); //set color to red
								printf("\n\n\t\t\t\t\tAccount has been logged in already.\n");
							}
							break;
						}
					case'3':
						{	
							system("cls");
							logo();
							if(loggedIn == 0) //Belongs to first if
							{
								int i;
								setColor(12); //set color to red
								printf("\n\t\t\t\t\tYou need to login first!\n");
								printf("\n\t\t\t\t\tProceeding in...");
								for (i = 3 ; i > 0; i--)
	            				{   
		            				printf(" %d", i);
		                			sleep(1);
	            				}
								login(username, password, &loggedIn);
							}
							
							if (loggedIn == 1)
							{
								setColor(14); //set color to yellow
								printf("\n\n\t\t\t\t\t1 > YES");
								printf("\n\t\t\t\t\t2 > NO");
								printf("\n\t\t\t\t\tAre you sure to terminate your account?: ");
									scanf("%d", &choice_term);
										fflush(stdin);
								if (choice_term == 1)
								{
									terminateAccount(username, password); //Function to terminate passing the current logged in account
								}
								else
								{
									system("cls");
									logo();
									setColor(14); //set color to yellow
									printf("\n\n\t\t\t\t  Account Logged out."); //Automatic Log out after this
									break;
								}
							}
							break;
						}
					case '4':
						{
							system("cls");
							logo();
							goto Main;
							break;
						}
					case '5':
						{
							system("cls");
							logo();
								if (loggedIn == 1)
								{
									setColor(14); //set color to yellow
									loggedIn = 0;
									printf("\n\n\t\t\t\t\t    Account Logged Out!");
								}
								else
								{
									setColor(12); //set color to red
									printf("\n\n\t\t\t\t\tNo account has been logged in!");
								}
							break;
						}
					default:
						system("cls");
						logo();
						setColor(12); //set color to red
						printf("\n\t\t\t\t\t  Sorry. Invalid Choice :(\n");
						break;
				}//Belongs to choice_2
				
            break;//Belongs to choice_1
            } 
            
            case '2': //Belongs to choice_1 (Transaction Processing)
                {
                	if (check_file_exists(ACCOUNTS_FILE) == 1) //Function to call if the file exist
                	{
						// Transaction processing functionality will be added here
						transactjump:
						system("cls");
						logo();
						setColor(14); //set color to yellow
	                	printf("\n\n\t\t\t\t\t  Transaction Processing");
	                	printf("\n\n\t\t\t\t\t1. Withdraw");
	                	printf("\n\t\t\t\t\t2. Deposit");
	                	printf("\n\t\t\t\t\t3. Money Transfer");
	                	printf("\n\t\t\t\t\t4. Balance Inquiry");
	                	printf("\n\t\t\t\t\t5. Back");
	                	printf("\n\n\t\t\t\t\tSelection: ");
	                		scanf(" %c", &choice_transact);
	                			fflush(stdin);
	                	switch(choice_transact)
	                	{
	                		case '1':
	                			{
	                				withdraw(username, password, &loggedIn);
	                				system("cls");
	                				logo();
	                				break;
								}
							case '2':
								{
									deposit(username, password, &loggedIn);
									system("cls");
									logo();
									break;
								}
							case '3':
								{
									money_transfer(username, password, &loggedIn);
									system("cls");
									logo();
									break;
								}
							case '4':
								{
									if(loggedIn == 0)
									{
										login(username, password, &loggedIn);
									}
									if(loggedIn == 1)
									{
										system("cls");
										logo();
										setColor(14);
										printf("\n\n\t\t\t\t\tAccount: %s", username);
										printf("\n\t\t\t\t\tCurrent Balance: $%0.2f", get_money_fromFile(username, password));
										printf("\n\t\t\t\t\tPress Any Button to Continue: ");
										getche();
										goto transactjump;
										break;
									}
								}
							case '5':
								{
									system("cls");
									logo();
									setColor(14); //set color to yellow
									printf("\n\n\t\t\t\t\t   Returned to Main Menu!");
									break;
								}
							default:
								system("cls");
				            	logo();
				            	setColor(12); //set color to red
				                printf("\n\t\t\t\t\t  Sorry. Invalid Choice :(\n");
						}
					}
					else
					{
						system("cls");
						logo();
						setColor(12); //set color to yellow
						printf("\n\n\t\t\t\t\tNo Accounts Registered!");
						goto Main;
					}
					break;
            	}
            
			case '3': //Belongs to choice_1 (Other Services
               {
		       services:
               		system("cls");
    				logo();
    				setColor(14); //Yellow
    				printf("\n\n\t\t\t\t\tOther Services");
    				printf("\n\n\t\t\t\t\t1. View Transaction History");
    				printf("\n\t\t\t\t\t2. Back");
    				printf("\n\n\t\t\t\t\tSelection: ");
    				scanf(" %c", &choice_services);
    					fflush(stdin);
	    				switch (choice_services) 
						{
	        				case '1':
	            				{
	                				display_transaction_history(username, password, &loggedIn);
	                				break;
	            				} 
	            			
							case '2':
	            				{
	            					system("cls");
									logo();
									setColor(14); //set color to yellow
									printf("\n\n\t\t\t\t\t   Returned to Main Menu!");
	            					break; 
								}
							default:
								system("cls");
								logo();
								printf("\n\t\t\t\t\t  Sorry. Invalid Choice :(\n");
								goto services;
	            			
						}
               	break;
			   }
                
            case '4': //Belongs to choice_1 (Exiting Case)
            	{
            		system("cls");
            		logo();
            		fflush(stdin);
            		setColor(14); //set color to yellow
            		printf("\n\t\t\t\t\tThank you for using TaGam Banking!!\n");
                	printf("\n\t\t\t\t\tExiting...\n");
                	return 0;
            	}
            default: //Belongs to choice_1 (If input does not match the selection)
            	system("cls");
            	logo();
            	fflush(stdin);
            	setColor(12); //set color to red
                printf("\n\t\t\t\t\t  Sorry. Invalid Choice :(\n");
                break;
        }
    }
}
