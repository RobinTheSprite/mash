//
// Created by Mark on 3/3/2019.
//
#include "shlobj.h"
#include <iostream>
using std::cout;
using std::endl;

//Syntax is the same as Linux
int main(int argc, char * argv[])
{
    //Get the current directory
    char currentDirectory[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentDirectory);

    //Get a handle to the first file in the current directory
    WIN32_FIND_DATA foundData;
    HANDLE fileHandle = FindFirstFile("*", &foundData);

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

        FindNextFile(fileHandle, &foundData);
    } while(GetLastError() != ERROR_NO_MORE_FILES);
    
    return 0;
}