#pragma once

#include "MySocket.h"

class MyServer : MySocket
{
public:
	MyServer(PCSTR port);
	SOCKET GetClient();
	void TestLoop(SOCKET sClient);

private:

};

