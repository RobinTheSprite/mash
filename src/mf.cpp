//
// Created by Mark on 3/15/2019.
//
#include <Windows.h>
#include <iostream>
#include "../mash-error.h"
using mash::printError;

//Syntax for command is: mf <filename>
int main(int argc, char * argv[])
{
    if (argc > 1)
    {
        //Attempt to create the file, otherwise print an error message
       if ( CreateFile(
                argv[1],
                GENERIC_ALL,
                FILE_SHARE_READ,
                nullptr,
                CREATE_NEW,
                FILE_ATTRIBUTE_NORMAL,
                nullptr )
                == INVALID_HANDLE_VALUE)
       {
           printError();
       }
    }
}