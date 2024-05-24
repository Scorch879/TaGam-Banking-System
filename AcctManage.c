#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logo.h"
#include "AcctManage.h"
#include "OtherServices.h"
#define MAX_ACCOUNTS 100 // Maximum number of accounts
#define MAX_USERNAME_LENGTH 11
#define MAX_PASSCODE_LENGTH 9
#define ACCOUNTS_FILE "database.txt" // File path for storing account data

// Function to check if an account exists
int accountExists(char *username,char *passcode) //username and passcode points to the username and passcode inputted 
{
    FILE *file = fopen(ACCOUNTS_FILE, "r"); //File syntax to open text file in read mode
    if (file == NULL) //If file cannot be read or does not exist
	{
		setColor(12); //red for error
        printf("\n\n\t\t\t\t\tError!\n\t\t\t\t\tReturning to Main screen.\n");
        return 0;
    }

    char fileUsername[MAX_USERNAME_LENGTH];
    char filePasscode[MAX_PASSCODE_LENGTH];
    float money;

    while (fscanf(file, "%s %s %f", fileUsername, filePasscode, &money) != EOF)  //EOF means end of file, loop until fscanf returns EOF
	{
        if (strcmp(username, fileUsername) == 0 && strcmp(passcode, filePasscode) == 0) //Checks to see if the inputted username and pasocde matches
		{
            fclose(file); //Closes the file 
            return 1; // Account found
        }
    }

    fclose(file); //Closes the file 
    return 0; // Account not found
}

int check_name(char *username) //username  points to the username inputted 
{
    FILE *file = fopen(ACCOUNTS_FILE, "a+"); //File syntax to open text file in read mode
    if (file == NULL) //If file cannot be read or does not exist
	{
		setColor(12); //red for error
        printf("\n\n\t\t\t\t\tError!\n\t\t\t\t\tReturning to Main screen.\n");
        return 0;
    }

    char fileUsername[MAX_USERNAME_LENGTH];
    char filePasscode[MAX_PASSCODE_LENGTH];
    float money;

    while (fscanf(file, "%s %s %f", fileUsername, filePasscode, &money) != EOF)  //EOF means end of file, loop until fscanf returns EOF
	{
        if (strcmp(username, fileUsername) == 0) //Checks to see if the inputted username and pasocde matches
		{
            fclose(file); //Closes the file 
            return 1; // Account found
        }
    }

    fclose(file); //Closes the file 
    return 0; // Account not found
}

// Function to login to an account
void login(char *username, char *password, int *loggedIn) 
{
	char cancel_choice;
    char loginusername[MAX_USERNAME_LENGTH];
    char loginpasscode[MAX_PASSCODE_LENGTH];
    
    login:
    system("cls");
    logo();
	setColor(14); // Set color to yellow for success message which is default color
    printf("\n\n\t\t\tEnter Username: ");
    scanf("%s", loginusername);
    printf("\n\t\t\tEnter Password: ");
    scanf("%s", loginpasscode);

    if (accountExists(loginusername, loginpasscode))  //Checks if account does exist using the function passing the inputs
	{
        strcpy(username, loginusername); //Copies the input to the username and passcode 
        strcpy(password, loginpasscode);
        *loggedIn = 1;
        system("cls");
        logo();
        setColor(14);//Yellow
        printf("\n\t\t\t\t     Account Logged in Successfully!\n");
        sleep(1);
    } 
	else 
	{
		system("cls");
		logo();
		setColor(12); // red for error
        printf("\n\t\t\t\tUsername or passcode does not exist or didn't match.\n");
        
        again:
        printf("\n\t\t\t\tDo you wish to login again? (Y / N): ");
        	scanf(" %c", &cancel_choice);
        switch(cancel_choice)
        {
        	case 'Y':
        	case 'y':
        		{
        			goto login;
        			break;
				}
        	case 'N': 
			case 'n':
        		{
        			system("cls");
        			logo();
        			return;
				}
			default:
				system("cls");
				logo();
				setColor(12); //Red
				printf("\n\t\t\t\tChoice Invalid!!");
				goto again;
				
		}
        
    }
}

