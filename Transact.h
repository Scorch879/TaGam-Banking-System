// Transact.h
#ifndef TRANSACT_H
#define TRANSACT_H

void withdraw(char *username, char *passcode, int *loggedIn);
void deposit(char *username, char *passcode, int *loggedIn);
void money_transfer(char *username, char *passcode, int *loggedIn);
int check_file_exists(const char *filename);
float get_money_fromFile(char *username, char *passcode);

//Function to check if file exists
int check_file_exists(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file != NULL)
    {
        fclose(file);
        return 1; // File exists
    }
    return 0; // File does not exist
}
#endif // Transact.h
