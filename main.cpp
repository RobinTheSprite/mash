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


int main(int argc, TCHAR *argv[])
{
    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInfo;

    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);

	char directory[MAX_PATH];
    while(true)
    {
		GetCurrentDirectory(MAX_PATH, directory);
		string dir(directory);
		cout << dir << " >>=>";

        string inputLine;
        getline(cin, inputLine);
        stringstream inputStream(inputLine);

        string partOfCommand;
        while(inputStream >> partOfCommand)
        {
            if (partOfCommand == "exit")
            {
                break;
            }
            char * prt = const_cast<char *>(partOfCommand.c_str());
            if (!CreateProcess(nullptr, prt, nullptr, nullptr, false, NORMAL_PRIORITY_CLASS, nullptr, nullptr, &startupInfo, &processInfo))
            {
                cout << "No command called " << prt << endl;
            }
        }
        if (partOfCommand == "exit")
        {
            break;
        }
    }

    WaitForSingleObject(processInfo.hProcess, INFINITE);
    CloseHandle( processInfo.hProcess );
    CloseHandle( processInfo.hThread );

    return 0;
}