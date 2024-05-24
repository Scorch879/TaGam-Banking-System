#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "OtherServices.h"
#define ACCOUNTS_FILE "database.txt" // File path for storing account data
#define MAX_USERNAME_LENGTH 100
#define MAX_PASSCODE_LENGTH 100

char fileUsername[MAX_USERNAME_LENGTH + 1];
char filePasscode[MAX_PASSCODE_LENGTH + 1];
float money;
int i = 0;

// Function to read the money from the file
float get_money_fromFile(char *username, char *passcode)
{
    FILE *file = fopen(ACCOUNTS_FILE, "r"); // Open the file in read mode
    if (file == NULL)
    {
    	setColor(12);//Red
        printf("\n\n\t\t\t\t\tError in accessing details!\n");
        return -1;
    }

    while (fscanf(file, "%s %s %f", fileUsername, filePasscode, &money) == 3)
    {
        if (strcmp(username, fileUsername) == 0 && strcmp(passcode, filePasscode) == 0)
        {
            fclose(file); // Close the file
            return money; // Returns money value
        }
    }

    fclose(file); // Close the file
    return -1; // Return a negative value to indicate username/passcode not found
}

float getMoney_byUsername(const char *username) 
{
    FILE *file = fopen(ACCOUNTS_FILE, "r"); // Read mode 
    if (file == NULL) 
	{
		setColor(12);//Red
        printf("\n\n\t\t\t\t\tError in accessing details!\n");
        return -1;
    }

    char fileUsername[MAX_USERNAME_LENGTH + 1]; // Variables so that it can just read from the file (temp)
    char filePasscode[MAX_PASSCODE_LENGTH + 1];
    float money;

    while (fscanf(file, "%s %s %f", fileUsername, filePasscode, &money) == 3)
	{
        if (strcmp(username, fileUsername) == 0)
		{
            fclose(file); // Close the file
            return money; // Return money value
        }
    }

    fclose(file); // Close the file
    return -1; // Return a negative value to indicate username not found
}

void updateMoney(const char *username, const char *passcode, float newMoney, int *status)
{
    FILE *file = fopen(ACCOUNTS_FILE, "r");
    if (file == NULL)
    {
    	setColor(12);//Red
        printf("\n\n\t\t\t\t\tError opening file for reading.\n");
        return;
    }


    // Read the entire file into memory
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);  
    fseek(file, 0, SEEK_SET);
    
    char *fileContent = (char *)malloc(fileSize + 1);
    fread(fileContent, 1, fileSize, file);
    fclose(file);
    fileContent[fileSize] = '\0';

    // Open the file for writing
    file = fopen(ACCOUNTS_FILE, "w");
    if (file == NULL)
    {
    	setColor(12); //Red
        printf("Error opening file for writing.\n");
        free(fileContent);
        return;
    }

    // Variables for scanning the file content
    char *line = strtok(fileContent, "\n");
    int found = 0;

    while (line != NULL) //Iterates through the token from strtok until it hits no more content (NULL)
    {
        sscanf(line, "%s %s %f", fileUsername, filePasscode, &money);
        if (strcmp(username, fileUsername) == 0 && (passcode == NULL || strcmp(passcode, filePasscode) == 0))
        {
            fprintf(file, "%s %s %.2f\n", fileUsername, filePasscode, newMoney);
            found = 1;
        }
        else
        {
            fprintf(file, "%s\n", line);
        }
        line = strtok(NULL, "\n"); //Tokenizing the the content of fileContent meaning it will split the contents of "file content"
    }								// Each substring ends with a newline character like username | passcode | money will be split
    								// The token returned by strok(line) represents a line in the file and then each line is then scanned
    								// Through using sscanf to extract the username | passcode | money value from it 
    								// If it matches any of the conditions above then it will update the corresponding money

    fclose(file);
    free(fileContent);

    if (found)
    {
    	setColor(14); //Yellow
        printf("\n\n\t\t\t\t\tTransaction Successful!\n");
        *status = 1;
    }
    else
    {
    	setColor(12);
        printf("\n\n\t\t\t\t\tAccount not found.\n");
        sleep(1);
    }
}

