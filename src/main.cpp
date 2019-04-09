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
#include "ShlObj.h"

namespace mash
{
//setVarNameAndValue
//Handles when the user sets a variable
void setVarNameAndValue(stringstream &lineParser, string &singleWord, string &varName, string &varValue)
{
    size_t isAssignment = singleWord.find('=');
    if (singleWord.back() == '=') // var name= value
    {
        singleWord.pop_back();
        varName = singleWord;
        lineParser >> varValue;
    }
    else if (isAssignment != string::npos) //var name=value
    {
        varName = singleWord.substr(0, isAssignment);
        varValue = singleWord.substr(isAssignment + 1, string::npos);

    }
    else
    {
        varName = singleWord;
        lineParser >> singleWord;
        if (singleWord == "=") //var name = value
        {
            lineParser >> varValue;
        }
    }
}

//getPath
//Returns the PATH environment variable for the current process as a string
string getPath()
{
    size_t bufferSize = 2000;
    char buffer[2000];
    if (GetEnvironmentVariable("Path", buffer, bufferSize) == 0)
    {
        cout << "Error getting the path" << endl;
    }

    return buffer;
}

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
        if (singleWord == "$path")
        {
            varValue = getPath();
            size_t whereToInsert = inputLine.find(singleWord);
            inputLine.erase(whereToInsert, singleWord.size());
            inputLine.insert(whereToInsert, varValue);
        }
        else if (singleWord.front() == '$')
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
        mash::insertVariableValues(inputLine, userVariables);

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
            string varName;
            string varValue;

            if (singleWord.front() == '=')
            {
                cout << "Variables need to be named" << endl;
                continue;
            }

            mash::setVarNameAndValue(lineParser, singleWord, varName, varValue);

            if (!varName.empty() && !varValue.empty())
            {
                if (varName == "path")
                {
                    string path = mash::getPath();
                    path.append(varValue);
                    path.append(";");

                    SetEnvironmentVariable("Path", path.data());
                }
                else
                {
                    userVariables[varName] = varValue;
                }
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