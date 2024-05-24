// AcctManage.h
#ifndef ACCTMANAGE_H
#define ACCTMANAGE_H

#define MAX_USERNAME_LENGTH 11
#define MAX_PASSCODE_LENGTH 9
#define ACCOUNTS_FILE "database.txt" // File path for storing account data

typedef struct 
{
    char username[MAX_USERNAME_LENGTH + 1]; // +1 for null terminator
    char passcode[MAX_PASSCODE_LENGTH + 1]; // +1 for null terminator
    float money;
} User;

void login(char *username, char *password, int *loggedIn);
void accountCreation();
void registerAccount(const char *username, const char *password, float money);
void terminateAccount(const char *username, const char *passcode);

#endif // AcctManage.h
