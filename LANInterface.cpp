//#include <stdio.h>
//#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <Tchar.h>


#pragma comment(lib, "ws2_32.lib")
//using namespace std;

#include "LANInterface.h"



bool LANInterface::Init_LANInterface(int port)
{

	this->_port = port;

	WSADATA wsa;

	//Initialise winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//create socket
	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char*)& server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(this->_port);
	InetPton(AF_INET, _T(SERVER), &server_addr.sin_addr.s_addr);

	this->_isConnectionSuccess = true;
	printf("Connection success on port %d \n", this->_port);

	char buf[BUFSIZE];
	std::string userInput;

	return true;

}


int LANInterface::sendPacket(const char* buf, int bufsize)
{
	if (sendto(sock, buf, bufsize, 0, (struct sockaddr*) & server_addr, sizeof(server_addr)) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d \n", WSAGetLastError());

		printf("on port %d \n", this->_port);
		//exit(EXIT_FAILURE);
	}
	return 1;
}


LANInterface::LANInterface()
{
	std::cout << "do not try use this constructor" << std::endl;
}

bool LANInterface::isConnected()
{
	return this->_isConnectionSuccess;
}

LANInterface::LANInterface(int port)
{
	Init_LANInterface(port);
}


LANInterface::~LANInterface()
{
	std::cout << "destructor" << std::endl;
	closesocket(sock);
	WSACleanup();
}
