#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logo.h"
#include "AcctManage.h"
#define TRANSACTION_HISTORY_FILE "transaction_history.txt"

// Function to generate a random reference number
char *generate_reference_number() 
{
	int i;
    char *ref_number = (char*)malloc(11 * sizeof(char));
    if (ref_number == NULL)
    {
    	return NULL; //IF memory fails
	}
	
	// Seed the random number generator
	srand(time(NULL) + rand());
	
    for (i = 0; i < 10; i++) 
	{
        ref_number[i] = 'A' + (rand() % 26);
    }
    ref_number[10] = '\0';
    return ref_number;
}

// Function to record a transaction
void record_transaction(const char* username, const char* transaction_type, float amount) 
{
    FILE *file = fopen(TRANSACTION_HISTORY_FILE, "a");
    if (file == NULL) 
	{
		system("cls");
		logo();
		setColor(12); //Red
        printf("Error opening transaction history file.\n");
        return;
    }
    
    char* ref_number = generate_reference_number();
	    if (ref_number != NULL)
	    {
		    fprintf(file, "%s %s %0.2f %s\n", username, transaction_type, amount, ref_number);
		    fclose(file);
		    free(ref_number);
		}
		else
		{
			system("cls");
			logo();
			printf("\n\n\t\t\t\tReference Code not Generated!\n");
		}
}

// Function to display transaction history
void display_transaction_history(char* username, char *passcode, int *loggedIn) 
{
	if (*loggedIn == 0)
    {
        login(username, passcode, loggedIn); // Calls the login function
    }
    
    FILE *file = fopen(TRANSACTION_HISTORY_FILE, "r");
    if (file == NULL) 
	{
		system("cls");
		logo();
		setColor(12); //Red
        printf("\n\n\t\t\t\t        No Transaction History Yet!\n");
        loggedIn = 0;
        return;
    }
	
    char file_username[MAX_USERNAME_LENGTH + 1];
    char transaction_type[20];
    float amount;
    char ref_number[11];
    int found = 0;
	
	while (fscanf(file, "%s %s %f %s", file_username, transaction_type, &amount, ref_number) == 4) 
	{
        if (strcmp(username, file_username) == 0) 
		{
			found = 1;
        }
    }
    
	rewind(file);//Reset file pointer
	
	if (found == 1)
	{
		system("cls");
		logo();
		setColor(14); //Yello
	    printf("\n\n\t\t\t\t Transaction History for Account: %s", username);
	    printf("\n\n\t\t\t    %-10s          %-15s %-10s", "Type", "Amount", "Reference Code");
	    printf("\n\t\t         \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\n"); //53	
		while (fscanf(file, "%s %s %f %s", file_username, transaction_type, &amount, ref_number) == 4) 
		{
	        if (strcmp(username, file_username) == 0) 
			{
				setColor(14); //Yellow
	            printf("\t\t\t   %-10s", transaction_type); 
	            setColor(9); // Light Blue
	            printf("\t    %10.2f", amount);
	            setColor(13); //Light Cyan
	            printf("\t          %-10s\n ", ref_number);
            } 
	    }
	
		setColor(14); //Yellow
		printf("\n\n\t\t\t\t      Press Any Button to Continue");
		getch();
		*loggedIn = 0;
		system("cls");
		logo();
	
	}
	    else
		{
			system("cls");
			logo();
			setColor(12); //Red
	        printf("\n\n\t\t\t\t\t   No transactions found!\n");
	    }
fclose(file);
}	
