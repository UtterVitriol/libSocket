#include "MyServer.h"

MyServer::MyServer(PCSTR port)
    :
    MySocket(port)
{
	int iResult = 0;
	DWORD dwError = 0;

    iResult = bind(m_socket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        freeaddrinfo(result);
        dwError = GetLastError();
        DERR(std::system_category().message(dwError).c_str(), dwError);
        throw MySocketException("Err");
        return;
    }

    DMSG("bind");

    freeaddrinfo(result);

    iResult = listen(m_socket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        dwError = GetLastError();
        DERR(std::system_category().message(dwError).c_str(), dwError);
        throw MySocketException("Err");
        return;
    }

    DMSG("listen");

    return;
}

SOCKET MyServer::GetClient()
{
    DWORD dwError = 0;

    DMSG("Waiting for client...");

    SOCKET socket = accept(m_socket, NULL, NULL);

    if (INVALID_SOCKET == socket)
    {
        dwError = GetLastError();
        DERR(std::system_category().message(dwError).c_str(), dwError);
        return socket;
    }

    DMSG("accept");

    return socket;
}

void MyServer::TestLoop(SOCKET sClient)
{
    char buff[4096] = { 0 };
    int iResult = 0;
    DWORD dwError = 0;

    for (;;)
    {
        ZeroMemory(buff, sizeof(buff));
        iResult = recv(sClient, buff, sizeof(buff), NULL);

        if (iResult <= 0)
        {
            dwError = GetLastError();
            DERR(std::system_category().message(dwError).c_str(), dwError);
            break;
        }

        printf("In: %s", buff);

        if (strncmp(buff, "q!", 2) == 0)
        {
            iResult = send(sClient, "Bye", 4, NULL);
            break;
        }

        iResult = send(sClient, buff, sizeof(buff), NULL);

        if (iResult <= 0)
        {
            dwError = GetLastError();
            DERR(std::system_category().message(dwError).c_str(), dwError);
            break;
        }
    }

}