#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>
using std::string;
#include <sstream>
using std::stringstream;
#include <map>
#include "ShlObj.h"
#include "commands.h"

int main()
{
    //Set up the processes that will be fired off later
    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInfo;

    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);
    ZeroMemory(&processInfo, sizeof(processInfo));

    std::map<string, string> userVariables;

	char currentDirectory[MAX_PATH];
    while(true)
    {
        //Print the current directory
		GetCurrentDirectory(MAX_PATH, currentDirectory);
		string dir(currentDirectory);
		cout << "MASH: " << dir << " >>=>";

		//Grab the user's input
        string inputLine;
        getline(cin, inputLine);
        if (!cin)
        {
            cout << "Error reading input" << endl;
        }

        //Check for built-in commands
        stringstream lineParser(inputLine);
        string singleWord;
        lineParser >> singleWord;
        if (inputLine == "exit")
        {
            break;
        }
        else if (singleWord == "cd")
        {
            lineParser >> singleWord;
            if (!singleWord.empty())
            {
                SetCurrentDirectory(singleWord.c_str());
                continue;
            }

        }
        else if (singleWord == "var")
        {
            lineParser >> singleWord;
            size_t isAssignment = singleWord.find('=');
            string varName;
            string varValue;
            if(singleWord.back() == '=')
            {
                singleWord.pop_back();
                varName = singleWord;
                lineParser >> singleWord;
                varValue = singleWord;
                userVariables[varName] = varValue;
            }
            else if (isAssignment != string::npos)
            {
                varName = singleWord.substr(0, isAssignment);
                varValue = singleWord.substr(isAssignment + 1, string::npos);
                userVariables[varName] = varValue;
            }
            continue;
        }

        //Spawn the process with the first word of the input
        auto prt = const_cast<char *>(inputLine.c_str());
        if (!CreateProcess(nullptr, prt, nullptr, nullptr, true, NORMAL_PRIORITY_CLASS, nullptr, nullptr, &startupInfo, &processInfo))
        {
            cout << "No command called \"" << prt << "\""<< endl;
        }
        WaitForSingleObject(processInfo.hProcess, INFINITE);
    }

    CloseHandle( processInfo.hProcess );
    CloseHandle( processInfo.hThread );

    return 0;
}