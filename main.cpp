#pragma comment(lib, "ws2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>



int main()
{
	// Load Winsock
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		std::cout << "Winsock Error : " << GetLastError() << std::endl;
		exit(-1);
	}

	// Create socket
	SOCKET ClientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (ClientSocket == INVALID_SOCKET)
	{
		std::cout << "fail create Socket : " << GetLastError() << std::endl;
		exit(-1);
	}

	// Server element to connect to
	SOCKADDR_IN ServerSOCKADDR;
	memset(&ServerSOCKADDR, 0, sizeof(SOCKADDR_IN));
	ServerSOCKADDR.sin_family = PF_INET;
	ServerSOCKADDR.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerSOCKADDR.sin_port = htons(3307);

	// Connect Socket
	int Result = connect(ClientSocket, (SOCKADDR*)&ServerSOCKADDR, sizeof(SOCKADDR_IN));
	if (Result == SOCKET_ERROR)
	{
		std::cout << "fail connect : " << GetLastError() << std::endl;
		exit(-1);
	}

	// recive
	char Buffer[1024];
	while (true)
	{
		int RecvBuffer = recv(ClientSocket, Buffer, 1024, 0);

		std::cout << RecvBuffer << std::endl;

		if (RecvBuffer == 0)
		{
			break;
		}
	}

	// Close sockets
	closesocket(ClientSocket);
	WSACleanup();

	return 0;
}