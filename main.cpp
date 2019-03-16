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
    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInfo;

    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);

	char currentDirectory[MAX_PATH];
    while(true)
    {
		GetCurrentDirectory(MAX_PATH, currentDirectory);
		string dir(currentDirectory);
		cout << "MASH: " << dir << " >>=>";

        string inputLine;

        getline(cin, inputLine);
        if (!cin)
        {
            cout << "Error reading input" << endl;
        }

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