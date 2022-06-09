#include <stdio.h>
#include <iostream>
#include  "bulk.h"
#include "LANInterface.h"
#include <fstream>


#include <sys/types.h> 
using namespace std;

struct tEmuRSP
{
	unsigned cmd;
	unsigned arg[63];

	unsigned stream[16384 - 1024 - 1024 - 64];
	unsigned spec_A[1024];
	unsigned spec_B[1024];
};
/*
int sockfd;
struct sockaddr_in servaddr;*/

LANInterface link;


int main(int argc, char* argv[])
{
	if (!link.Init_LANInterface())
	{
		std::cout << "Can't init stream" << std::endl;
		while (true);
		return 1;
	}

	std::ofstream wf("videodata.bin", ios::out | ios::binary);
	if (!wf) {
		cout << "Cannot open file!" << endl;
		while (true);
		return 1;
	}

	bool res = Usb_Init(); // PID_RX = 0x8887;PID_TX=0x8888
	if (res)
	{
		std::cout << "CET here" << std::endl;
		struct tEmuRSP rsp;
		int i = 0; // dedelte

		while (true)
		{
			int transf = Usb_Rd((unsigned char*)&rsp, sizeof(rsp));
			if (transf != sizeof(rsp))
			{
				continue;
			}


			if (rsp.arg[0] == 0xA9ED4BE0 &&
				rsp.arg[1] == 0x16422815 &&
				rsp.arg[2] == 0x1A9B6276 &&
				rsp.arg[3] == 0xFEDE7E8B)
			{
				int stream_sz = 0xFFFFFF & rsp.arg[4];
				int stream_num = rsp.arg[4] >> 24;

				//printf("%d\n", stream_num);
				
				//std::cout << "stream_num " << stream_num << " " << stream_sz << std::endl;
				//if ((stream_num == 0 || stream_num == 1 || stream_num == 2 || stream_num == 3) && stream_sz)
				if ((stream_num == 2 ) && stream_sz)
				{
					uint32_t* ptr = rsp.stream;
					
						//std::cout << "readed " << stream_sz * 4 << std::endl; //4 = sizeof(int)
						link.SendPacket((const char*)&rsp.stream, stream_sz * 4);
						/*wf.write((const char*)&rsp.stream, stream_sz * 4);
						i++;
						std::cout << i << endl;
						if (i > 1000) {

							wf.close();
							return -1;
						}*/
						
						//for expample: we are going to send stream thru udp socket
						/*sendto(sockfd,
							(const char*)&rsp.stream,
							stream_sz * 4,
							MSG_DONTWAIT,
							(const struct sockaddr*)&servaddr,
							sizeof(servaddr));*/
					
				}
			}
			else
			{
				for (int i = 0; i < sizeof(rsp) / 4; i++)
				{
					if (((int*)&rsp.arg[0])[i] == 0xA9ED4BE0)
					{
						Usb_Rd((unsigned char*)&rsp, 4 * i);
						break;
					}
				}
			}
		}
	}
	else {
		std::cout << "CET not here" << std::endl;
	}

	return 0;
}

/*		/**/

		//UsbDeInit();*/