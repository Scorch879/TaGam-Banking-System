#include <stdio.h>
#include <windows.h>

void setColor(int color) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void logo() 
{
    setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // Set text color to green-blue
    printf("\t\t\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n");
	printf("\t\t\xBA                                                                    \t\xBA\n");
    printf("\t\t\xBA                                                                    \t\xBA\n");
	printf("\t\t\xBA     	 _____      ____       __  __  \t____    _    _   _ _  __     \t\xBA\n");
    printf("\t\t\xBA    	|_   _|_ _ / ___| __ _|  \\/  |\t| __ )  / \\  | \\ | | |/ /    \t\xBA\n");
    printf("\t\t\xBA      	  | |/ _` | |  _ / _` | |\\/| |\t|  _ < / _ \\ |  \\| | ' /     \t\xBA\n");
    printf("\t\t\xBA      	  | | (_| | |_| | (_| | |  | |\t| |_) / ___ \\| |\\  | . \\     \t\xBA\n");
    printf("\t\t\xBA      	  |_|\\__,_|\\____|\\__,_|_|  |_|\t|____/_/   \\_\\_| \\_|_|__\\    \t\xBA\n");
    printf("\t\t\xBA                                                                    \t\xBA\n");
    printf("\t\t\xBA                                                                    \t\xBA\n");
    printf("\t\t\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n");
    setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED); // Reset Text Color
}

