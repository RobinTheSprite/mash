//
// Created by Mark on 3/15/2019.
//
#include <iostream>
#include <Windows.h>
#include "../mash-error.h"
using mash::printError;

//Syntax for command is: rf <filename>
int main(int argc, char * argv[])
{
    if (argc > 1)
    {
        //Attempt to remove the file, otherwise print an error message
        if ( DeleteFile(argv[1])
             == 0)
        {
            printError();
        }
    }
}