//
// Created by Mark on 3/3/2019.
//
#include "shlobj.h"
#include <iostream>
using std::cout;
using std::endl;

int main(int argc, char * argv[])
{
    char currentDirectory[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentDirectory);

    WIN32_FIND_DATA foundData;
    HANDLE fileHandle = FindFirstFile("*", &foundData);

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