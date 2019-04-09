//
// Created by Mark on 3/15/2019.
//
#include <Windows.h>
#include <winsock.h>
#include <iostream>
#include <iphlpapi.h>
#include <IcmpAPI.h>
#include <inaddr.h>
#include <vector>
#include <numeric>
#include "../mash-error.h"
using mash::printError;

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char * argv[])
{
   HANDLE icmpHandle = IcmpCreateFile();
   DWORD replySize = sizeof(ICMP_ECHO_REPLY);
   LPVOID reply[1024];
    if (argc > 1)
    {
        //Get the IP address from the command line
        unsigned long ipAddress = 0;
        ipAddress = inet_addr(argv[1]);
        if(ipAddress == 0)
        {
            std::cout << "That was not an IP address" << std::endl;
        }

        std::vector<size_t> responseTimes;
        //Send out five ICMP echoes
        for (auto i = 0; i < 5; ++i)
        {
            int retVal = IcmpSendEcho(
                    icmpHandle,
                    ipAddress,
                    nullptr,
                    0,
                    nullptr,
                    reply,
                    replySize,
                    1000);
            if (retVal == 0)
            {
                printError();
            }
            else
            {
                //Put the results on the screen
                auto theReply = (PICMP_ECHO_REPLY)reply;
                in_addr replyAddress{};
                replyAddress.S_un.S_addr = theReply->Address;
                responseTimes.push_back(theReply->RoundTripTime);
                std::cout << "Ping Received from " << inet_ntoa(replyAddress)
                          << " in " << theReply->RoundTripTime << " milliseconds" << std::endl;
            }
        }
        std::cout << std::endl;
        std::cout << responseTimes.size() << " of 5 replies recieved" << std::endl;
        std::cout << "Average Respsonse Time: "
                  << std::accumulate(responseTimes.begin(), responseTimes.end(), 0) / responseTimes.size()
                  << " milliseconds" << std::endl;
    }
    IcmpCloseHandle(icmpHandle);
}