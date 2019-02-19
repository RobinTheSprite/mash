#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>
using std::string;
#include <sstream>
using std::stringstream;

int main()
{
    while(true)
    {
        string inputLine;
        getline(cin, inputLine);
        stringstream inputStream(inputLine);

        string partOfCommand;
        while(inputStream >> partOfCommand)
        {
            cout << partOfCommand << endl;
        }

        break;
    }
    return 0;
}