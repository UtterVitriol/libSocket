#pragma once

#include "MySocket.h"

class MyClient : MySocket
{
public:
	MyClient(PCSTR ip, PCSTR port);
	void TestLoop();

private:
};

