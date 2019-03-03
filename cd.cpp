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
    if (argc > 1)
    {
        if (argv[1] == std::basic_string("."))
        {
            char directory[MAX_PATH];
            GetCurrentDirectory(MAX_PATH, directory);
            cout << directory << endl;
        }
    }
}