int verify_balance(float money, float amount)
{
	if (money >= amount && amount > 0)
		return 1;
	else
		return 0;
}

void deposit(char *username, char *passcode, int *loggedIn)
{
    float newMoney = 0;
    float depositAmount, record_transact_dep = 0;
    int status = 0;
    char confVal;
    system("cls");
    logo();

    if (*loggedIn == 0)
    {
        login(username, passcode, loggedIn);
    }

    money = get_money_fromFile(username, passcode);

    if (*loggedIn == 1)
    {
        while (1)
        {
        back:
        	system("cls");
        	logo();
        invalid_input_catch:
        	setColor(14);//Yellow
        	printf("\n\n\t\t\t\t\tUsername: %s", username);
        	printf("\n\t\t\t\t\tBalance: $%0.2f", money);
        	printf("\n\t\t\t\t\tMax Limit: $100,000.00");
            printf("\n\n\t\t\t\t\tPlease enter amount of money you want to deposit:\n");
            printf("\n\t\t\t\t\tAmount: ");
            if (scanf("%f", &depositAmount) == 0 || depositAmount < 0)  //checks if the input is truly a float
            {
            	fflush(stdin);
            	system("cls");
            	logo();
            	setColor(12); //Red
            	printf("\n\n\t\t\t\t\tInvalid Amount!\n");
            	goto invalid_input_catch;
			}
            
            if (depositAmount > 100000.50)
            {
                system("cls");
                logo();
                setColor(12);//Red
                printf("\n\n\t\t\t\t  Sorry. Deposit limit has been reached. Above 100k is not allowed.");
                printf("\n\n\t\t\t\t\tReturning in\n\t\t\t\t\t");
	                for (i = 2 ; i > 0; i--)
	            	{   
		            	printf("%d ", i);
		                sleep(1);
	            	}
            }
            else
            {
            	fflush(stdin);
            	break;
            }
        }

        system("cls");
        logo();
        setColor(14);//Yellow
        printf("\n\n\t\t\t\t\tDeposit Amount: $%.2f", depositAmount);
        printf("\n\t\t\t\t\tPlease confirm transaction:\n");
        printf("\t\t\t\t\tYES - Press 1        CANCEL - Press 0\n");
        printf("\t\t\t\t\t: ");
        scanf(" %c", &confVal);
			fflush(stdin);
        system("cls");
        logo();

        if (confVal == '1')
        {
        	record_transact_dep = depositAmount;
        	record_transaction(username, "Deposit" , depositAmount); 
            newMoney = money + depositAmount;
            updateMoney(username, passcode, newMoney, &status);
        }
        else if (confVal == '0')
        {
            goto back;
        }

        if (status == 1)
        {
        	setColor(14); //Yellow
            printf("\n\t\t\t\t\tNew Balance: $%.2f", newMoney);
           
            *loggedIn = 0;
            printf("\n\n\t\t\t\t\tReturning in\n\t\t\t\t\t");
	                for (i = 3 ; i > 0; i--)
	            	{   
		            	printf("%d ", i);
		                sleep(1);
	            	}
        }
    }
    else
    {
        system("cls");
        logo();
        printf("\n\n\t\t\t\t\tLogin Failed. Returning to Main Screen!");
        *loggedIn = 0;
    }
}

