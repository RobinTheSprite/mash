//
// Created by Mark on 3/15/2019.
//
#include <iostream>
#include <windows.h>
#include "../mash-error.h"

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