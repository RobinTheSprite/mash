//
// Created by Mark on 3/7/2019.
//
#include "aclapi.h"
#include <iostream>

int main(int argc, char * argv[])
{
    if (argc > 1)
    {
        if (strcmp(argv[2], "read") == 0)
        {
           if(SetNamedSecurityInfo(argv[1],
                   SE_FILE_OBJECT,
                   DACL_SECURITY_INFORMATION,
                   nullptr,
                   nullptr,
                   nullptr,
                   nullptr)
                != ERROR_SUCCESS)
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
               std::cout << "Error Setting Permissions: " << errorMessage << std::endl;


           }
        }
    }
    return 0;
}