//
// Created by Mark on 3/12/2019.
//
#include <iostream>

//Syntax for command is: echo <string>
int main(int argc, char * argv[])
{
    if (argc > 1)
    {
        //Simply print out everything after "echo," space delineated
        for (auto i = 1; i < argc; ++i)
        {
            std::cout << argv[i] << " ";
        }
        std::cout << std::endl;
    }
}