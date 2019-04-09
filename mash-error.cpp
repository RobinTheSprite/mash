// mash-error.cpp
// Created by Mark on 4/6/2019.
//

#include <Windows.h>
#include <iostream>

namespace mash
{

//printError
//Tell me what the last error in this thread was
void printError()
{
    LPTSTR errorMessage = nullptr;
    DWORD errorCode = GetLastError();
    FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER
                   | FORMAT_MESSAGE_FROM_SYSTEM
                   | FORMAT_MESSAGE_IGNORE_INSERTS,
                   nullptr,
                   errorCode,
                   0,
                   (LPTSTR)&errorMessage,
                   0,
                   nullptr );
    std::cout << "Error: " << errorMessage << std::endl;
}

}