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
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	//printf("Initialised.\n");

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

	//start communication
	/*while (1)
	{
		//send the message
		if (sendto(s, message, strlen(message), 0, (struct sockaddr*) & si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);
		//try to receive some data, this is a blocking call
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr*) & si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		puts(buf);
	}*/

	//Do-While Loop to send and recieve data
	char buf[BUFSIZE];
	std::string userInput;

	return true;

}


int LANInterface::sendPacket(const char* buf, int bufsize)
{
	if (sendto(sock, buf, bufsize, 0, (struct sockaddr*) & server_addr, sizeof(server_addr)) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	/*int sendResult = sendto(sock, buf, bufsize, 0x40, (sockaddr*)&server_addr, server_len);
	if (sendResult == SOCKET_ERROR)
	{
		std::cerr << "Can't send msg, Err #" << WSAGetLastError() << std::endl;
		//cin.get();
		return 0;
	}*/
	return 1;
}


LANInterface::LANInterface()
{
	Init_LANInterface(SERVER_PORT);
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
	closesocket(sock);
	WSACleanup();
}
