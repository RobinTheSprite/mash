//
// Created by Mark on 3/3/2019.
//
#include "shlobj.h"
#include <iostream>
#include "mash-error.h"
using std::cout;
using std::endl;

//Syntax is the same as Linux
int main(int argc, char * argv[])
{
    //Get the current directory
    char currentDirectory[MAX_PATH];
    if (GetCurrentDirectory(MAX_PATH, currentDirectory) == 0)
    {
        printError();
    }

    //Get a handle to the first file in the current directory
    WIN32_FIND_DATA foundData;
    if (HANDLE fileHandle = FindFirstFile("*", &foundData) == INVALID_HANDLE_VALUE)
    {
        printError();
    }

    //Find and print out the first and every subsequent file and directory
    do{
        if (foundData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
        {
            cout << "Directory: ";
        } 
        else
        {
            cout << "File:      ";
        }
        cout << foundData.cFileName << endl;

        if (FindNextFile(fileHandle, &foundData) == 0)
        {
            printError();
        }
    } while(GetLastError() != ERROR_NO_MORE_FILES);
    
    return 0;
}