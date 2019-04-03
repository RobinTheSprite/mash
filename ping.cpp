//
// Created by Mark on 3/15/2019.
//
#include <windows.h>
#include <iostream>
#include <iphlpapi.h>
#include <icmpapi.h>

#pragma comment(lib, "IPHLPAPI.lib")

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
//   DWORD replySize = sizeof(ICMP_ECHO_REPLY);
//   LPVOID reply[1024];
//    if (argc > 1)
//    {
//        if (IcmpSendEcho(
//                icmpHandle,
//                inet_addr(argv[1]),
//                nullptr,
//                0,
//                PIP_OPTION_INFORMATION(),
//                reply,
//                replySize,
//                1000)
//               == 0)
//        {
//            printError();
//        }
//    }
    IcmpCloseHandle(icmpHandle);
}