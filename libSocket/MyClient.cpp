#include "MyClient.h"

MyClient::MyClient(PCSTR ip, PCSTR port)
	:MySocket(ip, port)
{
	int iResult = 0;
	DWORD dwError = 0;

    DMSG("Connecting....");

	iResult = connect(m_socket, result->ai_addr, result->ai_addrlen);
	if (SOCKET_ERROR == iResult)
	{
		dwError = GetLastError();
		DERR(std::system_category().message(dwError).c_str(), dwError);
		throw MySocketException("Err");
	}

    DMSG("connect");
}

void MyClient::TestLoop()
{
    char buff[4096] = { 0 };
    int iResult = 0;
    DWORD dwError = 0;

    for (;;)
    {
        ZeroMemory(buff, sizeof(buff));

        fgets(buff, sizeof(buff), stdin);

        iResult = send(m_socket, buff, sizeof(buff), NULL);

        if (iResult <= 0)
        {
            dwError = GetLastError();
            DERR(std::system_category().message(dwError).c_str(), dwError);
            break;
        }

        printf("In: %s", buff);

        iResult = recv(m_socket, buff, sizeof(buff), NULL);

        if (iResult <= 0)
        {
            dwError = GetLastError();
            DERR(std::system_category().message(dwError).c_str(), dwError);
            break;
        }
    }

}