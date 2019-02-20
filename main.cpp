#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>
using std::string;
#include <sstream>
using std::stringstream;
#include "shlobj.h"
#include "commands.h"


int main()
{
	char directory[MAX_PATH];
	
    while(true)
    {
		size_t bufferLength = GetCurrentDirectory(MAX_PATH, directory);
		string dir(directory);
		cout << dir << "=>";

        string inputLine;
        getline(cin, inputLine);
        stringstream inputStream(inputLine);

        string partOfCommand;
        while(inputStream >> partOfCommand)
        {
			ShellExecute(NULL, NULL, partOfCommand.c_str(), "", NULL, SW_NORMAL);
        }

		if (partOfCommand == "exit")
		{
			break;
		}
    }

    return 0;
}