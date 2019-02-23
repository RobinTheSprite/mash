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
            char * prt = const_cast<char *>("notepad");
            CreateProcess(nullptr, prt, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo);
			//ShellExecute(NULL, NULL, partOfCommand.c_str(), "", NULL, SW_NORMAL);
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