//
// Created by Mark on 3/1/2019.
//
#include <iostream>
using std::cout;
using std::endl;
#include <cstring>
#include "shlobj.h"
int main(int argc, char * argv[])
{
    char currentDirectory[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentDirectory);
    if (argc > 1)
    {
        if (argv[1] == std::basic_string("."))
        {

            SetCurrentDirectory(currentDirectory);
        }
        else if (argv[1] == std::basic_string(".."))
        {
            SetCurrentDirectory("..");
        }
    }
}