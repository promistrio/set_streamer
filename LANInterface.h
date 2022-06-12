#pragma once


#define BUFSIZE         1024    //buffer
#define SERVER "127.0.0.1"

class LANInterface
{
public:
	LANInterface();
	LANInterface(int port);
	~LANInterface();

	bool isConnected();
	bool Init_LANInterface(int port);
	int sendPacket(const char* buf, int bufsize);

private:
	int _port = 0;
	bool _isConnectionSuccess = false;
	SOCKET sock;
	sockaddr_in server_addr, client_addr;
	int server_len;

};

