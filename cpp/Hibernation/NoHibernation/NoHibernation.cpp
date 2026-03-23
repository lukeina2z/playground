// NoHibernation.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "NoHibernation.h"
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <cstdio>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")


// This is an example of an exported variable
NOHIBERNATION_API int nNoHibernation=0;

// This is an example of an exported function.
NOHIBERNATION_API int fnNoHibernation(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CNoHibernation::CNoHibernation()
{
    return;
}

void CNoHibernation::Run()
{
    while (true)
    {
        // Resolve www.bing.com
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);

        struct addrinfo hints = {};
        hints.ai_family = AF_INET;
        struct addrinfo* result = nullptr;
        int res = getaddrinfo("www.bing.com", nullptr, &hints, &result);

        if (res != 0 || result == nullptr)
        {
            printf("Ping www.bing.com: FAIL (DNS resolution failed)\n");
            if (result) freeaddrinfo(result);
            WSACleanup();
            Sleep(30000);
            continue;
        }

        IN_ADDR addr = reinterpret_cast<sockaddr_in*>(result->ai_addr)->sin_addr;
        freeaddrinfo(result);
        WSACleanup();

        // Send ICMP ping
        HANDLE hIcmp = IcmpCreateFile();
        if (hIcmp == INVALID_HANDLE_VALUE)
        {
            printf("Ping www.bing.com: FAIL (IcmpCreateFile failed)\n");
            Sleep(30000);
            continue;
        }

        char replyBuffer[sizeof(ICMP_ECHO_REPLY) + 8];
        DWORD ret = IcmpSendEcho(hIcmp, addr.S_un.S_addr, nullptr, 0,
                                  nullptr, replyBuffer, sizeof(replyBuffer), 4000);
        if (ret > 0)
        {
            printf("Ping www.bing.com: SUCCESS\n");
        }
        else
        {
            printf("Ping www.bing.com: FAIL (error %lu)\n", GetLastError());
        }

        IcmpCloseHandle(hIcmp);
        Sleep(30000);
    }
}
