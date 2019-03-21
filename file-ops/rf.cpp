//
// Created by Mark on 3/15/2019.
//
#include <iostream>
#include <windows.h>

//Syntax for command is: rf <filename>
int main(int argc, char * argv[])
{
    if (argc > 1)
    {
        //Attempt to remove the file, otherwise print an error message
        if ( DeleteFile(argv[1])
             == 0)
        {
            LPTSTR errorMessage;
            DWORD errorCode = GetLastError();
            FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |
                           FORMAT_MESSAGE_FROM_SYSTEM |
                           FORMAT_MESSAGE_IGNORE_INSERTS,
                           nullptr,
                           errorCode,
                           0,
                           (LPTSTR)&errorMessage,
                           0,
                           nullptr );
            std::cout << "Error Deleting File \""<< argv[1] <<"\": "  << errorMessage << std::endl;
        }
    }
}