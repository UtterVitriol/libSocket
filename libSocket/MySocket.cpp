#include "MySocket.h"

MySocket::MySocket(PCSTR port)
{
	Init(NULL, port);
}

MySocket::MySocket(PCSTR ip, PCSTR port)
{
	Init(ip, port);
}

void MySocket::Init(PCSTR ip, PCSTR port)
{
	int iResult = 0;
	DWORD dwError = 0;
	
	iResult = WSAStartup(MAKEWORD(2, 2), &m_wsaData);
	DMSG("WSAStartup");

	if (iResult != 0)
	{
		dwError = GetLastError();
		DERR(std::system_category().message(dwError).c_str(), dwError);
		throw MySocketException("Err");
		return;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (!ip)
	{
		hints.ai_flags = AI_PASSIVE;
	}


	iResult = getaddrinfo(ip, port, &hints, &result);
	if (iResult != 0) {
		dwError = GetLastError();
		DERR(std::system_category().message(dwError).c_str(), dwError);
		throw MySocketException("Err");
		return ;
	}

	DMSG("getaddrinfo");

	m_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (m_socket == INVALID_SOCKET) {
		
		dwError = GetLastError();
		DERR(std::system_category().message(dwError).c_str(), dwError);
		freeaddrinfo(result);
		throw MySocketException("Err");
		return;
	}

	DMSG("socket");

	return;
}
