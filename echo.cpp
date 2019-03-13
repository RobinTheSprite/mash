//
// Created by Mark on 3/12/2019.
//
#include <iostream>

int main(int argc, char * argv[])
{
    if (argc > 1)
    {
        for (auto i = 1; i < argc; ++i)
        {
            std::cout << argv[i] << " ";
        }
        std::cout << std::endl;
    }
}