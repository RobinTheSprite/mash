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
           if(SetNamedSecurityInfo(argv[1], SE_FILE_OBJECT, DACL_SECURITY_INFORMATION | OWNER_SECURITY_INFORMATION, nullptr, nullptr, nullptr, nullptr)
                != ERROR_SUCCESS)
           {
               char wszMsgBuff[512];
               DWORD error = GetLastError();
               DWORD   dwChars = FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM |
                                                FORMAT_MESSAGE_IGNORE_INSERTS,
                                                NULL,
                                                error,
                                                0,
                                                wszMsgBuff,
                                                512,
                                                NULL );
               std::cout << "Error Setting Permissions: " << dwChars << std::endl;


           }
        }
    }
    return 0;
}