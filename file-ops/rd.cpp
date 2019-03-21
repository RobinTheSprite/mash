//
// Created by Mark on 3/15/2019.
//

#include <error.h>
#include <fileapi.h>
#include <windows.h>
#include <iostream>

//Syntax for command is: rd <filename>
int main(int argc, char * argv[])
{
    if (argc > 1)
    {
        //Attempt to remove the directory, otherwise print an error message
        if (RemoveDirectory(argv[1]) == 0)
        {
            if (GetLastError() == ERROR_FILE_NOT_FOUND)
            {
                std::cout << "The directory \"" << argv[1] << "\" does not exist" << std::endl;
            } 
            else
            {
                std::cout << "The directory \"" << argv[1] << "\" could not be removed" << std::endl;
            }
        }
    }
}