void withdraw(char *username, char *passcode, int *loggedIn)
{
    float newMoney = 0;
    float amount = 0;
    char choice_amount;
    int status = 0; // 0 means not yet success
	float record_transact_withdraw = 0;
    system("cls"); // Clears the screen
    logo(); // Calls logo function

    if (*loggedIn == 0)
    {
        login(username, passcode, loggedIn); // Calls the login function
    }

    money = get_money_fromFile(username, passcode); // Gets the username and passcode to find its balance

    if (*loggedIn == 1)
    {
    	Home:
    	setColor(14); //Yellow
        printf("\n\n\t\t\t\t\tUsername: %s", username);
        printf("\n\t\t\t\t\tBalance: $%0.2f", money);
        printf("\n\n\t\t\t\t\tSelect Withdrawal Amount:");
        printf("\n\t\t\t\t\t1: $500");
        printf("\n\t\t\t\t\t2: $1000");
        printf("\n\t\t\t\t\t3: $2000");
        printf("\n\t\t\t\t\t4: $5000");
        printf("\n\t\t\t\t\t5: $10,000");
        printf("\n\t\t\t\t\t6: Input Amount");
        printf("\n\t\t\t\t\tSelection: ");
        scanf(" %c", &choice_amount);
			fflush(stdin);
        // Check to see if balance is sufficient
        system("cls");
        logo();
        switch (choice_amount)
        {
            case '1': amount = 500; break;
            case '2': amount = 1000; break;
            case '3': amount = 2000; break;
            case '4': amount = 5000; break;
            case '5': amount = 10000; break;
            case '6':
            	{
            		setColor(14); //Yellow
                	printf("\n\n\t\t\t\t\tEnter Amount: ");
                	if (scanf("%f", &amount) == 0 || amount < 0)
                	{
                		fflush(stdin);
                		system("cls");
                		logo();
                		setColor(12);
                		printf("\n\n\t\t\t\t\tInvalid Amount!\n");
                		goto Home;
					}
                	
                	break;
            	}
            default:
            	fflush(stdin);
                		system("cls");
                		logo();
                		setColor(12);
                		printf("\n\n\t\t\t\t\tInvalid Choice!\n");
                		goto Home;
        }

        // Calculation and Money update Block
        if (verify_balance(money, amount) == 0)
        {
        	setColor(12);//Red
            printf("\n\t\t\t\t\tInsufficient Balance!!");
            printf("\n\t\t\t\t\tLogging Out!\n");
            *loggedIn = 0;
            printf("\n\n\t\t\t\t\tReturning in\n\t\t\t\t\t");
	                for (i = 2 ; i > 0; i--)
	            	{   
		            	printf("%d ", i);
		                sleep(1);
	            	}
        }
        else
        {
        		char choice_confirm;
        		setColor(14); //Yellow
        		printf("\n\n\t\t\t\t\tUsername: %s", username);
        		printf("\n\t\t\t\t\tBalance: $%0.2f", money);
        		printf("\n\t\t\t\t\tWithdraw Amount: $%.2f", amount);
       			printf("\n\t\t\t\t\tPlease confirm transaction:\n");
        		printf("\t\t\t\t\tYES - Press 1        CANCEL - Press 0\n");
        		printf("\t\t\t\t\t: ");
        			scanf(" %c", &choice_confirm);
        				fflush(stdin);
        		switch(choice_confirm)
        		{
        			case '1':
        				{
        					record_transact_withdraw = amount;
        					record_transaction(username, "Withdrawal" , record_transact_withdraw); 
        					newMoney = money - amount;
            				newMoney = roundf(newMoney * 100.0) / 100.0; // Round to two decimal places
            				updateMoney(username, passcode, newMoney, &status);
            				break;
						}
					case '0':
						{
							system("cls");
							logo();
							setColor(12); //Red
							printf("\n\t\t\t\t\tTransaction Cancelled!");
							sleep(1);
							goto Home;
							break;
						}
					default:
						system("cls");
						logo();
						setColor(12); //Red
						printf("\n\n\t\t\t\t\tInvalid Input, Please try again!");
						goto Home;
				}
			}
            

            if (status == 1)
            {
            	fflush(stdin);
            	system("cls");
            	logo();
            	setColor(14); //Yellow
            	printf("\n\n\t\t\t\t\tUsername: %s", username);
                printf("\n\t\t\t\t\tBalance: $%.2f", newMoney);
                printf("\n\t\t\t\t\tTransaction Success!\n");
                printf("\n\t\t\t\t\tPress any button to continue!");
                getchar();
                fflush(stdin);
                *loggedIn = 0;
            }
        }
    	else
    	{
	        system("cls");
	        logo();
	        setColor(12); //Red
	        printf("\n\n\t\t\t\t\tLogin Failed. Returning to Main Screen!");
	        *loggedIn = 0;
	        printf("\n\n\t\t\t\t\tReturning in\n\t\t\t\t\t");
	                for (i = 2 ; i > 0; i--)
	            	{   
		            	printf("%d ", i);
		                sleep(1);
	            	}
    	}
}

