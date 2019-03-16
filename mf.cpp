//
// Created by Mark on 3/15/2019.
//
#include <iostream>
#include <windows.h>

int main(int argc, char * argv[])
{
    if (argc > 1)
    {
       if ( CreateFile(
                argv[1],
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_READ,
                nullptr,
                CREATE_NEW,
                FILE_ATTRIBUTE_NORMAL,
                nullptr )
                == INVALID_HANDLE_VALUE)
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
           std::cout << "Error Creating File \""<< argv[1] <<"\": "  << errorMessage << std::endl;
       }
    }
}