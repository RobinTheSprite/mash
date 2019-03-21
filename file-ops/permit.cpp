//
// Created by Mark on 3/7/2019.
//
#include "aclapi.h"
#include "lmcons.h"
#include "sddl.h"
#include <iostream>

void printError()
{
    LPTSTR errorMessage;
    DWORD errorCode = GetLastError();
    FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM,
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
    if (argc > 1)
    {
        PACL dacl, newDacl = nullptr;
        PSECURITY_DESCRIPTOR security;
        GetNamedSecurityInfo(
                argv[1],
                SE_FILE_OBJECT,
                DACL_SECURITY_INFORMATION,
                nullptr,
                nullptr,
                &dacl,
                nullptr,
                &security
                );

        PSID sid;
        DWORD lenSid = SECURITY_MAX_SID_SIZE;
        sid = LocalAlloc(LMEM_FIXED, lenSid);
        if (CreateWellKnownSid(WinWorldSid, nullptr, sid, &lenSid) == 0)
        {
            printError();
        }

        EXPLICIT_ACCESS rule;
        ZeroMemory(&rule, sizeof(EXPLICIT_ACCESS));
        rule.grfInheritance = SUB_CONTAINERS_AND_OBJECTS_INHERIT;
        BuildTrusteeWithSid(&rule.Trustee, sid);

        if (strcmp(argv[2], "read") == 0)
        {
            rule.grfAccessPermissions = GENERIC_READ;
            rule.grfAccessMode = GRANT_ACCESS;
        }
        else if (strcmp(argv[2], "write") == 0)
        {
            rule.grfAccessPermissions = GENERIC_WRITE;
            rule.grfAccessMode = GRANT_ACCESS;
        }
        else if (strcmp(argv[2], "execute") == 0)
        {
            rule.grfAccessPermissions = GENERIC_EXECUTE;
            rule.grfAccessMode = GRANT_ACCESS;
        }

        if (SetEntriesInAcl(1, &rule, dacl, &newDacl) != ERROR_SUCCESS)
        {
            printError();
        }

        for (unsigned int i = 0; i < newDacl->AclSize; ++i)
        {
            LPVOID * ace;
            GetAce(newDacl, i, ace);
            if (Header.AceType == ACCESS_DENIED_ACE_TYPE)
            {

            }
        }

        if(SetNamedSecurityInfo(argv[1],
                                SE_FILE_OBJECT,
                                DACL_SECURITY_INFORMATION,
                                nullptr,
                                nullptr,
                                newDacl,
                                nullptr)
           != ERROR_SUCCESS)
        {
            printError();
        }

        LocalFree(sid);
        LocalFree(security);
        LocalFree(newDacl);
    }
    return 0;
}