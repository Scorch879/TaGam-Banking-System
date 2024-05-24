// Other_Services.h
#ifndef OTHER_SERVICES_H
#define OTHER_SERVICES_H
void record_transaction(const char *username, const char *transaction_type, float amount);
void display_transaction_history(char* username, char *passcode, int *loggedIn);
#endif
