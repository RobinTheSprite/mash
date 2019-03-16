//
// Created by Mark on 3/15/2019.
//
#include <error.h>
#include <fileapi.h>
#include <windows.h>
#include <iostream>

int main(int argc, char * argv[])
{
    if (argc > 1)
    {
        if (CreateDirectory(argv[1], nullptr) == 0)
        {
            if (GetLastError() == ERROR_ALREADY_EXISTS)
            {
                std::cout << "The directory \"" << argv[1] << "\" already exists" << std::endl;
            }
        }
    }
}