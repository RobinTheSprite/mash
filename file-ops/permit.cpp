//
// Created by Mark on 3/7/2019.
//
#include "aclapi.h"
#include "lmcons.h"
#include "sddl.h"
#include <iostream>
#include <vector>
#include "../mash-error.h"

//resetDenyAccess
//Deletes ACEs that deny access
//Does seem to do this, but access is still denied after deletion
void resetDenyAccess(PACL &dacl)
{
    for (DWORD i = 0; i < dacl->AceCount; ++i)
    {
        ACCESS_DENIED_ACE * ace = nullptr;
        if (!GetAce(dacl, i, (LPVOID*)&ace))
        {
            printError();
            break;
        }

        if (ace->Header.AceType == ACCESS_DENIED_ACE_TYPE)
        {
            DeleteAce(dacl, i);
        }
    }
}

//Syntax for command is:
//permit <filename> [reset] [read | !read] [write | !write] [execute | !execute]
int main(int argc, char * argv[])
{
    if (argc > 1)
    {
        PACL dacl, newDacl = nullptr;
        PSECURITY_DESCRIPTOR security;

        //Get the existing DACL for the file
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

        //Get the SID for "Everyone"
        PSID sid;
        DWORD lenSid = SECURITY_MAX_SID_SIZE;
        sid = LocalAlloc(LMEM_FIXED, lenSid);
        if (CreateWellKnownSid(WinWorldSid, nullptr, sid, &lenSid) == 0)
        {
            printError();
        }

        //Set every permission specified on the command line
        std::vector<EXPLICIT_ACCESS> rules;
        if (argc > 2)
        {
            for (auto i = 2; i < argc; ++i)
            {
                //Set up the new ACE
                EXPLICIT_ACCESS rule;
                ZeroMemory(&rule, sizeof(EXPLICIT_ACCESS));
                rule.grfInheritance = SUB_CONTAINERS_AND_OBJECTS_INHERIT;
                BuildTrusteeWithSid(&rule.Trustee, sid);

                //Decide what permissions the ACE will set
                if (argv[i][0] == '!')
                {
                    if (strcmp(argv[i], "!read") == 0)
                    {
                        rule.grfAccessPermissions = GENERIC_READ;
                        rule.grfAccessMode = DENY_ACCESS;
                        rules.emplace_back(rule);
                    }

                    if (strcmp(argv[i], "!write") == 0)
                    {
                        rule.grfAccessPermissions = GENERIC_WRITE;
                        rule.grfAccessMode = DENY_ACCESS;
                        rules.emplace_back(rule);
                    }

                    if (strcmp(argv[i], "!execute") == 0)
                    {
                        rule.grfAccessPermissions = GENERIC_EXECUTE;
                        rule.grfAccessMode = DENY_ACCESS;
                        rules.emplace_back(rule);
                    }
                }
                else
                {
                    if (strcmp(argv[i], "read") == 0)
                    {
                        rule.grfAccessPermissions = GENERIC_READ;
                        rule.grfAccessMode = GRANT_ACCESS;
                        rules.emplace_back(rule);
                    }

                    if (strcmp(argv[i], "write") == 0)
                    {
                        rule.grfAccessPermissions = GENERIC_WRITE;
                        rule.grfAccessMode = GRANT_ACCESS;
                        rules.emplace_back(rule);
                    }

                    if (strcmp(argv[i], "execute") == 0)
                    {
                        rule.grfAccessPermissions = GENERIC_EXECUTE;
                        rule.grfAccessMode = GRANT_ACCESS;
                        rules.emplace_back(rule);
                    }

                    if(strcmp(argv[i], "reset") == 0)
                    {
                        resetDenyAccess(dacl);
                    }
                }
            }
        }

        //Stick the new ACE into the DACL
        if (SetEntriesInAcl((ULONG)rules.size(), rules.data(), dacl, &newDacl) != ERROR_SUCCESS)
        {
            printError();
        }

        //Stick the DACL back into the file
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