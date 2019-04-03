#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>
using std::string;
#include <sstream>
using std::stringstream;
#include <algorithm>
#include <map>
#include "shlobj.h"

//insertVariableValues
//Strips out any variable names and replaces them with the correct values
void insertVariableValues(string & inputLine, const std::map<string, string> & userVariables)
{
    string singleWord;
    stringstream insertVarValues(inputLine);
    while (insertVarValues >> singleWord)
    {
        string varName;
        string varValue;
        if (singleWord.front() == '$')
        {
            varName = singleWord.substr(1, string::npos);
            if (userVariables.count(varName) != 0)
            {
                varValue = userVariables.at(varName);
                size_t whereToInsert = inputLine.find(singleWord);
                inputLine.erase(whereToInsert, singleWord.size());
                inputLine.insert(whereToInsert, varValue);
            }
        }
    }
}

int main()
{
    //Set up the processes that will be fired off later
    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInfo;

    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);
    ZeroMemory(&processInfo, sizeof(processInfo));

    std::map<string, string> userVariables;
    bool runInBackground{false};

    char currentDirectory[MAX_PATH];
    while (true)
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

        //Insert the values of any listed variables
        insertVariableValues(inputLine, userVariables);

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

            if (singleWord.front() == '=')
            {
                std::cout << "Variables need to be named" << std::endl;
                continue;
            }

            if (singleWord.back() == '=') // var name= value
            {
                singleWord.pop_back();
                varName = singleWord;
                lineParser >> varValue;
                userVariables[varName] = varValue;
            }
            else if (isAssignment != string::npos) //var name=value
            {
                varName = singleWord.substr(0, isAssignment);
                varValue = singleWord.substr(isAssignment + 1, string::npos);
                userVariables[varName] = varValue;
            }

            varName = singleWord;
            lineParser >> singleWord;
            if (singleWord == "=") //var name = value
            {
                lineParser >> userVariables[varName];
            }

            continue;
        }
        else if (singleWord == "bg")
        {
            runInBackground = true;
            inputLine = inputLine.substr(3, string::npos);
        }

        //Spawn the process with the first word of the input
        auto prt = const_cast<char *>(inputLine.c_str());
        if (!CreateProcess(nullptr, prt, nullptr, nullptr, true, NORMAL_PRIORITY_CLASS, nullptr, nullptr, &startupInfo,
                           &processInfo))
        {
            cout << "No command called \"" << prt << "\"" << endl;
        }

        if(!runInBackground)
        {
            WaitForSingleObject(processInfo.hProcess, INFINITE);
        }
        runInBackground = false;
    }

    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);

    return 0;
}