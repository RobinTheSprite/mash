//
// Created by Mark on 3/15/2019.
//
#include "windows.h"
#include "winsock.h"
#include "iphlpapi.h"
#include "icmpapi.h"
#include <iostream>

int main(int argc, char * argv[])
{
   auto icmpHandle = IcmpCreateFile();
   DWORD replySize = sizeof(ICMP_ECHO_REPLY);
   LPVOID reply[1024];
    if (argc > 1)
    {
        if (IcmpSendEcho(
                icmpHandle,
                inet_addr(argv[1]),
                nullptr,
                0,
                PIP_OPTION_INFORMATION(),
                reply,
                replySize,
                1000)
               == 0)
        {
            LPTSTR errorMessage;
            DWORD errorCode = GetLastError();
            FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |
                           FORMAT_MESSAGE_FROM_SYSTEM |
                           FORMAT_MESSAGE_IGNORE_INSERTS,
                           nullptr,
                           errorCode,
                           0,
                           (LPTSTR)&errorMessage,
                           0,
                           nullptr );
            std::cout << "Error: " << errorMessage << std::endl;
        }
    }
    IcmpCloseHandle(icmpHandle);
}