//
// Created by Mark on 3/3/2019.
//
#include "ShlObj.h"
#include <iostream>
using std::cout;
using std::endl;
#include <string>
#include "../mash-error.h"
using mash::printError;

std::string getDateAndTime(FILETIME filetime)
{
    SYSTEMTIME systemtime;
    char localDate[255], localTime[255];

    FileTimeToLocalFileTime( &filetime, &filetime );
    FileTimeToSystemTime( &filetime, &systemtime );
    GetDateFormat( LOCALE_USER_DEFAULT, DATE_LONGDATE, &systemtime, nullptr,
                   localDate, 255 );
    GetTimeFormat( LOCALE_USER_DEFAULT, 0, &systemtime, nullptr, localTime, 255 );

    std::string returnString(localDate);
    returnString.append(", ");
    returnString.append(localTime);
    return returnString;
}

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
    HANDLE fileHandle = FindFirstFile("*", &foundData);
    if (fileHandle == INVALID_HANDLE_VALUE)
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

        cout << foundData.cFileName;

        //Check if the user wants all of the file's info
        if (argc > 1)
        {
            if (strcmp(argv[1], "-all") == 0)
            {


                cout << "\tCreated: " << getDateAndTime(foundData.ftCreationTime)
                                     << "\tModified: " << getDateAndTime(foundData.ftLastWriteTime)
                                     << "\tSize: "
                                     << (foundData.nFileSizeHigh * (MAXDWORD + 1)) + foundData.nFileSizeLow
                                     << " bytes" << endl;
            }
        }
        else
        {
            cout << endl;
        }

        FindNextFile(fileHandle, &foundData);
    } while(GetLastError() != ERROR_NO_MORE_FILES);
    
    return 0;
}