void accountCreation() 
{
    User *newUser = (User *)malloc(sizeof(User));
    if (newUser == NULL) 
	{
        printf("Memory allocation failed.\n");
        return;
    }
	fflush(stdin);
	system("cls");
	logo();
	while(1) //Username Loop
	{
		username:
		setColor(14); //set color
	    printf("\n\n\t\t  Enter Account Username (No SPACES | Max = 10 characters!!): ");
	    scanf("%[^\n]", newUser->username);
	    	fflush(stdin);
				
	    		//Condition Blocks for error trapping
	    		if (strlen(newUser->username) > 10 || strlen(newUser->username) < 5)
	    		{
	    			if (strchr(newUser->username, ' ') != NULL) //Maybe redundant?
	    			{
		    			system("cls");
		    			logo();
		    			setColor(12); //red for error
		    			printf("\n\t\t\t\tUsername is too long or too short. Try again!\n");
						printf("\n\t\t\t\t   Username contains spaces. Try again!\n");
						goto username;
					}
	    			system("cls");
	    			logo();
	    			setColor(12); //red for error
	    			printf("\n\t\t\t\tUsername is too long or too short. Try again!\n");
				}
				else if (strchr(newUser->username, ' ') != NULL)
				{
					system("cls");
	    			logo();
	    			setColor(12); //red for error
					printf("\n\t\t\t\t   Username contains spaces. Try again!\n");
				}
				else
				{
					if (check_name(newUser->username) == 1)
					{
						system("cls");
		    			logo();
		    			setColor(12); //red for error
						printf("\n\t\t\t\t   Username already used. Try again!\n");
					}
					else
						break;
				}
				
	}
	
	while(1) //Passcode Loop
	{
		password:
		setColor(14); //Yellow
	    printf("\n\t\t  Enter Account 8-Character Password: ");
	    	scanf("%[^\n]", newUser->passcode);
    		fflush(stdin);
	    		if (strlen(newUser->passcode) > 8 || strlen(newUser->passcode) < 3) 
	    		{
	    			if (strchr(newUser->passcode, ' ') != NULL) //if all error has been tripped
	    			{
	    				system("cls"); //Maybe redundant?
			    		logo();
			    		setColor(12); //red for error
			    		printf("\n\t\t\t      Password is too long or too short :). Try again!\n");
						printf("\n\t\t\t\t   Password contains spaces. Try again!\n");	
						goto password;
					}
	    			system("cls"); //if too short or long only
		    		logo();
		    		setColor(12); //red for error
	    			printf("\n\t\t\t      Password is too long or too short :). Try again!\n");
				}
				else if (strchr(newUser->passcode, ' ') != NULL) //Space is only the error
				{
					system("cls");
		    		logo();
		    		setColor(12); //red for error
					printf("\n\t\t\t\t   Password contains spaces. Try again!\n");			
				}
				else
					break;
				
	}
    newUser->money = 0; //Initializes to 0 

    registerAccount(newUser->username, newUser->passcode, newUser->money); //Passes the pointer username and passcode to the function

    free(newUser); //frees newUser
}

