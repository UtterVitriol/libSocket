#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <cstdio>
#include <string>
#include <system_error>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "AdvApi32.lib")

#ifndef NDEBUG
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define DERR(s, d) fprintf(stderr, "[-]: %s:%d:%s(): %s - %d\n", __FILENAME__, __LINE__, __func__, s, d)
#define DMSG(s) printf("[+]: %s:%d:%s(): %s\n", __FILENAME__, __LINE__, __func__, s)
#else
#define DERR(s,d)
#define DMSG(s)
#endif

class MySocketException : public std::exception
{
public:
	MySocketException(PCSTR message0) : message(message){}

	PCSTR what()
	{
		return message;
	}

private:
	PCSTR message;
};

class MySocket
{
public:
	MySocket(PCSTR port);
	MySocket(PCSTR ip, PCSTR port);
	~MySocket() { WSACleanup(); closesocket(m_socket); }

	WSADATA m_wsaData;
	SOCKET m_socket = INVALID_SOCKET;
	struct addrinfo *result = NULL;
	struct addrinfo hints;

private:
	void Init(PCSTR ip, PCSTR port);
};

