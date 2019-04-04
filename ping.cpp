//
// Created by Mark on 3/15/2019.
//
#include <Windows.h>
#include <winsock.h>
#include <iostream>
#include <iphlpapi.h>
#include <IcmpAPI.h>
#include <inaddr.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

//printError
//Tell me what the last error in this thread was
void printError()
{
    LPTSTR errorMessage = nullptr;
    DWORD errorCode = GetLastError();
    FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                   nullptr,
                   errorCode,
                   0,
                   (LPTSTR)&errorMessage,
                   0,
                   nullptr );
    std::cout << "Error Setting Permissions: " << errorMessage << std::endl;
}

int main(int argc, char * argv[])
{
   HANDLE icmpHandle = IcmpCreateFile();
   DWORD replySize = sizeof(ICMP_ECHO_REPLY);
   LPVOID reply[1024];
    if (argc > 1)
    {
        unsigned long ipAddress = 0;

        ipAddress = inet_addr(argv[1]);
        if(ipAddress == 0)
        {
            std::cout << "That was not an IP address" << std::endl;
        }

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
                auto theReply = (PICMP_ECHO_REPLY)reply;
                in_addr replyAddress{};
                replyAddress.S_un.S_addr = theReply->Address;

                std::cout << "Ping Received from " << inet_ntoa(replyAddress)
                          << " in " << theReply->RoundTripTime << " milliseconds" << std::endl;
            }
        }
    }
    IcmpCloseHandle(icmpHandle);
}