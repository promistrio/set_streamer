#pragma once


#define BUFSIZE         1024    //buffer
#define SERVER_PORT     54000   //server port #
#define SERVER "127.0.0.1"

class LANInterface
{
public:
	LANInterface();
	~LANInterface();

	bool Init_LANInterface();
	int SendPacket(const char* buf, int bufsize);

private:
	SOCKET sock;
	sockaddr_in server_addr, client_addr;
	int server_len;

};