void registerAccount(const char *username, const char *password, float money) 
{
    FILE *file = fopen("database.txt", "a"); // Open the file in appendmode
    if (file != NULL) 
    {
        char fileUsername[MAX_USERNAME_LENGTH + 1];
        char filePasscode[MAX_PASSCODE_LENGTH + 1];
        float fileMoney;

        // Read each line of the file to check for duplicates
        while (fscanf(file, "%s %s %f", fileUsername, filePasscode, &fileMoney) == 3) 
        {
            if (strcmp(username, fileUsername) == 0) // Check for username duplication
            {
                fclose(file); // Close the file
                system("cls");
                logo();
                setColor(12); // Set color to red for error message
                printf("\n\n\t\t\t\t\t  Username already exists!\n");
                return;
            }
        }

        fclose(file); // Close the file
        
        // If no duplicate found, open the file in append mode to register the new account
        file = fopen("database.txt", "a+");
        if (file != NULL) 
        {
            fprintf(file, "%s %s %0.2f\n", username, password, money); // Append the new account details
            fclose(file); // Close the file
            system("cls");
            logo();
            setColor(14); // Set color to yellow for success message which is default color
            printf("\n\n\t\t\t\t\tAccount registered successfully!\n");
        } 
        else 
        {
        	system("cls");
        	logo();
            printf("\n\n\t\t\t\t\tFailed to open database file.\n");
        }
    } 
    else 
    {
    	system("cls");
        logo();
        printf("\n\n\t\t\t\t\tFailed to open database file.\n");
    }
}

void removeAccountFromFile(const char *username, const char *passcode) 
{
	int i = 0;
	float money = get_money_fromFile(username, passcode); //Retrieve Money to check if its 0
	
	if (money == 0.00)
	{
	    FILE *file = fopen(ACCOUNTS_FILE, "r"); //Opens the file for read mode
	    if (file == NULL) 
	    {
	    	setColor(12);
	        printf("\n\n\t\t\t\t\tError opening file for reading.\n");
	        return;
	    }
	
	    FILE *tempFile = fopen("temp.txt", "w"); //Opens the temp_file for write mode
	    if (tempFile == NULL) 
	    {
	    	setColor(12);
	        printf("\n\n\t\t\t\t\tError opening temporary file.\n");
	        fclose(file); //Closes the original file to prevent corruption
	        return; //Return if error occurs
	    }
	
	    char fileUsername[MAX_USERNAME_LENGTH]; //Declaration of fileusername (temporary)
	    char filePasscode[MAX_PASSCODE_LENGTH];//Declaration of filepasscode (temporary)
		
		    while (fscanf(file, "%s %s %f", fileUsername, filePasscode, &money) != EOF)  //EOF means end of file
		    {
		        if (strcmp(username, fileUsername) != 0 || strcmp(passcode, filePasscode) != 0) //Checks to see if the inputted username and pasocde doesatch
		        {
		            fprintf(tempFile, "%s %s %.2f\n", fileUsername, filePasscode, money); //Copies the accounts into the new file to erase the old one
		        }
		    }
		
		    fclose(file);
		    fclose(tempFile);//closes the tempfile
		
		    // Remove the original file and rename the temporary file
		    remove(ACCOUNTS_FILE);
		    rename("temp.txt", ACCOUNTS_FILE);
			system("cls");
			logo();
			setColor(14); //Yellow
		    printf("\n\n\t\t\t\t\tAccount terminated successfully!\n");
		    printf("\n\n\t\t\t\t\tReturning in\n\t\t\t\t\t");
		        for (i = 2 ; i >= 0; i--)
		        {   
			    	printf("%d ", i);
			    	sleep(1);
		       	}
		    system("cls");
		    logo();
		    setColor(14);
		    printf("\n\n\t\t\t\t\tAccount terminated successfully!\n");
	}
	else
	{
		system("cls");
		logo();
		setColor(12);
		printf("\n\n\t\t\t\t\tAccount has remaining balance!\n");
		printf("\n\n\t\t\t\t\tReturning in\n\t\t\t\t\t");
		for (i = 2 ; i >= 0; i--)
        {   
	    	printf("%d ", i);
	    	sleep(1);
		}
	    system("cls");
	    logo();
		}
	
}

// Function to terminate an account
void terminateAccount(const char *username, const char *passcode) 
{
    removeAccountFromFile(username, passcode); //Calls function and passing the username and passcode which points to the username and password
}