void money_transfer(char *username, char *passcode, int *loggedIn)
{
    float mainAcctMoney, recipientAcctMoney, amount;
    char recipient_username[MAX_USERNAME_LENGTH + 1];
    int status = 0;

    system("cls");
    logo();

    if (*loggedIn == 0)
    {
        login(username, passcode, loggedIn);
    }

    if (*loggedIn == 1)
    {
        mainAcctMoney = get_money_fromFile(username, passcode); // Retrieve the main account balance

        if (mainAcctMoney == -1) // Check if Account is not found
        {
            system("cls");
            logo();
            setColor(12); //Red
            printf("\n\n\t\t\t\t\tAccount does not exist!\n");
            *loggedIn = 0;
            return;
        }

        // Recipient Block
        system("cls");
        logo();
        while(1)
        {
        	transfer:
        	setColor(14); //Yellow
            printf("\n\n\t\t\t\t\tUsername: %s", username);
            printf("\n\t\t\t\t\tCurrent Balance: $%0.2f", mainAcctMoney);
            printf("\n\t\t\t\t\tEnter Recipient Account Name: ");
            scanf("%s", recipient_username);
            	fflush(stdin);
            //Condition to check if recipient_username is same as username
            if (strcmp(recipient_username, username) == 0)
            {
            	system("cls");
            	logo();
            	setColor(12);
            	printf("\n\n\t\t\t\t   Recipient cannot be the same account!!");
            	goto transfer;
			}
            
            recipientAcctMoney = getMoney_byUsername(recipient_username); // Retrieve Recipient Account balance
            if (recipientAcctMoney == -1)
            {
                system("cls");
                logo();
                setColor(12); //Red
                printf("\n\t\t\t\t\tRecipient Account not Found!\n");
            }
            else
                break;
        }

        // Funds Block
        system("cls");
        logo();
        funds:
        setColor(14); //Yellows
        printf("\n\n\t\t\t\t\tUsername: %s", username);
        printf("\n\t\t\t\t\tCurrent Balance: $%0.2f", mainAcctMoney);
        printf("\n\t\t\t\t\tEnter Recipient Account Name: %s", recipient_username);
        printf("\n\n\t\t\t\t\tEnter Amount to transfer: ");
        if (scanf("%f", &amount) != 1 || amount < 0)
        {
        	fflush(stdin);
        	system("cls");
        	logo();
        	setColor(12); //Red
        	printf("\n\n\t\t\t\t\tAmount Invalid!");
        	fflush(stdin);
        	fflush(stdin);
        	goto funds;
		}
        else
        {
        	system("cls");
        	logo();
        	char choice_transfer_confirm;
        	choice_transfer:
        	setColor(14); //Yellow
       		printf("\n\n\t\t\t\t\tUsername: %s", username);
       		printf("\n\t\t\t\t\tBalance: $%0.2f", money);
       		printf("\n\t\t\t\t\tTransfer Amount: $%.2f", amount);
       		printf("\n\t\t\t\t\tRecipient Account Name: %s", recipient_username);
       		printf("\n\t\t\t\t\tPlease confirm transaction:\n");
       		printf("\t\t\t\t\tYES - Press 1        CANCEL - Press 0\n");
       		printf("\t\t\t\t\t: ");
       			scanf(" %c", &choice_transfer_confirm);
        	switch(choice_transfer_confirm)
        	{
        		case '1':
        			{
						        if (verify_balance(mainAcctMoney, amount) == 0)
						        {
						            system("cls");
						            logo();
						            setColor(12); //Red
						            printf("\n\n\t\t\t\t\tInsufficient Balance!!");
						            printf("\n\t\t\t\t\tLogging Out!");
						            *loggedIn = 0;
						            printf("\n\n\t\t\t\t\tReturning in\n\t\t\t\t\t");
						                for (i = 2 ; i > 0; i--)
						            	{   
							            	printf("%d ", i);
							                sleep(1);
						            	}
						            return;
						        }
						
						        // Deduction of money from main account
						        mainAcctMoney -= amount;
						        mainAcctMoney = roundf(mainAcctMoney * 100.0) / 100.0; // Round to two decimal places
						        updateMoney(username, passcode, mainAcctMoney, &status);
								
						        if (status == 1)
						        {
						            // Addition of amount to recipient's account
						            recipientAcctMoney += amount;
						            recipientAcctMoney = roundf(recipientAcctMoney * 100.0) / 100.0; // Round to two decimal places
						            updateMoney(recipient_username, NULL, recipientAcctMoney, &status); // Use NULL for passcode
						
						            if (status == 1)
						            {
						                system("cls");
						                logo();
						                setColor(14); //Yellow
						                record_transaction(username, "Transfer", amount);
						                record_transaction(recipient_username, "Transfer", amount);
						                printf("\n\n\t\t\t\t\tTransfer Successful!");
						                printf("\n\t\t\t\t\tUsername: %s", username);
						                printf("\n\t\t\t\t\tCurrent Balance: $%.2f", mainAcctMoney);
						                printf("\n\n\t\t\t\t\tReturning in\n\t\t\t\t\t");
						                for (i = 2 ; i > 0; i--)
						            	{   
							            	printf("%d ", i);
							                sleep(1);
						            	}
						            }
						            else
						            {
						                // Rollback in case of failure to update recipient's account
						                mainAcctMoney += amount;
						                updateMoney(username, passcode, mainAcctMoney, &status);
						                record_transaction(username, "Failed", amount);
						                system("cls");
						                logo();
						                setColor(12); //Red
						                printf("\n\n\t\t\t\t\tTransfer Failed. Transaction Cancelled!");
						                printf("\n\n\t\t\t\t\tReturning in\n\t\t\t\t\t");
						                for (i = 2 ; i > 0; i--)
						            	{   
							            	printf("%d ", i);
							                sleep(1);
						            	}
						            }
						        }
						        else
						        {
						            for (i = 2 ; i >= 0; i--)
						            {   
						            	system("cls");
						            	logo();
										setColor(12); //Red
						            	printf("\n\n\t\t\t\t\tTransfer Failed. Returning to Main Screen in %d\n", i);
						            	printf("\n\n\t\t\t\t\tReturning in\n\t\t\t\t\t");
						                for (i = 2 ; i > 0; i--)
						            	{   
							            	printf("%d ", i);
							                sleep(1);
						            	}
									}
						    	}
						        
						        *loggedIn = 0;
						break;
					}		
				case '0':
					{
						system("cls");
						logo();
						setColor(12); //Red
						printf("\n\n\t\t\t\t\tTransaction Cancelled!\n");
						goto transfer;
						break;
					}
				default:
				    	system("cls");
						logo();
						setColor(12); //red
						printf("\n\n\t\t\t\t\tInvalid Input!\n");
						goto transfer;
			}
		}
	}	
}
